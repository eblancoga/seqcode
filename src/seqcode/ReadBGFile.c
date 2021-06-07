/*************************************************************************
*                                                                        *
*   Module: ReadBG                                                       *
*                                                                        *
*   Process the profile in BedGraph                                      *
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

long ReadBGFile (char *FileName, 
		 long* ChrSizes, 
		 dict* ChrNames, 
		 unsigned int** READS)
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
  float signal;

  /* Code for the hash */
  int key;

  /* Number of lines */
  long nLines;

  /* BG interval pointer */
  long i;

  char mess[MAXSTRING];


  /* 0. Open BG file to read the profile and OutputFile to write*/
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The BG file can not be opened to read");

  /* 1. Reset counters */
  nLines = 0;  

  /* Init the info messages */
  printReadingInit();
  
  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Message about processing lines... */
      printReadingInfo(nLines);

      if (line[0]=='t' && line[1]=='r' && line[2]=='a' && line[3]=='c' && line[4]=='k')
	{
	  sprintf(mess,"Skipping track header:\n%s",line);
	  printMess(mess);
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

	  /* There are 4 mandatory columns */
	  if (line1 == NULL || line2 == NULL || line3 == NULL || line4 == NULL)
	    {
	      sprintf(mess,"Unexpected format <chr,pos1,pos2,signal> in the line :\n-->%s\n",lineCopy);
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
	      sprintf(mess,"Wrong format in the pos1 of the BG line:\n-->%s\n",lineCopy);
	      printError(mess);
	    }
	  
	  /* Position 2 */
	  if (sscanf(line3,"%ld",&pos2) != 1)
	    {
	      sprintf(mess,"Wrong format in the pos2 of the BG line:\n-->%s\n",lineCopy);
	      printError(mess);
	    }
	  
	  /* Signal */
	  if (sscanf(line4,"%f",&signal) != 1)
	    {
	      sprintf(mess,"Wrong format in the signal of the BG line:\n-->%s\n",lineCopy);
	      printError(mess);
	    }
	  
	  /* Check limits for this chromosome */
	  key = getkeyDict(ChrNames,chr);
	  
	  if (key == NOTFOUND)
	    {
	      sprintf(mess,"Unknown chromosome in this line (skip):\n%s",lineCopy);
	      printMess(mess);
	    }
	  else
	    {
	      /* Check the positions in this chromosome */
	      if (pos1 < ChrSizes[key] && pos2 < ChrSizes[key] && (pos1 < pos2))
		{
		  /* Set the number of reads in this interval: bin correction */
		  pos1 = pos1/WINDOWRES;
		  pos2 = pos2/WINDOWRES;
		  for(i=pos1; i < pos2; i++) 
		    {
		      READS[key][i] = signal;
		    }
		}
	      else
		{
		  sprintf(mess,"Skipping line (out of limits):\n%s",lineCopy);
		  printMess(mess);
		}
	    }
	}	  

      /* Increase the total number of lines */
      nLines++;
    }

  fclose(file);

  /* Return the number of lines in the file */
  return(nLines);
}
  
