/*************************************************************************
*                                                                        *
*   Module: computemaxsignal                                             *
*                                                                        *
*   ComputeMaxSignal main program                                        *
*                                                                        *
*   This file is part of the SeqCode 1.0 distribution                    *
*                                                                        *
*     Copyright (C) 2020 - Enrique BLANCO GARCIA                         *
*                                                                        *
*  This program is free software; you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation; either version 2 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
*  This program is distributed in the hope that it will be useful,       *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*  GNU General Public License for more details.                          *
*                                                                        *
*  You should have received a copy of the GNU General Public License     *
*  along with this program; if not, write to the Free Software           * 
*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             *
*************************************************************************/

#include "seqcode/seqcode.h"

/************************************************************************
                            ENVIRONMENTAL variables
************************************************************************/

/* Verbose flag (memory/processing information) */
int VRB=0;

/* Bin resolution */
int WINDOWRES = WINDOWRES_COMPUTEMAX;

/* Spike-in normalization */
int SPIKEIN = 0;

/* Analyze upstream sequence of the TSS */
int UPS=0;

/* Input profile requires unzip before processing */
int ZIP=0;

/* Accounting time and results */
account *m;

/************************************************************************
                             MAIN program
************************************************************************/

int main (int argc, char *argv[])
{
  char ChromInfoFile[FILENAMELENGTH],
    RefgeneFile[FILENAMELENGTH],
    ProfileFile[FILENAMELENGTH];
  int Upstream;
  
  long* ChrSizes;
  dict* ChrNames;

  dict* GeneNames;
  int* GeneChrs;

  transcript** Transcripts;

  unsigned int** READS;

  long FileSize;

  char tmpFileName[TMPFILENAMELENGTH];
  pid_t pid;

  int tmpSystem;
  
  char mess[MAXSTRING];

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account *) InitAcc();  
  
  /* 0.b. Read setup options */
  readargv_computemaxsignal(argc,argv,ChromInfoFile,RefgeneFile,ProfileFile,&Upstream);

  printSeqCodeHeader(COMPUTEMAXSIGNAL);
  StartingTime(mess,m);
  printMess(mess);
  
  /* 1. Allocating data structures */
  printMess("Request Memory to Operating System");
  ChrNames = (dict *) RequestMemoryDictionary();
  ChrSizes = (long *) RequestMemoryChrSizes();
  GeneNames = (dict *) RequestMemoryDictionary();
  GeneChrs = (int *) RequestMemoryGeneChrs();
  Transcripts = (transcript**) RequestMemoryTranscripts();
   
  /* 2. Read the ChrSize file */
  printMess("Reading Chromosome Sizes");
  m->nChrs = ReadChrFile (ChromInfoFile,ChrSizes,ChrNames);
  sprintf(mess,"Size was successfully acquired for %d chromosomes",m->nChrs);
  printRes(mess);

  /*  Additional allocating data structures */
  READS = (unsigned int**) RequestMemoryREADS(ChrSizes,ChrNames);

  /* 3. Read the Refgene file */
  printMess("Reading Refgene file");
  FileSize = GetFileSize(RefgeneFile);
  sprintf(mess,"%s: %.2lf Mb",RefgeneFile,(float)FileSize/MEGABYTE);
  printRes(mess);
  
  m->nTotalTranscripts = ReadRefgeneFile2(RefgeneFile,Transcripts,ChrNames,GeneNames,GeneChrs);
  sprintf(mess,"%ld transcripts of RefSeq were successfully acquired",m->nTotalTranscripts);
  printRes(mess);

  /* 4. Check: the profile file requires unzip? */
  printMess("Processing the ChIP profile");
  FileSize = GetFileSize(ProfileFile);
  sprintf(mess,"%s: %.2lf Mb",ProfileFile,(float)FileSize/MEGABYTE);
  printRes(mess);
  
  if (ZIP)
    {
      /* Unique temporary file */
      pid = getpid();
      sprintf(tmpFileName,"%s_%d",TMPFILE,pid);
      sprintf(mess,"Uncompressing the profile into the tmp file: %s",tmpFileName);
      printMess(mess);
      sprintf(mess,"gzip -d -c %s > %s",ProfileFile,tmpFileName);
      printRes(mess);
      tmpSystem = system(mess);
      
      FileSize = GetFileSize(tmpFileName);
      sprintf(mess,"%s: %.2lf Mb",tmpFileName,(float)FileSize/MEGABYTE);
      printRes(mess);

      printMess("Working with the uncompressed BedGraph file");
      m->nLines = ReadBGFile(tmpFileName,ChrSizes,ChrNames,READS);
      sprintf(mess,"%ld lines of the profile were successfully processed",m->nLines);
      printRes(mess);

      printMess("Removing the uncompressed profile tmp file");
      sprintf(mess,"rm -f %s",tmpFileName);
      printRes(mess);
      tmpSystem = system(mess);
    }
  else
    {
      printMess("Working with the uncompressed BedGraph file");
      m->nLines = ReadBGFile(ProfileFile,ChrSizes,ChrNames,READS);
      sprintf(mess,"%ld lines of the profile were successfully processed",m->nLines);
      printRes(mess);
    }
  
  /* 5. Process the file of RefSeq genes */
  printMess("Processing the List of RefSeq genes");
  m->nGenes = ProcessGenesMax(RefgeneFile,
			      Transcripts,
			      ChrNames,ChrSizes,
			      GeneNames,GeneChrs,
			      Upstream,READS);
  sprintf(mess,"%d genes were successfully processed",m->nGenes);
  printRes(mess); 
  

  /* 6. The End */
  OutputTime(m);  
  
  exit(0);
  return(0);
}
