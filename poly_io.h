#ifndef	POLY_IO_H
#define	POLY_IO_H	"$Header$"

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

// $Log$
// Revision 1.1  2005/02/28 16:23:13  klamer
// PL6
//
// Revision 1.1  1992/12/07  10:46:35  klamer
// Initial revision
//

#ifdef __GNUG__
#pragma interface
#endif

#ifndef _IOSTREAM_H
#include	<iostream.h>
#endif

#define	POLY_MAGIC	"PolyMagic"

class Poly;
class Point;
// class PolyPList;
class PolyNode;
union	hvec3_t;

Poly 	*read_poly( istream & );

istream &operator>>(istream &, Point &);
ostream	&operator<<(ostream &, const PolyPList &);
ostream	&operator<<(ostream &, const Poly &);
ostream	&operator<<(ostream &, const PolyNode &);
ostream	&operator<<(ostream &, const Point &);
ostream	&operator<<(ostream &, enum EdgeState);
ostream	&operator<<(ostream &, enum LogicStates);
ostream	&operator<<(ostream &, const hvec3_t &);

#endif	/* POLY_IO_H */
