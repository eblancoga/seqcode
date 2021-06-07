/*************************************************************************
*                                                                        *
*   Module: ReadChrFile                                                  *
*                                                                        *
*   Reading Chr Size file                                                *
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

extern int VRB;

void OutputChrSizes(long* ChrSizes, int nChrs)
{
  int i;

  if (VRB)
    {
      fprintf(stderr,"\t\t\tChromosome sizes:\n");
      for(i=0; i<nChrs; i++)
	{
	  fprintf(stderr,"\t\t\t%-20d | \t\t\t %ld\n", i, ChrSizes[i]);
	}
    }
}

int ReadChrFile (char *FileName, long* ChrSizes, dict* ChrNames)
{
  /* File handle */
  FILE *file;
  
  /* Number of distinct chromosome names into the file */
  int nChrs;

  /* Split every input line into several tokens <chr,size> */
  char line[MAXLINE];
  char *line1;
  char *line2;

  /* Backup line */
  char lineCopy[MAXLINE];
  
  /* Values */
  char chr[MAXCHRNAME];
  long size;

  /* Code for the hash */
  int key;

  char mess[MAXSTRING];


  /* 0. Open ChrSize file to read the information */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The ChrSize file can not be opened to read");
  
  /* 1. Reset counters */
  nChrs = 0;  
  
  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Backup copy of the line to show error messages */
      strcpy(lineCopy,line);
		  
      /* Extracting values of current line: only using field1 and field2 */
      line1 = (char *) strtok(line,TAB);
      line2 = (char *) strtok(NULL,TAB);
		  
      /* There are 2 mandatory columns */
      if (line1 == NULL || line2 == NULL)
	{
	  sprintf(mess,"Unexpected format <chr,size> in the line :\n-->%s\n",lineCopy);
	  printError(mess);
	}
      
      /* Name of the Chromosome */
      if (sscanf(line1,"%s",chr) != 1)
	{
	  sprintf(mess,"Wrong format in the chromosome name:\n-->%s\n",lineCopy);
	  printError(mess);
	}
      
      /* Size of the Chromosome */
      if (sscanf(line2,"%ld",&size) != 1)
	{
	  sprintf(mess,"Wrong format in the size of the chromosome:\n-->%s\n",lineCopy);
	  printError(mess);
	}
      
      /* Register this chromosome name into the dictionary */
      key = setkeyDict(ChrNames,chr);
      
      /* Store this size for this chromosome name */
      ChrSizes[key] = size;

      /* Increase the total number of available chromosomes */
      nChrs++;
    }
  
  fclose(file);

  /* Show the content of the chromosome dictionary */
  showDict(ChrNames);

  /* Show the size of each chromosome */
  OutputChrSizes(ChrSizes,nChrs);
  
  /* Return the number of distinct chromosome names in the file */
  return(nChrs);
}
  
