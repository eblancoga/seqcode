/*************************************************************************
*                                                                        *
*   Module: ReadRefgeneFileMarkExons                                     *
*                                                                        *
*   Use the transcripts to mark the exons along the chromosomes          *
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

extern int WINDOWRES;

void ParseExonsCoordinates(char* sExons,
			   long* Exons,
			   int nExons,
			   char* lineCopy)
{
  char *aux;
  int i;
  long pos;
  char mess[MAXSTRING];
 
  /* pos1,pos2,pos3,... */
  /* first coordinate (string) */
  aux = (char *) strtok(sExons,CSV);
  
  /* first coordinate (number) */
  if (sscanf(aux,"%ld",&pos) != 1)
    {
      sprintf(mess,"Wrong format in the exons coordinates:\n-->%s\n",lineCopy);
      printError(mess);
    }
  Exons[0] = pos;

  /* the rest of coordinates */
  for(i=1; i<nExons; i++)
    {
      aux = (char *) strtok(NULL,CSV);

      if (sscanf(aux,"%ld",&pos) != 1)
	{
	  sprintf(mess,"Wrong format in the exons coordinates:\n-->%s\n",lineCopy);
	  printError(mess);
	}
      Exons[i] = pos;
    }  
}

long ReadRefgeneFileMarkExons (char *FileName, 
			       long* ChrSizes, 
			       dict* ChrNames, 
			       unsigned int** EXONS)
{
  /* File handle */
  FILE* file;
  
  /* Split every input line into several tokens <chr,size> */
  char line[MAXLINE];
  char* line1;
  char* line2;
  char* line3;
  char* line4;
  char *line5;
  char *line6;
  char *line7;
  char *line8;
  char *line9;
  char *line10;
  char *line11;
  char *line12;
  char *line13;

  /* Backup line */
  char lineCopy[MAXLINE];
  
  /* Values */
  char chr[MAXCHRNAME];
  long pos1;
  long pos2;
  long cds1;
  long cds2;
  char strand;
  char gene[MAXGENENAME];
  char transcript[MAXGENENAME];

  /* Exons coordinates */
  int nExons;
  int iExons;
  char sExonsL[MAXEXONSINFO];
  char sExonsR[MAXEXONSINFO];
  long ExonsL[MAXEXONS];
  long ExonsR[MAXEXONS];
  long exon1;
  long exon2;

  /* Code for the hash */
  int key;

  /* Number of lines */
  int nTranscripts;

  /* Read interval pointer */
  long j;

  char mess[MAXSTRING];

  /* 0. Open refGene.txt file to read the information */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The refGene.txt file can not be opened to read");
  
  /* 1. Reset counters */
  nTranscripts = 0;  

  /* Init the info messages */
  printReadingInit();
  
  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Message about processing lines... */
      printReadingInfo(nTranscripts);

      /* Backup copy of the line to show error messages */
      strcpy(lineCopy,line);
      
      /* Extracting values of current line: only using field1 and field2 */
      line1 = (char *) strtok(line,TAB);
      line2 = (char *) strtok(NULL,TAB);
      line3 = (char *) strtok(NULL,TAB);
      line4 = (char *) strtok(NULL,TAB);
      line5 = (char *) strtok(NULL,TAB);
      line6 = (char *) strtok(NULL,TAB);
      line7 = (char *) strtok(NULL,TAB);
      line8 = (char *) strtok(NULL,TAB);
      line9 = (char *) strtok(NULL,TAB);
      line10 = (char *) strtok(NULL,TAB);
      line11 = (char *) strtok(NULL,TAB);
      line12 = (char *) strtok(NULL,TAB);
      line13 = (char *) strtok(NULL,TAB);
      
      /* There are 13 mandatory columns */
      if (line1 == NULL || line2 == NULL 
	  || line3 == NULL || line4 == NULL
	  || line5 == NULL || line6 == NULL
	  || line7 == NULL || line8 == NULL
	  || line9 == NULL || line10 == NULL
	  || line11 == NULL || line12 == NULL
	  || line13 == NULL)
	{
	  sprintf(mess,"Unexpected format for refGene.txt files (line %d):\n-->%s\n",
		  nTranscripts,lineCopy);
	  printMess(mess);
	}
      
      /* F2: Transcript */
      if (sscanf(line2,"%s",transcript) != 1)
        {
          sprintf(mess,"Wrong format in the transcript code (NM_XXXX):\n-->%s\n",lineCopy);
          printError(mess);
        }
      
      /* F3: Chromosome */
      if (sscanf(line3,"%s",chr) != 1)
        {
          sprintf(mess,"Wrong format in the chromosome name:\n-->%s\n",lineCopy);
          printError(mess);
        }
      
      /* F4: Strand */
      if (sscanf(line4,"%c",&strand) != 1)
        {
          sprintf(mess,"Wrong format in the strand :\n-->%s\n",lineCopy);
          printError(mess);
        }
      
      /* F5: TSS1 */
      if (sscanf(line5,"%ld",&pos1) != 1)
        {
          sprintf(mess,"Wrong format in the TSS1 :\n-->%s\n",lineCopy);
          printError(mess);
        }
      
      /* F6: TSS2 */
      if (sscanf(line6,"%ld",&pos2) != 1)
        {
          sprintf(mess,"Wrong format in the TSS2 :\n-->%s\n",lineCopy);
          printError(mess);
        }

      /* F7: CDS1 */
      if (sscanf(line7,"%ld",&cds1) != 1)
        {
          sprintf(mess,"Wrong format in the CDS1 :\n-->%s\n",lineCopy);
          printError(mess);
        }
      
      /* F8: CDS2 */
      if (sscanf(line8,"%ld",&cds2) != 1)
        {
          sprintf(mess,"Wrong format in the CDS2 :\n-->%s\n",lineCopy);
          printError(mess);
        }
      
      /* F9: nExons */
      if (sscanf(line9,"%d",&nExons) != 1)
        {
          sprintf(mess,"Wrong format in the nExons :\n-->%s\n",lineCopy);
          printError(mess);
        }

      /* F10: sExonsL */
      if (sscanf(line10,"%s",sExonsL) != 1)
        {
          sprintf(mess,"Wrong format in the sExonsL :\n-->%s\n",lineCopy);
          printError(mess);
        }

      ParseExonsCoordinates(sExonsL,ExonsL,nExons,lineCopy);

      /* F11: sExonsR */
      if (sscanf(line11,"%s",sExonsR) != 1)
        {
          sprintf(mess,"Wrong format in the sExonsR :\n-->%s\n",lineCopy);
          printError(mess);
        }

      ParseExonsCoordinates(sExonsR,ExonsR,nExons,lineCopy);
      
      /* F13: Gene name */
      if (sscanf(line13,"%s",gene) != 1)
        {
          sprintf(mess,"Wrong format in the gene symbol name:\n-->%s\n",lineCopy);
          printError(mess);
        }
      
      /* Only using Chromosome names for which we have Chr size into the dictionary */
      key = getkeyDict(ChrNames,chr);
      if (key == NOTFOUND)
        {
        }
      else
        {
	  /* Get the key for this chromosome */
	  key = getkeyDict(ChrNames,chr);
	  
	  /* Speed up rules: not checking chr is right, position is not out of boundaries */
	  /* Define the EXON regions to be marked along this chromosome */
	  if (strand == cFORWARD)
	    {
	      /* Reading exon by exon: ExonsL and ExonsR */
	      for(iExons=0; iExons<nExons; iExons++)
		{
		  exon1 = ExonsL[iExons]/WINDOWRES;
		  exon2 = ExonsR[iExons]/WINDOWRES;
		  
		  /* Position by position of the current exon */
		  for(j=exon1;j<exon2;j++)
		    {
		      EXONS[key][j]=cEXON;
		    }
		}
	    }
	  else
	    {
	      /* Reverse gene */
	      /* Reading exon by exon: ExonsL and ExonsR */
	      for(iExons=0; iExons<nExons; iExons++)
		{
		  exon1 = ExonsL[iExons]/WINDOWRES;
		  exon2 = ExonsR[iExons]/WINDOWRES;
		  
		  /* Position by position of the current exon */
		  for(j=exon1;j<exon2;j++)
		    {
		      EXONS[key][j]=cEXON;
		    }
		}
	    }  
	}
      
      /* Increase the total number of lines */
      nTranscripts++;
    }

  fclose(file);

  /* Return the number of lines in the file */
  return(nTranscripts);
}
  
