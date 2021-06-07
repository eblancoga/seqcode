/*************************************************************************
*                                                                        *
*   Module: ProcessGenomePeaks                                           *
*                                                                        *
*   Process SAM reads to find regions above a predefined number of reads *
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
extern float T;

extern account* m;

/* Process the BED file, annotating the intersections with transcripts + Upstream */
int ProcessGenomePeaks(dict* ChrNames,
		       long* ChrSizes,
		       unsigned int** READS,
		       char* TrackName,
		       char* OutputFileName,
		       long nreads)
{
  /* File handle */
  FILE* outfile;

  /* Number of chromosomes into the file */
  long nChromosomes;

  int i;
  node *p;
  long j;
  float normfactor;
  long startpos;
  float value;
  long limitSearch;

  char mess[MAXSTRING];


  /* 0. Prepare the output file to print the BED regions */
  if ((outfile=fopen(OutputFileName, "w"))==NULL)
    {
      sprintf(mess,"The BED output file %s can not be opened to write",
	      OutputFileName);
      printError(mess);
    }

  /* UCSC Bed track header */
  fprintf(outfile,"track name=%s description=%s visibility=dense color=50,50,50\n",
	  TrackName,TrackName);
  
  /* 1. Reset counters */
  nChromosomes = 0;  
  normfactor = (float)nreads/MEGA;
  
  /* 2. Visit the chromosomes in the dictionary to call the peaks */ 
  for(i=0; i < MAXENTRY; i++)
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
		      ChrSizes[p->key]);
	      printRes(mess);
	      
	      /* Retrieve the ending position of this chromosome */
	      limitSearch = ChrSizes[p->key]/WINDOWRES;

	      for(j=0; j<limitSearch; j++)
		{
		  startpos = (j*WINDOWRES) +1;
		  value = READS[p->key][j]/normfactor;

		  /* A peak is a region above T normalized reads */
		  if (value>T)
		    {
		      fprintf(outfile,"%s\t%ld\t%ld\t%.2f\n",
			      p->s,
			      startpos,
			      startpos+WINDOWRES-1,
			      value);
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
  
