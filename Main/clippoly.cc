//    nclip: a polygon clip library

//    Copyright (C) 1993  Klamer Schutte

//    klamer@mi.el.utwente.nl

//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.

//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.

//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

//    WARNING: This code has a lot of memory leaks. This is the way I received the
//             code. I have not bothered to fix this problem yet. gsl 11/2/96
//             I have found that I read the code in error. There do not appear to be
//             any memory leaks. gsl 1/27/97
//
//    Added version identifier variable "ident".


#include	<iostream.h>

#include	"poly.h"
#include	"polyio.h" //Mac had a problem with underscore in filename, so removed underscore. gsl 10/17/96
#include	"nclip.h"

char ident[] = "@(#)Clippoly by Klamer Schutte,\n@(#)Macintosh port version 1.5 by Gregg Leichtman 8/11/97";

void clear(PolyPList &l);  //added prototype to make compiler happy. gsl 10/17/96

void
clear(PolyPList &l)
{
	PolyPListIter	i(l);
	while(i())
		delete i.val();
}

int
main(int, char *[])
{
	PolyPList	a_min_b, b_min_a, a_and_b;

	cout << "Enter the two input polygons to be clipped, one vertex per" << endl
	     << "line where each polygon ends with the word \"PolyMagic\"" << endl
	     << "on a separate line, then press the enter or return key" << endl
	     << "(Do not duplicate the first and last points of the polygon.):" << endl
	     << endl; // added. gsl 11/2/96

	Poly	*a = read_poly(cin), *b = read_poly(cin);

	// printf("Area a %g b %g\n", a->area(), b->area());

	clip_poly( *a, *b, a_min_b, b_min_a, a_and_b );

	cout << endl << "a_min_b:\n" << a_min_b; //added <cr> at start of output, since
	                                         //SIOUX window in Metrowerks CodeWarrior 9.0
	                                         //starts output for the first
	                                         //line at the top of the window and then continues
	                                         //output at the bottom of the window starting
	                                         //with the second line. This is more of a fix
	                                         //for a symptom, rather than a fix for the
	                                         //problem. Changed out_file.dist to reflect
	                                         //extra <cr> at top of output file. gsl 10/25/96 
	cout << "b_min_a:\n" << b_min_a;
	cout << "a_and_b:\n" << a_and_b;

	delete	a;
	delete	b;

	clear(a_min_b);
	clear(b_min_a);
	clear(a_and_b);

	return 0;
}
