/*************************************************************************
*                                                                        *
*   Module: ReadRefgeneFile2                                             *
*                                                                        *
*   Reading refGene.txt file                                             *
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

extern account *m;

long ReadRefgeneFile2(char* FileName,
		      transcript** Transcripts, 
		      dict* ChrNames,
		      dict* GeneNames,
		      int* GeneChrs)
{
  /* File handle */
  FILE *file;
  
  /* Total number of transcripts in the file */
  long nTranscripts;

  /* Split every input line into several tokens <refGene.txt> */
  char line[MAXLINE];
  char *line1;
  char *line2;
  char *line3;
  char *line4;
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
  char strand;
  char gene[MAXGENENAME];
  char transcript[MAXGENENAME];

 /* Code for the hash */
  int key;
  int keyGene;

  char mess[MAXSTRING];


  /* 0. Open refGene.txt file to read the information */
  if ((file=fopen(FileName, "r"))==NULL)
    printError("The refGene.txt file can not be opened to read");
  
  /* 1. Reset counters */
  nTranscripts = 0;  
  
  /* 2. Read while there are lines left in the input file */
  while(fgets(line,MAXLINE,file)!=NULL)
    {
      /* Backup copy of the line to show error messages */
      strcpy(lineCopy,line);
		  
      /* Extracting values of current line: */
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
	  sprintf(mess,"Unexpected format for refGene.txt files (line %ld):\n-->%s\n",
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
	  ;
	}
      else
	{
	  /* Store the information for this transcript in the appropriate chromosome */
	  strcpy(Transcripts[key][m->nTranscripts[key]].nm,transcript);
	  strcpy(Transcripts[key][m->nTranscripts[key]].gene,gene);
	  strcpy(Transcripts[key][m->nTranscripts[key]].chr,chr);
	  Transcripts[key][m->nTranscripts[key]].strand = strand;
	  
	  /* Register the range of positions for this transcript */
	  Transcripts[key][m->nTranscripts[key]].pos1 = pos1;
	  Transcripts[key][m->nTranscripts[key]].pos2 = pos2;
	  
	  /* Save the chromosome in which this gene is found */
	  keyGene = getkeyDict(GeneNames,gene);
	  if (keyGene == NOTFOUND)
	    {
	      keyGene = setkeyDict(GeneNames,gene);
	      
	      /* Store the key for this chromosome in the key of this gene */
	      GeneChrs[keyGene]= key;
	    }

	  /* Increase the total number of transcripts in this chromosome */
	  m->nTranscripts[key]++;
      
	  /* (info) Increase the total number of transcripts in the file */
	  nTranscripts++;
	}
    }
      
  fclose(file);
  
  /* Return the number of distinct transcripts in the file */
  return(nTranscripts);
}
  
