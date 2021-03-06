/*************************************************************************
*                                                                        *
*   Module: readargv_scorePhastCons                                      *
*                                                                        *
*   Read set up options and filenames from user input (scorePhastCons)   *
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
extern float THRESHOLD;
extern int WINDOWRES;

/* required by getopts */
extern char* optarg;
extern int optind;

/* usage string */
char USAGE[MAXUSAGE][MAXSTRING];

void printHelp_scorePhastCons()
{
  fprintf(stderr,"%s\n",USAGE[0]);
  fprintf(stderr,"%s\n",USAGE[1]);
  fprintf(stderr,"%s\n",USAGE[2]);
  fprintf(stderr,"%s\n",USAGE[3]);
  
  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"\t-t : Threshold to filter out predictions with PhastCons<T (default: 0).\n");
  fprintf(stderr,"\t-w : Window resolution (default: 10).\n");
  fprintf(stderr,"\t-v : Verbose. Display info messages.\n");
  fprintf(stderr,"\t-x : Prefix for the output folder.\n");
  fprintf(stderr,"\t-h : Show this help.\n");
  fprintf(stderr,"\n");

  fprintf(stderr,"%s\n",USAGE[4]);
  fprintf(stderr,"%s\n",USAGE[5]);
  fprintf(stderr,"%s\n",USAGE[6]);

  exit(0);
}

void readargv_scorePhastCons(int argc,char* argv[],
			     char ChromInfoFile[FILENAMELENGTH],
			     char RefgeneFile[FILENAMELENGTH],
			     char PhastConsFolder[FILENAMELENGTH],
			     char PeaksFile[FILENAMELENGTH],
			     char UserName[FILENAMELENGTH],
			     char Prefix[PREFIXLENGTH],
			     float* Threshold)
{
  int c;
  char mess[MAXSTRING];

  int nFiles;

  /* Adding usage messages */
  sprintf(USAGE[0],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  SCOREPHASTCONS);
  sprintf(USAGE[1],
	  "NAME\n\t%s - a program to score genomic regions with PhastCons conservation values.\n",
	  SCOREPHASTCONS);
  sprintf(USAGE[2],
	  "SYNOPSIS\n\t%s [-t <0-1>][-w <bp>][-v][-x prefix][-h]\n\t<chrom_info> <refGene.txt> <PhastCons folder> <peaks.bed> <name>\n",SCOREPHASTCONS);      
  sprintf(USAGE[3],
         "OUTPUT\n\tOne folder with 1 file:\n\t- List of peaks + scores of PhastCons.\n");
  sprintf(USAGE[4],
	  "SEE ALSO\n\tSeqCode homepage: %s\n\tGitHub source code: %s\n",
	  HOMEPAGE,SOURCECODE);
  sprintf(USAGE[5],
	  "AUTHORS\n\tWritten by %s.\n",
	  AUTHORSHIP);
  sprintf(USAGE[6],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  SCOREPHASTCONS);

  /* Default no prefix mode */
  strcpy(Prefix,".");
  
  /* Reading setup options */
  while ((c = getopt(argc,argv,"t:w:vx:h")) != -1)
    switch(c)
      {
      case 't': *Threshold = atof(optarg);
        break;
      case 'w':
        WINDOWRES = atoi(optarg);
        break;
      case 'v': VRB++;
	break;
      case 'x':
	strcpy(Prefix,optarg);
	break;
      case 'h': printHelp_scorePhastCons();
	break;
      }
  
  /* Setup Errors : Wrong number of filenames */
  nFiles = argc - optind;

  if (nFiles != 5)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
      
      sprintf(mess,"5 parameters are expected, %d are provided instead\n",
	      nFiles);
      printError(mess);
    }

  /* Acquire the name of the input files  */ 
  strcpy(ChromInfoFile,argv[optind]); 
  strcpy(RefgeneFile,argv[optind+1]);
  strcpy(PhastConsFolder,argv[optind+2]);
  strcpy(PeaksFile,argv[optind+3]);
  strcpy(UserName,argv[optind+4]);
}
