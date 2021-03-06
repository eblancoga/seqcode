/*************************************************************************
*                                                                        *
*   Module: combineTSSmaps                                               *
*                                                                        *
*   CombineTSSmaps main program                                          *
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

/* Background color: color1 */
char BGCOLOR[MAXCOLORNAME];

/* Foreground color: color2 */
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
float COLORIZE = 0;

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
    ReadsFile1[FILENAMELENGTH],
    ReadsFile2[FILENAMELENGTH],
    GenesFile[FILENAMELENGTH],
    UserName1[USERNAMELENGTH],
    UserName2[USERNAMELENGTH];

  int L;
  
  dict* ChrNames;
  long* ChrSizes;

  dict* GeneNames;
  int* GeneChrs;

  transcript** Transcripts;

  unsigned int** READS1;
  unsigned int** READS2;

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

  int tmpSystem;
  
  char mess[MAXSTRING];

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account *) InitAcc();  
  
  /* 0.b. Read setup options */
  readargv_combineTSSmaps(argc,argv,
			  ChromInfoFile,
			  RefgeneFile,
			  ReadsFile1,
			  ReadsFile2,
			  GenesFile,
			  UserName1,
			  UserName2,
			  Prefix,
			  &L);
  printSeqCodeHeader(COMBINETSSMAPS);
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
  READS1 = (unsigned int**) RequestMemoryREADS(ChrSizes,ChrNames);
  READS2 = (unsigned int**) RequestMemoryREADS(ChrSizes,ChrNames);

  /* 3. Create the output files for the TSS maps representations*/
  printMess("3. Prepare the Output Folder");

  /* Check Name and Prefix for special characters: create subfolders if necessary */
  if ((ValidationUserName(UserName1) == TRUE) && (ValidationUserName(UserName2) == TRUE))
    {
      if (ValidationPrefix(Prefix) == TRUE)
	{
	  sprintf(OutputDirName,"%s/%s-%s_TSSmap_%d",Prefix,UserName1,UserName2,L);
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
	  sprintf(OutputFileName2,"%s/HEATmatrix_%s-%s_%d.txt",OutputDirName,UserName1,UserName2,L);
	  sprintf(mess,"Filename for the HEAT matrix %s",OutputFileName2);
	  printRes(mess);
  
	  sprintf(OutputFileName3,"%s/HEATmatrix_%s-%s_%d_processed.txt",OutputDirName,UserName1,UserName2,L);
	  sprintf(mess,"Filename for the processed HEAT matrix %s",OutputFileName3);
	  printRes(mess);
	  
	  sprintf(OutputFileName4,"%s/HEATmatrix_%s-%s_%d_genes.txt",OutputDirName,UserName1,UserName2,L);
	  sprintf(mess,"Filename for the HEAT gene rank %s",OutputFileName4);
	  printRes(mess);
	  
	  sprintf(PlotFileName2,"%s/PlotHEATmap_%s-%s_%d.pdf",OutputDirName,UserName1,UserName2,L);
	  sprintf(mess,"PDF file for the HEAT plot file %s",PlotFileName2);
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
      sprintf(mess,"Names %s or %s for output did not pass the control (please, edit and run again)",UserName1,UserName2);
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
  
  /* 5a. Acquire the BAM/SAM reads file 1 */
  printMess("5a. Processing the BAM/SAM file 1");
  
  FileSize = GetFileSize(ReadsFile1);
  sprintf(mess,"%s: %.2lf Mb",ReadsFile1,(float)FileSize/MEGABYTE);
  printRes(mess);

  ReadSAMFile(ReadsFile1,ChrSizes,ChrNames,READS1);
  m->nReads1 = m->nReads;
  m->nFwdReads1 = m->nFwdReads;
  m->nRvsReads1 = m->nRvsReads;
  sprintf(mess,"%ld reads of the SAM file processed",m->nReads1);
  printRes(mess);                                               
  sprintf(mess,"%ld forward reads acquired",m->nFwdReads1);      
  printRes(mess);                                               
  sprintf(mess,"%ld reverse reads acquired",m->nRvsReads1);      
  printRes(mess);

  /* 5b. Acquire the BAM/SAM reads file 2 */
  printMess("5b. Processing the BAM/SAM file 2");
  
  FileSize = GetFileSize(ReadsFile2);
  sprintf(mess,"%s: %.2lf Mb",ReadsFile2,(float)FileSize/MEGABYTE);
  printRes(mess);

  ReadSAMFile(ReadsFile2,ChrSizes,ChrNames,READS2);    
  m->nReads2 = m->nReads;
  m->nFwdReads2 = m->nFwdReads;
  m->nRvsReads2 = m->nRvsReads;
  sprintf(mess,"%ld reads of the SAM file processed",m->nReads2);
  printRes(mess);                                               
  sprintf(mess,"%ld forward reads acquired",m->nFwdReads2);      
  printRes(mess);                                               
  sprintf(mess,"%ld reverse reads acquired",m->nRvsReads2);      
  printRes(mess);

  /* 6. Process the file of target genes */
  printMess("6. Processing the List of target genes");

  m->nGenes = CombineTargetGenesMaps(GenesFile,Transcripts,
				     ChrNames,ChrSizes,
				     GeneNames,GeneChrs,
				     L,READS1,READS2,
				     OutputFileName2,
				     m->nReads1,
				     m->nReads2);
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

  /* 7. Produce the final file to produce the combined TSS map */
  if (m->nGenes>0)
    {
      printMess("7. Running R to produce the plots");

      sprintf(RscriptFileName,"%s/RscriptTSSmap_%s-%s_%d.txt",
	      OutputDirName,UserName1,UserName2,L);
      sprintf(mess,"Preparing the Rscript file %s",RscriptFileName);
      printMess(mess);
      
      CreateRscriptCombinedMaps(OutputFileName3,
				RscriptFileName,
				PlotFileName2,
				UserName1,
				UserName2,
				L,
				m->nReads1,
				m->nReads2,
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
