/*************************************************************************
*                                                                        *
*   Module: produceTESmaps                                               *
*                                                                        *
*   ProduceTESmaps main program                                          *
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
int WINDOWRES = WINDOWRES_MAPS;

/* Normalize for the total reads */
int NORM = FALSE;

/* Spike-in normalization */
int SPIKEIN = 0;

/* Background  color */
char BGCOLOR[MAXCOLORNAME];

/* Foreground color */
char FGCOLOR[MAXCOLORNAME];

/* Foreground color: color3 */
char FGCOLORB[MAXCOLORNAME];

/* Heatmap background color */
char HBGCOLOR[MAXCOLORNAME];

/* General background color */
char GBGCOLOR[MAXCOLORNAME];

/* General foreground color */
char GFGCOLOR[MAXCOLORNAME];

/* Uniform plot: 0-1 */
int UNIFORM = 0;

/* Noise reduction limit in heatmaps */
float NOISET = NOISETHRESHOLD;

/* Colorize the heatmaps */
int COLORIZE = 0;

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
    RefgeneFile[FILENAMELENGTH],
    ReadsFile[FILENAMELENGTH],
    GenesFile[FILENAMELENGTH],
    UserName[USERNAMELENGTH];

  int L;
  
  long* ChrSizes;
  dict* ChrNames;

  dict* GeneNames;
  int* GeneChrs;

  transcript** Transcripts;

  unsigned int** READS;

  long FileSize;

  char OutputDirName[DIRNAMELENGTH];
  char OutputFileName2[FILENAMELENGTH];
  char OutputFileName3[FILENAMELENGTH];
  char OutputFileName4[FILENAMELENGTH];
  char Prefix[PREFIXLENGTH];
  
  char RscriptFileName[FILENAMELENGTH];
  char PlotFileName2[FILENAMELENGTH];

  dict* RColors;
  char RGBcodes[MAXCOLORS][MAXRGBCODE];

  float normfactor;
  
  int tmpSystem;
  
  char mess[MAXSTRING];

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account *) InitAcc();  
  
  /* 0.b. Read setup options */
  readargv_produceTESmaps(argc,argv,
			  ChromInfoFile,RefgeneFile,
			  ReadsFile,GenesFile,
			  UserName,Prefix,&L);

  printSeqCodeHeader(PRODUCETESMAPS);
  StartingTime(mess,m);
  printMess(mess);
  
  /* 1. Allocating data structures */
  printMess("1. Request Memory to Operating System");
  ChrNames = (dict *) RequestMemoryDictionary();
  ChrSizes = (long *) RequestMemoryChrSizes();
  GeneNames = (dict *) RequestMemoryDictionary();
  GeneChrs = (int *) RequestMemoryGeneChrs();
  Transcripts = (transcript**) RequestMemoryTranscripts();
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

  /* 3. Create output files for TES and HEAT representations*/
  printMess("3. Prepare the Output Folder");

  /* Check Name and Prefix for special characters: create subfolders if necessary */
  if (ValidationUserName(UserName) == TRUE)
    {
      if (ValidationPrefix(Prefix) == TRUE)
	{
	  /* Definition of the output folder */
	  sprintf(OutputDirName,"%s/%s_TESmap_%d",Prefix,UserName,L);
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
	  sprintf(OutputFileName2,"%s/HEATmatrix_%s_%d.txt",OutputDirName,UserName,L);
	  sprintf(mess,"Filename for the HEAT matrix %s",OutputFileName2);
	  printRes(mess);
	  
	  sprintf(OutputFileName3,"%s/HEATmatrix_%s_%d_processed.txt",OutputDirName,UserName,L);
	  sprintf(mess,"Filename for the processed HEAT matrix %s",OutputFileName3);
	  printRes(mess);
	  
	  sprintf(OutputFileName4,"%s/HEATmatrix_%s_%d_genes.txt",OutputDirName,UserName,L);
	  sprintf(mess,"Filename for the HEAT gene rank %s",OutputFileName4);
	  printRes(mess);
	  
	  sprintf(PlotFileName2,"%s/PlotHEATmap_%s_%d.pdf",OutputDirName,UserName,L);
	  sprintf(mess,"PDF file for the heat plot file %s",PlotFileName2);
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
  printMess("4. Reading Refgene file");
  FileSize = GetFileSize(RefgeneFile);
  sprintf(mess,"%s: %.2lf Mb",RefgeneFile,(float)FileSize/MEGABYTE);
  printRes(mess);
  
  m->nTotalTranscripts = ReadRefgeneFile2(RefgeneFile,Transcripts,ChrNames,GeneNames,GeneChrs);
  sprintf(mess,"%ld transcripts of RefSeq were successfully acquired",m->nTotalTranscripts);
  printRes(mess);
  
  /* 5. Acquire the BAM/SAM reads */
  printMess("5. Processing the BAM/SAM file");
  
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

  /* Normalization factor */
  if (NORM)
    {
      /* Traditional model: total number of reads of the sample */
      normfactor = (float)m->nReads/MEGA;
      
      sprintf(mess,"Normalization factor: %f",normfactor);
      printRes(mess);
    }
  if (SPIKEIN)
    {
      /* Reference-adjusted normalization: total number of reads of the spike/refence */
      normfactor = (float)SPIKEIN/MEGA;
      
      sprintf(mess,"Normalization spike-in factor: %f",normfactor);
      printRes(mess);
    }
  
  /* 6. Process the file of target genes */
  printMess("6. Processing the List of target genes");

  m->nGenes = ProcessTargetGenesTESMaps(GenesFile,Transcripts,
					ChrNames,ChrSizes,
					GeneNames,GeneChrs,
					L,READS,
					OutputFileName2,
					m->nReads);
  sprintf(mess,"%d target genes were successfully processed",m->nGenes);
  printRes(mess);

  /* Rank the heatmap using the avg. number of reads per gene */
  sprintf(mess,"Extracting gene avg. values in %s",OutputFileName4);
  printRes(mess);
  sprintf(mess,"cut -f 1,%d %s | sort -nrk 2 > %s",
	  ((2*L)/WINDOWRES)+2,
	  OutputFileName2,
	  OutputFileName4);
  printRes(mess);
  tmpSystem = system(mess);
  
  sprintf(mess,"Ranking the heat file: %s",
	  OutputFileName3);
  printRes(mess);
  
  sprintf(mess,"sort -nk %d %s | cut -f 2-%d > %s",
	  ((2*L)/WINDOWRES)+2,
	  OutputFileName2,
	  ((2*L)/WINDOWRES)+1,
	  OutputFileName3);
  printRes(mess);
  tmpSystem = system(mess); 

  /* 7. Produce the final file to produce the TES plot */
  if (m->nGenes>0)
    {
      printMess("7. Running R to produce the plots");

      sprintf(RscriptFileName,"%s/RscriptTESmap_%s_%d.txt",OutputDirName,UserName,L);
      sprintf(mess,"Preparing the Rscript file %s",RscriptFileName);
      printRes(mess);
      
      CreateRscriptTESMaps(OutputFileName3,
			   RscriptFileName,
			   PlotFileName2,
			   UserName,L,
			   m->nReads,
			   m->nGenes);
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
