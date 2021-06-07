/*************************************************************************
*                                                                        *
*   Module: ReadProcessPeaksMaps                                         *
*                                                                        *
*   Reading BED file to generate a heat map of peaks                     *
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

long ReadProcessPeaksMaps(char* FileName,
		      long* ChrSizes,
		      dict* ChrNames,
		      int L,
		      unsigned int** READS,
		      char* OutputFileName2,
		      char* OutputFileName3,
		      long nreads)
{
  /* File handle */
  FILE *file;
  FILE *outfile;
  FILE* outfileH;
    
  /* Total number of peaks in the file */
  int nPeaks;

  /* Split every input line into several tokens <chr,pos1,pos2,group> */
  char line[MAXLINE];
  char *line1;
  char *line2;
  char *line3;
  char *line4;

  /* Backup line */
  char lineCopy[MAXLINE];
  
  /* Values */
  char chr[MAXCHRNAME];
  long pos1;
  long pos2;
  char score[MAXSTRING];

  /* Code for the hash */
  int key;

  /* Reads of each gene */
  long* AUXREGION;
  char peakname[MAXGENENAME];

  long i;
  long maxCenter;
  int maxReads;
  int j;

  char mess[MAXSTRING];

  /* 0. Open BED file to read the information */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The BED file can not be opened to read");
  
  /* Prepare to write the output file with the center in column 4 */
  if ((outfile=fopen(OutputFileName2, "w"))==NULL)
    {
      sprintf(mess,"The centered-BED file output file %s can not be opened to write",
	      OutputFileName2);
      printError(mess);
    }

  if ((outfileH=fopen(OutputFileName3, "w"))==NULL)
    {
      sprintf(mess,"The heatmap profile output file %s can not be opened to write",
	      OutputFileName3);
      printError(mess);
    }
  
  /* Request auxiliary memory */
  AUXREGION = (long*) RequestMemoryRegion(((2*L)/WINDOWRES)+1);


  /* 1. Reset counters */
  nPeaks = 0;  
  
  /* Init the info messages */
  printReadingInit();

  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Message about processing lines... */
      printReadingInfoSmall(nPeaks);
     
      if (line[0]=='t' && line[1]=='r' && line[2]=='a' && line[3]=='c' && line[4]=='k')
        {
          /* Skip this line */
        }
      else
        {
	  /* Backup copy of the line to show error messages */
	  strcpy(lineCopy,line);
	  
	  /* Extracting values of current line: BED format */
	  line1 = (char *) strtok(line,TAB);
	  line2 = (char *) strtok(NULL,TAB);
	  line3 = (char *) strtok(NULL,TAB);
	  line4 = (char *) strtok(NULL,TAB);
	  
	  /* There are 3 mandatory columns: score is optional */
	  if (line1 == NULL || line2 == NULL || line3 == NULL)
	    {
	      sprintf(mess,"Unexpected format for <chr,pos1,pos2,score> in the line :\n-->%s\n",lineCopy);
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
	  
	  /* Register this chromosome name into the dictionary (if necessary) */
	  key = getkeyDict(ChrNames,chr);
	  if (key == NOTFOUND)
	    {
	      key = setkeyDict(ChrNames,chr);
	    }
	  
	  /* Control: Out of range? */
	  if ((pos1-L)/WINDOWRES<0 || (pos2+L)/WINDOWRES>=ChrSizes[key]/WINDOWRES)
	    {
	      /* sprintf(mess,"Peak not useful: %s\n",lineCopy);
		 printRes(mess); */
	    }
	  else
	    {
	      /* Search the center of the current peak (max ChIP signal) */
	      maxCenter = 0;
	      maxReads = 0;
	      for(i=(pos1-L)/WINDOWRES; i<(pos2+L)/WINDOWRES; i++)
		{
		  if (READS[key][i]>maxReads)
		    {
		      maxCenter = i;
		      maxReads = READS[key][i];
		    }
		}

	      /* Correcting to obtain the real position in the genome */
	      maxCenter = maxCenter*WINDOWRES;
		      
	      /* Update this PEAK region */
	      for(i=(maxCenter-L)/WINDOWRES,j=0; i<(maxCenter+L)/WINDOWRES; i++, j=j+WINDOWRES)
		{
		  /* peak heatmap plot*/
		  AUXREGION[i-((maxCenter-L)/WINDOWRES)] = READS[key][i];
		}

	      /* save the max point (center) and the number of reads in the outputfile2.bed */
	      fprintf(outfile,
		      "%s\t%ld\t%ld\t%s\t%ld\t%d\n",
		      chr,pos1,pos2,score,maxCenter,maxReads);

	      /* Identify the current peak */
	      sprintf(peakname,"peak_%d",nPeaks);
	      
	      /* Output this peak into the HEAT matrix output file */
	      OutputOneGeneHeatFile(peakname,
				    AUXREGION,
				    L,nreads,
				    outfileH); 
	      
	      /* (info) Increase the total number of transcripts in the file */
	      nPeaks++;
	    }
	}
    }

  fclose(file);
  fclose(outfile);
  fclose(outfileH);

  /* Return the number of distinct transcripts in the file */
  return(nPeaks);
}
  
