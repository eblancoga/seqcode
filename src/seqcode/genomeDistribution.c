/*************************************************************************
*                                                                        *
*   Module: genomeDistribution                                           *
*                                                                        *
*   GenomeDistribution main program                                      *
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
int WINDOWRES = WINDOWRES_GENOME;

/* Spike-in normalization */
int SPIKEIN = 0;

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

/* Pie chart viridis palette */
int PALETTE = 0;

/* Background color */
char BGCOLOR[MAXCOLORNAME];

/* Foreground color */
char FGCOLOR[MAXCOLORNAME];

/* Foreground color: color3 */
char FGCOLORB[MAXCOLORNAME];

/* General background  color */
char GBGCOLOR[MAXCOLORNAME];

/* General foreground color */
char GFGCOLOR[MAXCOLORNAME];

/* Heatmap background color */
char HBGCOLOR[MAXCOLORNAME];

/* Colorize the heatmaps */
int COLORIZE = 1;

/* Uniform plot: 0-1 */
int UNIFORM = 0;

/* Count frequencies in distinct classes of promoters, exons and introns */
int DETAILED = FALSE;

/* Count frequencies in three classes: promoters, genic and intergenic */
int SIMPLIFIED = FALSE;

/* Accounting time and results */
account *m;

/************************************************************************
                            MAIN program
************************************************************************/

int main (int argc, char *argv[])
{
  char ChromInfoFile[FILENAMELENGTH];
  char RefgeneFile[FILENAMELENGTH];
  char PeaksFile[FILENAMELENGTH];
  char UserName[USERNAMELENGTH];
  
  long* ChrSizes;
  dict* ChrNames;

  unsigned int** REGIONS;

  long FileSize;

  char OutputDirName[DIRNAMELENGTH];
  char OutputFileName[FILENAMELENGTH];
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
  readargv_genomeDistribution(argc,argv,
			      ChromInfoFile,
			      RefgeneFile,
			      PeaksFile,
			      UserName,
			      Prefix);
  printSeqCodeHeader(GENOMEDISTRIBUTION);
  StartingTime(mess,m);
  printMess(mess);
  
  /* 1. Allocating data structures */
  printMess("1. Request Memory to Operating System");
  ChrNames = (dict *) RequestMemoryDictionary();
  ChrSizes = (long *) RequestMemoryChrSizes();
  RColors = (dict *) RequestMemoryDictionary();

  /* Color control */
  LoadRColors(RColors,RGBcodes);
  ValidateRColorsPieCharts(COLOR1,COLOR2,COLOR3,
			   COLOR4,COLOR5,COLOR6,
			   COLOR7,RColors);
  
  /* Setting Viridis palette colors (optional) */
  if (PALETTE)
    {
      SetViridisColorsPieCharts(COLOR1,COLOR2,COLOR3,
				COLOR4,COLOR5,COLOR6,
				COLOR7,PALETTE);
    }

  printRes("Loading the R color schema");
   
  /* 2. Read the ChrSize file */
  printMess("2. Reading Chromosome Sizes");
  m->nChrs = ReadChrFile (ChromInfoFile,ChrSizes,ChrNames);
  sprintf(mess,"Size was successfully acquired for %d chromosomes",m->nChrs);
  printRes(mess);

  /*  Additional allocating data structures */
  REGIONS = (unsigned int**) RequestMemoryREADS(ChrSizes,ChrNames);

  /* 3. Create output files for the genome chart */
  printMess("3. Prepare the Output Folder");
  
  /* Check Name and Prefix for special characters: create subfolders if necessary */
  if (ValidationUserName(UserName) == TRUE)
    {
      if (ValidationPrefix(Prefix) == TRUE)
	{
	  /* Definition of the output folder */
	  sprintf(OutputDirName,"%s/%s_GENOMEchart",Prefix,UserName);
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
	  sprintf(OutputFileName,"%s/GENOMEchart_%s.txt",OutputDirName,UserName);
	  sprintf(mess,"Filename for the marked peak file %s",OutputFileName);
	  printRes(mess);
	  
	  sprintf(RscriptFileName,"%s/RscriptGENOMEchart_%s.txt",OutputDirName,UserName);
	  sprintf(mess,"Preparing the Rscript file %s",RscriptFileName);
	  printRes(mess);
	  
	  sprintf(PlotFileName,"%s/PlotGENOMEchart_%s.pdf",OutputDirName,UserName);
	  sprintf(mess,"PDF file for the GENOME chart %s",PlotFileName);
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

  /* 4. Read the Refgene file and mark positions along chromosomes */
  printMess("4. Reading Refgene file");
  FileSize = GetFileSize(RefgeneFile);
  sprintf(mess,"%s: %.2lf Mb",RefgeneFile,(float)FileSize/MEGABYTE);
  printRes(mess);
  
  m->nTotalTranscripts = ReadRefgeneFileMark(RefgeneFile,
					     ChrSizes,
					     ChrNames,
					     REGIONS);
  sprintf(mess,"%ld transcripts of RefSeq were successfully acquired",
	  m->nTotalTranscripts);
  printRes(mess);

  /* 5. Process the file of peaks */
  printMess("5. Processing the list of peaks");

  m->nPeaks = ProcessPeaksMarks(PeaksFile,
				ChrNames,ChrSizes,
				REGIONS,
				OutputFileName,
				RscriptFileName,
				PlotFileName,
				UserName);
  sprintf(mess,"%ld peaks of PeaksFile were successfully acquired",
	  m->nPeaks);
  printRes(mess); 
 
  /* 6. Produce the final file to produce the pie chart plot */
  printMess("6. Running R to produce the plots");

  sprintf(mess,"R CMD BATCH %s",RscriptFileName);
  printRes(mess);
  tmpSystem = system(mess);
      
  printRes("Removing the out R file");
  sprintf(mess,"rm -f *.Rout");
  printRes(mess);
  tmpSystem = system(mess);

  /* 7. The End */
  OutputTime(m);  
  
  exit(0);
  return(0);
}
