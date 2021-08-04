/*************************************************************************
*                                                                        *
*   Module: readargv_genomeDistribution                                  *
*                                                                        *
*   Read set up options/filenames from user input (genomeDistribution)   *
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
extern int DETAILED;
extern int SIMPLIFIED;
extern char COLOR1[MAXCOLORNAME];
extern char COLOR2[MAXCOLORNAME];
extern char COLOR3[MAXCOLORNAME];
extern char COLOR4[MAXCOLORNAME];
extern char COLOR5[MAXCOLORNAME];
extern char COLOR6[MAXCOLORNAME];
extern char COLOR7[MAXCOLORNAME];
extern int GRADIENT;
extern int PALETTE;
extern int QUALITATIVE;

/* required by getopts */
extern char* optarg;
extern int optind;

/* usage string */
char USAGE[MAXUSAGE][MAXSTRING];

void printHelp_genomeDistribution()
{
  fprintf(stderr,"%s\n",USAGE[0]);
  fprintf(stderr,"%s\n",USAGE[1]);
  fprintf(stderr,"%s\n",USAGE[2]);
  fprintf(stderr,"%s\n",USAGE[3]);

  fprintf(stderr,"OPTIONS\n");
  fprintf(stderr,"\t-1 : Color 1, Distal/Promoter (default: coral).\n");  
  fprintf(stderr,"\t-2 : Color 2, Proximal/Intragenic (default: darkred).\n");  
  fprintf(stderr,"\t-3 : Color 3, 5'UTR/Intergenic (default: burlywood).\n");  
  fprintf(stderr,"\t-4 : Color 4, 3'UTR (default: orchid).\n");  
  fprintf(stderr,"\t-5 : Color 5, CDS (default: chartreuse3).\n");  
  fprintf(stderr,"\t-6 : Color 6, Introns (default: gold).\n");  
  fprintf(stderr,"\t-7 : Color 7, Intergenic (default: corflowerblue).\n");  
  fprintf(stderr,"\t-d : Detailed analysis with introns/exons/promoters.\n");
  fprintf(stderr,"\t-g : Gradient palette from Color1 to white.\n");
  fprintf(stderr,"\t-p : Viridis palettes (1=viridis|2=magma|3=plasma|4=inferno).\n");
  fprintf(stderr,"\t-q : ColorBrewer palettes (1=accent|2=paired).\n");
  fprintf(stderr,"\t-s : Simplified with genic/intragenic/intergenic (X bp around TSS).\n");
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

void readargv_genomeDistribution(int argc,char* argv[],
				 char ChromInfoFile[FILENAMELENGTH],
				 char RefgeneFile[FILENAMELENGTH],
				 char PeaksFile[FILENAMELENGTH],
				 char UserName[USERNAMELENGTH],
				 char Prefix[PREFIXLENGTH])
{
  int c;
  char mess[MAXSTRING];

  int nFiles;

  /* Adding usage messages */
  sprintf(USAGE[0],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  GENOMEDISTRIBUTION);
  sprintf(USAGE[1],
	  "NAME\n\t%s - a program to examine the distribution of peaks within distinct genomic features.\n",
	  GENOMEDISTRIBUTION);
  sprintf(USAGE[2],
	  "SYNOPSIS\n\t%s [-1/7 <Rcolor>][-d][-g <Rcolor>][-p 1234][-q 12][-s <bp>][-w <bp>][-v][-x prefix][-h]\n\t<chrom_info> <refGene.txt> <peaks.bed> <name>\n",
	  GENOMEDISTRIBUTION);      
  sprintf(USAGE[3],
	  "OUTPUT\n\tOne folder with 3 files:\n\t- Peaks associated to genomic regions\n\t- R script commands\n\t- Graphical representation (R is required).\n");
  sprintf(USAGE[4],
	  "SEE ALSO\n\tSeqCode homepage: %s\n\tGitHub source code: %s\n",
	  HOMEPAGE,SOURCECODE);
  sprintf(USAGE[5],
	  "AUTHORS\n\tWritten by %s.\n",
	  AUTHORSHIP);
  sprintf(USAGE[6],
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n",
	  VERSION,
	  GENOMEDISTRIBUTION);
  
  /* Default palette of colors */
  strcpy(COLOR1,DEFAULT_COLOR1);
  strcpy(COLOR2,DEFAULT_COLOR2);
  strcpy(COLOR3,DEFAULT_COLOR3);
  strcpy(COLOR4,DEFAULT_COLOR4);
  strcpy(COLOR5,DEFAULT_COLOR5);
  strcpy(COLOR6,DEFAULT_COLOR6);
  strcpy(COLOR7,DEFAULT_COLOR7);

  /* Default no prefix mode */
  strcpy(Prefix,".");
  
  /* Reading setup options */
  while ((c = getopt(argc,argv,"1:2:3:4:5:6:7:dgp:q:s:w:vx:h")) != -1)
    switch(c)
      {
      case '1':
        strcpy(COLOR1,optarg);
        break;
      case '2':
        strcpy(COLOR2,optarg);
        break;
      case '3':
        strcpy(COLOR3,optarg);
        break;
      case '4':
        strcpy(COLOR4,optarg);
        break;
      case '5':
        strcpy(COLOR5,optarg);
        break;
      case '6':
        strcpy(COLOR6,optarg);
        break;
      case '7':
        strcpy(COLOR7,optarg);
        break;
      case 'd':
	DETAILED = TRUE;
	break;
      case 'g':
	GRADIENT = TRUE;
	break;
      case 'p':
	PALETTE = atoi(optarg);
        break;
      case 'q':
	QUALITATIVE = atoi(optarg);
        break;
      case 's':
	SIMPLIFIED = atoi(optarg);
        break;
      case 'w':
        WINDOWRES = atoi(optarg);
        break;
      case 'v':
	VRB++;
	break;
      case 'x':
	strcpy(Prefix,optarg);
	break;
      case 'h': printHelp_genomeDistribution();
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
  strcpy(RefgeneFile,argv[optind+1]);
  strcpy(PeaksFile,argv[optind+2]);
  strcpy(UserName,argv[optind+3]);

  /* Control of errors */
  if (DETAILED && SIMPLIFIED)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
      
      sprintf(mess,"Incompatible options (detailed and simplified)\n");
      printError(mess);
    }

  if (GRADIENT && PALETTE)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
      
      sprintf(mess,"Incompatible options (gradient and viridis palette)\n");
      printError(mess);
    }

    if (GRADIENT && QUALITATIVE)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
      
      sprintf(mess,"Incompatible options (gradient and qualitative palette)\n");
      printError(mess);
    }

    if (PALETTE && QUALITATIVE)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);
      
      sprintf(mess,"Incompatible options (viridis palette and qualitative palette)\n");
      printError(mess);
    }
  
  if (SIMPLIFIED<0 || SIMPLIFIED>MAXSIMPLIFIED)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"Promoter definition must be between 1 and %d (%d)\n",MAXSIMPLIFIED,SIMPLIFIED);
      printError(mess);
    }

    if (PALETTE<0 || PALETTE>MAXPALETTE)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"Viridis palette definition must be between 1 and %d (%d)\n",MAXPALETTE,PALETTE);
      printError(mess);
    }

    if (QUALITATIVE<0 || QUALITATIVE>MAXQUALITATIVE)
    {
      fprintf(stderr,"%s\n",USAGE[0]);
      fprintf(stderr,"%s\n",USAGE[1]);
      fprintf(stderr,"%s\n",USAGE[2]);

      sprintf(mess,"Qualitative palette definition must be between 1 and %d (%d)\n",MAXQUALITATIVE,QUALITATIVE);
      printError(mess);
    }
}
