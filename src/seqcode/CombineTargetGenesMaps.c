/*************************************************************************
*                                                                        *
*   Module: CombineTargetGenesMaps                                       *
*                                                                        *
*   Combine target genes to generate heat maps                           *
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

/* Process target genes to produce the TSS heat maps */
int CombineTargetGenesMaps(char* FileName,
			   transcript** Transcripts, 
			   dict* ChrNames,
			   long* ChrSizes,
			   dict* GeneNames,
			   int* GeneChrs,
			   int L,
			   unsigned int** READS1,
			   unsigned int** READS2,
			   char* OutputFileName2,
			   long nreads1,
			   long nreads2)
{
  /* File handle */
  FILE* file;
  FILE* outfile;
  
  /* Split every input line into several tokens <gene,[refseq]> */
  char line[MAXLINE];
  char *line1;
  char *line2;

  /* Backup line */
  char lineCopy[MAXLINE];
  
  /* Values */
  char gene[MAXGENENAME];
  char nmcode[MAXGENENAME];

  /* Code for the hash */
  int key;
  int keyGene;

  /* Reads of each gene */
  long* AUXREGION;

  long i;
  int found;

  long tss;
  int j;

  float value,value1,value2;
  
  /* Number of lines */
  long nLines;

  char mess[MAXSTRING];


  /* 0. Open the file of target genes */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The file of target genes can not be opened to read");

  if ((outfile=fopen(OutputFileName2, "w"))==NULL)
    {
      sprintf(mess,"The heatmap profile output file %s can not be opened to write",
	      OutputFileName2);
      printError(mess);
    }
      
  /* Request auxiliary memory */
  AUXREGION = (long*) RequestMemoryRegion(((2*L)/WINDOWRES)+1);

  /* 1. Reset counters */
  nLines = 0;  
 
  printRes("List of non-available genes:");
 
  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Backup copy of the line to show error messages */
      strcpy(lineCopy,line);

      /* Extracting values of current line: gene [+ nmcode] */
      line1 = (char *) strtok(line,TAB);
      line2 = (char *) strtok(NULL,TAB);

      /* Store the gene name */
      if (sscanf(line1,"%s",gene) != 1)
        {
          sprintf(mess,"Wrong format in the gene symbol name:\n-->%s\n",lineCopy);
          printError(mess);
        }
      
      /* Store the transcript RefSeq code (NM), if available */
      if (line2 == NULL)
        {
          strcpy(nmcode,NMNULL);
        }
      else
        {
          if (sscanf(line2,"%s",nmcode) != 1)
            {
              sprintf(mess,"Wrong format in the transcript code:\n-->%s\n",lineCopy);
              printError(mess);
            }
        }
      
      /* Verification: this gene is registered into our dictionary? */
      keyGene = getkeyDict(GeneNames,gene);
      if (keyGene == NOTFOUND)
        {
          printRes(gene);
        }
      else
        {
          /* Identify in which chromosome the gene is */
          key = GeneChrs[keyGene];

          /* Retrieve the information for this gene */
          i=0;
          found = FALSE;
          if (!strcmp(nmcode,NMNULL))
            {
              /* (a) Select arbitrarily one transcript */
              while (i<m->nTranscripts[key] && !found)
                {
                  if (!strcmp(gene,Transcripts[key][i].gene))
                    {
                      found = TRUE;
                    }
                  else
                    {
                      i++;
                    }
                }
            }
	  else
            {
              /* (b) Select the transcript provided in the line */
              while (i<m->nTranscripts[key] && !found)
                {
                  if (!strcmp(nmcode,Transcripts[key][i].nm))
                    {
                      found = TRUE;
                    }
                  else
                    {
                      i++;
                    }
                }
            }

	  if (found)
	    {
	      /* sprintf(mess,">>>>>>>>> Processing gene %s - transcript: %s %s %s %c %ld %ld",
		      gene,
		      Transcripts[key][i].gene,
		      Transcripts[key][i].nm,
		      Transcripts[key][i].chr,
		      Transcripts[key][i].strand,
		      Transcripts[key][i].pos1,
		      Transcripts[key][i].pos2);
		      printMess(mess); */

	      /* Retrieve the strand/coordinates of this transcript to generate the AUXREGION */
	      if (Transcripts[key][i].strand=='+')
		{
		  tss = Transcripts[key][i].pos1;

		  /* Control: Out of range? */
		  if ((tss-L)/WINDOWRES<0 || (tss+L)/WINDOWRES>=ChrSizes[key]/WINDOWRES)
		    {
		      printRes(gene);
		    }
		  else
		    {
		      /* Update the gene individual map row */
		      for(i=(tss-L)/WINDOWRES,j=0; i<(tss+L)/WINDOWRES; i++, j=j+WINDOWRES)
			{
			  value1 = READS1[key][i];
			  value2 = READS2[key][i];
			  value1 = (value1>0)?log10(value1):0;
			  value2 = (value2>0)?log10(value2):0;
			  value = value1 - value2;

			  AUXREGION[i-((tss-L)/WINDOWRES)] = value;
			}

		      /* Output this gene into the HEAT matrix output file */
		      OutputOneGeneCombinedHeatFile(gene,
						    AUXREGION,
						    L,
						    outfile); 

		      /* Increase the total number of genes that were used to build the profile */
		      nLines++;
		    }
		}
	      else
		{
		  tss = Transcripts[key][i].pos2;

		  /* Control: Out of range? */
		  if ((tss-L)/WINDOWRES<0 || (tss+L)/WINDOWRES>=ChrSizes[key]/WINDOWRES)
		    {
		      printRes(gene);
		    }
		  else
		    {
		      /* Update the gene individual map row */
		      for(i=(tss+L)/WINDOWRES,j=0; i>(tss-L)/WINDOWRES; i--, j=j+WINDOWRES)
			{
			  value1 = READS1[key][i];
			  value2 = READS2[key][i];
			  value1 = (value1>0)?log10(value1):0;
			  value2 = (value2>0)?log10(value2):0;
			  value = value1 - value2;
			  
			  AUXREGION[((tss+L)/WINDOWRES)-i] = value;
			}		  
		      
		      /* Output this gene into the HEAT matrix output file */
		      OutputOneGeneCombinedHeatFile(gene,
						    AUXREGION,
						    L,
						    outfile);

		      /* Increase the total number of genes that were used to build the profile */
		      nLines++;
		    }
		}
	    }
	  else
	    {
	      printRes(gene);
	    }
	}
      
    }
  
  fclose(file);
  fclose(outfile);

  /* Return the number of lines in the file */
  return(nLines);
}
  
