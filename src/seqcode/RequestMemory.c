/*************************************************************************
*                                                                        *
*   Module: RequestMemory                                                *
*                                                                        *
*   Asking operating system for memory for data structures               *
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

/* Allocating accounting data structure in memory */
account* RequestMemoryAccounting()
{
  account* m; 

  if ((m = (account *) malloc(sizeof(account))) == NULL)
	printError("Not enough memory: account");

  return(m);
}

/* Allocate the array to store the size of each chromosome */
long* RequestMemoryChrSizes()
{
  long* v;

  if ((v =(long *) calloc(MAXCHRS, sizeof(long))) == NULL)
    printError("Not enough memory: ChrSizes array");

  /* Update total memory stats */
  m->nMemory = m->nMemory + MAXCHRS*sizeof(long);

  return(v);
}

/* Allocate the dictionary of chromosome names */
dict * RequestMemoryDictionary()
{
  dict* d;

  if ((d = (dict *)malloc(sizeof(dict))) == NULL)
    printError("Not enough memory: dictionary of Chromosome names");

  resetDict(d);

  /* Update total memory stats */
  m->nMemory = m->nMemory + sizeof(dict);

  return(d);
}

/* Allocate the matrix for the coordinates of transcripts in separate chrs */
transcript** RequestMemoryTranscripts()
{
  transcript** v;
  int i;

  /* First dimension of the matrix: CHRS */
  if ((v =(transcript **) calloc(MAXCHRS,sizeof(transcript*))) == NULL)
	  printError("Not enough memory: Transcripts matrix (CHRS)");

  /* Second dimension of the matrix: TRANSCRIPTS */
  for(i=0;i<MAXCHRS;i++)
    {
      if ((v[i] =(transcript *) calloc(MAXTRANSCRIPTS, sizeof(transcript))) == NULL)
	printError("Not enough memory: Transcripts matrix (TRANSCRIPTS)");
    }

  /* Update total memory stats */
  m->nMemory = m->nMemory + MAXCHRS*sizeof(transcript);

  return(v);
}

/* Allocate the matrix to store the coordinates of all peaks in separate chrs */
peak** RequestMemoryPeaks()
{
  peak** v;
  int i;

  /* First dimension of the matrix: CHRS */
  if ((v =(peak **) calloc(MAXCHRS,sizeof(peak*))) == NULL)
	  printError("Not enough memory: Peaks matrix (MAXCHRS)");

  /* Second dimension of the matrix: PEAKS */
  for(i=0;i<MAXCHRS;i++)
    {
      if ((v[i] =(peak *) calloc(MAXPEAKS, sizeof(peak))) == NULL)
	printError("Not enough memory: Peaks matrix (MAXPEAKS)");
    }

  /* Update total memory stats */
  m->nMemory = m->nMemory + MAXCHRS*sizeof(peak);

  return(v);
}

/* Allocate the array to store the chr of each gene */
int* RequestMemoryGeneChrs()
{
  int* v;

  if ((v =(int *) calloc(MAXGENES, sizeof(int))) == NULL)
    printError("Not enough memory: GeneChrs array");

  /* Update total memory stats */
  m->nMemory = m->nMemory + MAXGENES*sizeof(int);

  return(v);
}

/* Allocate the array to store the avg. profile of reads */
long* RequestMemoryRegion(int L)
{
  long* v;

  if ((v =(long *) calloc(2*L, sizeof(long))) == NULL)
    printError("Not enough memory: REGION array");

  /* Update total memory stats */
  m->nMemory = m->nMemory + 2*L*sizeof(long);

  return(v);
}

