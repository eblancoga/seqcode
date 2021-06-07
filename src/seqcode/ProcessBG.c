/*************************************************************************
*                                                                        *
*   Module: ProcessBG                                                    *
*                                                                        *
*   Process the MACS BedGraph profile                                    *
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

extern int COMPACT;

long ProcessBGFile (char *FileName, 
		    long* ChrSizes, 
		    dict* ChrNames, 
		    char* OutputFile,
		    char* TrackName)
{
  /* File handle */
  FILE* file;
  FILE* fileW;
  
  /* Split every input line into several tokens <chr,pos1,pos2,level> */
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
  int signal;

  /* Variables for compact processing */
  long length,start,end;
  int sum;
  long prevPos2;
  int prevKey;
  char prevChr[MAXCHRS];

  /* Code for the hash */
  int key;

  /* Number of lines */
  long nLines;

  char mess[MAXSTRING];


  /* 0. Open BG file to read the profile and OutputFile to write*/
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The BG file can not be opened to read");

  if ((fileW=fopen(OutputFile, "w"))==NULL)
    printError("The Output BG file can not be opened to write");

  fprintf(fileW,"track type=bedGraph name=\"%s\" description=\"%s\" visibility=\"full\" color=\"0,0,100\"\n",TrackName,TrackName);

  /* 1. Reset counters */
  nLines = 0;  
  length = 0;

  /* Init the info messages */
  printReadingInit();
  
  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Message about processing lines... */
      printReadingInfo(nLines);

      if (line[0]=='t' && line[1]=='r' && line[2]=='a' && line[3]=='c' && line[4]=='k')
	{
	  /* Skip */
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
	  if (sscanf(line4,"%d",&signal) != 1)
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
	      /* Init prevKey with the first chromosome */
	      if (nLines==1)
		{
		  prevKey = key;
		  strcpy(prevChr,chr);
		}

	      /* Check the positions in this chromosome */
	      if (pos1 < ChrSizes[key] && pos2 < ChrSizes[key])
		{
		  if (COMPACT)
		    {
		      /* Opening a new block with this line */
		      if (length==0)
			{
			  start = pos1;
			  length = pos2-pos1+1;
			  sum = signal*length;
			  prevPos2 = pos2;
			  prevKey = key;
			  strcpy(prevChr,chr);
			}
		      /* Working inside current block */
		      else
			{
			  if (prevPos2<pos1 || prevKey != key)
			    {
			      /* Closing current block in previous line */
			      sum = sum / length;
			      end = prevPos2;
			      fprintf(fileW,"%s\t%ld\t%ld\t%d\n",prevChr,start,end,sum);
				  
			      /* Opening a new block with this line */
			      start = pos1;
			      length = pos2-pos1+1;
			      sum = signal*length;
			      prevPos2 = pos2;
			      prevKey = key;
			      strcpy(prevChr,chr);
			    }
			  else
			    {
			      /* Extending the block with the current line */
			      length = length + (pos2-(pos1+1)+1);
			      sum = sum + (pos2-(pos1+1)+1)*signal;
			      prevPos2 = pos2;
			      prevKey = key;
			      strcpy(prevChr,chr);

			      /* Closing current block in this line (depending on length) */
			      if (length > COMPACTRES)
				{
				  sum = sum / length;
				  end = pos2-1;
				  fprintf(fileW,"%s\t%ld\t%ld\t%d\n",chr,start,end,sum);
				  
				  /* reset length counter for new block */
				  length=0;
				}
			    }
			}
		    }
		  else
		    {
		      fprintf(fileW,"%s\t%ld\t%ld\t%d\n",chr,pos1,pos2,signal);
		    }
		}
	      else
		{
		  /* Skip */
		}
	    }
	}	  

      /* Increase the total number of lines */
      nLines++;
    }

  fclose(file);
  fclose(fileW);

  /* Return the number of lines in the file */
  return(nLines);
}
  
