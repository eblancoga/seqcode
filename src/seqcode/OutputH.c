/*************************************************************************
*                                                                        *
*   Module: OutputH                                                      *
*                                                                        *
*   Management: Generate for every gene the row in the heat map          *
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
extern int WINDOWRES;
extern float NOISET;
extern int NORM;
extern int SPIKEIN;


/* Preprocess and generate each row for a heat map */
void OutputOneGeneHeatFile(char* gene,
			   long* REGION,
			   int L,
			   long nreads,
			   FILE* file)
{
  /* Number of elements to visit */
  int i;
  float total;
  float avg;
  float value;

  /* Normalization factor */
  float normfactor;

  /* Gene symbol name */
  fprintf(file,"%s\t",gene);

  total = 0.0;

  /* -L:0:+L REGION */
  for(i=0; i < (2*L)/WINDOWRES; i++)
    {
      value = (double) REGION[i];

      /* transform into log scale to uniform the scale */
      if (SPIKEIN>0)
	{
	  /* Reference-adjusted normalization: total number of reads of the spike/refence */
	  normfactor = (float)SPIKEIN/MEGA;
	  value = value/normfactor;
	}
      else
	{
	  if (NORM>0)
	    {
	      /* Traditional model: total number of reads of the sample */
	      normfactor = (float)nreads/MEGA;
	      value = value/normfactor;
	    }
	  else
	    {
	      /* No normalization */
	    }
	}

      /* Log-scale of each spot in the heat map */
      value = (value>0)?log10(value):0;
      
      /* Filter to remove low quality areas: useful for abundant samples */
      if (value<NOISET)
      	{
	  value = 0.0;
	} 

      fprintf(file,"%.1f\t",value);
      total = total + value;
    }

  /* Computing the avg.value for sorting */
  avg = total/((2*L)/WINDOWRES);

  fprintf(file,"%.2lf\n",avg);
}

/* Preprocess and generate each row for a combined heat map */
void OutputOneGeneCombinedHeatFile(char* gene,
				   long* REGION,
				   int L,
				   FILE* file)
{
  /* Number of elements to visit */
  int i;
  float total;
  float avg;
  float value;

  /* Gene symbol name */
  fprintf(file,"%s\t",gene);

  total = 0.0;

  /* -L:0:+L REGION */
  for(i=0; i < (2*L)/WINDOWRES; i++)
    {
      value = (double) REGION[i];

      /* Filter to remove low quality areas: useful for abundant samples */
      if ((value>0 && value<NOISET) || (value<0 && value>-NOISET))
      	{
	  value = 0.0;
	} 

      fprintf(file,"%.1f\t",value);
      total = total + value;
    }

  /* Computing the avg.value for sorting */
  avg = total/((2*L)/WINDOWRES);

  fprintf(file,"%.2lf\n",avg);
}

/* Preprocess and generate each row for a gene heat map */
void OutputOneGeneGENEHeatFile(char* gene,
			       long* UPSTREAM,
			       long* IDEALGENE,
			       long* DOWNSTREAM,
			       int L,
			       long nreads,
			       FILE* file)
{
  /* Number of elements to visit */
  int i;
  float total;
  float avg;
  float value;

  /* Gene symbol name */
  fprintf(file,"%s\t",gene);

  total = 0.0;
  
  /* UPSTREAM REGION (L) */
  for(i=0; i<(L/WINDOWRES); i++)
    {
      value = (double) UPSTREAM[i];

      /* transform into log scale to uniform the scale */
      value = (value>0)?log10(value):0;
      
      /* Filter to remove low quality areas: useful for abundant samples */
      if (value<NOISET)
      	{
	  value = 0.0;
	} 
      
      fprintf(file,"%.1f\t",value);
      total = total + value;
    }

  /* GENE REGION (2*L) */
  for(i=0; i<(L/WINDOWRES); i++)
    {
      value = (double) IDEALGENE[i];

      /* transform into log scale to uniform the scale */
      value = (value>0)?log10(value):0;
      
      /* Filter to remove low quality areas: useful for abundant samples */
      if (value<NOISET)
      	{
	  value = 0.0;
	} 

      fprintf(file,"%.1f\t%.1f\t",value,value);
      total = total + (value)*2;
    }

  /* DOWNSTREAM REGION (L) */
  for(i=0; i<(L/WINDOWRES); i++)
    {
      value = (double) DOWNSTREAM[i];

      /* transform into log scale to uniform the scale */
      value = (value>0)?log10(value):0;

      /* Filter to remove low quality areas: useful for abundant samples */
      if (value<NOISET)
      	{
	  value = 0.0;
	} 

      fprintf(file,"%.1f\t",value);
      total = total + value;
    }

  /* Computing the avg.value for sorting */
  avg = total/((4*L)/WINDOWRES);

  fprintf(file,"%.2lf\n",avg);
}

