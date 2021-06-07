/*************************************************************************
*                                                                        *
*   Module: ProcessPeaks                                                 *
*                                                                        *
*   Process the BED peaks and find overlapping gene transcripts          *
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

extern account* m;

/* Check for intersection for a given peak and the transcripts in this chromosome */
void FindIntersections(char chr[], 
		       long pos1A,
		       long pos2A,
		       char score[],
		       transcript** Transcripts,
		       int key)
{
  /* NM coordinates */
  long pos1B;
  long pos2B;
  long i;
  
  int intersection;

  /* Visit all the transcripts in this chromosome to check for intersection */
  for(i=0; i < m->nTranscripts[key]; i++)
    {
      pos1B = Transcripts[key][i].pos1;
      pos2B = Transcripts[key][i].pos2;

      intersection = FALSE;
      
      /* CASE 1: A on the left, B on the right, overlap in the middle (pos1A<pos1B<pos2A) */
      if (pos1A <= pos1B && pos1B <= pos2A)
	{
	  intersection = TRUE;
	}
      
      /* CASE 2: B on the left, A on the right, overlap in the middle (pos1A<pos2B<pos2A) */
      if (pos1A <= pos2B && pos2B <= pos2A)
	{
	  intersection = TRUE;
	}

      /*CASE 3: A (smaller) is inside B */
      if (pos1B <= pos1A && pos2A <= pos2B)
	{
	  intersection = TRUE;
	}

      /* CASE 4: B (smaller) is inside A */
      if (pos1A <= pos1B && pos2B <= pos2A)
	{
	  intersection = TRUE;
	}

      /* If intersection, output the result */
      if (intersection == TRUE)
	OutputMatch(chr,pos1A,pos2A,score,Transcripts[key][i]);
    }
}

/* Process the BED file, annotating the intersections with transcripts + Upstream */
long ProcessPeaks(char* FileName,transcript** Transcripts, dict* ChrNames)
{
  /* File handle */
  FILE* file;
  
  /* Split every input line into several tokens <chr,size> */
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

  /* Code for the hash */
  int key;

  /* Number of lines */
  long nLines;

  char mess[MAXSTRING];


  /* 0. Open BED file to read the peaks */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The BED file can not be opened to read");

  /* 1. Reset counters */
  nLines = 0;  
  
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
	      sprintf(mess,"Skip line, unknown chromosome (%s):\n-->%s\n",chr,lineCopy);
	      printMess(mess);
	    }
	  else
	    {
	      /* Find possible overlap with gene transcripts in the catalog (in this chr) */
	      FindIntersections(chr,pos1,pos2,score,Transcripts,key);
	    }

	  /* Increase the total number of lines (peaks) */
	  nLines++;
	}
    }
  
  fclose(file);

  /* Return the number of lines in the file */
  return(nLines);
}
  
