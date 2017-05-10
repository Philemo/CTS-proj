/*
   This file is part of PyCarrara

   Copyright (C) 2010 Frederic Rible (frible@teaser.fr)

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the program; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.
 */
#include <stdio.h>
void trace_close();
FILE *trace_open();
void trace_init();

#ifdef WITH_TRACE
#define DEBUG_FILE "C:/Users/Philippe/Documents/Projets/Plugins/carrara_debug.txt"
#define TR(...)	{ FILE *debug = trace_open(); fprintf(debug, "%p ", this); fprintf(debug, __VA_ARGS__ ); fprintf(debug,"\n");fflush(debug); }
#define TRS(...)	{ FILE *debug = trace_open(); fprintf(debug, "%p ", 0); fprintf(debug, __VA_ARGS__ ); fprintf(debug,"\n");fflush(debug); }
#define TR_MCS(v) { char str[1024]; v.ToCPtr(str); TR(#v "=%s\n", str) }
#else
#define TR(...) {}
#define TRS(...) {}
#define TR_MCS(v) {}
#endif

#define TR_INT(v) TR(#v "=%d\n", v)


