/*************************************************************************
*                                                                        *
*   Module: ReadSAM                                                      *
*                                                                        *
*   Process the mapped reads in SAM format                               *
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
#include "samtools/sam.h"

extern int AVGL;
extern int WINDOWRES;
extern int DEMO;
extern account* m;

void ReadSAMFile (char* FileName, 
		  long* ChrSizes, 
		  dict* ChrNames, 
		  unsigned int** READS)
{
  /* Samtools variables */
  tamFile fph;
  bam_header_t *info; 
  samfile_t *file;
  bam1_t *read;
  int ret;

  /* Values */
  int code;
  char chr[MAXCHRS];
  long pos,pos1,pos2;

  /* Code for the hash */
  int key;

  /* Read interval pointer */
  long i;

  char mess[MAXSTRING];


  /* 0. Open BAM/SAM file to acquire the name of the sequences */
  fph = sam_open(FileName);
 
  if (!fph)
    printError("The BAM/SAM file can not be opened to read");

  /* init the header stucture */
  info = sam_header_read(fph);
  sam_close(fph);

  /* 1. Open BAM/SAM file to acquire the reads */
  file = samopen(FileName, "rb", 0);

  if (!file)
    printError("The BAM/SAM file can not be opened to read");

  /* 2. Init the info messages */
  printReadingInit();
  
  /* 3. Read while there are lines left in the input file */
  m->nReads=0;
  m->nFwdReads=0;
  m->nRvsReads=0;

  /* init the bam read stucture */
  read = bam_init1();

  while ((ret = samread(file,read)) >= 0)
    {
      /* Message about processing lines... */
      printReadingInfo(m->nReads);      
      
      /* Save the info from this BAM read */
      code = read->core.flag;
      
      /* Control: reads with invalid chromosomes are omitted */
      if (read->core.tid == NOTFOUND)
	{
	  /* Current read is not included into the calculations */
	}
      else
	{
	  strcpy(chr,info->target_name[read->core.tid]);
	  pos = read->core.pos+1;
      
	  /* Correction for read extension */
	  if (!(code & 16))
	    {
	      /* Forward read */
	      pos1 = pos/WINDOWRES;
	      pos2 = (pos + AVGL)/WINDOWRES;
	      m->nFwdReads++;
	    }
	  else
	    {
	      /* Reverse read */
	      pos1 = ((pos - AVGL)/WINDOWRES)+1;
	      pos2 = (pos/WINDOWRES)+1;
	      m->nRvsReads++;
	    }	  

	  /* Search the chromosome in the internal dictionary */
	  key = getkeyDict(ChrNames,chr);

	  /* Control: Chromosome available? */
	  if (key == NOTFOUND)
	    {
	      /* Current read is not included into the calculations */
	    }
	  else
	    {
	      /* Control: Out of range? */
	      if (pos >= ChrSizes[key] || pos < AVGL)
		{
		  /* Current read is not included into the calculations */
		}
	      else
		{
		  /* Update the number of reads in this interval of positions */
		  for(i=pos1; i < pos2; i++) 
		    {
		      READS[key][i]++; 
		    }
	      
		  /* Increase the total number of valid reads */
		  m->nReads++;
		}
	    }
	}
    }

  /* One million reads are necessary for normalization (DEMO mode omits this control) */
  if (m->nReads < MEGA && DEMO==FALSE)
    {
      sprintf(mess,"The number of reads is low (%ld, minimum: %d)",m->nReads,MEGA);
      printError(mess);
    }
  
  /* Close the SAM file and other structures */
  samclose(file);
  bam_destroy1(read);
  bam_header_destroy(info);
}
  
void ReadSAMPairedFile (char *FileName, 
			long* ChrSizes, 
			dict* ChrNames, 
			unsigned int** READS)
{
  /* Samtools variables */
  tamFile fph;
  bam_header_t *info; 
  samfile_t *file;
  bam1_t *read;
  int ret;

  /* Values */
  int code;
  char chr[MAXCHRS];
  long pos,pos1,pos2;

  /* Code for the hash */
  int key;

  /* Read interval pointer */
  long i;

  char mess[MAXSTRING];

  
  /* 0. Open BAM/SAM file to acquire the name of the sequences */
  fph = sam_open(FileName);
  
  if (!fph)
    printError("The BAM/SAM file can not be opened to read");
  
  /* init the header stucture */
  info = sam_header_read(fph);
  sam_close(fph);
  
  /* 1. Open BAM/SAM file to acquire the reads */
  file = samopen(FileName, "rb", 0);

  if (!file)
    printError("The BAM/SAM file can not be opened to read");

  /* 2. Init the info messages */
  printReadingInit();
  
  /* 3. Read while there are lines left in the input file */
  m->nReads=0;
  m->nFwdReads=0;
  m->nRvsReads=0;

  /* init the bam read stucture */
  read = bam_init1();

  while ((ret = samread(file,read)) >= 0)
    {
      /* Message about processing lines... */
      printReadingInfo(m->nReads);      

      /* Save the info from this BAM read */
      code = read->core.flag;

     /* Control: reads with invalid chromosomes are omitted */
      if (read->core.tid == NOTFOUND)
	{
	  /* Current read is not included into the calculations */
	}
      else
	{
	  strcpy(chr,info->target_name[read->core.tid]);
	  pos = read->core.pos+1;

	  /* Selection of reads mapped in proper pairs */
	  if (code & 2)
	    {
	      /* Correction for read extension */
	      if (!(code & 16))
		{
		  /* Forward read */
		  pos1 = pos/WINDOWRES;
		  pos2 = (pos + AVGL)/WINDOWRES;
		  m->nFwdReads++;
		}
	      else
		{
		  /* Reverse read */
		  pos1 = ((pos - AVGL)/WINDOWRES)+1;
		  pos2 = (pos/WINDOWRES)+1;
		  m->nRvsReads++;
		}	  
	      
	      /* Search the chromosome in the internal dictionary */
	      key = getkeyDict(ChrNames,chr);
	      
	      /* Control: Chromosome available? */
	      if (key == NOTFOUND)
		{
		  /* Current read is not included into the calculations */
		}
	      else
		{
		  /* Control: Out of range? */
		  if (pos >= ChrSizes[key] || pos < AVGL)
		    {
		      /* Current read is not included into the calculations */
		    }
		  else
		    {
		      /* Update the number of reads in this interval of positions */
		      for(i=pos1; i < pos2; i++) 
			{
			  READS[key][i]++; 
			}
		    }
		  
		  /* Increase the total number of valid reads */
		  m->nReads++;
		}
	    }
	}
    }
  
  /* One million reads are necessary for normalization  (DEMO mode omits this control) */
  if (m->nReads < MEGA && DEMO==FALSE)
    {
      sprintf(mess,"The number of reads is low (%ld, minimum: %d)",m->nReads,MEGA);
      printError(mess);
    }
  
  /* Close the SAM file and other structures */
  samclose(file);
  bam_destroy1(read);
  bam_header_destroy(info);
}
