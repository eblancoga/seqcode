/*************************************************************************
*                                                                        *
*   Module: ProcessTargetGenes                                           *
*                                                                        *
*   Process target genes to accumulate reads on the avg. profile         *
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
extern account* m;

/* Process the genes in the refGene file: find the MAX ChIP signal */
int ProcessGenesMax(char RefgeneFile[FILENAMELENGTH],
		    transcript** Transcripts, 
		    dict* ChrNames,
		    long* ChrSizes,
		    dict* GeneNames,
		    int* GeneChrs,
		    int Upstream,
		    unsigned int** READS)
{
  /* File handle */
  FILE* file;

  /* Split every input line into several tokens <chr,size> */
  char line[MAXLINE];
  char *line1;
  char *line2;
  char *line3;
  char *line4;
  char *line5;
  char *line6;
  char *line7;
  char *line8;
  char *line9;
  char *line10;
  char *line11;
  char *line12;
  char *line13;

  /* Backup line */
  char lineCopy[MAXLINE];
  
  /* Values */
  char gene[MAXGENENAME];
  char nm[MAXGENENAME];

  /* Code for the hash */
  int key;
  int keyGene;

  long i;
  long iGene;
  int found;

  long tss;
  long end;
  int j;

  /* Number of lines */
  long nLines;

  char mess[MAXSTRING];

  int max;
  float avg;


 /* 0. Open the file of target genes */
  if ((file=fopen(RefgeneFile, "r"))==NULL)
    printError("The file of target genes can not be opened to read");

  /* 1. Reset counters */
  nLines = 0;  
  
  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Backup copy of the line to show error messages */
      strcpy(lineCopy,line);

      /* Extracting values of current line: */
      line1 = (char *) strtok(line,TAB);
      line2 = (char *) strtok(NULL,TAB);
      line3 = (char *) strtok(NULL,TAB);
      line4 = (char *) strtok(NULL,TAB);
      line5 = (char *) strtok(NULL,TAB);
      line6 = (char *) strtok(NULL,TAB);
      line7 = (char *) strtok(NULL,TAB);
      line8 = (char *) strtok(NULL,TAB);
      line9 = (char *) strtok(NULL,TAB);
      line10 = (char *) strtok(NULL,TAB);
      line11 = (char *) strtok(NULL,TAB);
      line12 = (char *) strtok(NULL,TAB);
      line13 = (char *) strtok(NULL,TAB);

      /* There are 13 mandatory columns */
      if (line1 == NULL || line2 == NULL
          || line3 == NULL || line4 == NULL
          || line5 == NULL || line6 == NULL
          || line7 == NULL || line8 == NULL
          || line9 == NULL || line10 == NULL
          || line11 == NULL || line12 == NULL
          || line13 == NULL)
        {
          sprintf(mess,"Unexpected format for refGene.txt files (line %ld):\n-->%s\n",
                  nLines,lineCopy);
          printMess(mess);
        }

      /* F2: Transcript code */
      if (sscanf(line2,"%s",nm) != 1)
        {
          sprintf(mess,"Wrong format in the RefSeq NM transcript code:\n-->%s\n",lineCopy);
          printError(mess);
        }

     /* F13: Gene name */
      if (sscanf(line13,"%s",gene) != 1)
        {
          sprintf(mess,"Wrong format in the gene symbol name:\n-->%s\n",lineCopy);
          printError(mess);
        }

      /* Verification: this gene is registered into our dictionary? */
      keyGene = getkeyDict(GeneNames,gene);
      if (keyGene == NOTFOUND)
	{
	  sprintf(mess,"Skip line, unknown gene name:\n-->%s\n",lineCopy);
	  printMess(mess);
	}
      else
	{
	  /* Identify in which chromosome the gene is */
	  key = GeneChrs[keyGene];

	  /* Search this transcript of this gene to access their coordinates */
	  found = FALSE;
	  i=0;
	  while (i<m->nTranscripts[key] && !found)
	    {
	      if (!strcmp(nm,Transcripts[key][i].nm))
		{
		  found = TRUE;
		}
	      else
		{
		  i++;
		}
	    }

	  if (found)
	    {
	      /* Copy the position of this transcript for this gene */
	      iGene = i;

	      /* sprintf(mess,"Processing RefSeq gene %s \n\t\t transcript: %s %s %s %c %ld %ld",
		      gene,
		      Transcripts[key][i].gene,
		      Transcripts[key][i].nm,
		      Transcripts[key][i].chr,
		      Transcripts[key][i].strand,
		      Transcripts[key][i].pos1,
		      Transcripts[key][i].pos2);
		      printMess(mess); */

	      /* Retrieve the strand/coordinates of this transcript to search the MAX */
	      if (Transcripts[key][i].strand=='+')
		{
		  tss = Transcripts[key][i].pos1;
		  end = Transcripts[key][i].pos2+1;

		  /* Control: Out of range? */
		  if (tss-Upstream<0 || end>=ChrSizes[key])
		    {
		      printMess("Skipping this gene: potentially out of range in this chromosome");
		    }
		  else
		    {
		      /* Search the MAX in this region */
		      max = NOSIGNAL;
		      avg = 0;
		      for(i=(tss-Upstream)/WINDOWRES,j=0; i<end/WINDOWRES; i++, j++)
			{
			  avg = avg + READS[key][i];
			  max = MAX(max,READS[key][i]);
			}
		      
		      /* Compute the avg. value */
		      avg = avg / j;
		      OutputGeneAvgMax(Transcripts[key][iGene],avg,max);

		      /* Increase the total number of genes that were used to build the profile */
		      nLines++;
		    }
		}
	      else
		{
		  tss = Transcripts[key][i].pos2;
		  end = Transcripts[key][i].pos1;

		  /* Control: Out of range? */
		  if (end<0 || (tss+Upstream)>=ChrSizes[key])
		    {
		      printMess("Skipping this gene: potentially out of range in this chromosome");
		    }
		  else
		    {
		      /* Search the MAX in this region */
		      max = NOSIGNAL;
		      avg = 0;
		      for(i=(tss+Upstream)/WINDOWRES,j=0; i>end/WINDOWRES; i--, j++)
			{
			  avg = avg + READS[key][i];
			  max = MAX(max,READS[key][i]);
			}	

		      /* Compute the avg. value */
		      avg = avg / j;
		      OutputGeneAvgMax(Transcripts[key][iGene],avg,max);

		      /* Increase the total number of genes that were used to build the profile */
		      nLines++;
		    }
		}
	    }
	  else
	    {
	      sprintf(mess,"Skip line, no transcripts were found for this gene name:\n-->%s\n",lineCopy);
	      printMess(mess);
	    }
	}
      
    }
  
  fclose(file);

  /* Return the number of lines in the file */
  return(nLines);
}
  
