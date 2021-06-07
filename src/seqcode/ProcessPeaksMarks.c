/*************************************************************************
*                                                                        *
*   Module: ProcessPeaksMarks                                            *
*                                                                        *
*   Describe the genome distribution of the peaks                        *
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

extern int WINDOWRES;
extern int DETAILED;
extern int SIMPLIFIED;
extern account* m;

/* Process the BED file, annotating the intersections with transcripts + Upstream */
long ProcessPeaksMarks(char* FileName,
		       dict* ChrNames,
		       long* ChrSizes,  
		       unsigned int** REGIONS,
		       char* OutputFileName,
		       char* RscriptFileName,
		       char* PlotFileName,
		       char* TrackName)
{
  /* File handle */
  FILE* file;
  FILE* outfile;
  
  /* Split every input line into several tokens <chr,pos1,pos2,score> */
  char line[MAXLINE];
  char* line1;
  char* line2;
  char* line3;
  char* line4;

  /* Backup line */
  char lineCopy[MAXLINE];
  
  /* Values */
  char chr[MAXCHRS];
  long pos1,pos2;
  char score[MAXSTRING];

  /* Read interval pointer */
  long start;
  long stop;
  long i;

  /* Boolean values */
  int promoter;
  int intragenic;
  int distal;
  int proximal;
  int utr5;
  int utr3;
  int cds;
  int intron;

  /* Code for the hash */
  int key;

  /* Number of lines */
  long nLines;

  /* Final statistics */
  int nPromoters;
  int nIntragenics;
  int nIntergenics;
  int nDistals;
  int nProximals;
  int nUtr5s;
  int nUtr3s;
  int nCDSs;
  int nIntrons;

  char mess[MAXSTRING];
  char sRegion[MAXSTRING];


  /* 0. Open BED file to read the peaks */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The BED file can not be opened to read");

 /* 0B. Prepare the output file to print the marked BED peaks */
  if ((outfile=fopen(OutputFileName, "w"))==NULL)
    {
      sprintf(mess,"The marked BED File %s file can not be opened to write",
              OutputFileName);
      printError(mess);
    }

  /* 1. Reset counters */
  nLines = 0;  
  nPromoters = 0;  
  nIntragenics = 0;  
  nIntergenics = 0;
  nDistals = 0;    
  nProximals = 0;    
  nUtr5s = 0;
  nUtr3s = 0;
  nCDSs = 0;
  nIntrons = 0;
  
  /* Init the info messages */
  printReadingInit();

  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Message about processing lines... */
      printReadingInfoSmall(nLines);

      if (line[0]=='t' && line[1]=='r' && line[2]=='a' && line[3]=='c' && line[4]=='k')
	{
	  /* Skip this line */
	}
      else
	{
	  /* Backup copy of the line to show error messages */
	  strcpy(lineCopy,line);
	  
	  /* Extracting values of current line: only using field1 and field2 */
	  line1 = (char *) strtok(line,TAB);
	  line2 = (char *) strtok(NULL,TAB);
	  line3 = (char *) strtok(NULL,TAB);
	  line4 = (char *) strtok(NULL,TAB);

	  /* There are 3 mandatory columns: score is optional */
	  if (line1 == NULL || line2 == NULL || line3 == NULL)
	    {
	      sprintf(mess,"Unexpected format <chr,pos1,pos2,score> in the line:\n-->%s\n",lineCopy);
	      printError(mess);
	    }
	  
	  /* Chromosome */
	  if (sscanf(line1,"%s",chr) != 1)
	    {
	      sprintf(mess,"Wrong format in the chromosome name:\n-->%s\n",lineCopy);
	      printError(mess);
	    }
	  
	  /* Position 1 */
	  if (sscanf(line2,"%ld",&pos1) != 1)
	    {
	      sprintf(mess,"Wrong format in the pos1 of the BED line:\n-->%s\n",lineCopy);
	      printError(mess);
	    }
	  
	  /* Position 2 */
	  if (sscanf(line3,"%ld",&pos2) != 1)
	    {
	      sprintf(mess,"Wrong format in the pos2 of the BED line:\n-->%s\n",lineCopy);
	      printError(mess);
	    }
	  
	  /* Score is optional */
	  if (line4 == NULL)
	    {
	      strcpy(score,sNOSCORE);
	    }
	  else
	    {
	      if (sscanf(line4,"%s",score) != 1)
		{
		  sprintf(mess,"Wrong format in the score of the BED line:\n-->%s\n",lineCopy);
		  printError(mess);
		}
	    }

	  /* Verification: this chromosome is registered into our dictionary? */
	  key = getkeyDict(ChrNames,chr);
	  if (key == NOTFOUND)
	    {
	      //sprintf(mess,"Skip line, unknown chromosome (%s):\n-->%s\n",chr,lineCopy);
	      //printMess(mess);
	    }
	  else
	    {
	      /* Scanning the peak region for genome features */
	      start = pos1/WINDOWRES;
	      stop = pos2/WINDOWRES;
	      
	      /*** BASIC INFORMATION ***/
	      /* Final stats: one peak can be in multiple categories */
	      if (DETAILED==FALSE)
		{
		  /* Genome features */
		  promoter = FALSE;
		  intragenic = FALSE;
		  
		  for(i=start; i<=stop; i++) 
		    {
		      if (REGIONS[key][i]==cPROMOTER)
			{
			  promoter = TRUE;
			}
		      if (REGIONS[key][i]==cINTRAGENIC)
			{
			  intragenic = TRUE;
			}
		    }
	      
		  /* String to capture the distinct overlapping regions */
		  strcpy(sRegion,"");
		  
		  if (promoter==TRUE)
		    {
		      strcat(sRegion,sPROMOTER);
		      nPromoters++;
		    }
		  
		  if (intragenic==TRUE)
		    {
		      strcat(sRegion,sINTRAGENIC);
		      nIntragenics++;
		    }
		  
		  /* Intergenic if no other mark is present */
		  if (promoter == FALSE && intragenic == FALSE)
		    {
		      strcpy(sRegion,sINTERGENIC);
		      nIntergenics++;
		    }
		  
		  /* print final BED peak + mark */
		  fprintf(outfile,"%s\t%ld\t%ld\t%s\n",
			  chr,
			  pos1,
			  pos2,
			  sRegion);
		}
	      else
		{
		  /*** DETAILED INFORMATION ***/
		  /* Genome features */
		  distal = FALSE;
		  proximal = FALSE;
		  utr5 = FALSE;
		  utr3 = FALSE;
		  cds = FALSE;
		  intron = FALSE;
		  
		  for(i=start; i<=stop; i++) 
		    {
		      if (REGIONS[key][i]==cDISTAL)
			{
			  distal = TRUE;
			}
		      if (REGIONS[key][i]==cPROXIMAL)
			{
			  proximal = TRUE;
			}
		      if (REGIONS[key][i]==c5UTR)
			{
			  utr5 = TRUE;
			}
		      if (REGIONS[key][i]==c3UTR)
			{
			  utr3 = TRUE;
			}
		      if (REGIONS[key][i]==cCDS)
			{
			  cds = TRUE;
			}
		      if (REGIONS[key][i]==cINTRON)
			{
			  intron = TRUE;
			}
		    }

		  /* String to capture the distinct overlapping regions */
		  strcpy(sRegion,"");
		  
		  if (distal==TRUE)
		    {
		      strcat(sRegion,sDISTAL);
		      nDistals++;
		    }
		  if (proximal==TRUE)
		    {
		      strcat(sRegion,sPROXIMAL);
		      nProximals++;
		    }
		  if (utr5==TRUE)
		    {
		      strcat(sRegion,s5UTR);
		      nUtr5s++;
		    }
		  if (cds==TRUE)
		    {
		      strcat(sRegion,sCDS);
		      nCDSs++;
		    }
		  if (utr3==TRUE)
		    {
		      strcat(sRegion,s3UTR);
		      nUtr3s++;
		    }
		  if (intron==TRUE)
		    {
		      strcat(sRegion,sINTRON);
		      nIntrons++;
		    }

		  /* Intergenic if no other mark is present */
		  if (distal == FALSE && proximal == FALSE && 
		      utr5 == FALSE && utr3 == FALSE && 
		      cds == FALSE && intron == FALSE)
		    {
		      strcpy(sRegion,sINTERGENIC);
		      nIntergenics++;
		    }
		  
		  /* print final BED peak + genome mark */
		  fprintf(outfile,"%s\t%ld\t%ld\t%s\n",
			  chr,
			  pos1,
			  pos2,
			  sRegion);
		}
	    }
	      
	  /* Increase the total number of lines (peaks) */
	  nLines++;
	}
    }
  
  fclose(file);
  fclose(outfile);

  /* Prepare the R script to produce the pie chart */
  if (DETAILED==FALSE && SIMPLIFIED==FALSE)
    {
      CreateRscriptChart(RscriptFileName,
			 PlotFileName,
			 nPromoters,
			 nIntragenics,
			 nIntergenics,
			 TrackName,
			 nLines);
    }
  if (SIMPLIFIED)
    {
      CreateRscriptChartSimplified(RscriptFileName,
				   PlotFileName,
				   nPromoters,
				   nIntragenics,
				   nIntergenics,
				   TrackName,
				   nLines); 
    }
  if (DETAILED)
    {
      CreateRscriptChartDetailed(RscriptFileName,
				 PlotFileName,
				 nUtr5s,
				 nUtr3s,
				 nCDSs,
				 nDistals,
				 nProximals,
				 nIntrons,
				 nIntergenics,
				 TrackName,
				 nLines);
    }
  
  /* Return the number of lines in the file */
  return(nLines);
}
  
