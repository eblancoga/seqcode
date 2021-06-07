/*************************************************************************
*                                                                        *
*   Module: matchpeaksgenes                                              *
*                                                                        *
*   MatchPeaksGenes main program                                         *
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

/************************************************************************
                            ENVIRONMENTAL variables
************************************************************************/

/* Verbose flag (memory/processing information) */
int VRB=0;

/* Analyze upstream sequence of the TSS + gene body */
int UPS=0;

/* Analyze upstream sequence of the TSS - no gene body */
int NUPS=0;

/* Analyze downstream sequence of the TES + gene body */
int DOW=0;

/* Analyze downstream sequence of the TES - no gene body */
int NDOW=0;

/* Analyze sequence around of the TSS (left/right) */
int TSS=0;

/* Analyze sequence around of the TES (left/right) */
int TES=0;

/* Spike-in normalization */
int SPIKEIN = 0;

/* Accounting time and results */
account *m;

/************************************************************************
                            MAIN program
************************************************************************/

int main (int argc, char *argv[])
{
  char PeaksFile[FILENAMELENGTH], 
    RefgeneFile[FILENAMELENGTH];

  int Upstream,
    Downstream,
    TSSrange,
    TESrange;
  
  dict* ChrNames;

  transcript** Transcripts;

  char mess[MAXSTRING];

  long FileSize;

  
  /** 0. Starting and reading options, parameters and sequence... **/
  
  /* 0.a. Initializing stats and time counters */
  m = (account*) InitAcc();  

  /* 0.b. Read setup options */
  readargv_matchpeaksgenes(argc,argv,
			   PeaksFile,
			   RefgeneFile,
			   &Upstream,&Downstream,
			   &TSSrange,&TESrange);
  printSeqCodeHeader(MATCHPEAKSGENES);
  StartingTime(mess,m);
  printMess(mess);

  /* 1. Allocating data structures */
  printMess("1. Request Memory to Operating System");
  Transcripts = (transcript**) RequestMemoryTranscripts();
  ChrNames = (dict *) RequestMemoryDictionary();

  /*2. Read the Refgene file */
  printMess("2. Reading Refgene file");
  FileSize = GetFileSize(RefgeneFile);
  sprintf(mess,"%s: %.2lf Mb",RefgeneFile,(float)FileSize/MEGABYTE);
  printRes(mess);

  m->nTotalTranscripts = ReadRefgeneFile(RefgeneFile,Transcripts,
					 Upstream,Downstream,
					 TSSrange,TESrange,
					 ChrNames);
  sprintf(mess,"%ld transcripts of RefSeq were successfully acquired",m->nTotalTranscripts);
  printRes(mess);

  /*3. Process the Peaks to identify neighbouring genes */
  printMess("3. Processing the Peaks BED file");
  FileSize = GetFileSize(PeaksFile);
  sprintf(mess,"%s: %.2lf Mb",PeaksFile,(float)FileSize/MEGABYTE);
  printRes(mess);
  
  m->nPeaks = ProcessPeaks(PeaksFile,Transcripts,ChrNames);
  sprintf(mess,"\n\t%ld peaks were successfully processed",m->nPeaks);
  printRes(mess);

  /* 4. The End */
  OutputTime(m);  
  
  exit(0);
  return(0);
}
