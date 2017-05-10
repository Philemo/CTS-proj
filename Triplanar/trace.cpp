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

#include "trace.h"

static FILE *debug;

#ifdef WITH_TRACE
void trace_init() {
	fopen_s(&debug, DEBUG_FILE, "wt");
	trace_close();
}

void trace_close() {
	fclose(debug);
	debug = NULL;
}

FILE *trace_open()
{
	if (!debug) fopen_s(&debug, DEBUG_FILE, "at");
	return debug;
}

#else
void trace_init() {
}

void trace_close() {
}
#endif
