/*************************************************************************
*                                                                        *
*   Module: ColorManager                                                 *
*                                                                        *
*   Control the use of R colors in SeqCode plots                         *
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

void LoadRColors(dict* RColors,
		 char RGBcodes[MAXCOLORS][MAXRGBCODE])
{
  /* Code for the hash */
  int key;               

  /* Register each color ant the RGB code into the dictionary */
  key = setkeyDict(RColors,"white"); strcpy(RGBcodes[key],"255,255,255");
  key = setkeyDict(RColors,"aliceblue"); strcpy(RGBcodes[key],"240,248,255");
  key = setkeyDict(RColors,"antiquewhite"); strcpy(RGBcodes[key],"250,235,215");
  key = setkeyDict(RColors,"antiquewhite1"); strcpy(RGBcodes[key],"255,239,219");
  key = setkeyDict(RColors,"antiquewhite2"); strcpy(RGBcodes[key],"238,223,204");
  key = setkeyDict(RColors,"antiquewhite3"); strcpy(RGBcodes[key],"205,192,176");
  key = setkeyDict(RColors,"antiquewhite4"); strcpy(RGBcodes[key],"139,131,120");
  key = setkeyDict(RColors,"aquamarine"); strcpy(RGBcodes[key],"127,255,212");
  key = setkeyDict(RColors,"aquamarine1"); strcpy(RGBcodes[key],"127,255,212");
  key = setkeyDict(RColors,"aquamarine2"); strcpy(RGBcodes[key],"118,238,198");
  key = setkeyDict(RColors,"aquamarine3"); strcpy(RGBcodes[key],"102,205,170");
  key = setkeyDict(RColors,"aquamarine4"); strcpy(RGBcodes[key],"69,139,116");
  key = setkeyDict(RColors,"azure"); strcpy(RGBcodes[key],"240,255,255");
  key = setkeyDict(RColors,"azure1"); strcpy(RGBcodes[key],"240,255,255");
  key = setkeyDict(RColors,"azure2"); strcpy(RGBcodes[key],"224,238,238");
  key = setkeyDict(RColors,"azure3"); strcpy(RGBcodes[key],"193,205,205");
  key = setkeyDict(RColors,"azure4"); strcpy(RGBcodes[key],"131,139,139");
  key = setkeyDict(RColors,"beige"); strcpy(RGBcodes[key],"245,245,220");
  key = setkeyDict(RColors,"bisque"); strcpy(RGBcodes[key],"255,228,196");
  key = setkeyDict(RColors,"bisque1"); strcpy(RGBcodes[key],"255,228,196");
  key = setkeyDict(RColors,"bisque2"); strcpy(RGBcodes[key],"238,213,183");
  key = setkeyDict(RColors,"bisque3"); strcpy(RGBcodes[key],"205,183,158");
  key = setkeyDict(RColors,"bisque4"); strcpy(RGBcodes[key],"139,125,107");
  key = setkeyDict(RColors,"black"); strcpy(RGBcodes[key],"0,0,0");
  key = setkeyDict(RColors,"blanchedalmond"); strcpy(RGBcodes[key],"255,235,205");
  key = setkeyDict(RColors,"blue"); strcpy(RGBcodes[key],"0,0,255");
  key = setkeyDict(RColors,"blue1"); strcpy(RGBcodes[key],"0,0,255");
  key = setkeyDict(RColors,"blue2"); strcpy(RGBcodes[key],"0,0,238");
  key = setkeyDict(RColors,"blue3"); strcpy(RGBcodes[key],"0,0,205");
  key = setkeyDict(RColors,"blue4"); strcpy(RGBcodes[key],"0,0,139");
  key = setkeyDict(RColors,"blueviolet"); strcpy(RGBcodes[key],"138,43,226");
  key = setkeyDict(RColors,"brown"); strcpy(RGBcodes[key],"165,42,42");
  key = setkeyDict(RColors,"brown1"); strcpy(RGBcodes[key],"255,64,64");
  key = setkeyDict(RColors,"brown2"); strcpy(RGBcodes[key],"238,59,59");
  key = setkeyDict(RColors,"brown3"); strcpy(RGBcodes[key],"205,51,51");
  key = setkeyDict(RColors,"brown4"); strcpy(RGBcodes[key],"139,35,35");
  key = setkeyDict(RColors,"burlywood"); strcpy(RGBcodes[key],"222,184,135");
  key = setkeyDict(RColors,"burlywood1"); strcpy(RGBcodes[key],"255,211,155");
  key = setkeyDict(RColors,"burlywood2"); strcpy(RGBcodes[key],"238,197,145");
  key = setkeyDict(RColors,"burlywood3"); strcpy(RGBcodes[key],"205,170,125");
  key = setkeyDict(RColors,"burlywood4"); strcpy(RGBcodes[key],"139,115,85");
  key = setkeyDict(RColors,"cadetblue"); strcpy(RGBcodes[key],"95,158,160");
  key = setkeyDict(RColors,"cadetblue1"); strcpy(RGBcodes[key],"152,245,255");
  key = setkeyDict(RColors,"cadetblue2"); strcpy(RGBcodes[key],"142,229,238");
  key = setkeyDict(RColors,"cadetblue3"); strcpy(RGBcodes[key],"122,197,205");
  key = setkeyDict(RColors,"cadetblue4"); strcpy(RGBcodes[key],"83,134,139");
  key = setkeyDict(RColors,"chartreuse"); strcpy(RGBcodes[key],"127,255,0");
  key = setkeyDict(RColors,"chartreuse1"); strcpy(RGBcodes[key],"127,255,0");
  key = setkeyDict(RColors,"chartreuse2"); strcpy(RGBcodes[key],"118,238,0");
  key = setkeyDict(RColors,"chartreuse3"); strcpy(RGBcodes[key],"102,205,0");
  key = setkeyDict(RColors,"chartreuse4"); strcpy(RGBcodes[key],"69,139,0");
  key = setkeyDict(RColors,"chocolate"); strcpy(RGBcodes[key],"210,105,30");
  key = setkeyDict(RColors,"chocolate1"); strcpy(RGBcodes[key],"255,127,36");
  key = setkeyDict(RColors,"chocolate2"); strcpy(RGBcodes[key],"238,118,33");
  key = setkeyDict(RColors,"chocolate3"); strcpy(RGBcodes[key],"205,102,29");
  key = setkeyDict(RColors,"chocolate4"); strcpy(RGBcodes[key],"139,69,19");
  key = setkeyDict(RColors,"coral"); strcpy(RGBcodes[key],"255,127,80");
  key = setkeyDict(RColors,"coral1"); strcpy(RGBcodes[key],"255,114,86");
  key = setkeyDict(RColors,"coral2"); strcpy(RGBcodes[key],"238,106,80");
  key = setkeyDict(RColors,"coral3"); strcpy(RGBcodes[key],"205,91,69");
  key = setkeyDict(RColors,"coral4"); strcpy(RGBcodes[key],"139,62,47");
  key = setkeyDict(RColors,"cornflowerblue"); strcpy(RGBcodes[key],"100,149,237");
  key = setkeyDict(RColors,"cornsilk"); strcpy(RGBcodes[key],"255,248,220");
  key = setkeyDict(RColors,"cornsilk1"); strcpy(RGBcodes[key],"255,248,220");
  key = setkeyDict(RColors,"cornsilk2"); strcpy(RGBcodes[key],"238,232,205");
  key = setkeyDict(RColors,"cornsilk3"); strcpy(RGBcodes[key],"205,200,177");
  key = setkeyDict(RColors,"cornsilk4"); strcpy(RGBcodes[key],"139,136,120");
  key = setkeyDict(RColors,"cyan"); strcpy(RGBcodes[key],"0,255,255");
  key = setkeyDict(RColors,"cyan1"); strcpy(RGBcodes[key],"0,255,255");
  key = setkeyDict(RColors,"cyan2"); strcpy(RGBcodes[key],"0,238,238");
  key = setkeyDict(RColors,"cyan3"); strcpy(RGBcodes[key],"0,205,205");
  key = setkeyDict(RColors,"cyan4"); strcpy(RGBcodes[key],"0,139,139");
  key = setkeyDict(RColors,"darkblue"); strcpy(RGBcodes[key],"0,0,139");
  key = setkeyDict(RColors,"darkcyan"); strcpy(RGBcodes[key],"0,139,139");
  key = setkeyDict(RColors,"darkgoldenrod"); strcpy(RGBcodes[key],"184,134,11");
  key = setkeyDict(RColors,"darkgoldenrod1"); strcpy(RGBcodes[key],"255,185,15");
  key = setkeyDict(RColors,"darkgoldenrod2"); strcpy(RGBcodes[key],"238,173,14");
  key = setkeyDict(RColors,"darkgoldenrod3"); strcpy(RGBcodes[key],"205,149,12");
  key = setkeyDict(RColors,"darkgoldenrod4"); strcpy(RGBcodes[key],"139,101,8");
  key = setkeyDict(RColors,"darkgray"); strcpy(RGBcodes[key],"169,169,169");
  key = setkeyDict(RColors,"darkgreen"); strcpy(RGBcodes[key],"0,100,0");
  key = setkeyDict(RColors,"darkgrey"); strcpy(RGBcodes[key],"169,169,169");
  key = setkeyDict(RColors,"darkkhaki"); strcpy(RGBcodes[key],"189,183,107");
  key = setkeyDict(RColors,"darkmagenta"); strcpy(RGBcodes[key],"139,0,139");
  key = setkeyDict(RColors,"darkolivegreen"); strcpy(RGBcodes[key],"85,107,47");
  key = setkeyDict(RColors,"darkolivegreen1"); strcpy(RGBcodes[key],"202,255,112");
  key = setkeyDict(RColors,"darkolivegreen2"); strcpy(RGBcodes[key],"188,238,104");
  key = setkeyDict(RColors,"darkolivegreen3"); strcpy(RGBcodes[key],"162,205,90");
  key = setkeyDict(RColors,"darkolivegreen4"); strcpy(RGBcodes[key],"110,139,61");
  key = setkeyDict(RColors,"darkorange"); strcpy(RGBcodes[key],"255,140,0");
  key = setkeyDict(RColors,"darkorange1"); strcpy(RGBcodes[key],"255,127,0");
  key = setkeyDict(RColors,"darkorange2"); strcpy(RGBcodes[key],"238,118,0");
  key = setkeyDict(RColors,"darkorange3"); strcpy(RGBcodes[key],"205,102,0");
  key = setkeyDict(RColors,"darkorange4"); strcpy(RGBcodes[key],"139,69,0");
  key = setkeyDict(RColors,"darkorchid"); strcpy(RGBcodes[key],"153,50,204");
  key = setkeyDict(RColors,"darkorchid1"); strcpy(RGBcodes[key],"191,62,255");
  key = setkeyDict(RColors,"darkorchid2"); strcpy(RGBcodes[key],"178,58,238");
  key = setkeyDict(RColors,"darkorchid3"); strcpy(RGBcodes[key],"154,50,205");
  key = setkeyDict(RColors,"darkorchid4"); strcpy(RGBcodes[key],"104,34,139");
  key = setkeyDict(RColors,"darkred"); strcpy(RGBcodes[key],"139,0,0");
  key = setkeyDict(RColors,"darksalmon"); strcpy(RGBcodes[key],"233,150,122");
  key = setkeyDict(RColors,"darkseagreen"); strcpy(RGBcodes[key],"143,188,143");
  key = setkeyDict(RColors,"darkseagreen1"); strcpy(RGBcodes[key],"193,255,193");
  key = setkeyDict(RColors,"darkseagreen2"); strcpy(RGBcodes[key],"180,238,180");
  key = setkeyDict(RColors,"darkseagreen3"); strcpy(RGBcodes[key],"155,205,155");
  key = setkeyDict(RColors,"darkseagreen4"); strcpy(RGBcodes[key],"105,139,105");
  key = setkeyDict(RColors,"darkslateblue"); strcpy(RGBcodes[key],"72,61,139");
  key = setkeyDict(RColors,"darkslategray"); strcpy(RGBcodes[key],"47,79,79");
  key = setkeyDict(RColors,"darkslategray1"); strcpy(RGBcodes[key],"151,255,255");
  key = setkeyDict(RColors,"darkslategray2"); strcpy(RGBcodes[key],"141,238,238");
  key = setkeyDict(RColors,"darkslategray3"); strcpy(RGBcodes[key],"121,205,205");
  key = setkeyDict(RColors,"darkslategray4"); strcpy(RGBcodes[key],"82,139,139");
  key = setkeyDict(RColors,"darkslategrey"); strcpy(RGBcodes[key],"47,79,79");
  key = setkeyDict(RColors,"darkturquoise"); strcpy(RGBcodes[key],"0,206,209");
  key = setkeyDict(RColors,"darkviolet"); strcpy(RGBcodes[key],"148,0,211");
  key = setkeyDict(RColors,"deeppink"); strcpy(RGBcodes[key],"255,20,147");
  key = setkeyDict(RColors,"deeppink1"); strcpy(RGBcodes[key],"255,20,147");
  key = setkeyDict(RColors,"deeppink2"); strcpy(RGBcodes[key],"238,18,137");
  key = setkeyDict(RColors,"deeppink3"); strcpy(RGBcodes[key],"205,16,118");
  key = setkeyDict(RColors,"deeppink4"); strcpy(RGBcodes[key],"139,10,80");
  key = setkeyDict(RColors,"deepskyblue"); strcpy(RGBcodes[key],"0,191,255");
  key = setkeyDict(RColors,"deepskyblue1"); strcpy(RGBcodes[key],"0,191,255");
  key = setkeyDict(RColors,"deepskyblue2"); strcpy(RGBcodes[key],"0,178,238");
  key = setkeyDict(RColors,"deepskyblue3"); strcpy(RGBcodes[key],"0,154,205");
  key = setkeyDict(RColors,"deepskyblue4"); strcpy(RGBcodes[key],"0,104,139");
  key = setkeyDict(RColors,"dimgray"); strcpy(RGBcodes[key],"105,105,105");
  key = setkeyDict(RColors,"dimgrey"); strcpy(RGBcodes[key],"105,105,105");
  key = setkeyDict(RColors,"dodgerblue"); strcpy(RGBcodes[key],"30,144,255");
  key = setkeyDict(RColors,"dodgerblue1"); strcpy(RGBcodes[key],"30,144,255");
  key = setkeyDict(RColors,"dodgerblue2"); strcpy(RGBcodes[key],"28,134,238");
  key = setkeyDict(RColors,"dodgerblue3"); strcpy(RGBcodes[key],"24,116,205");
  key = setkeyDict(RColors,"dodgerblue4"); strcpy(RGBcodes[key],"16,78,139");
  key = setkeyDict(RColors,"firebrick"); strcpy(RGBcodes[key],"178,34,34");
  key = setkeyDict(RColors,"firebrick1"); strcpy(RGBcodes[key],"255,48,48");
  key = setkeyDict(RColors,"firebrick2"); strcpy(RGBcodes[key],"238,44,44");
  key = setkeyDict(RColors,"firebrick3"); strcpy(RGBcodes[key],"205,38,38");
  key = setkeyDict(RColors,"firebrick4"); strcpy(RGBcodes[key],"139,26,26");
  key = setkeyDict(RColors,"floralwhite"); strcpy(RGBcodes[key],"255,250,240");
  key = setkeyDict(RColors,"forestgreen"); strcpy(RGBcodes[key],"34,139,34");
  key = setkeyDict(RColors,"gainsboro"); strcpy(RGBcodes[key],"220,220,220");
  key = setkeyDict(RColors,"ghostwhite"); strcpy(RGBcodes[key],"248,248,255");
  key = setkeyDict(RColors,"gold"); strcpy(RGBcodes[key],"255,215,0");
  key = setkeyDict(RColors,"gold1"); strcpy(RGBcodes[key],"255,215,0");
  key = setkeyDict(RColors,"gold2"); strcpy(RGBcodes[key],"238,201,0");
  key = setkeyDict(RColors,"gold3"); strcpy(RGBcodes[key],"205,173,0");
  key = setkeyDict(RColors,"gold4"); strcpy(RGBcodes[key],"139,117,0");
  key = setkeyDict(RColors,"goldenrod"); strcpy(RGBcodes[key],"218,165,32");
  key = setkeyDict(RColors,"goldenrod1"); strcpy(RGBcodes[key],"255,193,37");
  key = setkeyDict(RColors,"goldenrod2"); strcpy(RGBcodes[key],"238,180,34");
  key = setkeyDict(RColors,"goldenrod3"); strcpy(RGBcodes[key],"205,155,29");
  key = setkeyDict(RColors,"goldenrod4"); strcpy(RGBcodes[key],"139,105,20");
  key = setkeyDict(RColors,"gray"); strcpy(RGBcodes[key],"190,190,190");
  key = setkeyDict(RColors,"gray0"); strcpy(RGBcodes[key],"0,0,0");
  key = setkeyDict(RColors,"gray1"); strcpy(RGBcodes[key],"3,3,3");
  key = setkeyDict(RColors,"gray2"); strcpy(RGBcodes[key],"5,5,5");
  key = setkeyDict(RColors,"gray3"); strcpy(RGBcodes[key],"8,8,8");
  key = setkeyDict(RColors,"gray4"); strcpy(RGBcodes[key],"10,10,10");
  key = setkeyDict(RColors,"gray5"); strcpy(RGBcodes[key],"13,13,13");
  key = setkeyDict(RColors,"gray6"); strcpy(RGBcodes[key],"15,15,15");
  key = setkeyDict(RColors,"gray7"); strcpy(RGBcodes[key],"18,18,18");
  key = setkeyDict(RColors,"gray8"); strcpy(RGBcodes[key],"20,20,20");
  key = setkeyDict(RColors,"gray9"); strcpy(RGBcodes[key],"23,23,23");
  key = setkeyDict(RColors,"gray10"); strcpy(RGBcodes[key],"26,26,26");
  key = setkeyDict(RColors,"gray11"); strcpy(RGBcodes[key],"28,28,28");
  key = setkeyDict(RColors,"gray12"); strcpy(RGBcodes[key],"31,31,31");
  key = setkeyDict(RColors,"gray13"); strcpy(RGBcodes[key],"33,33,33");
  key = setkeyDict(RColors,"gray14"); strcpy(RGBcodes[key],"36,36,36");
  key = setkeyDict(RColors,"gray15"); strcpy(RGBcodes[key],"38,38,38");
  key = setkeyDict(RColors,"gray16"); strcpy(RGBcodes[key],"41,41,41");
  key = setkeyDict(RColors,"gray17"); strcpy(RGBcodes[key],"43,43,43");
  key = setkeyDict(RColors,"gray18"); strcpy(RGBcodes[key],"46,46,46");
  key = setkeyDict(RColors,"gray19"); strcpy(RGBcodes[key],"48,48,48");
  key = setkeyDict(RColors,"gray20"); strcpy(RGBcodes[key],"51,51,51");
  key = setkeyDict(RColors,"gray21"); strcpy(RGBcodes[key],"54,54,54");
  key = setkeyDict(RColors,"gray22"); strcpy(RGBcodes[key],"56,56,56");
  key = setkeyDict(RColors,"gray23"); strcpy(RGBcodes[key],"59,59,59");
  key = setkeyDict(RColors,"gray24"); strcpy(RGBcodes[key],"61,61,61");
  key = setkeyDict(RColors,"gray25"); strcpy(RGBcodes[key],"64,64,64");
  key = setkeyDict(RColors,"gray26"); strcpy(RGBcodes[key],"66,66,66");
  key = setkeyDict(RColors,"gray27"); strcpy(RGBcodes[key],"69,69,69");
  key = setkeyDict(RColors,"gray28"); strcpy(RGBcodes[key],"71,71,71");
  key = setkeyDict(RColors,"gray29"); strcpy(RGBcodes[key],"74,74,74");
  key = setkeyDict(RColors,"gray30"); strcpy(RGBcodes[key],"77,77,77");
  key = setkeyDict(RColors,"gray31"); strcpy(RGBcodes[key],"79,79,79");
  key = setkeyDict(RColors,"gray32"); strcpy(RGBcodes[key],"82,82,82");
  key = setkeyDict(RColors,"gray33"); strcpy(RGBcodes[key],"84,84,84");
  key = setkeyDict(RColors,"gray34"); strcpy(RGBcodes[key],"87,87,87");
  key = setkeyDict(RColors,"gray35"); strcpy(RGBcodes[key],"89,89,89");
  key = setkeyDict(RColors,"gray36"); strcpy(RGBcodes[key],"92,92,92");
  key = setkeyDict(RColors,"gray37"); strcpy(RGBcodes[key],"94,94,94");
  key = setkeyDict(RColors,"gray38"); strcpy(RGBcodes[key],"97,97,97");
  key = setkeyDict(RColors,"gray39"); strcpy(RGBcodes[key],"99,99,99");
  key = setkeyDict(RColors,"gray40"); strcpy(RGBcodes[key],"102,102,102");
  key = setkeyDict(RColors,"gray41"); strcpy(RGBcodes[key],"105,105,105");
  key = setkeyDict(RColors,"gray42"); strcpy(RGBcodes[key],"107,107,107");
  key = setkeyDict(RColors,"gray43"); strcpy(RGBcodes[key],"110,110,110");
  key = setkeyDict(RColors,"gray44"); strcpy(RGBcodes[key],"112,112,112");
  key = setkeyDict(RColors,"gray45"); strcpy(RGBcodes[key],"115,115,115");
  key = setkeyDict(RColors,"gray46"); strcpy(RGBcodes[key],"117,117,117");
  key = setkeyDict(RColors,"gray47"); strcpy(RGBcodes[key],"120,120,120");
  key = setkeyDict(RColors,"gray48"); strcpy(RGBcodes[key],"122,122,122");
  key = setkeyDict(RColors,"gray49"); strcpy(RGBcodes[key],"125,125,125");
  key = setkeyDict(RColors,"gray50"); strcpy(RGBcodes[key],"127,127,127");
  key = setkeyDict(RColors,"gray51"); strcpy(RGBcodes[key],"130,130,130");
  key = setkeyDict(RColors,"gray52"); strcpy(RGBcodes[key],"133,133,133");
  key = setkeyDict(RColors,"gray53"); strcpy(RGBcodes[key],"135,135,135");
  key = setkeyDict(RColors,"gray54"); strcpy(RGBcodes[key],"138,138,138");
  key = setkeyDict(RColors,"gray55"); strcpy(RGBcodes[key],"140,140,140");
  key = setkeyDict(RColors,"gray56"); strcpy(RGBcodes[key],"143,143,143");
  key = setkeyDict(RColors,"gray57"); strcpy(RGBcodes[key],"145,145,145");
  key = setkeyDict(RColors,"gray58"); strcpy(RGBcodes[key],"148,148,148");
  key = setkeyDict(RColors,"gray59"); strcpy(RGBcodes[key],"150,150,150");
  key = setkeyDict(RColors,"gray60"); strcpy(RGBcodes[key],"153,153,153");
  key = setkeyDict(RColors,"gray61"); strcpy(RGBcodes[key],"156,156,156");
  key = setkeyDict(RColors,"gray62"); strcpy(RGBcodes[key],"158,158,158");
  key = setkeyDict(RColors,"gray63"); strcpy(RGBcodes[key],"161,161,161");
  key = setkeyDict(RColors,"gray64"); strcpy(RGBcodes[key],"163,163,163");
  key = setkeyDict(RColors,"gray65"); strcpy(RGBcodes[key],"166,166,166");
  key = setkeyDict(RColors,"gray66"); strcpy(RGBcodes[key],"168,168,168");
  key = setkeyDict(RColors,"gray67"); strcpy(RGBcodes[key],"171,171,171");
  key = setkeyDict(RColors,"gray68"); strcpy(RGBcodes[key],"173,173,173");
  key = setkeyDict(RColors,"gray69"); strcpy(RGBcodes[key],"176,176,176");
  key = setkeyDict(RColors,"gray70"); strcpy(RGBcodes[key],"179,179,179");
  key = setkeyDict(RColors,"gray71"); strcpy(RGBcodes[key],"181,181,181");
  key = setkeyDict(RColors,"gray72"); strcpy(RGBcodes[key],"184,184,184");
  key = setkeyDict(RColors,"gray73"); strcpy(RGBcodes[key],"186,186,186");
  key = setkeyDict(RColors,"gray74"); strcpy(RGBcodes[key],"189,189,189");
  key = setkeyDict(RColors,"gray75"); strcpy(RGBcodes[key],"191,191,191");
  key = setkeyDict(RColors,"gray76"); strcpy(RGBcodes[key],"194,194,194");
  key = setkeyDict(RColors,"gray77"); strcpy(RGBcodes[key],"196,196,196");
  key = setkeyDict(RColors,"gray78"); strcpy(RGBcodes[key],"199,199,199");
  key = setkeyDict(RColors,"gray79"); strcpy(RGBcodes[key],"201,201,201");
  key = setkeyDict(RColors,"gray80"); strcpy(RGBcodes[key],"204,204,204");
  key = setkeyDict(RColors,"gray81"); strcpy(RGBcodes[key],"207,207,207");
  key = setkeyDict(RColors,"gray82"); strcpy(RGBcodes[key],"209,209,209");
  key = setkeyDict(RColors,"gray83"); strcpy(RGBcodes[key],"212,212,212");
  key = setkeyDict(RColors,"gray84"); strcpy(RGBcodes[key],"214,214,214");
  key = setkeyDict(RColors,"gray85"); strcpy(RGBcodes[key],"217,217,217");
  key = setkeyDict(RColors,"gray86"); strcpy(RGBcodes[key],"219,219,219");
  key = setkeyDict(RColors,"gray87"); strcpy(RGBcodes[key],"222,222,222");
  key = setkeyDict(RColors,"gray88"); strcpy(RGBcodes[key],"224,224,224");
  key = setkeyDict(RColors,"gray89"); strcpy(RGBcodes[key],"227,227,227");
  key = setkeyDict(RColors,"gray90"); strcpy(RGBcodes[key],"229,229,229");
  key = setkeyDict(RColors,"gray91"); strcpy(RGBcodes[key],"232,232,232");
  key = setkeyDict(RColors,"gray92"); strcpy(RGBcodes[key],"235,235,235");
  key = setkeyDict(RColors,"gray93"); strcpy(RGBcodes[key],"237,237,237");
  key = setkeyDict(RColors,"gray94"); strcpy(RGBcodes[key],"240,240,240");
  key = setkeyDict(RColors,"gray95"); strcpy(RGBcodes[key],"242,242,242");
  key = setkeyDict(RColors,"gray96"); strcpy(RGBcodes[key],"245,245,245");
  key = setkeyDict(RColors,"gray97"); strcpy(RGBcodes[key],"247,247,247");
  key = setkeyDict(RColors,"gray98"); strcpy(RGBcodes[key],"250,250,250");
  key = setkeyDict(RColors,"gray99"); strcpy(RGBcodes[key],"252,252,252");
  key = setkeyDict(RColors,"gray100"); strcpy(RGBcodes[key],"255,255,255");
  key = setkeyDict(RColors,"green"); strcpy(RGBcodes[key],"0,255,0");
  key = setkeyDict(RColors,"green1"); strcpy(RGBcodes[key],"0,255,0");
  key = setkeyDict(RColors,"green2"); strcpy(RGBcodes[key],"0,238,0");
  key = setkeyDict(RColors,"green3"); strcpy(RGBcodes[key],"0,205,0");
  key = setkeyDict(RColors,"green4"); strcpy(RGBcodes[key],"0,139,0");
  key = setkeyDict(RColors,"greenyellow"); strcpy(RGBcodes[key],"173,255,47");
  key = setkeyDict(RColors,"grey"); strcpy(RGBcodes[key],"190,190,190");
  key = setkeyDict(RColors,"grey0"); strcpy(RGBcodes[key],"0,0,0");
  key = setkeyDict(RColors,"grey1"); strcpy(RGBcodes[key],"3,3,3");
  key = setkeyDict(RColors,"grey2"); strcpy(RGBcodes[key],"5,5,5");
  key = setkeyDict(RColors,"grey3"); strcpy(RGBcodes[key],"8,8,8");
  key = setkeyDict(RColors,"grey4"); strcpy(RGBcodes[key],"10,10,10");
  key = setkeyDict(RColors,"grey5"); strcpy(RGBcodes[key],"13,13,13");
  key = setkeyDict(RColors,"grey6"); strcpy(RGBcodes[key],"15,15,15");
  key = setkeyDict(RColors,"grey7"); strcpy(RGBcodes[key],"18,18,18");
  key = setkeyDict(RColors,"grey8"); strcpy(RGBcodes[key],"20,20,20");
  key = setkeyDict(RColors,"grey9"); strcpy(RGBcodes[key],"23,23,23");
  key = setkeyDict(RColors,"grey10"); strcpy(RGBcodes[key],"26,26,26");
  key = setkeyDict(RColors,"grey11"); strcpy(RGBcodes[key],"28,28,28");
  key = setkeyDict(RColors,"grey12"); strcpy(RGBcodes[key],"31,31,31");
  key = setkeyDict(RColors,"grey13"); strcpy(RGBcodes[key],"33,33,33");
  key = setkeyDict(RColors,"grey14"); strcpy(RGBcodes[key],"36,36,36");
  key = setkeyDict(RColors,"grey15"); strcpy(RGBcodes[key],"38,38,38");
  key = setkeyDict(RColors,"grey16"); strcpy(RGBcodes[key],"41,41,41");
  key = setkeyDict(RColors,"grey17"); strcpy(RGBcodes[key],"43,43,43");
  key = setkeyDict(RColors,"grey18"); strcpy(RGBcodes[key],"46,46,46");
  key = setkeyDict(RColors,"grey19"); strcpy(RGBcodes[key],"48,48,48");
  key = setkeyDict(RColors,"grey20"); strcpy(RGBcodes[key],"51,51,51");
  key = setkeyDict(RColors,"grey21"); strcpy(RGBcodes[key],"54,54,54");
  key = setkeyDict(RColors,"grey22"); strcpy(RGBcodes[key],"56,56,56");
  key = setkeyDict(RColors,"grey23"); strcpy(RGBcodes[key],"59,59,59");
  key = setkeyDict(RColors,"grey24"); strcpy(RGBcodes[key],"61,61,61");
  key = setkeyDict(RColors,"grey25"); strcpy(RGBcodes[key],"64,64,64");
  key = setkeyDict(RColors,"grey26"); strcpy(RGBcodes[key],"66,66,66");
  key = setkeyDict(RColors,"grey27"); strcpy(RGBcodes[key],"69,69,69");
  key = setkeyDict(RColors,"grey28"); strcpy(RGBcodes[key],"71,71,71");
  key = setkeyDict(RColors,"grey29"); strcpy(RGBcodes[key],"74,74,74");
  key = setkeyDict(RColors,"grey30"); strcpy(RGBcodes[key],"77,77,77");
  key = setkeyDict(RColors,"grey31"); strcpy(RGBcodes[key],"79,79,79");
  key = setkeyDict(RColors,"grey32"); strcpy(RGBcodes[key],"82,82,82");
  key = setkeyDict(RColors,"grey33"); strcpy(RGBcodes[key],"84,84,84");
  key = setkeyDict(RColors,"grey34"); strcpy(RGBcodes[key],"87,87,87");
  key = setkeyDict(RColors,"grey35"); strcpy(RGBcodes[key],"89,89,89");
  key = setkeyDict(RColors,"grey36"); strcpy(RGBcodes[key],"92,92,92");
  key = setkeyDict(RColors,"grey37"); strcpy(RGBcodes[key],"94,94,94");
  key = setkeyDict(RColors,"grey38"); strcpy(RGBcodes[key],"97,97,97");
  key = setkeyDict(RColors,"grey39"); strcpy(RGBcodes[key],"99,99,99");
  key = setkeyDict(RColors,"grey40"); strcpy(RGBcodes[key],"102,102,102");
  key = setkeyDict(RColors,"grey41"); strcpy(RGBcodes[key],"105,105,105");
  key = setkeyDict(RColors,"grey42"); strcpy(RGBcodes[key],"107,107,107");
  key = setkeyDict(RColors,"grey43"); strcpy(RGBcodes[key],"110,110,110");
  key = setkeyDict(RColors,"grey44"); strcpy(RGBcodes[key],"112,112,112");
  key = setkeyDict(RColors,"grey45"); strcpy(RGBcodes[key],"115,115,115");
  key = setkeyDict(RColors,"grey46"); strcpy(RGBcodes[key],"117,117,117");
  key = setkeyDict(RColors,"grey47"); strcpy(RGBcodes[key],"120,120,120");
  key = setkeyDict(RColors,"grey48"); strcpy(RGBcodes[key],"122,122,122");
  key = setkeyDict(RColors,"grey49"); strcpy(RGBcodes[key],"125,125,125");
  key = setkeyDict(RColors,"grey50"); strcpy(RGBcodes[key],"127,127,127");
  key = setkeyDict(RColors,"grey51"); strcpy(RGBcodes[key],"130,130,130");
  key = setkeyDict(RColors,"grey52"); strcpy(RGBcodes[key],"133,133,133");
  key = setkeyDict(RColors,"grey53"); strcpy(RGBcodes[key],"135,135,135");
  key = setkeyDict(RColors,"grey54"); strcpy(RGBcodes[key],"138,138,138");
  key = setkeyDict(RColors,"grey55"); strcpy(RGBcodes[key],"140,140,140");
  key = setkeyDict(RColors,"grey56"); strcpy(RGBcodes[key],"143,143,143");
  key = setkeyDict(RColors,"grey57"); strcpy(RGBcodes[key],"145,145,145");
  key = setkeyDict(RColors,"grey58"); strcpy(RGBcodes[key],"148,148,148");
  key = setkeyDict(RColors,"grey59"); strcpy(RGBcodes[key],"150,150,150");
  key = setkeyDict(RColors,"grey60"); strcpy(RGBcodes[key],"153,153,153");
  key = setkeyDict(RColors,"grey61"); strcpy(RGBcodes[key],"156,156,156");
  key = setkeyDict(RColors,"grey62"); strcpy(RGBcodes[key],"158,158,158");
  key = setkeyDict(RColors,"grey63"); strcpy(RGBcodes[key],"161,161,161");
  key = setkeyDict(RColors,"grey64"); strcpy(RGBcodes[key],"163,163,163");
  key = setkeyDict(RColors,"grey65"); strcpy(RGBcodes[key],"166,166,166");
  key = setkeyDict(RColors,"grey66"); strcpy(RGBcodes[key],"168,168,168");
  key = setkeyDict(RColors,"grey67"); strcpy(RGBcodes[key],"171,171,171");
  key = setkeyDict(RColors,"grey68"); strcpy(RGBcodes[key],"173,173,173");
  key = setkeyDict(RColors,"grey69"); strcpy(RGBcodes[key],"176,176,176");
  key = setkeyDict(RColors,"grey70"); strcpy(RGBcodes[key],"179,179,179");
  key = setkeyDict(RColors,"grey71"); strcpy(RGBcodes[key],"181,181,181");
  key = setkeyDict(RColors,"grey72"); strcpy(RGBcodes[key],"184,184,184");
  key = setkeyDict(RColors,"grey73"); strcpy(RGBcodes[key],"186,186,186");
  key = setkeyDict(RColors,"grey74"); strcpy(RGBcodes[key],"189,189,189");
  key = setkeyDict(RColors,"grey75"); strcpy(RGBcodes[key],"191,191,191");
  key = setkeyDict(RColors,"grey76"); strcpy(RGBcodes[key],"194,194,194");
  key = setkeyDict(RColors,"grey77"); strcpy(RGBcodes[key],"196,196,196");
  key = setkeyDict(RColors,"grey78"); strcpy(RGBcodes[key],"199,199,199");
  key = setkeyDict(RColors,"grey79"); strcpy(RGBcodes[key],"201,201,201");
  key = setkeyDict(RColors,"grey80"); strcpy(RGBcodes[key],"204,204,204");
  key = setkeyDict(RColors,"grey81"); strcpy(RGBcodes[key],"207,207,207");
  key = setkeyDict(RColors,"grey82"); strcpy(RGBcodes[key],"209,209,209");
  key = setkeyDict(RColors,"grey83"); strcpy(RGBcodes[key],"212,212,212");
  key = setkeyDict(RColors,"grey84"); strcpy(RGBcodes[key],"214,214,214");
  key = setkeyDict(RColors,"grey85"); strcpy(RGBcodes[key],"217,217,217");
  key = setkeyDict(RColors,"grey86"); strcpy(RGBcodes[key],"219,219,219");
  key = setkeyDict(RColors,"grey87"); strcpy(RGBcodes[key],"222,222,222");
  key = setkeyDict(RColors,"grey88"); strcpy(RGBcodes[key],"224,224,224");
  key = setkeyDict(RColors,"grey89"); strcpy(RGBcodes[key],"227,227,227");
  key = setkeyDict(RColors,"grey90"); strcpy(RGBcodes[key],"229,229,229");
  key = setkeyDict(RColors,"grey91"); strcpy(RGBcodes[key],"232,232,232");
  key = setkeyDict(RColors,"grey92"); strcpy(RGBcodes[key],"235,235,235");
  key = setkeyDict(RColors,"grey93"); strcpy(RGBcodes[key],"237,237,237");
  key = setkeyDict(RColors,"grey94"); strcpy(RGBcodes[key],"240,240,240");
  key = setkeyDict(RColors,"grey95"); strcpy(RGBcodes[key],"242,242,242");
  key = setkeyDict(RColors,"grey96"); strcpy(RGBcodes[key],"245,245,245");
  key = setkeyDict(RColors,"grey97"); strcpy(RGBcodes[key],"247,247,247");
  key = setkeyDict(RColors,"grey98"); strcpy(RGBcodes[key],"250,250,250");
  key = setkeyDict(RColors,"grey99"); strcpy(RGBcodes[key],"252,252,252");
  key = setkeyDict(RColors,"grey100"); strcpy(RGBcodes[key],"255,255,255");
  key = setkeyDict(RColors,"honeydew"); strcpy(RGBcodes[key],"240,255,240");
  key = setkeyDict(RColors,"honeydew1"); strcpy(RGBcodes[key],"240,255,240");
  key = setkeyDict(RColors,"honeydew2"); strcpy(RGBcodes[key],"224,238,224");
  key = setkeyDict(RColors,"honeydew3"); strcpy(RGBcodes[key],"193,205,193");
  key = setkeyDict(RColors,"honeydew4"); strcpy(RGBcodes[key],"131,139,131");
  key = setkeyDict(RColors,"hotpink"); strcpy(RGBcodes[key],"255,105,180");
  key = setkeyDict(RColors,"hotpink1"); strcpy(RGBcodes[key],"255,110,180");
  key = setkeyDict(RColors,"hotpink2"); strcpy(RGBcodes[key],"238,106,167");
  key = setkeyDict(RColors,"hotpink3"); strcpy(RGBcodes[key],"205,96,144");
  key = setkeyDict(RColors,"hotpink4"); strcpy(RGBcodes[key],"139,58,98");
  key = setkeyDict(RColors,"indianred"); strcpy(RGBcodes[key],"205,92,92");
  key = setkeyDict(RColors,"indianred1"); strcpy(RGBcodes[key],"255,106,106");
  key = setkeyDict(RColors,"indianred2"); strcpy(RGBcodes[key],"238,99,99");
  key = setkeyDict(RColors,"indianred3"); strcpy(RGBcodes[key],"205,85,85");
  key = setkeyDict(RColors,"indianred4"); strcpy(RGBcodes[key],"139,58,58");
  key = setkeyDict(RColors,"ivory"); strcpy(RGBcodes[key],"255,255,240");
  key = setkeyDict(RColors,"ivory1"); strcpy(RGBcodes[key],"255,255,240");
  key = setkeyDict(RColors,"ivory2"); strcpy(RGBcodes[key],"238,238,224");
  key = setkeyDict(RColors,"ivory3"); strcpy(RGBcodes[key],"205,205,193");
  key = setkeyDict(RColors,"ivory4"); strcpy(RGBcodes[key],"139,139,131");
  key = setkeyDict(RColors,"khaki"); strcpy(RGBcodes[key],"240,230,140");
  key = setkeyDict(RColors,"khaki1"); strcpy(RGBcodes[key],"255,246,143");
  key = setkeyDict(RColors,"khaki2"); strcpy(RGBcodes[key],"238,230,133");
  key = setkeyDict(RColors,"khaki3"); strcpy(RGBcodes[key],"205,198,115");
  key = setkeyDict(RColors,"khaki4"); strcpy(RGBcodes[key],"139,134,78");
  key = setkeyDict(RColors,"lavender"); strcpy(RGBcodes[key],"230,230,250");
  key = setkeyDict(RColors,"lavenderblush"); strcpy(RGBcodes[key],"255,240,245");
  key = setkeyDict(RColors,"lavenderblush1"); strcpy(RGBcodes[key],"255,240,245");
  key = setkeyDict(RColors,"lavenderblush2"); strcpy(RGBcodes[key],"238,224,229");
  key = setkeyDict(RColors,"lavenderblush3"); strcpy(RGBcodes[key],"205,193,197");
  key = setkeyDict(RColors,"lavenderblush4"); strcpy(RGBcodes[key],"139,131,134");
  key = setkeyDict(RColors,"lawngreen"); strcpy(RGBcodes[key],"124,252,0");
  key = setkeyDict(RColors,"lemonchiffon"); strcpy(RGBcodes[key],"255,250,205");
  key = setkeyDict(RColors,"lemonchiffon1"); strcpy(RGBcodes[key],"255,250,205");
  key = setkeyDict(RColors,"lemonchiffon2"); strcpy(RGBcodes[key],"238,233,191");
  key = setkeyDict(RColors,"lemonchiffon3"); strcpy(RGBcodes[key],"205,201,165");
  key = setkeyDict(RColors,"lemonchiffon4"); strcpy(RGBcodes[key],"139,137,112");
  key = setkeyDict(RColors,"lightblue"); strcpy(RGBcodes[key],"173,216,230");
  key = setkeyDict(RColors,"lightblue1"); strcpy(RGBcodes[key],"191,239,255");
  key = setkeyDict(RColors,"lightblue2"); strcpy(RGBcodes[key],"178,223,238");
  key = setkeyDict(RColors,"lightblue3"); strcpy(RGBcodes[key],"154,192,205");
  key = setkeyDict(RColors,"lightblue4"); strcpy(RGBcodes[key],"104,131,139");
  key = setkeyDict(RColors,"lightcoral"); strcpy(RGBcodes[key],"240,128,128");
  key = setkeyDict(RColors,"lightcyan"); strcpy(RGBcodes[key],"224,255,255");
  key = setkeyDict(RColors,"lightcyan1"); strcpy(RGBcodes[key],"224,255,255");
  key = setkeyDict(RColors,"lightcyan2"); strcpy(RGBcodes[key],"209,238,238");
  key = setkeyDict(RColors,"lightcyan3"); strcpy(RGBcodes[key],"180,205,205");
  key = setkeyDict(RColors,"lightcyan4"); strcpy(RGBcodes[key],"122,139,139");
  key = setkeyDict(RColors,"lightgoldenrod"); strcpy(RGBcodes[key],"238,221,130");
  key = setkeyDict(RColors,"lightgoldenrod1"); strcpy(RGBcodes[key],"255,236,139");
  key = setkeyDict(RColors,"lightgoldenrod2"); strcpy(RGBcodes[key],"238,220,130");
  key = setkeyDict(RColors,"lightgoldenrod3"); strcpy(RGBcodes[key],"205,190,112");
  key = setkeyDict(RColors,"lightgoldenrod4"); strcpy(RGBcodes[key],"139,129,76");
  key = setkeyDict(RColors,"lightgoldenrodyellow"); strcpy(RGBcodes[key],"250,250,210");
  key = setkeyDict(RColors,"lightgray"); strcpy(RGBcodes[key],"211,211,211");
  key = setkeyDict(RColors,"lightgreen"); strcpy(RGBcodes[key],"144,238,144");
  key = setkeyDict(RColors,"lightgrey"); strcpy(RGBcodes[key],"211,211,211");
  key = setkeyDict(RColors,"lightpink"); strcpy(RGBcodes[key],"255,182,193");
  key = setkeyDict(RColors,"lightpink1"); strcpy(RGBcodes[key],"255,174,185");
  key = setkeyDict(RColors,"lightpink2"); strcpy(RGBcodes[key],"238,162,173");
  key = setkeyDict(RColors,"lightpink3"); strcpy(RGBcodes[key],"205,140,149");
  key = setkeyDict(RColors,"lightpink4"); strcpy(RGBcodes[key],"139,95,101");
  key = setkeyDict(RColors,"lightsalmon"); strcpy(RGBcodes[key],"255,160,122");
  key = setkeyDict(RColors,"lightsalmon1"); strcpy(RGBcodes[key],"255,160,122");
  key = setkeyDict(RColors,"lightsalmon2"); strcpy(RGBcodes[key],"238,149,114");
  key = setkeyDict(RColors,"lightsalmon3"); strcpy(RGBcodes[key],"205,129,98");
  key = setkeyDict(RColors,"lightsalmon4"); strcpy(RGBcodes[key],"139,87,66");
  key = setkeyDict(RColors,"lightseagreen"); strcpy(RGBcodes[key],"32,178,170");
  key = setkeyDict(RColors,"lightskyblue"); strcpy(RGBcodes[key],"135,206,250");
  key = setkeyDict(RColors,"lightskyblue1"); strcpy(RGBcodes[key],"176,226,255");
  key = setkeyDict(RColors,"lightskyblue2"); strcpy(RGBcodes[key],"164,211,238");
  key = setkeyDict(RColors,"lightskyblue3"); strcpy(RGBcodes[key],"141,182,205");
  key = setkeyDict(RColors,"lightskyblue4"); strcpy(RGBcodes[key],"96,123,139");
  key = setkeyDict(RColors,"lightslateblue"); strcpy(RGBcodes[key],"132,112,255");
  key = setkeyDict(RColors,"lightslategray"); strcpy(RGBcodes[key],"119,136,153");
  key = setkeyDict(RColors,"lightslategrey"); strcpy(RGBcodes[key],"119,136,153");
  key = setkeyDict(RColors,"lightsteelblue"); strcpy(RGBcodes[key],"176,196,222");
  key = setkeyDict(RColors,"lightsteelblue1"); strcpy(RGBcodes[key],"202,225,255");
  key = setkeyDict(RColors,"lightsteelblue2"); strcpy(RGBcodes[key],"188,210,238");
  key = setkeyDict(RColors,"lightsteelblue3"); strcpy(RGBcodes[key],"162,181,205");
  key = setkeyDict(RColors,"lightsteelblue4"); strcpy(RGBcodes[key],"110,123,139");
  key = setkeyDict(RColors,"lightyellow"); strcpy(RGBcodes[key],"255,255,224");
  key = setkeyDict(RColors,"lightyellow1"); strcpy(RGBcodes[key],"255,255,224");
  key = setkeyDict(RColors,"lightyellow2"); strcpy(RGBcodes[key],"238,238,209");
  key = setkeyDict(RColors,"lightyellow3"); strcpy(RGBcodes[key],"205,205,180");
  key = setkeyDict(RColors,"lightyellow4"); strcpy(RGBcodes[key],"139,139,122");
  key = setkeyDict(RColors,"limegreen"); strcpy(RGBcodes[key],"50,205,50");
  key = setkeyDict(RColors,"linen"); strcpy(RGBcodes[key],"250,240,230");
  key = setkeyDict(RColors,"magenta"); strcpy(RGBcodes[key],"255,0,255");
  key = setkeyDict(RColors,"magenta1"); strcpy(RGBcodes[key],"255,0,255");
  key = setkeyDict(RColors,"magenta2"); strcpy(RGBcodes[key],"238,0,238");
  key = setkeyDict(RColors,"magenta3"); strcpy(RGBcodes[key],"205,0,205");
  key = setkeyDict(RColors,"magenta4"); strcpy(RGBcodes[key],"139,0,139");
  key = setkeyDict(RColors,"maroon"); strcpy(RGBcodes[key],"176,48,96");
  key = setkeyDict(RColors,"maroon1"); strcpy(RGBcodes[key],"255,52,179");
  key = setkeyDict(RColors,"maroon2"); strcpy(RGBcodes[key],"238,48,167");
  key = setkeyDict(RColors,"maroon3"); strcpy(RGBcodes[key],"205,41,144");
  key = setkeyDict(RColors,"maroon4"); strcpy(RGBcodes[key],"139,28,98");
  key = setkeyDict(RColors,"mediumaquamarine"); strcpy(RGBcodes[key],"102,205,170");
  key = setkeyDict(RColors,"mediumblue"); strcpy(RGBcodes[key],"0,0,205");
  key = setkeyDict(RColors,"mediumorchid"); strcpy(RGBcodes[key],"186,85,211");
  key = setkeyDict(RColors,"mediumorchid1"); strcpy(RGBcodes[key],"224,102,255");
  key = setkeyDict(RColors,"mediumorchid2"); strcpy(RGBcodes[key],"209,95,238");
  key = setkeyDict(RColors,"mediumorchid3"); strcpy(RGBcodes[key],"180,82,205");
  key = setkeyDict(RColors,"mediumorchid4"); strcpy(RGBcodes[key],"122,55,139");
  key = setkeyDict(RColors,"mediumpurple"); strcpy(RGBcodes[key],"147,112,219");
  key = setkeyDict(RColors,"mediumpurple1"); strcpy(RGBcodes[key],"171,130,255");
  key = setkeyDict(RColors,"mediumpurple2"); strcpy(RGBcodes[key],"159,121,238");
  key = setkeyDict(RColors,"mediumpurple3"); strcpy(RGBcodes[key],"137,104,205");
  key = setkeyDict(RColors,"mediumpurple4"); strcpy(RGBcodes[key],"93,71,139");
  key = setkeyDict(RColors,"mediumseagreen"); strcpy(RGBcodes[key],"60,179,113");
  key = setkeyDict(RColors,"mediumslateblue"); strcpy(RGBcodes[key],"123,104,238");
  key = setkeyDict(RColors,"mediumspringgreen"); strcpy(RGBcodes[key],"0,250,154");
  key = setkeyDict(RColors,"mediumturquoise"); strcpy(RGBcodes[key],"72,209,204");
  key = setkeyDict(RColors,"mediumvioletred"); strcpy(RGBcodes[key],"199,21,133");
  key = setkeyDict(RColors,"midnightblue"); strcpy(RGBcodes[key],"25,25,112");
  key = setkeyDict(RColors,"mintcream"); strcpy(RGBcodes[key],"245,255,250");
  key = setkeyDict(RColors,"mistyrose"); strcpy(RGBcodes[key],"255,228,225");
  key = setkeyDict(RColors,"mistyrose1"); strcpy(RGBcodes[key],"255,228,225");
  key = setkeyDict(RColors,"mistyrose2"); strcpy(RGBcodes[key],"238,213,210");
  key = setkeyDict(RColors,"mistyrose3"); strcpy(RGBcodes[key],"205,183,181");
  key = setkeyDict(RColors,"mistyrose4"); strcpy(RGBcodes[key],"139,125,123");
  key = setkeyDict(RColors,"moccasin"); strcpy(RGBcodes[key],"255,228,181");
  key = setkeyDict(RColors,"navajowhite"); strcpy(RGBcodes[key],"255,222,173");
  key = setkeyDict(RColors,"navajowhite1"); strcpy(RGBcodes[key],"255,222,173");
  key = setkeyDict(RColors,"navajowhite2"); strcpy(RGBcodes[key],"238,207,161");
  key = setkeyDict(RColors,"navajowhite3"); strcpy(RGBcodes[key],"205,179,139");
  key = setkeyDict(RColors,"navajowhite4"); strcpy(RGBcodes[key],"139,121,94");
  key = setkeyDict(RColors,"navy"); strcpy(RGBcodes[key],"0,0,128");
  key = setkeyDict(RColors,"navyblue"); strcpy(RGBcodes[key],"0,0,128");
  key = setkeyDict(RColors,"oldlace"); strcpy(RGBcodes[key],"253,245,230");
  key = setkeyDict(RColors,"olivedrab"); strcpy(RGBcodes[key],"107,142,35");
  key = setkeyDict(RColors,"olivedrab1"); strcpy(RGBcodes[key],"192,255,62");
  key = setkeyDict(RColors,"olivedrab2"); strcpy(RGBcodes[key],"179,238,58");
  key = setkeyDict(RColors,"olivedrab3"); strcpy(RGBcodes[key],"154,205,50");
  key = setkeyDict(RColors,"olivedrab4"); strcpy(RGBcodes[key],"105,139,34");
  key = setkeyDict(RColors,"orange"); strcpy(RGBcodes[key],"255,165,0");
  key = setkeyDict(RColors,"orange1"); strcpy(RGBcodes[key],"255,165,0");
  key = setkeyDict(RColors,"orange2"); strcpy(RGBcodes[key],"238,154,0");
  key = setkeyDict(RColors,"orange3"); strcpy(RGBcodes[key],"205,133,0");
  key = setkeyDict(RColors,"orange4"); strcpy(RGBcodes[key],"139,90,0");
  key = setkeyDict(RColors,"orangered"); strcpy(RGBcodes[key],"255,69,0");
  key = setkeyDict(RColors,"orangered1"); strcpy(RGBcodes[key],"255,69,0");
  key = setkeyDict(RColors,"orangered2"); strcpy(RGBcodes[key],"238,64,0");
  key = setkeyDict(RColors,"orangered3"); strcpy(RGBcodes[key],"205,55,0");
  key = setkeyDict(RColors,"orangered4"); strcpy(RGBcodes[key],"139,37,0");
  key = setkeyDict(RColors,"orchid"); strcpy(RGBcodes[key],"218,112,214");
  key = setkeyDict(RColors,"orchid1"); strcpy(RGBcodes[key],"255,131,250");
  key = setkeyDict(RColors,"orchid2"); strcpy(RGBcodes[key],"238,122,233");
  key = setkeyDict(RColors,"orchid3"); strcpy(RGBcodes[key],"205,105,201");
  key = setkeyDict(RColors,"orchid4"); strcpy(RGBcodes[key],"139,71,137");
  key = setkeyDict(RColors,"palegoldenrod"); strcpy(RGBcodes[key],"238,232,170");
  key = setkeyDict(RColors,"palegreen"); strcpy(RGBcodes[key],"152,251,152");
  key = setkeyDict(RColors,"palegreen1"); strcpy(RGBcodes[key],"154,255,154");
  key = setkeyDict(RColors,"palegreen2"); strcpy(RGBcodes[key],"144,238,144");
  key = setkeyDict(RColors,"palegreen3"); strcpy(RGBcodes[key],"124,205,124");
  key = setkeyDict(RColors,"palegreen4"); strcpy(RGBcodes[key],"84,139,84");
  key = setkeyDict(RColors,"paleturquoise"); strcpy(RGBcodes[key],"175,238,238");
  key = setkeyDict(RColors,"paleturquoise1"); strcpy(RGBcodes[key],"187,255,255");
  key = setkeyDict(RColors,"paleturquoise2"); strcpy(RGBcodes[key],"174,238,238");
  key = setkeyDict(RColors,"paleturquoise3"); strcpy(RGBcodes[key],"150,205,205");
  key = setkeyDict(RColors,"paleturquoise4"); strcpy(RGBcodes[key],"102,139,139");
  key = setkeyDict(RColors,"palevioletred"); strcpy(RGBcodes[key],"219,112,147");
  key = setkeyDict(RColors,"palevioletred1"); strcpy(RGBcodes[key],"255,130,171");
  key = setkeyDict(RColors,"palevioletred2"); strcpy(RGBcodes[key],"238,121,159");
  key = setkeyDict(RColors,"palevioletred3"); strcpy(RGBcodes[key],"205,104,137");
  key = setkeyDict(RColors,"palevioletred4"); strcpy(RGBcodes[key],"139,71,93");
  key = setkeyDict(RColors,"papayawhip"); strcpy(RGBcodes[key],"255,239,213");
  key = setkeyDict(RColors,"peachpuff"); strcpy(RGBcodes[key],"255,218,185");
  key = setkeyDict(RColors,"peachpuff1"); strcpy(RGBcodes[key],"255,218,185");
  key = setkeyDict(RColors,"peachpuff2"); strcpy(RGBcodes[key],"238,203,173");
  key = setkeyDict(RColors,"peachpuff3"); strcpy(RGBcodes[key],"205,175,149");
  key = setkeyDict(RColors,"peachpuff4"); strcpy(RGBcodes[key],"139,119,101");
  key = setkeyDict(RColors,"peru"); strcpy(RGBcodes[key],"205,133,63");
  key = setkeyDict(RColors,"pink"); strcpy(RGBcodes[key],"255,192,203");
  key = setkeyDict(RColors,"pink1"); strcpy(RGBcodes[key],"255,181,197");
  key = setkeyDict(RColors,"pink2"); strcpy(RGBcodes[key],"238,169,184");
  key = setkeyDict(RColors,"pink3"); strcpy(RGBcodes[key],"205,145,158");
  key = setkeyDict(RColors,"pink4"); strcpy(RGBcodes[key],"139,99,108");
  key = setkeyDict(RColors,"plum"); strcpy(RGBcodes[key],"221,160,221");
  key = setkeyDict(RColors,"plum1"); strcpy(RGBcodes[key],"255,187,255");
  key = setkeyDict(RColors,"plum2"); strcpy(RGBcodes[key],"238,174,238");
  key = setkeyDict(RColors,"plum3"); strcpy(RGBcodes[key],"205,150,205");
  key = setkeyDict(RColors,"plum4"); strcpy(RGBcodes[key],"139,102,139");
  key = setkeyDict(RColors,"powderblue"); strcpy(RGBcodes[key],"176,224,230");
  key = setkeyDict(RColors,"purple"); strcpy(RGBcodes[key],"160,32,240");
  key = setkeyDict(RColors,"purple1"); strcpy(RGBcodes[key],"155,48,255");
  key = setkeyDict(RColors,"purple2"); strcpy(RGBcodes[key],"145,44,238");
  key = setkeyDict(RColors,"purple3"); strcpy(RGBcodes[key],"125,38,205");
  key = setkeyDict(RColors,"purple4"); strcpy(RGBcodes[key],"85,26,139");
  key = setkeyDict(RColors,"red"); strcpy(RGBcodes[key],"255,0,0");
  key = setkeyDict(RColors,"red1"); strcpy(RGBcodes[key],"255,0,0");
  key = setkeyDict(RColors,"red2"); strcpy(RGBcodes[key],"238,0,0");
  key = setkeyDict(RColors,"red3"); strcpy(RGBcodes[key],"205,0,0");
  key = setkeyDict(RColors,"red4"); strcpy(RGBcodes[key],"139,0,0");
  key = setkeyDict(RColors,"rosybrown"); strcpy(RGBcodes[key],"188,143,143");
  key = setkeyDict(RColors,"rosybrown1"); strcpy(RGBcodes[key],"255,193,193");
  key = setkeyDict(RColors,"rosybrown2"); strcpy(RGBcodes[key],"238,180,180");
  key = setkeyDict(RColors,"rosybrown3"); strcpy(RGBcodes[key],"205,155,155");
  key = setkeyDict(RColors,"rosybrown4"); strcpy(RGBcodes[key],"139,105,105");
  key = setkeyDict(RColors,"royalblue"); strcpy(RGBcodes[key],"65,105,225");
  key = setkeyDict(RColors,"royalblue1"); strcpy(RGBcodes[key],"72,118,255");
  key = setkeyDict(RColors,"royalblue2"); strcpy(RGBcodes[key],"67,110,238");
  key = setkeyDict(RColors,"royalblue3"); strcpy(RGBcodes[key],"58,95,205");
  key = setkeyDict(RColors,"royalblue4"); strcpy(RGBcodes[key],"39,64,139");
  key = setkeyDict(RColors,"saddlebrown"); strcpy(RGBcodes[key],"139,69,19");
  key = setkeyDict(RColors,"salmon"); strcpy(RGBcodes[key],"250,128,114");
  key = setkeyDict(RColors,"salmon1"); strcpy(RGBcodes[key],"255,140,105");
  key = setkeyDict(RColors,"salmon2"); strcpy(RGBcodes[key],"238,130,98");
  key = setkeyDict(RColors,"salmon3"); strcpy(RGBcodes[key],"205,112,84");
  key = setkeyDict(RColors,"salmon4"); strcpy(RGBcodes[key],"139,76,57");
  key = setkeyDict(RColors,"sandybrown"); strcpy(RGBcodes[key],"244,164,96");
  key = setkeyDict(RColors,"seagreen"); strcpy(RGBcodes[key],"46,139,87");
  key = setkeyDict(RColors,"seagreen1"); strcpy(RGBcodes[key],"84,255,159");
  key = setkeyDict(RColors,"seagreen2"); strcpy(RGBcodes[key],"78,238,148");
  key = setkeyDict(RColors,"seagreen3"); strcpy(RGBcodes[key],"67,205,128");
  key = setkeyDict(RColors,"seagreen4"); strcpy(RGBcodes[key],"46,139,87");
  key = setkeyDict(RColors,"seashell"); strcpy(RGBcodes[key],"255,245,238");
  key = setkeyDict(RColors,"seashell1"); strcpy(RGBcodes[key],"255,245,238");
  key = setkeyDict(RColors,"seashell2"); strcpy(RGBcodes[key],"238,229,222");
  key = setkeyDict(RColors,"seashell3"); strcpy(RGBcodes[key],"205,197,191");
  key = setkeyDict(RColors,"seashell4"); strcpy(RGBcodes[key],"139,134,130");
  key = setkeyDict(RColors,"sienna"); strcpy(RGBcodes[key],"160,82,45");
  key = setkeyDict(RColors,"sienna1"); strcpy(RGBcodes[key],"255,130,71");
  key = setkeyDict(RColors,"sienna2"); strcpy(RGBcodes[key],"238,121,66");
  key = setkeyDict(RColors,"sienna3"); strcpy(RGBcodes[key],"205,104,57");
  key = setkeyDict(RColors,"sienna4"); strcpy(RGBcodes[key],"139,71,38");
  key = setkeyDict(RColors,"skyblue"); strcpy(RGBcodes[key],"135,206,235");
  key = setkeyDict(RColors,"skyblue1"); strcpy(RGBcodes[key],"135,206,255");
  key = setkeyDict(RColors,"skyblue2"); strcpy(RGBcodes[key],"126,192,238");
  key = setkeyDict(RColors,"skyblue3"); strcpy(RGBcodes[key],"108,166,205");
  key = setkeyDict(RColors,"skyblue4"); strcpy(RGBcodes[key],"74,112,139");
  key = setkeyDict(RColors,"slateblue"); strcpy(RGBcodes[key],"106,90,205");
  key = setkeyDict(RColors,"slateblue1"); strcpy(RGBcodes[key],"131,111,255");
  key = setkeyDict(RColors,"slateblue2"); strcpy(RGBcodes[key],"122,103,238");
  key = setkeyDict(RColors,"slateblue3"); strcpy(RGBcodes[key],"105,89,205");
  key = setkeyDict(RColors,"slateblue4"); strcpy(RGBcodes[key],"71,60,139");
  key = setkeyDict(RColors,"slategray"); strcpy(RGBcodes[key],"112,128,144");
  key = setkeyDict(RColors,"slategray1"); strcpy(RGBcodes[key],"198,226,255");
  key = setkeyDict(RColors,"slategray2"); strcpy(RGBcodes[key],"185,211,238");
  key = setkeyDict(RColors,"slategray3"); strcpy(RGBcodes[key],"159,182,205");
  key = setkeyDict(RColors,"slategray4"); strcpy(RGBcodes[key],"108,123,139");
  key = setkeyDict(RColors,"slategrey"); strcpy(RGBcodes[key],"112,128,144");
  key = setkeyDict(RColors,"snow"); strcpy(RGBcodes[key],"255,250,250");
  key = setkeyDict(RColors,"snow1"); strcpy(RGBcodes[key],"255,250,250");
  key = setkeyDict(RColors,"snow2"); strcpy(RGBcodes[key],"238,233,233");
  key = setkeyDict(RColors,"snow3"); strcpy(RGBcodes[key],"205,201,201");
  key = setkeyDict(RColors,"snow4"); strcpy(RGBcodes[key],"139,137,137");
  key = setkeyDict(RColors,"springgreen"); strcpy(RGBcodes[key],"0,255,127");
  key = setkeyDict(RColors,"springgreen1"); strcpy(RGBcodes[key],"0,255,127");
  key = setkeyDict(RColors,"springgreen2"); strcpy(RGBcodes[key],"0,238,118");
  key = setkeyDict(RColors,"springgreen3"); strcpy(RGBcodes[key],"0,205,102");
  key = setkeyDict(RColors,"springgreen4"); strcpy(RGBcodes[key],"0,139,69");
  key = setkeyDict(RColors,"steelblue"); strcpy(RGBcodes[key],"70,130,180");
  key = setkeyDict(RColors,"steelblue1"); strcpy(RGBcodes[key],"99,184,255");
  key = setkeyDict(RColors,"steelblue2"); strcpy(RGBcodes[key],"92,172,238");
  key = setkeyDict(RColors,"steelblue3"); strcpy(RGBcodes[key],"79,148,205");
  key = setkeyDict(RColors,"steelblue4"); strcpy(RGBcodes[key],"54,100,139");
  key = setkeyDict(RColors,"tan"); strcpy(RGBcodes[key],"210,180,140");
  key = setkeyDict(RColors,"tan1"); strcpy(RGBcodes[key],"255,165,79");
  key = setkeyDict(RColors,"tan2"); strcpy(RGBcodes[key],"238,154,73");
  key = setkeyDict(RColors,"tan3"); strcpy(RGBcodes[key],"205,133,63");
  key = setkeyDict(RColors,"tan4"); strcpy(RGBcodes[key],"139,90,43");
  key = setkeyDict(RColors,"thistle"); strcpy(RGBcodes[key],"216,191,216");
  key = setkeyDict(RColors,"thistle1"); strcpy(RGBcodes[key],"255,225,255");
  key = setkeyDict(RColors,"thistle2"); strcpy(RGBcodes[key],"238,210,238");
  key = setkeyDict(RColors,"thistle3"); strcpy(RGBcodes[key],"205,181,205");
  key = setkeyDict(RColors,"thistle4"); strcpy(RGBcodes[key],"139,123,139");
  key = setkeyDict(RColors,"tomato"); strcpy(RGBcodes[key],"255,99,71");
  key = setkeyDict(RColors,"tomato1"); strcpy(RGBcodes[key],"255,99,71");
  key = setkeyDict(RColors,"tomato2"); strcpy(RGBcodes[key],"238,92,66");
  key = setkeyDict(RColors,"tomato3"); strcpy(RGBcodes[key],"205,79,57");
  key = setkeyDict(RColors,"tomato4"); strcpy(RGBcodes[key],"139,54,38");
  key = setkeyDict(RColors,"turquoise"); strcpy(RGBcodes[key],"64,224,208");
  key = setkeyDict(RColors,"turquoise1"); strcpy(RGBcodes[key],"0,245,255");
  key = setkeyDict(RColors,"turquoise2"); strcpy(RGBcodes[key],"0,229,238");
  key = setkeyDict(RColors,"turquoise3"); strcpy(RGBcodes[key],"0,197,205");
  key = setkeyDict(RColors,"turquoise4"); strcpy(RGBcodes[key],"0,134,139");
  key = setkeyDict(RColors,"violet"); strcpy(RGBcodes[key],"238,130,238");
  key = setkeyDict(RColors,"violetred"); strcpy(RGBcodes[key],"208,32,144");
  key = setkeyDict(RColors,"violetred1"); strcpy(RGBcodes[key],"255,62,150");
  key = setkeyDict(RColors,"violetred2"); strcpy(RGBcodes[key],"238,58,140");
  key = setkeyDict(RColors,"violetred3"); strcpy(RGBcodes[key],"205,50,120");
  key = setkeyDict(RColors,"violetred4"); strcpy(RGBcodes[key],"139,34,82");
  key = setkeyDict(RColors,"wheat"); strcpy(RGBcodes[key],"245,222,179");
  key = setkeyDict(RColors,"wheat1"); strcpy(RGBcodes[key],"255,231,186");
  key = setkeyDict(RColors,"wheat2"); strcpy(RGBcodes[key],"238,216,174");
  key = setkeyDict(RColors,"wheat3"); strcpy(RGBcodes[key],"205,186,150");
  key = setkeyDict(RColors,"wheat4"); strcpy(RGBcodes[key],"139,126,102");
  key = setkeyDict(RColors,"whitesmoke"); strcpy(RGBcodes[key],"245,245,245");
  key = setkeyDict(RColors,"yellow"); strcpy(RGBcodes[key],"255,255,0");
  key = setkeyDict(RColors,"yellow1"); strcpy(RGBcodes[key],"255,255,0");
  key = setkeyDict(RColors,"yellow2"); strcpy(RGBcodes[key],"238,238,0");
  key = setkeyDict(RColors,"yellow3"); strcpy(RGBcodes[key],"205,205,0");
  key = setkeyDict(RColors,"yellow4"); strcpy(RGBcodes[key],"139,139,0");
  key = setkeyDict(RColors,"yellowgreen"); strcpy(RGBcodes[key],"154,205,50");
}

/* Check the existence of these two colors in the R color schema */
void ValidateRColors(char BGCOLOR[MAXCOLORNAME],
		     char FGCOLOR[MAXCOLORNAME],
		     char GBGCOLOR[MAXCOLORNAME],
		     char GFGCOLOR[MAXCOLORNAME],
		     char HBGCOLOR[MAXCOLORNAME],
		     char FGCOLORB[MAXCOLORNAME],
		     dict* RColors)
{
  int key;
  
  key = getkeyDict(RColors,BGCOLOR);
  if (key == NOTFOUND)
    {
      printError("Problems with the BG color (undefined in R:colors())");
    }

  key = getkeyDict(RColors,FGCOLOR);
  if (key == NOTFOUND)
    {
      printError("Problems with the FG color (undefined in R:colors())");
    }

  key = getkeyDict(RColors,FGCOLORB);
  if (key == NOTFOUND)
    {
      printError("Problems with the FG color (bottom) (undefined in R:colors())");
    }

  key = getkeyDict(RColors,GBGCOLOR);
  if (key == NOTFOUND)
    {
      printError("Problems with the GBG color (undefined in R:colors())");
    }

  key = getkeyDict(RColors,GFGCOLOR);
  if (key == NOTFOUND)
    {
      printError("Problems with the GFG color (undefined in R:colors())");
    }

  key = getkeyDict(RColors,HBGCOLOR);
  if (key == NOTFOUND)
    {
      printError("Problems with the HBG color (undefined in R:colors())");
    }
}

/* Check the existence of these two colors in the R color schema */
void ValidateOneRColor(char FGCOLOR[MAXCOLORNAME],
		       dict* RColors,
		       char RGBcodes[MAXCOLORS][MAXRGBCODE],
		       char* TrackColor)
{
  int key;
  
  key = getkeyDict(RColors,FGCOLOR);
  if (key == NOTFOUND)
    {
      printError("Problems with the FG color (undefined in R:colors())");

    }

  /* Retrieving the rgb string*/
  strcpy(TrackColor,RGBcodes[key]);
}

/* Check the existence of these two colors in the R color schema */
void ValidateRColorsPieCharts(char COLOR1[MAXCOLORNAME],
			      char COLOR2[MAXCOLORNAME],
			      char COLOR3[MAXCOLORNAME],
			      char COLOR4[MAXCOLORNAME],
			      char COLOR5[MAXCOLORNAME],
			      char COLOR6[MAXCOLORNAME],
			      char COLOR7[MAXCOLORNAME],
			      dict* RColors)
{
  int key;

  if (strcmp(COLOR1,DEFAULT_COLOR1))
    {
      key = getkeyDict(RColors,COLOR1);
      if (key == NOTFOUND)
	{
	  printError("Problems with the Color 1 (undefined in R:colors())");
	}
    }

  if (strcmp(COLOR2,DEFAULT_COLOR2))
    {
      key = getkeyDict(RColors,COLOR2);
      if (key == NOTFOUND)
	{
	  printError("Problems with the Color 2 (undefined in R:colors())");
	}
    }

  if (strcmp(COLOR3,DEFAULT_COLOR3))
    {
      key = getkeyDict(RColors,COLOR3);
      if (key == NOTFOUND)
	{
	  printError("Problems with the Color 3 (undefined in R:colors())");
	}
    }

  if (strcmp(COLOR4,DEFAULT_COLOR4))
    {
      key = getkeyDict(RColors,COLOR4);
      if (key == NOTFOUND)
	{
	  printError("Problems with the Color 4 (undefined in R:colors())");
	}
    }

  if (strcmp(COLOR5,DEFAULT_COLOR5))
    {
      key = getkeyDict(RColors,COLOR5);
      if (key == NOTFOUND)
	{
	  printError("Problems with the Color 5 (undefined in R:colors())");
	}
    }

  if (strcmp(COLOR6,DEFAULT_COLOR6))
    {
      key = getkeyDict(RColors,COLOR6);
      if (key == NOTFOUND)
	{
	  printError("Problems with the Color 6 (undefined in R:colors())");
	}
    }
  
  if (strcmp(COLOR7,DEFAULT_COLOR7))
    {
      key = getkeyDict(RColors,COLOR7);
      if (key == NOTFOUND)
	{
	  printError("Problems with the Color 7 (undefined in R:colors())");
	}
    }
}

/* Check the existence of these two colors in the R color schema */
void SetViridisColorsPieCharts(char COLOR1[MAXCOLORNAME],
			       char COLOR2[MAXCOLORNAME],
			       char COLOR3[MAXCOLORNAME],
			       char COLOR4[MAXCOLORNAME],
			       char COLOR5[MAXCOLORNAME],
			       char COLOR6[MAXCOLORNAME],
			       char COLOR7[MAXCOLORNAME],
			       int mode)
{
  /* Define Viridis colors (1) */
  if (mode==1)
    {
      strcpy(COLOR1,VIRIDIS_COLOR1);
      strcpy(COLOR2,VIRIDIS_COLOR2);
      strcpy(COLOR3,VIRIDIS_COLOR3);
      strcpy(COLOR4,VIRIDIS_COLOR4);
      strcpy(COLOR5,VIRIDIS_COLOR5);
      strcpy(COLOR6,VIRIDIS_COLOR6);
      strcpy(COLOR7,VIRIDIS_COLOR7);
    }

  /* Define Magma colors (2) */
  if (mode==2)
    {
      strcpy(COLOR1,MAGMA_COLOR1);
      strcpy(COLOR2,MAGMA_COLOR2);
      strcpy(COLOR3,MAGMA_COLOR3);
      strcpy(COLOR4,MAGMA_COLOR4);
      strcpy(COLOR5,MAGMA_COLOR5);
      strcpy(COLOR6,MAGMA_COLOR6);
      strcpy(COLOR7,MAGMA_COLOR7);
    }

  /* Define Plasma colors (3) */
  if (mode==3)
    {
      strcpy(COLOR1,PLASMA_COLOR1);
      strcpy(COLOR2,PLASMA_COLOR2);
      strcpy(COLOR3,PLASMA_COLOR3);
      strcpy(COLOR4,PLASMA_COLOR4);
      strcpy(COLOR5,PLASMA_COLOR5);
      strcpy(COLOR6,PLASMA_COLOR6);
      strcpy(COLOR7,PLASMA_COLOR7);
    }
  
  /* Define Inferno colors (3) */
  if (mode==4)
    {
      strcpy(COLOR1,INFERNO_COLOR1);
      strcpy(COLOR2,INFERNO_COLOR2);
      strcpy(COLOR3,INFERNO_COLOR3);
      strcpy(COLOR4,INFERNO_COLOR4);
      strcpy(COLOR5,INFERNO_COLOR5);
      strcpy(COLOR6,INFERNO_COLOR6);
      strcpy(COLOR7,INFERNO_COLOR7);
    }
}
