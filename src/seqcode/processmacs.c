/*************************************************************************
*                                                                        *
*   Module: processmacs                                                  *
*                                                                        *
*   processMACS main program                                             *
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

/* Compact averaged BedGraph profiles */
int COMPACT = FALSE;

/* Spike-in normalization */
int SPIKEIN = 0;

/* Accounting time and results */
account *m;

/************************************************************************
                            MAIN program
************************************************************************/

int main (int argc, char *argv[])
{
  char   ChromInfoFile[FILENAMELENGTH],
    MACSFile[FILENAMELENGTH],
    OutputFile[FILENAMELENGTH],
    OutputZip[TMPFILENAMELENGTH],
    TrackName[USERNAMELENGTH];
  
  long* ChrSizes;
  dict* ChrNames;

  long FileSize;

  char tmpFileName[TMPFILENAMELENGTH];

  pid_t pid;

  int tmpSystem;
  
  char mess[MAXSTRING];

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account*) InitAcc();  
  
  /* 0.b. Read setup options */
  readargv_processmacs(argc,argv,ChromInfoFile,MACSFile,OutputFile,TrackName);

  printSeqCodeHeader(PROCESSMACS);
  StartingTime(mess,m);
  printMess(mess);
  
  /* 1. Allocating ProcessMACS data structures */
  printMess("1. Request Memory to Operating System");
  ChrSizes = (long *) RequestMemoryChrSizes();
  ChrNames = (dict *) RequestMemoryDictionary();

  /*2. Read the ChrSize file */
  printMess("2. Reading Chromosome Sizes");
  m->nChrs = ReadChrFile (ChromInfoFile,ChrSizes,ChrNames);
  sprintf(mess,"Size was successfully acquired for %d chromosomes",m->nChrs);
  printRes(mess);

  /*3. Process the BG zip file */
  printMess("3. Processing the BedGraph file");

  FileSize = GetFileSize(MACSFile);
  sprintf(mess,"Size of %s: %.2lf Mb\n",
	  MACSFile,(float)FileSize/MEGABYTE);
  printRes(mess);

  /* Unique temporary file */
  pid = getpid();
  sprintf(tmpFileName,"%s_%d",TMPFILE,pid);

  sprintf(mess,"Uncompressing the profile into the tmp file: %s",tmpFileName);
  printRes(mess);
  sprintf(mess,"gzip -d -c %s > %s",MACSFile,tmpFileName);
  printRes(mess);
  tmpSystem = system(mess);

  FileSize = GetFileSize(tmpFileName);
  sprintf(mess,"Size of %s: %.2lf Mb\n",
	  tmpFileName,(float)FileSize/MEGABYTE);
  printRes(mess);

  printRes("Generating the output BedGraph file");
  m->nLines = ProcessBGFile (tmpFileName, ChrSizes, ChrNames,OutputFile,TrackName);
  sprintf(mess,"%ld lines were successfully processed",m->nLines);
  printRes(mess);

  /* Inform about the final output file size (no zip) */
  FileSize = GetFileSize(OutputFile);
  sprintf(mess,"Size of %s: %.2lf Mb\n",
	  OutputFile,(float)FileSize/MEGABYTE);
  printRes(mess);

  /* Remove older compressed file and compress the current one */
  sprintf(OutputZip,"%s.gz",OutputFile);
  printRes("Removing older compressed output file (if any)");
  sprintf(mess,"rm -f %s",OutputZip);
  tmpSystem = system(mess);

  printRes("Compressing the output BedGraph file");
  sprintf(mess,"gzip %s",OutputFile);
  tmpSystem = system(mess);

  /* Inform about the final output file size (after zip) */
  FileSize = GetFileSize(OutputZip);
  sprintf(mess,"Final size of %s: %.2lf Mb\n",
	  OutputZip,(float)FileSize/MEGABYTE);
  printRes(mess);

  printRes("Removing the uncompressed profiletmp file");
  sprintf(mess,"rm -f %s",tmpFileName);
  printRes(mess);
  tmpSystem = system(mess);

  /* 4. The End */
  OutputTime(m);  
  
  exit(0);
  return(0);
}
