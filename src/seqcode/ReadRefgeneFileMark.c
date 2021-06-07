/*************************************************************************
*                                                                        *
*   Module: ReadRefgeneFileMark                                          *
*                                                                        *
*   Use the transcripts to mark the chromosomes (exons/introns/...)      *
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
extern int DETAILED;
extern int SIMPLIFIED;

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

long ReadRefgeneFileMark (char *FileName, 
			  long* ChrSizes, 
			  dict* ChrNames, 
			  unsigned int** REGIONS)
{
  /* File handle */
  FILE* file;
  
  /* Split every input line into several tokens <chr,size> */
  char line[MAXLINE];
  char* line1;
  char* line2;
  char* line3;
  char* line4;
  char* line5;
  char* line6;
  char* line7;
  char* line8;
  char* line9;
  char* line10;
  char* line11;
  char* line12;
  char* line13;

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
  long intron1;
  long intron2;

  /* Code for the hash */
  int key;

  /* Number of lines */
  int nTranscripts;

  /* Read interval pointer */
  long start;
  long stop;
  long i;
  long j;
  long startDistal;
  long stopDistal;
  long startProximal;
  long stopProximal;
  long start5;
  long stop5;
  long start3;
  long stop3;
  long startCDS;
  long stopCDS;

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
      printReadingInfoSmall(nTranscripts);

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
	  sprintf(mess,"Unexpected format in refGene.txt (line %d):\n-->%s\n",
		  nTranscripts,lineCopy);
	  printError(mess);
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
	  //sprintf(mess,"The chromosome %s is not included into the list of valid chromosomes\n",chr);
          //printMess(mess);
        }
      else
        {
	  /* BASIC: promoter, intragenic, intergenic */
	  if (DETAILED == FALSE && SIMPLIFIED == FALSE)
	    {
	      /* Define the PROMOTER region to be marked along this chromosome */
	      if (strand == cFORWARD)
		{
		  start = (pos1 - PROMOTERSIZE)/WINDOWRES;
		  if (start<0)
		    {
		      start=0;
		    }

		  stop = pos1/WINDOWRES;
		}
	      else
		{
		  /* Reverse gene */
		  start = pos2/WINDOWRES;
		  stop = (pos2 + PROMOTERSIZE)/WINDOWRES;
		}	  
	      
	      /* Set 'P' (promoter) in this interval of positions */
	      for(i=start; i<stop; i++) 
		{
		  REGIONS[key][i]=cPROMOTER; 
		}

	      /* Define the INTRAGENIC region to be marked along this chromosome */
	      start = pos1/WINDOWRES;
	      stop = pos2/WINDOWRES;

	      /* Set 'G' (intragenic) in this interval of positions */
	      /* promoter has priority  */
	      for(i=start; i<stop; i++) 
		{
		  if (REGIONS[key][i]!=cPROMOTER)
		    {
		      REGIONS[key][i]=cINTRAGENIC;
		    }	  
		}
	    }

	  /* SIMPLIFIED: promoter (+/- bp around the TSS, genic, intergenic) */
	  if (SIMPLIFIED != FALSE)
	    {
	      /* Define the PROMOTER region to be marked around XXX bps of the TSS in this chromosome */
	      if (strand == cFORWARD)
		{
		  start = (pos1 - SIMPLIFIED)/WINDOWRES;
		  if (start<0)
		    {
		      start=0;
		    }

		  stop = (pos1 + SIMPLIFIED)/WINDOWRES;
		}
	      else
		{
		  /* Reverse gene */
		  start = (pos2 - SIMPLIFIED)/WINDOWRES;
		  stop = (pos2 + SIMPLIFIED)/WINDOWRES;
		}	  
	      
	      /* Set 'P' (promoter) in this interval of positions */
	      for(i=start; i<stop; i++) 
		{
		  REGIONS[key][i]=cPROMOTER; 
		}

	      /* Define the PROMOTER region to be marked around XXX bps of the TSS in this chromosome */
	      if (strand == cFORWARD)
		{
		  /* Define the GENIC region to be marked after the +/- promoter region in this chromosome */
		  start = (pos1+SIMPLIFIED)/WINDOWRES;
		  stop = pos2/WINDOWRES;
	      
		  /* Set 'G' (intragenic) in this interval of positions */
		  /* promoter has priority  */
		  for(i=start; i<stop; i++) 
		    {
		      if (REGIONS[key][i]!=cPROMOTER)
			{
			  REGIONS[key][i]=cINTRAGENIC;
			}	  
		    }
		}
	      else
		{
		  /* Define the GENIC region to be marked after the +/- promoter region in this chromosome */
		  start = pos1/WINDOWRES;
		  stop = (pos2-SIMPLIFIED)/WINDOWRES;

		  /* Set 'G' (intragenic) in this interval of positions */
		  /* promoter has priority  */
		  for(i=start; i<stop; i++) 
		    {
		      if (REGIONS[key][i]!=cPROMOTER)
			{
			  REGIONS[key][i]=cINTRAGENIC;
			}	  
		    }
		}
	    }
	  
	  /* DETAILED: proximal, distal, exon, intron, 5UTR, 3UTR) */
	  if (DETAILED != FALSE)
	    {
	      /* Define PROXIMAL/DISTAL promoters to be marked along this chromosome */
	      if (strand == cFORWARD)
		{
		  /* promoters */
		  startDistal = (pos1 - PROMOTERSIZE)/WINDOWRES;
		  if (startDistal<0)
		    {
		      startDistal = 0;
		    }

		  stopDistal = (pos1 - PROXIMALPOINT -1)/WINDOWRES;
		  if (stopDistal<0)
		    {
		      stopDistal = 0;
		    }
		  
		  startProximal = (pos1 - PROXIMALPOINT)/WINDOWRES;
		  if (startProximal<0)
		    {
		      startProximal = 0;
		    }

		  stopProximal = pos1/WINDOWRES;
		  
		  /* Set 'D' (distal promoter) in this interval of positions */
		  for(i=startDistal; i<stopDistal; i++) 
		    {
		      REGIONS[key][i]=cDISTAL; 
		    }
		  
		  /* Set 'X' (proximal promoter) in this interval of positions */
		  for(i=startProximal; i<stopProximal; i++) 
		    {
		      REGIONS[key][i]=cPROXIMAL; 
		    }
		  
		  /* intragenic */
		  start5 = pos1/WINDOWRES;
		  stop5 = (cds1-1)/WINDOWRES;
		  startCDS = cds1/WINDOWRES;
		  stopCDS = cds2/WINDOWRES;
		  start3 = (cds2+1)/WINDOWRES;
		  stop3 = pos2/WINDOWRES;

		  /* Reading exon by exon: ExonsL and ExonsR */
		  for(iExons=0; iExons<nExons; iExons++)
		    {
		      exon1 = ExonsL[iExons]/WINDOWRES;
		      exon2 = ExonsR[iExons]/WINDOWRES;

		      /* Mark intronic positions */
		      if (iExons>0 && iExons<nExons-1)
			{
			  intron2=exon1;
			  /* Position by position of the current intron */
			  for(j=intron1;j<intron2;j++)
			    {
			      /* Promoter has priority, exon has priority over introns */
			      if (REGIONS[key][j]!=cDISTAL && REGIONS[key][j]!=cPROXIMAL && 
				  REGIONS[key][j]!=c5UTR && REGIONS[key][j]!=c3UTR && REGIONS[key][j]!=cCDS)
				REGIONS[key][j]=cINTRON;
			    }
			}

		      /* Position by position of the current exon */
		      for(j=exon1;j<exon2;j++)
			{
			  /* Promoter has priority */
			  if (REGIONS[key][j]!=cDISTAL && REGIONS[key][j]!=cPROXIMAL)
			    {
			      if (j<startCDS)
				REGIONS[key][j]=c5UTR;
			      if (j>stopCDS)
				REGIONS[key][j]=c3UTR;
			      if (j>=startCDS && j<=stopCDS)
				REGIONS[key][j]=cCDS;
			    }
			}
		      
		      /* Mark intronic positions */
		      /* Prepare for next intron */
		      intron1 = exon2+1;
		    }
		}
	      else
		{
		  /* Reverse gene */
		  /* promoters */
		  startDistal = (pos2 + PROXIMALPOINT +1)/WINDOWRES;
		  stopDistal = (pos2 + PROMOTERSIZE)/WINDOWRES;
		  startProximal = pos2/WINDOWRES;
		  stopProximal = (pos2 + PROXIMALPOINT)/WINDOWRES;
		  
		  /* Set 'D' (distal promoter) in this interval of positions */
		  for(i=startDistal; i<stopDistal; i++) 
		    {
		      REGIONS[key][i]=cDISTAL; 
		    }
		  
		  /* Set 'X' (proximal promoter) in this interval of positions */
		  for(i=startProximal; i<stopProximal; i++) 
		    {
		      REGIONS[key][i]=cPROXIMAL; 
		    }

		  /* intragenic */
		  start5 = (cds2+1)/WINDOWRES;
		  stop5 = pos2/WINDOWRES;
		  startCDS = cds1/WINDOWRES;
		  stopCDS = cds2/WINDOWRES;
		  start3 = pos1/WINDOWRES;
		  stop3 = (cds1-1)/WINDOWRES;
		  
		  /* Reading exon by exon: ExonsL and ExonsR */
		  for(iExons=0; iExons<nExons; iExons++)
		    {
		      exon1 = ExonsL[iExons]/WINDOWRES;
		      exon2 = ExonsR[iExons]/WINDOWRES;

		      /* Mark intronic positions */
		      if (iExons>0 && iExons<nExons-1)
			{
			  intron2=exon1;
			  /* Position by position of the current intron */
			  for(j=intron1;j<intron2;j++)
			    {
			      /* Promoter has priority, exon has priority over introns */
			      if (REGIONS[key][j]!=cDISTAL && REGIONS[key][j]!=cPROXIMAL && 
				  REGIONS[key][j]!=c5UTR && REGIONS[key][j]!=c3UTR && REGIONS[key][j]!=cCDS)
				REGIONS[key][j]=cINTRON;
			    }
			}

		      /* Position by position of the current exon */
		      for(j=exon1;j<exon2;j++)
			{
			  /* Promoter has priority */
			  if (REGIONS[key][j]!=cDISTAL && REGIONS[key][j]!=cPROXIMAL)
			    {
			      if (j<startCDS)
				REGIONS[key][j]=c3UTR;
			      if (j>stopCDS)
				REGIONS[key][j]=c5UTR;
			      if (j>=startCDS && j<=stopCDS)
				REGIONS[key][j]=cCDS;
			    }
			}
		      
		      /* Mark intronic positions */
		      /* Prepare for next intron */
		      intron1 = exon2+1;
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
  
