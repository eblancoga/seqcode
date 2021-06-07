/*************************************************************************
*                                                                        *
*   Module: ProcessTargetGenesGENE                                       *
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
extern int FULL;

extern account* m;

/* Process the target genes to produce the idealized gene profile */
int ProcessTargetGenesGENE(char* FileName,
			   transcript** Transcripts, 
			   dict* ChrNames,
			   long* ChrSizes,
			   dict* GeneNames,
			   int* GeneChrs,
			   int L,
			   unsigned int** READS,
			   long* UPSTREAM,
			   long* IDEALGENE,
			   long* DOWNSTREAM,
			   char* OutputFileName2,
			   long nreads)
{
  /* File handle */
  FILE* file;
  FILE* outfile;
  
  /* Split every input line into several tokens <genes,[refseq]> */
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

  long i;
  int found;

  long pos1,pos2;
  int j;
  int x;

  long* ONEGENE;
  long geneLength;
  float c;
  long pos;
  long value;

  /* Number of lines */
  long nLines;

  char mess[MAXSTRING];


  /* 0.a Open the file of target genes */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The file of target genes can not be opened to read");

  /* (optional) Generation of a second output file with the profile of each gene */
  if (FULL)
    {
      if ((outfile=fopen(OutputFileName2, "w"))==NULL)
        {
          sprintf(mess,"The output file %s for the profile of all genes can not be opened to write",
                  OutputFileName2);
          printError(mess);
        }
    }
  
  /* Request auxiliar memory for ONEGENE */
  ONEGENE = (long*) RequestMemoryRegion(MAXGENELENGTH);

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
	      /*sprintf(mess,"Processing target gene %s - transcript: %s %s %s %c %ld %ld",
		      gene,
		      Transcripts[key][i].gene,
		      Transcripts[key][i].nm,
		      Transcripts[key][i].chr,
		      Transcripts[key][i].strand,
		      Transcripts[key][i].pos1,
		      Transcripts[key][i].pos2);
		      printMess(mess); */
	      
	      /* Retrieve the strand/coordinates of this transcript and update the UPS/ID/DOWNS */
	      if (Transcripts[key][i].strand=='+')
		{
		  pos1 = Transcripts[key][i].pos1;
		  pos2 = Transcripts[key][i].pos2;
		  geneLength = pos2 - pos1 +1;

		  /* Control: Out of range? */
		  if ((pos1-L)/WINDOWRES<0 || (pos2+L+1)/WINDOWRES>=ChrSizes[key] || geneLength<L)
		    {
		      /* Warning for L: printRes(gene); */
		    }
		  else
		    {
		      /* Print the gene name (web servers) */
		      if (FULL)
			{
			  fprintf(outfile,"%s ",gene);
			}
		      
		      /* A. Update the UPSTREAM region */
		      for(i=(pos1-L)/WINDOWRES,j=0; i<(pos1/WINDOWRES); i++, j=j+WINDOWRES)
			{
			  for(x=j; x<j+WINDOWRES; x++)
                            {
			      UPSTREAM[x] = UPSTREAM[x] + READS[key][i];

			      if (FULL)
                                {
                                  fprintf(outfile,"%.1f ",(float)READS[key][i]/(nreads/MEGA));
                                }
			    }			
			}
		      
		      /* B. Updating the IDEAL GENE */
		      /* Compute the TMPGENE region */
		      for(i=pos1/WINDOWRES,j=0; i<=(pos2/WINDOWRES); i++, j=j+WINDOWRES)
			{
			  for(x=j; x<j+WINDOWRES; x++)
                            {
			      ONEGENE[x] = READS[key][i];
			    }     
			}

		      /* Fractioning the real gene into L parts */
		      c = (float)geneLength/(float)L;

		      /* pos is the index over IGENE, i is the index over OGENE */
		      for(pos=0; pos<L; pos++)
			{
			  value = 0;
			  for(i=(int)(pos*c),j=0; j< (int)c; i++,j++)
			    {
			      value = value + ONEGENE[i];
			    }

			  IDEALGENE[pos] = IDEALGENE[pos] + value/(int)c;

			  if (FULL)
			    {
			      fprintf(outfile,"%.1f ",((float)value/(int)c)/(nreads/MEGA));
			    }
			}

		      /* C. Update the DOWNSTREAM region */
		      for(i=(pos2+1)/WINDOWRES,j=0; i<(pos2+L+1)/WINDOWRES; i++, j=j+WINDOWRES)
			{
			  for(x=j; x<j+WINDOWRES; x++)
                            {
			      DOWNSTREAM[x] = DOWNSTREAM[x] + READS[key][i];

			      if (FULL)
                                {
                                  fprintf(outfile,"%.1f ",(float)READS[key][i]/(nreads/MEGA));
                                }
			    }			
			}

		      /* D. Final end of line character */
		      if (FULL)
			{
			  fprintf(outfile,"\n");
                        }
		      
		      /* Increase the total number of genes that were used to build the profile */
		      nLines++;
		    }
		}
	      else
		{
		  pos1 = Transcripts[key][i].pos1;
		  pos2 = Transcripts[key][i].pos2;
		  geneLength = pos2 - pos1 +1;
		  
		  /* Control: Out of range? */
		  if ((pos1-L)/WINDOWRES<0 || (pos2+L+1)/WINDOWRES>=ChrSizes[key] || geneLength<L)
		    {
		      /* Warning for L: printRes(gene); */
		    }
		  else
		    {
		      /* Print the gene name (web servers) */
		      if (FULL)
			{
			  fprintf(outfile,"%s ",gene);
			}

		      /* A. Update the UPSTREAM region */
		      for(i=(pos2+L+1)/WINDOWRES,j=0; i>(pos2/WINDOWRES); i--, j=j+WINDOWRES)
			{
			  for(x=j; x<j+WINDOWRES; x++)
                            {
			      UPSTREAM[x] = UPSTREAM[x] + READS[key][i];
			      
			      if (FULL)
                                {
                                  fprintf(outfile,"%.1f ",(float)READS[key][i]/(nreads/MEGA));
                                }
			    }			
			}

		      /* B. Updating the IDEAL GENE */
		      /* Compute the TMPGENE region */
		      for(i=pos2/WINDOWRES,j=0; i>=pos1/WINDOWRES; i--, j=j+WINDOWRES)
			{
			  for(x=j; x<j+WINDOWRES; x++)
                            {
			      ONEGENE[x] = READS[key][i];
			    }
			}

		      /* Fractioning the real gene into L parts */
		      c = (float)geneLength/(float)L;

		      /* pos is the index over IGENE, i is the index over OGENE */
		      for(pos=0; pos<L; pos++)
			{
			  value = 0;
			  for(i=(int)(pos*c),j=0; j< (int)c; i++,j++)
			    {
			      value = value + ONEGENE[i];
			    }
			  
			  IDEALGENE[pos] = IDEALGENE[pos] + value/(int)c;

			  if (FULL)
			    {
			      fprintf(outfile,"%.1f ",((float)value/(int)c)/(nreads/MEGA));
			    }
			}

		      /* C. Update the DOWNSTREAM region */
		      for(i=(pos1-1)/WINDOWRES,j=0; i>(pos1-L)/WINDOWRES; i--, j=j+WINDOWRES)
			{
			  for(x=j; x<j+WINDOWRES; x++)
                            {
			      DOWNSTREAM[x] = DOWNSTREAM[x] + READS[key][i];
			      
			      if (FULL)
                                {
                                  fprintf(outfile,"%.1f ",(float)READS[key][i]/(nreads/MEGA));
                                }
			    }     
			}

		      /* D. Final end of line character */
		      if (FULL)
			{
			  fprintf(outfile,"\n");
                        }
		      
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

  if (FULL)
    {
      fclose(outfile);
    }
    
  /* Return the number of lines in the file */
  return(nLines);
}
  
