/*************************************************************************
*                                                                        *
*   Module: readargv_recoverChIPlevels                                   *
*                                                                        *
*   Read set up options and filenames from user input (recoverChIPlevels)*
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
extern int AVGL;
extern int WINDOWRES;
extern int SPIKEIN;
extern int NORM;
extern int DEMO;

/* required by getopts */
extern char* optarg;
extern int optind;

/* usage string */
char USAGE[MAXUSAGE][MAXSTRING];

void printHelp_recoverChIPlevels()
{
  fprintf(stderr,"%s\n",USAGE[0]);
  fprintf(stderr,"%s\n",USAGE[1]);
  fprintf(stderr,"%s\n",USAGE[2]);
  fprintf(stderr,"%s\n",USAGE[3]);

  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"\t-d : Demo mode for small BAM files (min number reads control off).\n");
  fprintf(stderr,"\t-l : Avg. fragment size (default: 150).\n");
  fprintf(stderr,"\t-n : Normalize using the total number of reads.\n");
  fprintf(stderr,"\t-s : Number of spike-in reads for reference-adjusted normalization (with -n).\n");
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

void readargv_recoverChIPlevels(int argc,char* argv[],
				char ChromInfoFile[FILENAMELENGTH],
				char ReadsFile[FILENAMELENGTH],
				char PeaksFile[FILENAMELENGTH],
				char UserName[FILENAMELENGTH],
				char Prefix[PREFIXLENGTH])
{
  int c;
  char mess[MAXSTRING];

  int nFiles;

  /* Adding usage messages */
  sprintf(USAGE[0],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  RECOVERCHIPLEVELS);
  sprintf(USAGE[1],
	  "NAME\n\t%s - a program to determine the ChIPseq/ATACseq/RNAseq avg/max/total counts of reads in a list of regions.\n",
	  RECOVERCHIPLEVELS);
  sprintf(USAGE[2],
	  "SYNOPSIS\n\t%s [-d][-l <bp>][-n][-s <reads>][-w <bp>][-v][-x prefix][-h]\n\t<chrom_info> <SAM file> <peaks.bed> <name> \n",RECOVERCHIPLEVELS);      
  sprintf(USAGE[3],
         "OUTPUT\n\tOne folder with 1 file:\n\t- List of peaks + counts of ChIPseq/ATACseq/RNAseq reads.\n");
  sprintf(USAGE[4],
	  "SEE ALSO\n\tSeqCode homepage: %s\n\tGitHub source code: %s\n",
	  HOMEPAGE,SOURCECODE);
  sprintf(USAGE[5],
	  "AUTHORS\n\tWritten by %s.\n",
	  AUTHORSHIP);
  sprintf(USAGE[6],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  RECOVERCHIPLEVELS);

  /* Default no prefix mode */
  strcpy(Prefix,".");
  
  /* Reading setup options */
  while ((c = getopt(argc,argv,"dl:ns:w:vx:h")) != -1)
    switch(c)
      {
      case 'd':
	DEMO++;
        break;
      case 'l':
	AVGL = atoi(optarg);
	break;
      case 'n': NORM++;
	break;
      case 's':
        SPIKEIN = atoi(optarg);
        break;
      case 'w':
        WINDOWRES = atoi(optarg);
        break;
      case 'v': VRB++;
	break;
      case 'x':
	strcpy(Prefix,optarg);
	break;
      case 'h': printHelp_recoverChIPlevels();
	break;
      }
  
  /* Setup Errors : Wrong number of filenames */
  nFiles = argc - optind;

  if (nFiles != 4)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
      
      sprintf(mess,"Four parameters are expected, %d are provided instead\n",
	      nFiles);
      printError(mess);
    }

  /* Acquire the name of the input files  */ 
  strcpy(ChromInfoFile,argv[optind]); 
  strcpy(ReadsFile,argv[optind+1]);
  strcpy(PeaksFile,argv[optind+2]);
  strcpy(UserName,argv[optind+3]);
}
