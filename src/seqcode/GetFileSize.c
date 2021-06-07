/*************************************************************************
*                                                                        *
*   Module: GetFileSize                                                  *
*                                                                        *
*   Find the size of input files (info)                                  *
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

/* Size of the input file */
long GetFileSize(char* File)
{
  struct stat *buf;
  long size;

  if ((buf = (struct stat*) malloc(sizeof(struct stat))) == NULL)
    printError("Not enough memory to analyze the file");

  if (stat(File,buf) != 0)
    printError("Impossible to access the file");

  /* Size (bytes) of this file */
  size = (long)buf->st_size;

  if (size == 0)
    printError("Empty file!");

  free(buf);

  return(size);
}

