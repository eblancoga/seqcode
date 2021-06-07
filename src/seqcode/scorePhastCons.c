/*************************************************************************
*                                                                        *
*   Module: scorePhastCons                                               *
*                                                                        *
*   scorePhastCons main program                                          *
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
int WINDOWRES = WINDOWRES_PHASTCONS;

/* Spike-in normalization */
int SPIKEIN = 0;

/* Conservation threshold filter */
float THRESHOLD=0;

/* Accounting time and results */
account *m;

/************************************************************************
                            MAIN program
************************************************************************/

int main (int argc, char *argv[])
{
  char ChromInfoFile[FILENAMELENGTH],
    RefgeneFile[FILENAMELENGTH],
    PhastConsFolder[FILENAMELENGTH],
    PeaksFile[FILENAMELENGTH];

  char UserName[USERNAMELENGTH];
  float Threshold;
    
  long* ChrSizes;
  dict* ChrNames;

  float** PHASTCONS;
  unsigned int** EXONS;

  long FileSize;

  char OutputDirName[DIRNAMELENGTH];
  char OutputFileName[FILENAMELENGTH];
  char Prefix[PREFIXLENGTH];
  
  int tmpSystem;
  
  char mess[MAXSTRING];

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account *) InitAcc();  
  
  /* 0.b. Read setup options */
  readargv_scorePhastCons(argc,argv,ChromInfoFile,RefgeneFile,PhastConsFolder,PeaksFile,UserName,Prefix,&Threshold);

  printSeqCodeHeader(SCOREPHASTCONS);
  StartingTime(mess,m);
  printMess(mess);
  
  /* 1. Allocating data structures */
  printMess("1. Request Memory to Operating System");
  ChrNames = (dict *) RequestMemoryDictionary();
  ChrSizes = (long *) RequestMemoryChrSizes();

  /* 2. Read the ChrSize file */
  printMess("2. Reading Chromosome Sizes");
  m->nChrs = ReadChrFile (ChromInfoFile,ChrSizes,ChrNames);
  sprintf(mess,"Size was successfully acquired for %d chromosomes",m->nChrs);
  printRes(mess);

  /*  Additional allocating data structures */
  PHASTCONS = (float**) RequestMemoryPHASTCONS(ChrSizes,ChrNames);
  EXONS = (unsigned int**) RequestMemoryREADS(ChrSizes,ChrNames);

  /* 3. Create output files for PEAK representations */
  printMess("3. Prepare the Output Folder");
  
  /* Check Name and Prefix for special characters: create subfolders if necessary */
  if (ValidationUserName(UserName) == TRUE)
    {
      if (ValidationPrefix(Prefix) == TRUE)
	{
	  /* Definition of the output folder */
	  sprintf(OutputDirName,"%s/%s_scorePhastCons",UserName,Prefix);
	  sprintf(mess,"Creating the output folder %s",OutputDirName);
	  printRes(mess);
	  
	  /* Creating the new Output folder */
	  if (mkdir(OutputDirName,0755))
	    {
	      printRes("Removing the old output folder");
	      sprintf(mess,"rm -rf %s",OutputDirName);
	      printRes(mess);
	      tmpSystem = system(mess);
	      
	      if (mkdir(OutputDirName,0755))
		{
		  printError("Problems with the creation of the output folder (please, check folder permissions)");
		}
	    }
	  
	  /* PEAKS output file */
	  sprintf(OutputFileName,"%s/scorePhastCons_%s.bed",OutputDirName,UserName);
	  sprintf(mess,"Filename for the PEAK ChIP levels file %s",OutputFileName);
	  printRes(mess);
	}
      else
	{
	  sprintf(mess,"Prefix %s for output did not pass the control (please, edit and run again)",Prefix);
	  printError(mess);
	}
    }
  else
    {
      sprintf(mess,"Name %s for output did not pass the control (please, edit and run again)",UserName);
      printError(mess);
    }
	  
  /* 4. Read the Refgene file */
  printMess("4. Reading Refgene file (exon information)");

  FileSize = GetFileSize(RefgeneFile);
  sprintf(mess,"%s: %.2lf Mb",RefgeneFile,(float)FileSize/MEGABYTE);
  printRes(mess);
  
  m->nLines = ReadRefgeneFileMarkExons(RefgeneFile,ChrSizes,ChrNames,EXONS);
  sprintf(mess,"%ld transcripts of RefSeq were successfully processed",m->nLines);
  printRes(mess);

  /* 5. Process the conservations scores from the PhastCons folder */
  printMess("5. Processing the PhastCons folder");

  ReadPhastConsFiles(PhastConsFolder,ChrSizes,ChrNames,PHASTCONS);
  
  /* 6. Process the file of peaks */
  printMess("6. Processing the List of peaks");

  m->nPeaks = ReadProcessPeaksPhastCons(PeaksFile,
					ChrSizes,
					ChrNames,
					PHASTCONS,
					EXONS,
					OutputFileName);
  
  sprintf(mess,"%ld peaks were successfully processed",m->nPeaks);
  printRes(mess);

  /* 7. The End */
  OutputTime(m);  
  
  exit(0);
  return(0);
}
