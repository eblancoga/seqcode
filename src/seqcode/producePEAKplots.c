/*************************************************************************
*                                                                        *
*   Module: producePEAKplots                                             *
*                                                                        *
*   ProducePEAKplots main program                                        *
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
int WINDOWRES = WINDOWRES_PLOTS;

/* Spike-in normalization */
int SPIKEIN = 0;

/* Background color */
char BGCOLOR[MAXCOLORNAME];

/* Foreground color */
char FGCOLOR[MAXCOLORNAME];

/* Foreground color: color3 */
char FGCOLORB[MAXCOLORNAME];

/* General background color */
char GBGCOLOR[MAXCOLORNAME];

/* General foreground color */
char GFGCOLOR[MAXCOLORNAME];

/* Heatmap background color */
char HBGCOLOR[MAXCOLORNAME];

/* Uniform plot: 0-1 */
int UNIFORM = 0;

/* Colorize the heatmaps */
int COLORIZE = 1;

/* Pie chart colors */
char COLOR1[MAXCOLORNAME];
char COLOR2[MAXCOLORNAME];
char COLOR3[MAXCOLORNAME];
char COLOR4[MAXCOLORNAME];
char COLOR5[MAXCOLORNAME];
char COLOR6[MAXCOLORNAME];
char COLOR7[MAXCOLORNAME];

/* Pie chart gradient monocolor */
int GRADIENT = 0;

/* Piechart: count frequencies in three classes: promoters, genic and intergenic */
int SIMPLIFIED = FALSE;

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
    PeaksFile[FILENAMELENGTH],
    UserName[USERNAMELENGTH];

  int L;
  
  long* ChrSizes;
  dict* ChrNames;

  unsigned int** READS;

  long* REGION;

  long FileSize;

  char OutputDirName[DIRNAMELENGTH];
  char OutputFileName[FILENAMELENGTH];
  char OutputFileName2[FILENAMELENGTH];
  char Prefix[PREFIXLENGTH];

  char RscriptFileName[FILENAMELENGTH];
  char PlotFileName[FILENAMELENGTH];

  dict* RColors;
  char RGBcodes[MAXCOLORS][MAXRGBCODE];

  int tmpSystem;
  
  char mess[MAXSTRING];

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account *) InitAcc();  
  
  /* 0.b. Read setup options */
  readargv_producePEAKplots(argc,argv,
			    ChromInfoFile,ReadsFile,
			    PeaksFile,UserName,Prefix,
			    &L);

  printSeqCodeHeader(PRODUCEPEAKPLOTS);
  StartingTime(mess,m);
  printMess(mess);
  
  /* 1. Allocating data structures */
  printMess("1. Request Memory to Operating System");
  ChrNames = (dict *) RequestMemoryDictionary();
  ChrSizes = (long *) RequestMemoryChrSizes();
  REGION = (long*) RequestMemoryRegion(L);
  RColors = (dict *) RequestMemoryDictionary();
  
  /* Color control */
  LoadRColors(RColors,RGBcodes);
  ValidateRColors(BGCOLOR,FGCOLOR,
		  GBGCOLOR,GFGCOLOR,
		  HBGCOLOR,FGCOLORB,
		  RColors);
  printRes("Loading the R color schema");
   
  /* 2. Read the ChrSize file */
  printMess("2. Reading Chromosome Sizes");
  m->nChrs = ReadChrFile (ChromInfoFile,ChrSizes,ChrNames);
  sprintf(mess,"Size was successfully acquired for %d chromosomes",m->nChrs);
  printRes(mess);

  /*  Additional allocating data structures */
  READS = (unsigned int**) RequestMemoryREADS(ChrSizes,ChrNames);

  /* 3. Prepare the output files for the PEAK representation*/
  printMess("3. Prepare the Output Folder");
  
  /* Check Name and Prefix for special characters: create subfolders if necessary */
  if (ValidationUserName(UserName) == TRUE)
    {
      if (ValidationPrefix(Prefix) == TRUE)
	{
	  /* Definition of the output folder */
	  sprintf(OutputDirName,"%s/%s_PEAKplot_%d",Prefix,UserName,L);
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
		  printError("Problems with the creation of the output folder");
		}
	    }

	  /* PEAK plots */
	  sprintf(OutputFileName,"%s/PEAKprofile_%s_%d.txt",OutputDirName,UserName,L);
	  sprintf(mess,"Filename for the PEAK average profile %s",OutputFileName);
	  printRes(mess);
	  
	  sprintf(PlotFileName,"%s/PlotPEAKprofile_%s_%d.pdf",OutputDirName,UserName,L);
	  sprintf(mess,"PDF file for the plot file %s",PlotFileName);
	  printRes(mess);
	  
	  sprintf(OutputFileName2,"%s/CenterBedPEAK_%s_%d.bed",OutputDirName,UserName,L);
	  sprintf(mess,"Filename for the Peak file + max points %s",OutputFileName2);
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

  ReadSAMFile(ReadsFile,ChrSizes,ChrNames,READS);
  sprintf(mess,"%ld reads of the SAM file processed",m->nReads);
  printRes(mess);
  sprintf(mess,"%ld forward reads acquired",m->nFwdReads);
  printRes(mess);
  sprintf(mess,"%ld reverse reads acquired",m->nRvsReads);
  printRes(mess);

  /* 5. Process the file of peaks */
  printMess("5. Processing the List of peaks");

  m->nPeaks = ReadProcessPeaks(PeaksFile,
			       ChrSizes,ChrNames,
			       L,READS,REGION,
			       OutputFileName,
			       OutputFileName2,
			       m->nReads);
  sprintf(mess,"%ld peaks were successfully processed",m->nPeaks);
  printRes(mess);

  /* 6. Produce the final file to produce the PEAK plot */
  if (m->nPeaks>0)
    {
      printMess("6. Running R to produce the plots");

      sprintf(RscriptFileName,"%s/RscriptPEAKprofile_%s_%d.txt",OutputDirName,UserName,L);
      sprintf(mess,"Preparing the Rscript file %s",RscriptFileName);
      printRes(mess);
      
      CreateRscriptPeak(OutputFileName,
			RscriptFileName,
			PlotFileName,
			UserName,L,
			m->nReads,
			m->nPeaks);
      sprintf(mess,"R CMD BATCH %s",RscriptFileName);
      printRes(mess);
      tmpSystem = system(mess);
      
      printRes("Removing the out R file");
      sprintf(mess,"rm -f *.Rout");
      printRes(mess);
      tmpSystem = system(mess);
    }

  /* 7. The End */
  OutputTime(m);  
  
  exit(0);
  return(0);
}
