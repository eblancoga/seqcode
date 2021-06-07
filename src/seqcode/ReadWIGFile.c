/*************************************************************************
*                                                                        *
*   Module: ReadWIG                                                      *
*                                                                        *
*   Reads the PhastCons profiles in WIG format                           *
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

long ReadWIGFile (char *FileName, 
		 long* ChrSizes, 
		 dict* ChrNames, 
		 float** PHASTCONS)
{
  /* File handle */
  FILE* file;
  
  /* Split every input line into several tokens */
  char line[MAXLINE];
  char* line1;
  char* line2;
  char* line3;
  char* line4;

  /* Backup line */
  char lineCopy[MAXLINE];
  
  /* Values */
  char chr[MAXCHRS];
  long start;
  long pos;
  int step;
  float score;

  /* Code for the hash */
  int key;

  /* Number of lines */
  long nLines;

  char mess[MAXSTRING];


  /* 0. Open WIG file to read the profile and OutputFile to write*/
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The WIG file can not be opened to read");

  /* 1. Reset counters */
  nLines = 0;  

  /* Init the info messages */
  printReadingInit();
  
  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Message about processing lines... */
      printReadingInfo(nLines);

      /* Skip track header */
      if (line[0]=='t' && line[1]=='r' && line[2]=='a' && line[3]=='c' && line[4]=='k')
	{
	  sprintf(mess,"Skipping track header:\n%s",line);
	  printMess(mess);
	}
      else
	{
	  /* Backup copy of the line to show error messages */
	  strcpy(lineCopy,line);

	  /* Extract the chromosome from variableStep header */
	  if (line[0]=='f' && line[1]=='i' && line[2]=='x' && line[3]=='e' && line[4]=='d')
	    {
	      /* Extracting (chr) from: fixedStep chrom=(chr) start=(start) step=(step) */
	      line1 = (char *) strtok(line,SPACE);
	      line2 = (char *) strtok(NULL,SPACE);
	      line3 = (char *) strtok(NULL,SPACE);
	      line4 = (char *) strtok(NULL,SPACE);

	      /* chromosome */
	      line1 = (char *) strtok(line2,sEQ);
	      line1 = (char *) strtok(NULL,sEQ);
	      
	      if (sscanf(line1,"%s",chr) != 1)
		{
		  sprintf(mess,"Wrong format in the chromosome header:\n-->%s\n",lineCopy);
		  printError(mess);
		}

	      /* start position */
	      line1 = (char *) strtok(line3,sEQ);
	      line1 = (char *) strtok(NULL,sEQ);

	      if (sscanf(line1,"%ld",&start) != 1)
		{
		  sprintf(mess,"Wrong format in the start of the WIG line:\n-->%s\n",lineCopy);
		  printError(mess);
		}
	      
	      /* step */
	      line1 = (char *) strtok(line4,sEQ);
	      line1 = (char *) strtok(NULL,sEQ);

	      if (sscanf(line1,"%d",&step) != 1)
		{
		  sprintf(mess,"Wrong format in the step of the WIG line:\n-->%s\n",lineCopy);
		  printError(mess);
		}
	      
	      /* Search the key for this chromosome */
	      key = getkeyDict(ChrNames,chr);
	      
	      if (key == NOTFOUND)
		{
		  sprintf(mess,"Unknown chromosome in this line (skip):\n%s",lineCopy);
		  printMess(mess);
		}
	      
	      /* Starting the count of positions in the current segment */
	      pos = start;
	    }
	  else
	    {
	      /* Backup copy of the line to show error messages */
	      strcpy(lineCopy,line);
	      
	      /* Extracting values of current line: only using field1 and field2 */
	      line1 = (char *) strtok(line,SPACE);
	      line2 = (char *) strtok(NULL,SPACE);
	      
	      /* There is 1 mandatory column */
	      if (line1 == NULL)
		{
		  sprintf(mess,"Unexpected format <pos> in the line :\n-->%s\n",lineCopy);
		  printError(mess);
		}
	      
	      /* Score */
	      if (sscanf(line1,"%f",&score) != 1)
		{
		  sprintf(mess,"Wrong format in the score of the WIG line:\n-->%s\n",lineCopy);
		  printError(mess);
		}

	      /* Check limits for this chromosome */
	      key = getkeyDict(ChrNames,chr);

	      /* Speed up rules: not checking for positions out of boundaries */
	      PHASTCONS[key][pos/WINDOWRES] = score;

	      /* Updating the next position */
	      pos = pos + step;
	    }	 
	} 

      /* Increase the total number of lines */
      nLines++;
    }

  fclose(file);

  /* Return the number of lines in the file */
  return(nLines);
}
