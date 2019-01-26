static const char rcs_id[] = "$Header: /home/mi7/klamer/src/c++/spie/RCS/primitives.cc,v 1.2 1994/01/04 12:55:37 klamer Exp klamer $";

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

// $Log: primitives.cc,v $
// Revision 1.2  1994/01/04  12:55:37  klamer
// Loosened assertion in angle() from angle < 2 pi to angle <= 2 pi.
//
// Revision 1.1  1993/10/27  14:44:13  klamer
// Initial revision
//
// Revision 1.1  1992/12/07  10:46:35  klamer
// Initial revision
//

#ifdef __GNUG__
#pragma implementation
#endif

//#include	<assert.h> removed. added assert in precompiled header. gsl 10/29/96
#include    <float.h> //added. gsl 10/24/96
#include	<math.h>

//#include	"err.h" removed. gsl 10/30/96

#include	"primitvs.h"

static const char h_rcs_id[] = PRIMITIVES_H;

#ifdef FLT_EPSILON            //added. gsl 10/24/96
#define EPSILON FLT_EPSILON
#else
#define EPSILON          1e-7
#endif
#define	ChkZero(x)		(Dabs(x) < EPSILON) // end added. gsl 10/24/96

const int PointList::def_len = 16;

PointList::PointList( int nr )
	: len( nr ), cur( 0 ), points( new Point[ nr ] )
{
	assert( nr > 0 );
}

PointList::~PointList()
{
	delete [] points;
}

void
PointList::add( const Point &add )
{
	/*if (cur + 1 >= len) removed. gsl 10/30/96
		fatal("PointList::add: Array too short (%d)\n", len);*/
    assert(cur + 1 < len); // added. gsl 10/30/96
	
	points[cur] = add;
}

double
angle(const Point &p1, const Point &p2, const Point &p3)
{
	Point	d1 = p1 - p2, d2 = p3 - p2;
	
	double	res = atan( d2 ) - atan( d1 );
	
	if (res < 0)
		res += M_PI * 2;

	assert( res >= 0 );
	assert( res <= M_PI * 2 );
	//assert( res > 0 || ChkZero(res));                  //added. gsl 10/24/96
	//assert( res < M_PI * 2 || ChkZero(res - M_PI * 2)); // "
			
	return res;
}

