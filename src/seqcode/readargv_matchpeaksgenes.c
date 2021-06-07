/*************************************************************************
*                                                                        *
*   Module: readargv_matchpeaksgenes                                     *
*                                                                        *
*   Read set up options and filenames from user input (matchpeaksgenes)  *
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

/* SeqCode external vars */
extern int VRB, UPS, DOW, NUPS, NDOW, TSS, TES;

/* required by getopts */
extern char* optarg;
extern int optind;

/* usage string */
char USAGE[MAXUSAGE][MAXSTRING];

void printHelp_matchpeaksgenes()
{
  fprintf(stderr,"%s\n",USAGE[0]);
  fprintf(stderr,"%s\n",USAGE[1]);
  fprintf(stderr,"%s\n",USAGE[2]);
  fprintf(stderr,"%s\n",USAGE[3]);

  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"\t-u : Use X bp upstream of the TSS, including gene body.\n");
  fprintf(stderr,"\t-d : Use X bp downstream of the TES, including gene body.\n");
  fprintf(stderr,"\t-U : Use X bp upstream of the TSS, excluding gene body.\n");
  fprintf(stderr,"\t-D : Use X bp downstream of the TES, excluding gene body.\n");
  fprintf(stderr,"\t-s : Use only +/- X bp around the TSS.\n");
  fprintf(stderr,"\t-e : Use only +/- X bp around the TES.\n");
  fprintf(stderr,"\t-v : Verbose. Display info messages.\n");
  fprintf(stderr,"\t-h : Show this help.\n");
  fprintf(stderr,"\n");

  fprintf(stderr,"%s\n",USAGE[4]);
  fprintf(stderr,"%s\n",USAGE[5]);
  fprintf(stderr,"%s\n",USAGE[6]);

  exit(0);
}

void readargv_matchpeaksgenes (int argc,char* argv[],
			       char* PeaksFile, 
			       char* RefgeneFile,
			       int* Upstream,
			       int* Downstream,
			       int* TSSrange,
			       int* TESrange)
{
  int c;
  char mess[MAXSTRING];

  int nFiles;


  /* Initial distances */
  *Upstream = 0;
  *Downstream = 0;
  *TESrange = 0;

  /* Adding usage messages */
  sprintf(USAGE[0],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  MATCHPEAKSGENES);
  sprintf(USAGE[1],
	  "NAME\n\t%s - a program to match peaks to genes.\n",
	  MATCHPEAKSGENES);
  sprintf(USAGE[2],
	  "SYNOPSIS\n\t%s [-udUDse <value>][-v][-h]\n\t<peaks.bed> <refGene.txt>\n",
	  MATCHPEAKSGENES);
  sprintf(USAGE[3],
	  "OUTPUT\n\tList of matches (STDOUT). Each line is a peak associated to a transcript.\n");
  sprintf(USAGE[4],
	  "SEE ALSO\n\tSeqCode homepage: %s\n\tGitHub source code: %s\n",
	  HOMEPAGE,SOURCECODE);
  sprintf(USAGE[5],
	  "AUTHORS\n\tWritten by %s.\n",
	  AUTHORSHIP);
  sprintf(USAGE[6],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  MATCHPEAKSGENES);

  /* Reading setup options */
  while ((c = getopt(argc,argv,"u:d:U:D:s:e:vh")) != -1)
    switch(c)
      {
      case 'u': *Upstream = atoi(optarg);
	UPS++;
	break;
      case 'd': *Downstream = atoi(optarg);
	DOW++;
	break;
      case 'U': *Upstream = atoi(optarg);
	NUPS++;
	break;
      case 'D': *Downstream = atoi(optarg);
	NDOW++;
	break;
      case 's': *TSSrange = atoi(optarg);
	TSS++;
	break;
      case 'e': *TESrange = atoi(optarg);
	TES++;
	break;
      case 'v': VRB++;
	break;
      case 'h': printHelp_matchpeaksgenes();
	break;
      }
  
  /* Setup Errors : Wrong number of filenames */
  nFiles = argc - optind;

  if (nFiles != 2)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"2 parameters are expected, %d are provided instead\n",
	      nFiles);
      printError(mess);
    }

  /* Acquire the name of the three input files  */ 
  strcpy(PeaksFile,argv[optind]); 
  strcpy(RefgeneFile,argv[optind+1]);

  /* Control of errors */
  if (UPS && *Upstream <=0)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"Upstream must be positive (%d)\n", *Upstream);
      printError(mess);
    }

  if (DOW && *Downstream <=0)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"Downstream must be positive (%d)\n", *Downstream);
      printError(mess);
    }

  if (TSS && *TSSrange <=0)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
      
      sprintf(mess,"TSSrange must be positive (%d)\n", *TESrange);
      printError(mess);
    }
  
  if (TES && *TESrange <=0)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"TESrange must be positive (%d)\n", *TESrange);
      printError(mess);
    }

  if (((TSS || TES) && (UPS || DOW)) || (UPS && NUPS) || (DOW && NDOW))
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"Incompatible options\n");
      printError(mess);
    }
}
