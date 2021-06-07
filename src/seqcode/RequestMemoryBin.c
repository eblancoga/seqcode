/*************************************************************************
*                                                                        *
*   Module: RequestMemoryBin                                             *
*                                                                        *
*   Asking operating system for memory for SAM reads                     *
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

extern int WINDOWRES;

/* Allocate the matrix to store the number of reads on each position */
unsigned int** RequestMemoryREADS(long* ChrSizes, dict* ChrNames)
{
  unsigned int** v;
  int i;
  long size;
  int lastkey;

  
  /* First dimension of the matrix: CHRS */
  if ((v =(unsigned int**) calloc(MAXCHRS,sizeof(unsigned int*))) == NULL)
    printError("Not enough memory: READS matrix (CHRS)");
  
  /* Second dimension of the matrix: Chromosome positions */
  lastkey = ChrNames->nextFree;

  /* allocation of the actual size of each chromosome */
  for(i=0; i < lastkey; i++)
    {
      size = (ChrSizes[i]/WINDOWRES) + EXTRAMEM;
      
      if ((v[i] =(unsigned int*) calloc(size, sizeof(unsigned int))) == NULL)
	printError("Not enough memory: unsigned int matrix (READS)");

      m->nMemory = m->nMemory + size*sizeof(unsigned int);
    }

  return(v);
}

/* Allocate the matrix to store the number of reads on each position */
float** RequestMemoryPHASTCONS(long* ChrSizes, dict* ChrNames)
{
  float** v;
  int i;
  long size;
  int lastkey;

  
  /* First dimension of the matrix: CHRS */
  if ((v =(float**) calloc(MAXCHRS,sizeof(float*))) == NULL)
    printError("Not enough memory: PHASTCONS matrix (CHRS)");
  
  /* Second dimension of the matrix: Chromosome positions */
  lastkey = ChrNames->nextFree;

  /* allocation of the actual size of each chromosome */
  for(i=0; i < lastkey; i++)
    {
      size = (ChrSizes[i]/WINDOWRES) + EXTRAMEM;
      
      if ((v[i] =(float*) calloc(size, sizeof(float))) == NULL)
	printError("Not enough memory: float matrix (PHASTCONS)");

      m->nMemory = m->nMemory + size*sizeof(float);
    }

  return(v);
}
