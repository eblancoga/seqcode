/*************************************************************************
*                                                                        *
*   Module: readargv_matchpeaks                                          *
*                                                                        *
*   Read set up options and filenames from user input (matchpeaks)       *
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
extern int VRB;
extern int OSIZE;

/* required by getopts */
extern char* optarg;
extern int optind;

/* usage string */
char USAGE[MAXUSAGE][MAXSTRING];

void printHelp_matchpeaks()
{
  fprintf(stderr,"%s\n",USAGE[0]);
  fprintf(stderr,"%s\n",USAGE[1]);
  fprintf(stderr,"%s\n",USAGE[2]);
  fprintf(stderr,"%s\n",USAGE[3]);

  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"\t-l : Minimum overlap size (default: 1).\n");
  fprintf(stderr,"\t-v : Verbose. Display info messages.\n");
  fprintf(stderr,"\t-h : Show this help.\n");
  fprintf(stderr,"\t-x : Prefix for the output folder.\n");
  fprintf(stderr,"\n");

  fprintf(stderr,"%s\n",USAGE[4]);
  fprintf(stderr,"%s\n",USAGE[5]);
  fprintf(stderr,"%s\n",USAGE[6]);

  exit(0);
}

void readargv_matchpeaks (int argc,char* argv[],
			  char* PeaksFileA, 
			  char* PeaksFileB,
			  char* NameA,
			  char* NameB,
			  char Prefix[PREFIXLENGTH])
{
  int c;
  char mess[MAXSTRING];

  int nFiles;

  /* Adding usage messages */
  sprintf(USAGE[0],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  MATCHPEAKS);
  sprintf(USAGE[1],
	 "NAME\n\t%s - a program to compare 2 lists of peaks/regions.\n",
	  MATCHPEAKS);
  sprintf(USAGE[2],
	 "SYNOPSIS\n\t%s [-l <bp>][-v][-x prefix][-h]\n\t<peaksA.bed> <peaksB.bed> <nameA> <nameB>\n",
	 MATCHPEAKS);
  sprintf(USAGE[3],
	 "OUTPUT\n\tOne folder with 3 files (BED): common in both, only in A, only in B.\n");
    sprintf(USAGE[4],
	  "SEE ALSO\n\tSeqCode homepage: %s\n\tGitHub source code: %s\n",
	  HOMEPAGE,SOURCECODE);
  sprintf(USAGE[5],
	  "AUTHORS\n\tWritten by %s.\n",
	  AUTHORSHIP);
  sprintf(USAGE[6],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  MATCHPEAKS);

  /* Default no prefix mode */
  strcpy(Prefix,".");
  
  /* Reading setup options */
  while ((c = getopt(argc,argv,"l:vx:h")) != -1)
    switch(c)
      {
      case 'l':
        OSIZE = atoi(optarg);
        break;
      case 'v': VRB++;
	break;
      case 'x':
	strcpy(Prefix,optarg);
	break;
      case 'h': printHelp_matchpeaks();
	break;
      }
  
  /* Setup Errors : Wrong number of filenames */
  nFiles = argc - optind;

  if (nFiles != 4)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,
	      "4 parameters are expected, %d are provided instead\n",
	      nFiles);
      printError(mess);
    }

  /* Acquire the name of the three input files  */ 
  strcpy(PeaksFileA,argv[optind]); 
  strcpy(PeaksFileB,argv[optind+1]);
  strcpy(NameA,argv[optind+2]);
  strcpy(NameB,argv[optind+3]);

  /* Control for overlap size */
  if (OSIZE<1)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"Overlap size must be a positive value\n");
      printError(mess);
    }
}
