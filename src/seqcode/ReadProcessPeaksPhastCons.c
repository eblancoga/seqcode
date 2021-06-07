/*************************************************************************
*                                                                        *
*   Module: ReadProcessPeaksPhastCons                                    *
*                                                                        *
*   Reading BED regions to assign the average PhastCons score            *
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

long ReadProcessPeaksPhastCons(char* FileName,
			       long* ChrSizes,
			       dict* ChrNames,
			       float** PHASTCONS,
			       unsigned int** EXONS,
			       char* OutputFileName)
{
  /* File handle */
  FILE *file;
  FILE* outfile;
    
  /* Total number of peaks in the file */
  int nPeaks;

  /* Split every input line into several tokens <chr,size> */
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

  long i;
  float avgScore;
  float maxScore;

  long lengthPeak;

  int exonic;

  char mess[MAXSTRING];

  /* 0. Open BED file to read the information */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The BED file can not be opened to read");

  /* Prepare to write the output file: BED + avg score + max score */
  if ((outfile=fopen(OutputFileName, "w"))==NULL)
    {
      sprintf(mess,"The BED file (+ avg/max PhastCons score) output file %s can not be opened to write",
              OutputFileName);
      printError(mess);
    }
  
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
	  
	  /* Search this chromosome name into the dictionary */
	  key = getkeyDict(ChrNames,chr);
	  if (key == NOTFOUND)
	    {
	      sprintf(mess,"Skipping this peak, chromosome not found:\n-->%s\n",lineCopy);
	      printMess(mess);
	    }
	  else
	    {
	      /* Control: Out of range? */
	      if ((pos1/WINDOWRES)<0 || (pos2/WINDOWRES)>=(ChrSizes[key]/WINDOWRES))
		{
		  sprintf(mess,"Skipping this peak, potentially out of range in this chromosome:\n-->%s\n",lineCopy);
		  printMess(mess);
		}
	      else
		{
		  avgScore = 0;
		  maxScore = 0;
		  lengthPeak = 0;
		  exonic = FALSE;
		  for(i=pos1/WINDOWRES; i<=pos2/WINDOWRES; i++)
		    {
		      /* Calculate the average/max ChIP signal */
		      avgScore = avgScore + PHASTCONS[key][i];
		      
		      if (PHASTCONS[key][i]>maxScore)
			{
			  maxScore = PHASTCONS[key][i];
			}
		      lengthPeak++;
		      
		      /* Check the overlap with refGene exons */
		      if(EXONS[key][i])
			{
			  exonic = TRUE;
			}
		    }
		  
		  avgScore = avgScore / lengthPeak;
		  
		  /* display the output peak information in the outputfile.bed */
		  if (exonic == TRUE)
		    {
		      fprintf(outfile,"%s\t%ld\t%ld\t%s\t%.2f\t%.2f\tEXON\n",chr,pos1,pos2,score,avgScore,maxScore);
		    }
		  else
		    {
		      fprintf(outfile,"%s\t%ld\t%ld\t%s\t%.2f\t%.2f\n",chr,pos1,pos2,score,avgScore,maxScore);
		    }
		  
		  /* (info) Increase the total number of peaks in the file */
		  nPeaks++;
		}
	    } 
	}
    }

  fclose(file);
  fclose(outfile);
 
  /* Return the number of peaks in the file */
  return(nPeaks);
}
  
