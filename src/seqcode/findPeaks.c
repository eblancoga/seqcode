/*************************************************************************
*                                                                        *
*   Module: findPeaks                                                    *
*                                                                        *
*   findPeaks main program                                               *
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

/* Read extension */
int AVGL = 150;

/* Bin resolution */
int WINDOWRES = WINDOWRES_PEAKS;

/* Spike-in normalization */
int SPIKEIN = 0;

/* Normalized read threshold for peak calling */
float T = FINDPEAKS_T;

/* Demo mode: no control of min number of reads */
int DEMO = FALSE;

/* Accounting time and results */
account *m;

/************************************************************************
                            MAIN program
************************************************************************/

int main (int argc, char *argv[])
{
  char ChromInfoFile[FILENAMELENGTH],
    ReadsFile[FILENAMELENGTH],
    UserName[USERNAMELENGTH];

  long* ChrSizes;
  dict* ChrNames;

  unsigned int** READS;

  long FileSize;

  char OutputDirName[DIRNAMELENGTH];
  char OutputFileName[FILENAMELENGTH];
  char Prefix[PREFIXLENGTH];

  int nChromosomes;

  char tmpFileName[TMPFILENAMELENGTH];

  int tmpSystem;
  
  char mess[MAXSTRING];

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account *) InitAcc();  
  
  /* 0.b. Read setup options */
  readargv_findPeaks(argc,argv,
		     ChromInfoFile,
		     ReadsFile,
		     UserName,
		     Prefix);

  printSeqCodeHeader(FINDPEAKS);
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
  READS = (unsigned int**) RequestMemoryREADS(ChrSizes,ChrNames);

  /* 3. Create the output files (list of peaks in BED */
  printMess("3. Prepare the Output Folder");

  /* Check Name and Prefix for special characters: create subfolders if necessary */
  if (ValidationUserName(UserName) == TRUE)
    {
      if (ValidationPrefix(Prefix) == TRUE)
	{
	  /* Definition of the output folder */
	  sprintf(OutputDirName,"%s/%s_findPeaks",Prefix,UserName);
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

	  /* Bed file */
	  sprintf(OutputFileName,"%s/%s.bed",OutputDirName,UserName);
	  sprintf(mess,"Filename for the Bed file %s",OutputFileName);
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

  /* 4. Acquire the BAM/SAM reads */
  printMess("4. Processing the BAM/SAM file");
  
  FileSize = GetFileSize(ReadsFile);
  sprintf(mess,"%s: %.2lf Mb",ReadsFile,(float)FileSize/MEGABYTE);
  printRes(mess);

  printRes("Processing Single-end sequencing reads");
  
  ReadSAMFile(ReadsFile,ChrSizes,ChrNames,READS);
  sprintf(mess,"%ld reads of the SAM file processed",m->nReads);
  printRes(mess);
  sprintf(mess,"%ld forward reads acquired",m->nFwdReads);
  printRes(mess);
  sprintf(mess,"%ld reverse reads acquired",m->nRvsReads);
  printRes(mess);

  /* 5. Process the chromosomes to cut above the threshold */
  printMess("5. Analyzing the reads to find peaks");

  nChromosomes = ProcessGenomePeaks(ChrNames,
				    ChrSizes,
				    READS,
				    UserName,
				    OutputFileName,
				    m->nReads);
  sprintf(mess,"%d chromosomes sucessfully included into the peak calling\n",
	  nChromosomes);
  printRes(mess);

  /* Inform about the final output file size (before zip) */
  printRes("Size of the resulting BED file (uncompressed):");
  FileSize = GetFileSize(OutputFileName);
  sprintf(mess,"%s: %.2lf Mb",OutputFileName,(float)FileSize/MEGABYTE);
  printRes(mess);

  /* Compress the resulting Bed file */
  printRes("Compressing the final BED profile\n");
  sprintf(mess,"gzip %s",OutputFileName);
  printRes(mess);
  tmpSystem = system(mess);
  
  /* Inform about the final output file size (after zip) */
  printRes("Size of the resulting BED file:");
  sprintf(tmpFileName,"%s.gz",OutputFileName);
  FileSize = GetFileSize(tmpFileName);
  sprintf(mess,"%s: %.2lf Mb",tmpFileName,(float)FileSize/MEGABYTE);
  printRes(mess);

  /* 6. The End */
  OutputTime(m);  
  
  exit(0);
  return(0);
}
