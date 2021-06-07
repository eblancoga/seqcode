/*************************************************************************
*                                                                        *
*   Module: readargv_computemaxsignal                                    *
*                                                                        *
*   Read set up options and filenames from user input (computemaxsignal) *
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
extern int WINDOWRES;
extern int UPS;
extern int ZIP;

/* required by getopts */
extern char* optarg;
extern int optind;

/* usage string */
char USAGE[MAXUSAGE][MAXSTRING];

void printHelp_computemaxsignal()
{
  fprintf(stderr,"%s\n",USAGE[0]);
  fprintf(stderr,"%s\n",USAGE[1]);
  fprintf(stderr,"%s\n",USAGE[2]);
  fprintf(stderr,"%s\n",USAGE[3]);

  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"\t-u : Include X bp upstream of the TSS.\n");
  fprintf(stderr,"\t-w : Window resolution (default: 10).\n");
  fprintf(stderr,"\t-z : Input profile is unzipped.\n");
  fprintf(stderr,"\t-v : Verbose. Display info messages.\n");
  fprintf(stderr,"\t-h : Show this help.\n");
  fprintf(stderr,"\n");

  fprintf(stderr,"%s\n",USAGE[4]);
  fprintf(stderr,"%s\n",USAGE[5]);
  fprintf(stderr,"%s\n",USAGE[6]);

  exit(0);
}

void readargv_computemaxsignal (int argc,char* argv[],
				char ChromInfoFile[FILENAMELENGTH],
				char RefgeneFile[FILENAMELENGTH],
				char ProfileFile[FILENAMELENGTH],
				int* Upstream)
{
  int c;
  char mess[MAXSTRING];

  int nFiles;

  /* Adding usage messages */
  sprintf(USAGE[0],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  COMPUTEMAXSIGNAL);
  sprintf(USAGE[1],
	  "NAME\n\t%s - a program to calculate the max signal for genes in one genome-wide profile.\n",
	  COMPUTEMAXSIGNAL);
  sprintf(USAGE[2],
	  "SYNOPSIS\n\t%s [-u <bp>][-w <bp>][-z][-v][-h] <chrom_info> <refGene.txt> <bedgraph.gz>\n",
	  COMPUTEMAXSIGNAL);
  sprintf(USAGE[3],
          "OUTPUT\n\tList of average and max number of reads of each RefSeq transcript.\n");
  sprintf(USAGE[4],
	  "SEE ALSO\n\tSeqCode homepage: %s\n\tGitHub source code: %s\n",
	  HOMEPAGE,SOURCECODE);
  sprintf(USAGE[5],
	  "AUTHORS\n\tWritten by %s.\n",
	  AUTHORSHIP);
  sprintf(USAGE[6],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  COMPUTEMAXSIGNAL);
  
  /* Reading setup options */
  while ((c = getopt(argc,argv,"u:w:zvh")) != -1)
    switch(c)
      {
      case 'u': *Upstream = atoi(optarg);
        UPS++;
        break;
      case 'w':
        WINDOWRES = atoi(optarg);
        break;
      case 'z': ZIP++;
	break;
      case 'v': VRB++;
	break;
      case 'h': printHelp_computemaxsignal();
	break;
      }
  
  /* Setup Errors : Wrong number of filenames */
  nFiles = argc - optind;

  if (nFiles != 3)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,
              "3 parameters are expected, %d are provided instead",
              nFiles);
      printError(mess);
    }

  /* Acquire the name of the input files  */ 
  strcpy(ChromInfoFile,argv[optind]); 
  strcpy(RefgeneFile,argv[optind+1]);
  strcpy(ProfileFile,argv[optind+2]);

  /* Control for upstream length */
  if (UPS && *Upstream <=0)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"Upstream must be positive (%d)\n", *Upstream);
      printError(mess);
    }
}
