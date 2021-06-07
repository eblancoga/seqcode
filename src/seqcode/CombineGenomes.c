/*************************************************************************
*                                                                        *
*   Module: CombineGenomes                                               *
*                                                                        *
*   Process two SAM read files to count reads on the Bg profile          *
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
extern int MINUSSTRAND;

extern account* m;

/* Process the genome to build the BedGraph profile */
int CombineGenomes(dict* ChrNames,
		   long* ChrSizes,
		   unsigned int** READS1,
		   unsigned int** READS2,
		   char* TrackName1,
		   char* TrackName2,
		   char* TrackColor,
		   char* OutputFileName,
		   long nreads1,
		   long nreads2)
{
  /* File handle */
  FILE* outfile;

  /* Number of chromosomes into the BG file */
  long nChromosomes;

  int i;
  node *p;
  long j;
  float normfactor1,normfactor2;
  long startpos;
  float value,value1,value2;
  long limitSearch;

  char mess[MAXSTRING];


  /* 0. Prepare the output file to print the BG records */
  if ((outfile=fopen(OutputFileName, "w"))==NULL)
    {
      sprintf(mess,"The BG profile output file %s can not be opened to write",
	      OutputFileName);
      printError(mess);
    }

  /* UCSC BedGraph track header */
  fprintf(outfile,"track type=bedGraph name=%s-%s description=%s-%s visibility=full color=%s\n",
	  TrackName1,TrackName2,TrackName1,TrackName2,TrackColor);
  
  /* 1. Reset counters */
  nChromosomes = 0;
  normfactor1 = (float)nreads1/MEGA;
  normfactor2 = (float)nreads2/MEGA;
  
  /* 2. Visit the chromosomes in the dictionary to retrieve and normalize the profiles */ 
  for(i=0 ; i < MAXENTRY ; i++)
    {
      if(ChrNames->T[i]!=NULL)     
	{
	  /* Explore the nodes in this position */
	  p = ChrNames->T[i];
	  
	  /* Searching the first position free */
	  while( p!= NULL )
	    {
	      /* Accessing current chromosome */
	      sprintf(mess,
		      "Processing chromosome %s (%d) - %ld",
		      p->s,
		      p->key,
		      ChrSizes[p->key]/WINDOWRES);
	      printRes(mess);
	      
	      /* Retrieve the ending position of this chromosome */
	      limitSearch = ChrSizes[p->key]/WINDOWRES;
	      for(j=0; j<limitSearch; j++)
		{
		  startpos = (j*WINDOWRES) +1;
		  value1 = READS1[p->key][j]/normfactor1;
		  value2 = READS2[p->key][j]/normfactor2;
		  value = value1 - value2;

		  if (value!=0)
		    {
		      if (MINUSSTRAND)
			{
			  fprintf(outfile,"%s\t%ld\t%ld\t%.2f\n",
				  p->s,
				  startpos,startpos+WINDOWRES-1,
				  -value);
			}
		      else
			{
			  fprintf(outfile,"%s\t%ld\t%ld\t%.2f\n",
				  p->s,
				  startpos,startpos+WINDOWRES-1,
				  value);
			}
		    }
		}
	      
		  /* Next chromosome in this position */
	      nChromosomes++;
	      p = p->next;
	    }
	}
    }    

  fclose(outfile);
  
  /* Return the number of chromosomes */
  return(nChromosomes);
}
  
