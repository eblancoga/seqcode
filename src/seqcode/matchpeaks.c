/*************************************************************************
*                                                                        *
*   Module: matchpeaks                                                   *
*                                                                        *
*   MatchPeaks main program                                              *
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

/* Overlap size */
int OSIZE=1;

/* Spike-in normalization */
int SPIKEIN = 0;

/* Accounting time and results */
account *m;


/************************************************************************
                            MAIN program
************************************************************************/

int main (int argc, char *argv[])
{
  char PeaksFileA[FILENAMELENGTH],
    PeaksFileB[FILENAMELENGTH];
  char NameA[USERNAMELENGTH],
    NameB[USERNAMELENGTH];
  
  dict* ChrNames;

  peak** PeaksA;
  peak** PeaksB;
  
  char OutputDirName[DIRNAMELENGTH];
  char OutputFileAB[FILENAMELENGTH];
  char OutputFileA[FILENAMELENGTH];
  char OutputFileB[FILENAMELENGTH];
  char Prefix[PREFIXLENGTH];
  
  int tmpSystem;
  
  char mess[MAXSTRING];

  long FileSize;

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account*) InitAcc();  

  /* 0.b. Read setup options */
  readargv_matchpeaks(argc,argv,PeaksFileA,PeaksFileB,NameA,NameB,Prefix);

  printSeqCodeHeader(MATCHPEAKS);
  StartingTime(mess,m);
  printMess(mess);
  
  /* 1. Allocating data structures */
  printMess("1. Request Memory to Operating System");
  PeaksA = (peak**) RequestMemoryPeaks();
  PeaksB = (peak**) RequestMemoryPeaks();
  ChrNames = (dict *) RequestMemoryDictionary();

  /* 2. Create the output files*/
  printMess("2. Prepare the Output Folder");

  /* Check Names and Prefix for special characters: create subfolders if necessary */
  if ((ValidationUserName(NameA) == TRUE) && (ValidationUserName(NameB) == TRUE))
    {
      if (ValidationPrefix(Prefix) == TRUE)
	{
	  /* Definition of the output folder */
	  sprintf(OutputDirName,"%s/%s_%s_matchpeaks",Prefix,NameA,NameB);
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
	  
	  /* Output files */
	  sprintf(OutputFileAB,"%s/common_%s_%s.bed",OutputDirName,NameA,NameB);
	  sprintf(mess,"Filename for the common peaks (%s)",OutputFileAB);
	  printRes(mess);
	  
	  sprintf(OutputFileA,"%s/only_%s.bed",OutputDirName,NameA);
	  sprintf(mess,"Filename for peaks only in %s (%s)",NameA,OutputFileA);
	  printRes(mess);
	  
	  sprintf(OutputFileB,"%s/only_%s.bed",OutputDirName,NameB);
	  sprintf(mess,"Filename for peaks only in %s (%s)",NameB,OutputFileB);
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
      sprintf(mess,"Names %s or %s for output did not pass the control (please, edit and run again)",NameA,NameB);
      printError(mess);
    }
	  
  /* 3. Read the PeaksFileA file */
  sprintf(mess,"3. Reading File A: %s",NameA);
  printMess(mess);
  FileSize = GetFileSize(PeaksFileA);
  sprintf(mess,"%s: %.2lf Mb",PeaksFileA,(float)FileSize/MEGABYTE);
  printRes(mess);

  m->nTotalPeaksA = ReadPeaksFile(PeaksFileA,PeaksA,m->nPeaksA,ChrNames);
  sprintf(mess,"%ld peaks were successfully acquired",m->nTotalPeaksA);
  printRes(mess);

  /* 4. Read the PeaksFileB file */
  sprintf(mess,"4. Reading File B: %s",NameB);
  printMess(mess);
  FileSize = GetFileSize(PeaksFileB);
  sprintf(mess,"%s: %.2lf Mb",PeaksFileB,(float)FileSize/MEGABYTE);
  printRes(mess);

  m->nTotalPeaksB = ReadPeaksFile(PeaksFileB,PeaksB,m->nPeaksB,ChrNames);
  sprintf(mess,"%ld peaks were successfully acquired",m->nTotalPeaksB);
  printRes(mess);

  /* 5. Compare both lists of peaks to mark intersected peaks */
  printMess("5. Processing both lists of Peaks");
  ProcessPeaksLists(PeaksA,PeaksB,ChrNames,NameA);

  /* 6. Output eack peak from A and B into different files */
  printMess("6. Output final results");
  OutputPeaksLists(PeaksA,PeaksB,
		   NameA,NameB,
		   OutputFileAB,
		   OutputFileA,
		   OutputFileB,
		   ChrNames);

  /* 7. The End */
  OutputTime(m);  
  
  exit(0);
  return(0);
}
