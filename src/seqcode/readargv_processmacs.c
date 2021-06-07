/*************************************************************************
*                                                                        *
*   Module: readargv_processmacs                                         *
*                                                                        *
*   Read set up options and filenames from user input                    *
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
extern int COMPACT;

/* required by getopts */
extern char* optarg;
extern int optind;

/* usage string */
char USAGE[MAXUSAGE][MAXSTRING];

void printHelp_processmacs()
{
  fprintf(stderr,"%s\n",USAGE[0]);
  fprintf(stderr,"%s\n",USAGE[1]);
  fprintf(stderr,"%s\n",USAGE[2]);
  fprintf(stderr,"%s\n",USAGE[3]);

  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"\t-c : Compact averaged BedGraph profile.\n");
  fprintf(stderr,"\t-v : Verbose. Display info messages.\n");
  fprintf(stderr,"\t-h : Show this help.\n");
  fprintf(stderr,"\n");

  fprintf(stderr,"%s\n",USAGE[4]);
  fprintf(stderr,"%s\n",USAGE[5]);
  fprintf(stderr,"%s\n",USAGE[6]);

  exit(0);
}

void readargv_processmacs(int argc,char* argv[],
			  char* ChromInfoFile, 
			  char* MACSFile,
			  char* OutputFile,
			  char* UserName)
{
  int c;
  char mess[MAXSTRING];

  int nFiles;

  /* Adding usage messages */
  sprintf(USAGE[0],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  PROCESSMACS);
  sprintf(USAGE[1],
	  "NAME\n\t%s - a program to clean MACS BedGraph profiles.\n",
	  PROCESSMACS);
  sprintf(USAGE[2],
	  "SYNOPSIS\n\t%s [-c][-v][-h]\n\t<chrom_info> <bedgraph.gzip> <output name> <track name>\n",PROCESSMACS);
  sprintf(USAGE[3],
	  "OUTPUT\n\tBedGraph processed profile.\n");
  sprintf(USAGE[4],
	  "SEE ALSO\n\tSeqCode homepage: %s\n\tGitHub source code: %s\n",
	  HOMEPAGE,SOURCECODE);
  sprintf(USAGE[5],
	  "AUTHORS\n\tWritten by %s.\n",
	  AUTHORSHIP);
  sprintf(USAGE[6],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  PROCESSMACS);

  /* Reading setup options */
  while ((c = getopt(argc,argv,"cvh")) != -1)
    switch(c)
      {
      case 'c': COMPACT++;
	break;
      case 'v': VRB++;
	break;
      case 'h': printHelp_processmacs();
	break;
      }
  
  /* Setup Errors : Wrong number of filenames */
  nFiles = argc - optind;

  if (nFiles != 4)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
  
      sprintf(mess,"Four names are expected, %d names are provided instead",
	      nFiles);
      printError(mess);
    }

  /* Acquire the name of the four input files  */ 
  strcpy(ChromInfoFile,argv[optind]); 
  strcpy(MACSFile,argv[optind+1]);
  strcpy(OutputFile,argv[optind+2]);
  strcpy(UserName,argv[optind+3]);
}
