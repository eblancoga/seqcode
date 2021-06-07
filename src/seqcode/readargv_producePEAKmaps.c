/*************************************************************************
*                                                                        *
*   Module: readargv_producePEAKmaps                                     *
*                                                                        *
*   Read set up options and filenames from user input (producePEAKmaps)  *
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
extern float NOISET;
extern float COLORIZE;
extern int DEMO;
extern char BGCOLOR[MAXCOLORNAME];
extern char FGCOLOR[MAXCOLORNAME];
extern char FGCOLORB[MAXCOLORNAME];
extern char GBGCOLOR[MAXCOLORNAME];
extern char GFGCOLOR[MAXCOLORNAME];
extern char HBGCOLOR[MAXCOLORNAME];

/* required by getopts */
extern char* optarg;
extern int optind;

/* usage string */
char USAGE[MAXUSAGE][MAXSTRING];

void printHelp_producePEAKmaps()
{
  fprintf(stderr,"%s\n",USAGE[0]);
  fprintf(stderr,"%s\n",USAGE[1]);
  fprintf(stderr,"%s\n",USAGE[2]);

  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"\t-b : Background or color1 (default: white).\n");
  fprintf(stderr,"\t-B : General background color (default: white).\n");
  fprintf(stderr,"\t-d : Demo mode for small BAM files (min number reads control off).\n");
  fprintf(stderr,"\t-f : Foreground or color2 (default: black).\n");
  fprintf(stderr,"\t-F : General foreground color (default: black).\n");
  fprintf(stderr,"\t-H : Heatmap background color (default: white).\n");
  fprintf(stderr,"\t-i : Increase the color intensity (default: 0).\n");
  fprintf(stderr,"\t-l : Avg. fragment size (default: 150).\n");
  fprintf(stderr,"\t-n : Normalize using the total number of reads.\n");
  fprintf(stderr,"\t-s : Number of spike-in reads for reference-adjusted normalization.\n");
  fprintf(stderr,"\t-t : Noise reduction cutoff (default: 1.5).\n");
  fprintf(stderr,"\t-w : Window resolution (default: 100).\n");
  fprintf(stderr,"\t-v : Verbose. Display info messages.\n");
  fprintf(stderr,"\t-x : Prefix for the output folder.\n");
  fprintf(stderr,"\t-h : Show this help.\n");
  fprintf(stderr,"\n");

  fprintf(stderr,"%s\n",USAGE[4]);
  fprintf(stderr,"%s\n",USAGE[5]);
  fprintf(stderr,"%s\n",USAGE[6]);

  exit(0);
}

void readargv_producePEAKmaps (int argc,char* argv[],
			       char ChromInfoFile[FILENAMELENGTH],
			       char ReadsFile[FILENAMELENGTH],
			       char PeaksFile[FILENAMELENGTH],
			       char UserName[USERNAMELENGTH],
			       char Prefix[PREFIXLENGTH],
			       int* L)
{
  int c;
  char mess[MAXSTRING];

  int nFiles;


  sprintf(USAGE[0],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  PRODUCEPEAKMAPS);
  sprintf(USAGE[1],
          "NAME\n\t%s - a program to produce ChIPseq/ATACseq/RNAseq heat maps centered in a list of peaks.\n",
          PRODUCEPEAKMAPS);
  sprintf(USAGE[2],
          "SYNOPSIS\n\t%s [-bBfFH <Rcolor>][-d][-i <real>][-l <bp>][-n][-s <reads>][-t <value>][-w <bp>][-v][-x prefix][-h]\n\t<chrom_info> <SAM file> <peaks.bed> <name> <length>\n",
          PRODUCEPEAKMAPS);
  sprintf(USAGE[3],
         "OUTPUT\n\tOne folder with 5 files:\n\t- Numerical distribution of reads.\n\t- Numerical distribution of reads (processed).\n\t- Ranking of peaks in the map.\n\t- R script commands.\n\t- Graphical representation (R is required).\n");
  sprintf(USAGE[4],
	  "SEE ALSO\n\tSeqCode homepage: %s\n\tGitHub source code: %s\n",
	  HOMEPAGE,SOURCECODE);
  sprintf(USAGE[5],
	  "AUTHORS\n\tWritten by %s.\n",
	  AUTHORSHIP);
  sprintf(USAGE[6],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  PRODUCEPEAKMAPS);

  
  /* Default background/foreground colors */
  strcpy(BGCOLOR,"white");
  strcpy(FGCOLOR,"black");
  strcpy(FGCOLORB,"black");
  strcpy(GBGCOLOR,"white");
  strcpy(GFGCOLOR,"black");
  strcpy(HBGCOLOR,"white");

  /* Default no prefix mode */
  strcpy(Prefix,".");

  /* Reading setup options */
  while ((c = getopt(argc,argv,"b:B:f:F:H:i:l:dns:t:w:vx:h")) != -1)
    switch(c)
      {
      case 'b':
        strcpy(BGCOLOR,optarg);
        break;
      case 'B':
        strcpy(GBGCOLOR,optarg);
        break;
      case 'd':
	DEMO++;
        break;
      case 'f':
        strcpy(FGCOLOR,optarg);
        break;
      case 'F':
        strcpy(GFGCOLOR,optarg);
        break;
      case 'H':
	strcpy(HBGCOLOR,optarg);
	break;
      case 'i':	
	COLORIZE= atof(optarg);
	break;
      case 'l':
	AVGL = atoi(optarg);
	break;
      case 'n': NORM++;
        break;
      case 's':
        SPIKEIN = atoi(optarg);
        break;
      case 't':
        NOISET= atof(optarg);
        break;
      case 'w':
        WINDOWRES = atoi(optarg);
        break;
      case 'v': VRB++;
	break;
      case 'x':
	strcpy(Prefix,optarg);
	break;
      case 'h': printHelp_producePEAKmaps();
	break;
      }
  
  /* Setup Errors : Wrong number of filenames */
  nFiles = argc - optind;

  if (nFiles != 5)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
      
      sprintf(mess,"Five parameters are expected, %d are provided instead\n",
	      nFiles);
      printError(mess);
    }

  /* Setup Errors : Normalization incompatible options */
  if (NORM>0 && SPIKEIN>0)
    {
      sprintf(mess,"The normalization options -n and -s cannot be activated simultaneously\n");	      
      printError(mess);
    }
  
  /* Acquire the name of the input files  */ 
  strcpy(ChromInfoFile,argv[optind]); 
  strcpy(ReadsFile,argv[optind+1]);
  strcpy(PeaksFile,argv[optind+2]);
  strcpy(UserName,argv[optind+3]);

  /* Length of the region to be plotted */
  *L = atoi(argv[optind+4]); 

  /* Control for min and max length */
  if (*L < MINLENGTH || *L > MAXLENGTH)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
      
      sprintf(mess,"Length must be a value between %d and %d\n",
	      MINLENGTH,MAXLENGTH);
      printError(mess);
    }
}
