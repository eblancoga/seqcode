/*************************************************************************
*                                                                        *
*   Module: account                                                      *
*                                                                        *
*   Accounting: results and run-time stats                               *
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

/* Init accounting (processmacs) */
account* InitAcc()
{
  account* m; 
  int i;

  /* Request memory to allocate accounting data */
  m = (account*) RequestMemoryAccounting();

  printMess("Reset accounting data");

  /* Reset counters */
  m->nChrs = 0;
  m->nLines = 0;

  for(i=0;i<MAXCHRS;i++)
    m->nTranscripts[i]=0;

  m->nPeaks = 0;
  m->nTotalTranscripts = 0;

  for(i=0;i<MAXCHRS;i++)
    m->nPeaksA[i]=0;

  for(i=0;i<MAXCHRS;i++)
    m->nPeaksB[i]=0;

  m->nTotalPeaksA = 0;
  m->nTotalPeaksB = 0;

  m->nReads=0;
  m->nFwdReads=0;
  m->nRvsReads=0;

  m->nReads1=0;
  m->nFwdReads1=0;
  m->nRvsReads1=0;

  m->nReads2=0;
  m->nFwdReads2=0;
  m->nRvsReads2=0;

  /* Reset memory account (bytes) */
  m->nMemory=0;

  /* Starting the count (running time) */
  /* Real time */
  (void) time(&m->tStart);

  /* CPU time */
  clock();

  return(m);
}
