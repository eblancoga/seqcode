/*************************************************************************
*                                                                        *
*   Module: ProcessPeaksLists                                            *
*                                                                        *
*   Process two lists of peaks to mark the intersected peaks             *
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

extern int OSIZE;

/* Check for intersection between two peaks */
int CompareTwoPeaks(peak A, peak B)
{
  /* Peaks coordinates */
  long pos1A,pos2A;
  long pos1B,pos2B;
  int intersection;
  int size;
  
  intersection = FALSE;

  /* Values for the comparison */
  pos1A = A.pos1;
  pos2A = A.pos2;

  pos1B = B.pos1;
  pos2B = B.pos2;

  /* CASE 1: A on the left, B on the right, overlap in the middle (pos1A<pos1B<pos2A) */
  if (pos1A <= pos1B && pos1B <= pos2A)
    {
      intersection = TRUE;
      size = pos2A - pos1B + 1;
    }
  
  /* CASE 2: B on the left, A on the right, overlap in the middle (pos1A<pos2B<pos2A) */
  if (pos1A <= pos2B && pos2B <= pos2A)
    {
      intersection = TRUE;
      size = pos2B - pos1A + 1;
    }
  
  /*CASE 3: A (smaller) is inside B */
  if (pos1B <= pos1A && pos2A <= pos2B)
    {
      intersection = TRUE;
      size = pos2A - pos1A + 1;
    }
  
  /* CASE 4: B (smaller) is inside A */
  if (pos1A <= pos1B && pos2B <= pos2A)
    {
      intersection = TRUE;
      size = pos2B - pos1B + 1;
    }

  /* Control of minimum size to accept the overlap */
  if (intersection == TRUE && size < OSIZE)
    {
      intersection = FALSE;
    }
  
  return(intersection);
}

/* Process both lists of peaks to mark the intersected peaks */
void ProcessPeaksLists(peak** PeaksA, peak** PeaksB, dict* ChrNames,char* NameA)
{
  
  /* Code for the hash */
  int lastkey;

  /* Number of elements to visit */
  int i;
  long j,k;

  /* Intersection boolean */
  int intersection;

  /* Messages */
  char mess[MAXSTRING];


  /* Identify the last key used in the dictionary of chromosomes */
  lastkey = ChrNames->nextFree;

  /* 1. Visit all available chromosomes */
  for(i=0; i < lastkey; i++)
    {
      sprintf(mess,"Running %ld peaks of %s in chromosome key %d", 
	      m->nPeaksA[i],NameA,i);
      printRes(mess);

      /* 2. Visit chromosome i */
      for(j=0; j < m->nPeaksA[i]; j++)
	{
	  /* 3. Comparison against the other list of peaks in this chr */
	  for(k=0; k < m->nPeaksB[i]; k++)
	    {
	      intersection = CompareTwoPeaks(PeaksA[i][j],PeaksB[i][k]);
	      
	      if (intersection == TRUE)
		{
		  /* 4. Mark both peaks as a positive intersection */
		  PeaksA[i][j].used = TRUE;
		  PeaksB[i][k].used = TRUE;
		}
	    }
	}
    }
}
  
