static const char rcs_id[] = "$Header$";

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
// Revision 1.4  2005/02/28 17:12:00  klamer
// PL9
//
// Revision 1.1  1992/12/07  10:46:35  klamer
// Initial revision
//

#ifdef __GNUG__
#pragma implementation
#endif

#include	<String.h>
#include	<iostream.h>

#include	<err.h>

#include	<poly.h>
#include	<primitives.h>
#include	<posadder.h>

#include	<graphmat.h>
//#include	"poly3node.h"
//#include	"poly3.h"
//#include	"poly2.h"

#include	"poly_io.h"

static const char h_rcs_id[] = POLY_IO_H;

Poly 	*
read_poly( istream &in )
{
	Point	p;
	
	in >> p;
	
	Poly	*new_poly = new Poly( p );
	
	while( in >> p )
		new_poly->add( p );

	String	magic;
	
	in.clear();
	in >> magic;
	
	if (magic != POLY_MAGIC)
		fatal("read_poly: wrong magic (%s)\n", (const char *) magic );
		
	return new_poly;
}
		
istream &
operator>>(istream &in, Point &p)
{
	double	x, y;
	
	in >> x >> y;

	if (!in)	// Failure?
		return in;
	
	p = Point(x,y);

	return in;
}

ostream	&
operator<<(ostream &out, const PolyPList &pl)
{
	PolyPListIter	iter(pl);
	
	while(iter())
		out << *iter.val();
		
	return out;
}

ostream &
operator<<(ostream &out, const Poly &poly)
{
	ConstPolyIter	iter(poly);
	
	while(iter())
		out << (iter.point());

	out << POLY_MAGIC << endl;
			
	return out;
}

ostream &
operator<<(ostream &out, const PolyNode &poly)
{
	out << poly.p << "next: " << poly.next << " prev: " << poly.prev 
		<< " link: " << poly._link << " state: " 
		<< poly.edgestate() 
		<< " parent: " << (void *) poly._parent_poly << endl;
	
	return out;
}

ostream &
operator<<(ostream &out, const Point &p)
{
	out << p.x() << '\t' << p.y() << endl;
	
	return out;
}

ostream &
operator<<(ostream &out, enum LogicStates state)
{
	switch(state)
	{case UnKnown:
		out << "UnKnown";
		break;
	case True:
		out << "True";
		break;
	case False:
		out << "False";
		break;
	case TrueFalse:
		out << "TrueFalse";
		break;
	default:
		error("<<: Unknown value in LogicStates: %d\n", (int)state);
		out << (int)state;
	}
	
	return out;
}

ostream &
operator<<(ostream &out, enum EdgeState state)
{
	switch(state)
	{case Unknown:
		out << "Unknown";
		break;
	case None:
		out << "None";
		break;
	case Shared:
		out << "Shared";
		break;
	case Inside:
		out << "Inside";
		break;
	default:
		error("<<: Unknown value in LogicStates: %d\n", (int)state);
		out << (int)state;
	}
	
	return out;
}

ostream &
operator<<(ostream&out, const hvec3_t &v)
{
	out << v_x(v) << ", " << v_y(v) << ", " << v_z(v) << ", " << v_w(v);

	return out;
} 
