/*************************************************************************
*                                                                        *
*   Module: ReadPhastConsFiles                                           *
*                                                                        *
*   Process the PhastCons scores (WIG format)                            *
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

void ReadPhastConsFiles(char* Folder,
			long* ChrSizes,
			dict* ChrNames,
			float** PHASTCONS)
{

  char FileName[FILENAMELENGTH];
  long FileSize;

  /* Number of chromosomes into the BG file */
  long nChromosomes;
  
  int i;
  node *p;
  long nLines;

  char mess[MAXSTRING];

  
  /* 1. Reset counters */
  nChromosomes = 0;
  
  /* 2. Visit the chromosomes in the dictionary to read the PhastCons profiles */ 
  for(i=0 ; i < MAXENTRY ; i++)
    {
      if(ChrNames->T[i]!=NULL)     
        {
          /* Explore the nodes in this position */
          p = ChrNames->T[i];
          
          /* Searching the first position free */
          while( p!= NULL )
            {
	      /* Accessing the PhastCons file of the current chromosome */
	      sprintf(FileName,"%s/%s.data",Folder,p->s);

	      FileSize = GetFileSize(FileName);
	      sprintf(mess,"Processing chromosome %s: %.2lf Mb",FileName,(float)FileSize/MEGABYTE);
	      printRes(mess);
  
	      /* Read the PhastCons profile */
	      nLines = ReadWIGFile(FileName,ChrSizes,ChrNames,PHASTCONS);
	      sprintf(mess,"%ld lines",nLines);
              printRes(mess);
	      
	      /* Next chromosome in this position */
              nChromosomes++;
              p = p->next;
	    }
	}
    }
}


