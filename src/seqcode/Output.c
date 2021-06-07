/*************************************************************************
*                                                                        *
*   Module: Output                                                       *
*                                                                        *
*   Management: generating text results (files, stdout)                  *
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

extern int VRB;
extern int SPIKEIN;

extern account* m;

/* Printing messages (information) */
void printMess(char* s)
{
  if (VRB)
    fprintf (stderr, "> %s\n",s);
}

/* Printing stats and results (information) */
void printRes(char* s)
{
  if (VRB)
    fprintf (stderr, "\t%s\n",s);
}

/* Printing error messages */
void printError(char* s)
{
  fprintf(stderr,"ERROR\n\t%s\n",s);

  fprintf(stderr,
	  "SEE ALSO\n\tSeqCode homepage: %s\n\tGitHub source code: %s\n\n",
	  HOMEPAGE,SOURCECODE);
  fprintf(stderr,
	  "AUTHORS\n\tWritten by %s\n\n",
	  AUTHORSHIP);
  fprintf(stderr,
	  "%s\t\t\t\t\t\tUser commands\t\t\t\t\t\t%s\n\n",
	  VERSION,VERSION);
  OutputTime(m);
  
  exit(1);
}

/* Printing SeqCode running header lines (information) */
void printSeqCodeHeader(char* s)
{
  char mess[MAXSTRING];
  char gap[MAXSTRING];
  int length1,length2;
  int i;

  
  if (VRB)
    {
      /* Print main line and determine the (variable) string length for filling gaps */
      sprintf(mess,"\n\n\t\t\t***** Running %s (%s) by Enrique Blanco (%d) *****\n",s,VERSION,YEAR);
      length1 = strlen(mess);
      fprintf(stderr,"%s",mess);

      /* Print second line and count the number of gaps to fit every output line in the same width */
      sprintf(mess,"\t\t\t***** GitHub  source code: https://github.com/eblancoga/seqcode ");
      length2 = strlen(mess);
      fprintf(stderr,"%s",mess);
      strcpy(gap,SPACE);
      for(i=length2;i<length1-10;i++)
	{
	  strcat(gap,SPACE);
	}
      fprintf(stderr,"%s *****\n",gap);

      /* Print third line and count the number of gaps to fit every output line in the same width */
      sprintf(mess,"\t\t\t***** SeqCode homepage at: http://ldicrocelab.crg.es ");
      length2 = strlen(mess);
      fprintf(stderr,"%s",mess);
      strcpy(gap,SPACE);
      for(i=length2;i<length1-10;i++)
	{
	  strcat(gap,SPACE);
	}
      fprintf(stderr,"%s *****\n\n\n",gap);
    }
}

/* Init message for reading big files */
void printReadingInit()
{
  if (VRB)
    {
      fprintf(stderr, "\tReading:\n");
    }
}

/* Printing messages: big files */
void printReadingInfo(long nLines)
{
  if (VRB && !(nLines % MESSAGE_FREQ))
    {
      fprintf(stderr, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\t[%10ld lines]",nLines);
    }
}

/* Printing messages: small files */
void printReadingInfoSmall(long nLines)
{
  if (VRB && !(nLines % MESSAGE_FREQ_SMALL))
    {
      fprintf(stderr, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\t[%10ld lines]",nLines);
    }
}

/* Display the intersection between a peak and a transcript */
void OutputMatch(char chr[],
		 long pos1A,
		 long pos2A,
		 char score[],
		 transcript t)
{
  printf("%s\t%ld\t%ld\t%s\t%s\t%s\t%s\t%c\t%ld\t%ld\n",
	 chr,
	 pos1A,
	 pos2A,
	 score,
	 t.gene,
	 t.nm,
	 t.chr,
	 t.strand,
	 t.pos1,
	 t.pos2);

}

/* Intersect and display the hits between two lists of peaks */
void OutputPeaksLists(peak** PeaksA,
		      peak** PeaksB,
		      char* NameA,
		      char* NameB,
		      char* OutputFileAB,
		      char* OutputFileA,
		      char* OutputFileB,
		      dict* ChrNames)
{
  
  /* Output files */
  FILE* fileAB;
  FILE* fileA;
  FILE* fileB;

  /* Code for the hash */
  int lastkey;

  /* Number of elements to visit */
  int i;
  long j,k;

  /* Number of intersected elements */
  long intAB_A,intAB_B,intA,intB;

  /* Messages */
  char mess[MAXSTRING];
    
  
  /* 0. Prepare three files to write: AB, A and B */
  
  if ((fileAB=fopen(OutputFileAB, "w"))==NULL)
    {
      sprintf(mess,"The OutputFileAB %s file can not be opened to write",OutputFileAB);
      printError(mess);
    }

  if ((fileA=fopen(OutputFileA, "w"))==NULL)
    {
      sprintf(mess,"The OutputFileA %s file can not be opened to write",OutputFileA);
      printError(mess);
    }

  if ((fileB=fopen(OutputFileB, "w"))==NULL)
    {
      sprintf(mess,"The OutputFileB %s file can not be opened to write",OutputFileB);
      printError(mess);
    }

  fprintf(fileAB,"track name=\"%s_%s_common\" description=\"%s_%s_common\" visibility=\"dense\" color=\"200,0,200\"\n",
	  NameA,NameB,NameA,NameB);
  fprintf(fileA,"track name=\"%s_only\" description=\"%s_only\" visibility=\"dense\" color=\"0,0,200\"\n",NameA,NameA);
  fprintf(fileB,"track name=\"%s_only\" description=\"%s_only\" visibility=\"dense\" color=\"200,0,0\"\n",NameB,NameB);

  /* 1. Visit all available chromosomes */
  /* Identify the last key used in the dictionary of chromosomes */
  lastkey = ChrNames->nextFree;

  intAB_A = 0;
  intAB_B = 0;
  intA = 0;
  intB = 0;

  for(i=0; i < lastkey; i++)
    {
      /* sprintf(mess,"Output: %ld peaks in %s, %ld peaks in %s (chromosome key %d)",
              m->nPeaksA[i],NameA,
	      m->nPeaksB[i],NameB,
	      i);
	      printRes(mess); */

      /* 2. Visit chromosome i in A */
      for(j=0; j < m->nPeaksA[i]; j++)
        {
	  if (PeaksA[i][j].used == TRUE)
	    {
	      fprintf(fileAB,"%s\t%ld\t%ld\t%s\t%s\n",
		      PeaksA[i][j].chr,
		      PeaksA[i][j].pos1,
		      PeaksA[i][j].pos2,
		      NameA,
		      PeaksA[i][j].score);
	      intAB_A++;
	    }
	  else
	    {
	      fprintf(fileA,"%s\t%ld\t%ld\t%s\t%s\n",
		      PeaksA[i][j].chr,
		      PeaksA[i][j].pos1,
		      PeaksA[i][j].pos2,
		      NameA,
		      PeaksA[i][j].score);
	      intA++;
	    }
	}

      /* 3. Visit chromosome i in B */
      for(k=0; k < m->nPeaksB[i]; k++)
	{
	  if (PeaksB[i][k].used  == TRUE)
	    {
	      fprintf(fileAB,"%s\t%ld\t%ld\t%s\t%s\n",
		      PeaksB[i][k].chr,
		      PeaksB[i][k].pos1,
		      PeaksB[i][k].pos2,
		      NameB,
		      PeaksB[i][k].score);
	      intAB_B++;
	    }
	  else
	    {
	      fprintf(fileB,"%s\t%ld\t%ld\t%s\t%s\n",
		      PeaksB[i][k].chr,
		      PeaksB[i][k].pos1,
		      PeaksB[i][k].pos2,
		      NameB,
		      PeaksB[i][k].score);
	      intB++;
	    }
	}
    }

  fclose(fileAB);
  fclose(fileA);
  fclose(fileB);

  /* Final stats */
  sprintf(mess,"Peaks intersected in A: %ld/%ld (%.2f%%)",intAB_A,
	  m->nTotalPeaksA,(float)100*intAB_A/(float)m->nTotalPeaksA);
  printRes(mess);

  sprintf(mess,"Peaks intersected in B: %ld/%ld (%.2f%%)",intAB_B,
	  m->nTotalPeaksB,(float)100*intAB_B/(float)m->nTotalPeaksB);
  printRes(mess);

  sprintf(mess,"Peaks non-intersected in A: %ld/%ld (%.2f%%)",intA,
	  m->nTotalPeaksA,(float)100*intA/(float)m->nTotalPeaksA);
  printRes(mess);

  sprintf(mess,"Peaks non intersected in B: %ld/%ld (%.2f%%)",intB,
	  m->nTotalPeaksB,(float)100*intB/(float)m->nTotalPeaksB);
  printRes(mess);
}

/* Generate the average distribution of reads around the TSS */
void OutputAvgReadsFile(long* REGION,
			int L,
			char* FileName,
			long ngenes,
			long nreads)
{
  
  /* Output file */
  FILE* file;

  /* Number of elements to visit */
  int i;

  /* Avg. value */
  float avg;

  /* Normalization factor */
  float normfactor;
  
  /* Messages */
  char mess[MAXSTRING];
    
  
  /* 0. Prepare one file to write */
  if ((file=fopen(FileName, "w"))==NULL)
    {
      sprintf(mess,"The avg. profile output file %s can not be opened to write",FileName);
      printError(mess);
    }

  /* Normalization factor */
  if (SPIKEIN == 0)
    {
      /* Traditional model: total number of reads of the sample */
      normfactor = (float)nreads/MEGA;

      sprintf(mess,"Normalization factor: %f",normfactor);
      printRes(mess);
    }
  else
    {
      /* Reference-adjusted normalization: total number of reads of the spike/refence */
      normfactor = (float)SPIKEIN/MEGA;

      sprintf(mess,"Normalization spike-in factor: %f",normfactor);
      printRes(mess);
    }

  /* 1. Visit all the region: -L..0..L */
  for(i=0; i < 2*L; i++)
    {
      avg = (double) REGION[i]/(ngenes*normfactor);
      fprintf(file,"%d\t%f\n",i-L,avg);
    }

  fclose(file);
}

/* Generate the avg combined distribution of reads around the TSS */
void OutputAvgReadsFileCombined(long* REGION,
				int L,
				char* FileName,
				long ngenes)
{
  
  /* Output file */
  FILE* file;


  /* Number of elements to visit */
  int i;

  /* Avg. value */
  float avg;

  /* Messages */
  char mess[MAXSTRING];
    
  
  /* 0. Prepare one file to write */
  if ((file=fopen(FileName, "w"))==NULL)
    {
      sprintf(mess,"The avg. profile output file %s can not be opened to write",FileName);
      printError(mess);
    }

  /* 1. Visit all the region: -L..0..L */
  for(i=0; i < 2*L; i++)
    {
      avg = (double) REGION[i]/ngenes;
      fprintf(file,"%d\t%f\n",i-L,avg);
    }

  fclose(file);
}

/* Generate the average distribution of reads along a normalized gene */
void OutputIdealGeneProfileFile(long* UPSTREAM,
				long* IDEALGENE,
				long* DOWNSTREAM,
				int L,
				char* FileName,
				long nreads)
{
  
  /* Output file */
  FILE* file;

  /* Number of elements to visit */
  int i;

  /* Avg. value */
  float avg;

  /* Normalization factor */
  float normfactor;

  /* Position in the profile */
  int position;

  /* Messages */
  char mess[MAXSTRING];
    
  
  /* 0. Prepare one file to write */
  if ((file=fopen(FileName, "w"))==NULL)
    {
      sprintf(mess,"The avg. profile output file %s can not be opened to write",FileName);
      printError(mess);
    }

  /* Normalization factor */
  if (SPIKEIN == 0)
    {
      /* Traditional model: total number of reads of the sample */
      normfactor = (float)nreads/MEGA;

      sprintf(mess,"Normalization factor: %f",normfactor);
      printRes(mess);
    }
  else
    {
      /* Reference-adjusted normalization: total number of reads of the spike/refence */
      normfactor = (float)SPIKEIN/MEGA;
      
      sprintf(mess,"Normalization spike-in factor: %f",normfactor);
      printRes(mess);
    }
  
  /* 1. UPSTREAM REGION */
  for(i=0; i < L; i++)
    {
      avg = (double) UPSTREAM[i]/(m->nGenes*normfactor);
      position = i-L-1;

      fprintf(file,"%d\t%f\n",position,avg);
    }

  /* 2. IDEALGENE REGION: 2-fold amplification in the X axis */
  for(i=0; i < L; i++)
    {
      avg = (double) IDEALGENE[i]/(m->nGenes*normfactor);
      position = 2*i;

      fprintf(file,"%d\t%f\n",position,avg);
    }

  /* 3. DOWNSTREAM REGION */
  for(i=0; i < L; i++)
    {
      avg = (double) DOWNSTREAM[i]/(m->nGenes*normfactor);
      position = i+2*L;

      fprintf(file,"%d\t%f\n",position,avg);
    }

  fclose(file);
}

/* Display the profile avg and max points for a given gene */
void OutputGeneAvgMax(transcript t, float avg, int max)
{
  printf("%s\t%s\t%s\t%c\t%ld\t%ld\t%.2f\t%d\n",
	 t.gene,
	 t.nm,
	 t.chr,
	 t.strand,
	 t.pos1,
	 t.pos2,
	 avg,
	 max);
}

/* Extracting the Computing running time by using accounting information */
void StartingTime(char* mess, account* m)
{
    char* s;

    /* 1. Extract the starting time to display */
    s = ctime(&m->tStart);
    s[strlen(s)-1] = '\0';

    /* 2. Prepare the time for printing in a message */
    sprintf(mess,"0. Running on %s",s);
}

/* Extracting the Computing running time by using accounting information */
void GetTime(char* mess, account* m)
{
    char* s;

    /* 1. Extract the starting time to display */
    s = ctime(&m->tStart);
    s[strlen(s)-1] = '\0';

    /* 2. Prepare the time for printing in a message */
    sprintf(mess,"[%s]",s);
}

/* Computing running time by using accounting information */
void OutputTime(account* m)
{
  time_t tEnd;
  int t;
  float caux;
  char mess[MAXSTRING];


  /* Real time */
  time(&tEnd);

  /* CPU time */
  caux = (float)clock() / (float)CLOCKS_PER_SEC;

  t = (int) tEnd - m->tStart;

  /* Correction */
  if (t < caux)
    t++;

  printRes("__________________________________________________________________________\n");
  
  sprintf(mess,"Memory usage: \t%.2f Megabytes",
	  (float)m->nMemory/MEGABYTE);
  printRes(mess);

  sprintf(mess,"CPU time: \t%.2f secs",caux);
  printRes(mess);
  
  sprintf(mess,"Total time: \t%d secs (%.2f mins)\n\n",
	  t,(float)t/MINUTE);
  printRes(mess);
}

int ValidationUserName(char UserName[USERNAMELENGTH])
{

  /* Check the list of non-eligible symbols */
  if (strchr(UserName,SPECSYMBOL1)==NULL &&
      strchr(UserName,SPECSYMBOL2)==NULL &&
      strchr(UserName,SPECSYMBOL3)==NULL &&
      strchr(UserName,SPECSYMBOL4)==NULL &&
      strchr(UserName,SPECSYMBOL5)==NULL &&
      strchr(UserName,SPECSYMBOL6)==NULL &&
      strchr(UserName,SPECSYMBOL7)==NULL &&
      strchr(UserName,SPECSYMBOL8)==NULL &&
      strchr(UserName,SPECSYMBOL9)==NULL &&
      strchr(UserName,SPECSYMBOL10)==NULL &&
      strchr(UserName,SPECSYMBOL11)==NULL &&
      strchr(UserName,SPECSYMBOL12)==NULL &&
      strchr(UserName,SPECSYMBOL13)==NULL &&
      strchr(UserName,SPECSYMBOL14)==NULL &&
      strchr(UserName,SPECSYMBOL15)==NULL &&
      strchr(UserName,SPECSYMBOL16)==NULL &&
      strchr(UserName,SPECSYMBOL17)==NULL &&
      strchr(UserName,SPECSYMBOL18)==NULL &&
      strchr(UserName,SPECSYMBOL19)==NULL &&
      strchr(UserName,SPECSYMBOL20)==NULL &&
      strchr(UserName,' ')==NULL)
    return (TRUE);
  else
    return (FALSE);
  
}

int ValidationPrefix(char Prefix[PREFIXLENGTH])
{
  int i;
  int j;
  int k;
  char folder[DIRNAMELENGTH];
  char path[MAXPREFIXES][DIRNAMELENGTH];
  char mess[MAXSTRING];
  char subdirs[PREFIXLENGTH];
  
  
  /* Check the list of non-eligible symbols */
  if (strchr(Prefix,SPECSYMBOL1)==NULL &&
      strchr(Prefix,SPECSYMBOL2)==NULL &&
      strchr(Prefix,SPECSYMBOL3)==NULL &&
      strchr(Prefix,SPECSYMBOL4)==NULL &&
      strchr(Prefix,SPECSYMBOL5)==NULL &&
      strchr(Prefix,SPECSYMBOL6)==NULL &&
      strchr(Prefix,SPECSYMBOL7)==NULL &&
      /* '/' is allowed to denote subdirectories strchr(Prefix,SPECSYMBOL8)==NULL && */
      strchr(Prefix,SPECSYMBOL9)==NULL &&
      strchr(Prefix,SPECSYMBOL10)==NULL &&
      strchr(Prefix,SPECSYMBOL11)==NULL &&
      strchr(Prefix,SPECSYMBOL12)==NULL &&
      strchr(Prefix,SPECSYMBOL13)==NULL &&
      strchr(Prefix,SPECSYMBOL14)==NULL &&
      strchr(Prefix,SPECSYMBOL15)==NULL &&
      strchr(Prefix,SPECSYMBOL16)==NULL &&
      strchr(Prefix,SPECSYMBOL17)==NULL &&
      strchr(Prefix,SPECSYMBOL18)==NULL &&
      strchr(Prefix,SPECSYMBOL19)==NULL &&
      strchr(Prefix,SPECSYMBOL20)==NULL &&
      strchr(Prefix,' ')==NULL)
    {
      /* Parse the prefix (as a list of folders separated by '/' */
      for(i=0,j=0,k=0;i<=strlen(Prefix);i++)
	{
	  if (Prefix[i]!='/' && Prefix[i]!='\0')
	    {
	      folder[j]=Prefix[i];
	      j++;
	    }
	  else
	    {
	      folder[j]='\0';
	      if (j>0)
		{
		  strcpy(path[k],folder);
		  k++;

		  if (k>MAXPREFIXES)
		    printError("Please, reduce the number of levels (folders) in the prefix");
		}
	      j=0;
	    }
	}

      /* Check for subfolder existence and create dir if not */
      strcpy(subdirs,"");
      for(i=0;i<k;i++)
	{
	  strcat(subdirs,path[i]);
	  strcat(subdirs,"/");
	  
	  if (mkdir(subdirs,0755))
	    {
	      sprintf(mess,"The prefix folder %s exists",subdirs);
	      printRes(mess);
	    }
	  else
	    {
	      sprintf(mess,"The prefix folder %s has been created",subdirs);
	      printRes(mess);
	    }
	}
      
      return (TRUE);
    }
  else
    return (FALSE);
}
