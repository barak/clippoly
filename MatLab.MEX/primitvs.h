#ifndef	PRIMITIVES_H
#define	PRIMITIVES_H	"$Header: /home/mi7/klamer/src/c++/spie/RCS/primitives.h,v 1.1 1993/10/27 14:43:55 klamer Exp $"

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

// $Log: primitives.h,v $
// Revision 1.1  1993/10/27  14:43:55  klamer
// Initial revision
//
// Revision 1.1  1993/10/27  14:43:55  klamer
// Initial revision
//
// Revision 1.1  1992/12/07  10:46:35  klamer
// Initial revision
//

#ifdef __GNUG__
#pragma interface
#endif

#ifndef M_PI
#include	<math.h>
#endif
#ifndef GRAPHMAT_INCLUDE
#include	"graphmat.h"   // use local path not <xxx>. gsl 10/31/96
#endif
#ifndef assert
//#include	<assert.h> removed. added assert in precompiled header. gsl 10/29/96
#include    <float.h> //added. gsl 10/24/96
#endif

#ifndef M_PI  //MW CW on Mac does not have M_PI, so I added it. gsl 10/17/96
//#define M_PI pi MetroWerks removed the definition of 
//                pi, since it is not part of the ANSI definition; therefore I put the
//                definition in directly. gsl 5/1/97
#define M_PI 3.14159265358979323846
#endif
#ifdef mac_h /* moved for IBM PC compatibility. gsl 6/6/97 */
#define atan atanClipPoly //Can't overload an 'extern "C"' function on the Mac in CW. gsl 10/14/96
#endif
#ifdef FLT_EPSILON            //added. gsl 10/24/96
#define EPSILON FLT_EPSILON
#else
#define EPSILON          1e-7
#endif
#define	ChkZero(x)		(Dabs(x) < EPSILON) // end added. gsl 10/24/96
#define Dabs(x) (((x)<0) ? (-(x)):(x))

class Point
{
	double	_x, _y;
	
public:
	Point()
		{ }
	Point( double x, double y )
		: _x(x), _y(y)
		{ }
	Point( const hvec2_t &h )
		: _x(v_x(h)), _y(v_y(h))
		{ }

	double	x() const
		{ return _x; }
	double	&x()
		{ return _x; }
	double	y() const
		{ return _y; }
	double	&y()
		{ return _y; }
	
	void setPt(Point p);

	// operator hvec2_t();	// Does crash g++ 2.2.1 when used :-(
	hvec2_t	hvec() const
//		{ hvec2_t res; v_fill2( x(), y(), 1.0, &res ); return res; }
		{ hvec2_t res; v_x(res) = x(); v_y(res) = y(); v_w(res) = 1;
			return res; }
	const Point &operator=( const hvec2_t &copy )
		{ _x = v_x(copy); _y = v_y( copy); return *this; }
	const Point &operator=( const Point &copy )
		{ _x = copy.x(); _y = copy.y(); return *this; }
};

inline Point	
operator+( const Point &p1, const Point &p2 )
{
	return Point( p1.x() + p2.x(), p1.y() + p2.y() );
}
	
inline Point	
operator-( const Point &p1, const Point &p2 )
{
	return Point( p1.x() - p2.x(), p1.y() - p2.y() );
}

inline void Point::setPt(Point p)
		{ _x = p.x(); _y = p.y(); } // added. gsl 2/14/97
			
inline double
len( const Point p )
{
	return sqrt( p.x() * p.x() + p.y() * p.y() );
}
 
inline Point	
operator/( const Point &p, double div )
{
	return Point( p.x() / div, p.y() / div );
}

inline int
operator==( const Point &p1, const Point &p2 )
{
	//return (p1.x() == p2.x()) && (p1.y() == p2.y()); removed. gsl 10/24/96
	//return ChkZero(p1.x() - p2.x()) && ChkZero(p1.y() - p2.y()); //added. gsl 10/24/96
    return ChkZero(len(p1 - p2)); // changed to a fuzzy Euclidean distance measure. gsl 11/22/96
}

inline int
operator!=( const Point &p1, const Point &p2 )
{
	//return (p1.x() != p2.x()) || (p1.y() != p2.y()); removed. gsl 10/24/96
	//return ! ChkZero(p1.x() - p2.x()) || ! ChkZero(p1.y() - p2.y()); //added. gsl 10/24/96
    return ! ChkZero(len(p1 - p2)); // changed to a fuzzy Euclidean distance measure. gsl 11/22/96
}

inline int
operator<( const Point &p1, const Point &p2 )
{
	//return (p1.y() < p2.y()) || ((p1.y() == p2.y()) && (p1.x() < p2.x())); removed. gsl 10/24/96
	return (p1.y() < p2.y()) || (ChkZero(p1.y() - p2.y()) && (p1.x() < p2.x())); //added. gsl 10/24/96
}

inline int
operator>( const Point &p1, const Point &p2 )
{
	//return (p1.y() > p2.y()) || ((p1.y() == p2.y()) && (p1.x() > p2.x())); removed. gsl 10/24/96
	return (p1.y() > p2.y()) || (ChkZero(p1.y() - p2.y()) && (p1.x() > p2.x())); //added. gsl 10/24/96
}

double	angle( const Point &p1, const Point &p2, const Point &p3 );

inline double
atan( const Point &p )
{
	assert( (p.x() != 0) || (p.y() != 0) ); //removed. gsl 10/24/96
	//assert( ! ChkZero(p.x()) || ! ChkZero(p.y()) ); //added. gsl 10/24/96
	return atan2( p.y(), p.x() );
}

inline Point 
point(const hvec3_t &p)
{
	hvec3_t	pn;
	v_homo3( &p, &pn );
	
	return Point( v_x(pn), v_y(pn) );
}

class PointList
{
	friend class PointListIter;
	
	int	len, cur;
	Point	*points;

	static const int	def_len; //	= 16;
	// Make copy constructor and assignment unusable
	PointList( PointList &copy );
	operator=( PointList copy );
		
public:
	PointList( int nr = def_len );
	~PointList();
	
	void	add( const Point &add );
};

class PointListIter
{
	const PointList	&pl;
	int				cnt;
	
public:
	PointListIter( const PointList &list )
		: pl( list ), cnt( -1 )
		{ }
	
	int	operator() ()
		{ if (++cnt < pl.cur) return 1; else return 0; }
	
	const Point	&point() const
		{ return pl.points[cnt]; }
};

class Edge
{
	Point	point1, point2;
	// int		shared;
	
public:
	Edge( const Point &p1, const Point &p2 ) //, int share = -1 )
		: point1( p1 ), point2( p2 ) //, shared( share )
		{ }
	Point	middle() const
		{ return (point1 + point2) / 2.0; }
	// void	set_shared( int val )
	//	{ shared = val; }
	
	const Point	&p1() const
		{ return point1; } 
	const Point 	&p2() const
		{ return point2; }	
};

#endif	/* PRIMITIVES_H */
