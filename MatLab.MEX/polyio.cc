static const char rcs_id[] = "$Header: /home/klamer/src/c++/est_akker/RCS/poly_io.cc,v 1.1 1992/12/07 10:46:35 klamer Exp klamer $";

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

// $Log: poly_io.cc,v $
// Revision 1.1  1992/12/07  10:46:35  klamer
// Initial revision
//

#ifdef __GNUG__
#pragma implementation
#endif

#ifndef mac_h // added for IBM PC compatibility. gsl 6/6/97
#include "ibmPc.h"
#endif

#include	"String.h" //changed so that compiler searches in local directory instead of system
                       //directory. Avoids conflict with existing String.h file on Mac. gsl 10/16/96

#include	<iostream.h>

//#include	"err.h" removed. gsl 10/30/96

#include	"poly.h"        // use local path not <xxx>. gsl 10/31/96
#include	"primitvs.h"    // use local path not <xxx>. gsl 10/31/96
#include	"posadder.h"    // use local path not <xxx>. gsl 10/31/96

#include	"graphmat.h"    // use local path not <xxx>. gsl 10/31/96
//#include	"poly3node.h"
//#include	"poly3.h"
//#include	"poly2.h"

#include	"polyio.h" //renamed file from poly_io.h to polyio.h;
                       //underscore caused probs. on Mac. gsl 10/16/96;
                       //also renamed this file to polyio.cc for the
                       //same reason.
static const char h_rcs_id[] = POLY_IO_H;

/*Poly *
read_poly( istream &in )
{
	Point p;
	
	in >> p;
	
	Poly *new_poly = new Poly( p );
	
	while( in >> p )
		new_poly->add( p );

	String magic;
	
	in.clear();
	in >> magic;
	
	if (magic != POLY_MAGIC)
		fatal("read_poly: wrong magic (%s)\n", (const char *) magic );
		
	return new_poly;
} not used in MatLab MEX function. Replaced with convPoly below. gsl 10/25/96 */
		
Poly *
inPoly( 
#ifdef MatLabV4 //added. gsl 5/9/97
  Matrix
#endif
#ifdef MatLabV5
  const mxArray
#endif
  *mat )              /*Routine added to allow conversion between MatLab
                        matrices and "Poly" class objects. Takes input MatLab
                        polygon and converts it to Schutte's Poly class.
                        Polygon can wrap-around where first and last
                        vertices are identical (within epsilon) or
                        they can each be unique, in which case the
                        last vertex is assumed to connect to the
                        first vertex. gsl 10/25/96
                       */
{
	double *polyML;
	Point p, pl;
	int i, m, n;
	
	/* Point to the MatLab input polygon. */

	polyML = mxGetPr(mat);

	/* Get its dimensions. */
	
	m = mxGetM(mat);
	n = mxGetN(mat);
	
	// Get the first and last vertices.
	
	if ( m >= n ) { // matrix ordered as one vertex per row where 1st col. is x and 2nd col. is y
	                // m == n == 2. assume vertices are one per row.
	                // Note: MatLab stores matrices in Fortran column order.
		p = Point(PT(polyML,m,0,0),PT(polyML,m,0,1));      // 1st
		pl = Point(PT(polyML,m,m-1,0),PT(polyML,m,m-1,1)); // last
		
	    if ( p == pl)  { // first and last vertex of polygon are identical (within epsilon), so
	        m--; // one less point in polygon
	        assert( m > 1); // must have at least two unique vertices to form a polygon.
	    }
	}
	else { // matrix ordered as one vertex per column where 1st row is x and 2nd row is y
		p = Point(PT(polyML,m,0,0),PT(polyML,m,1,0));      // 1st
		pl = Point(PT(polyML,m,0,n-1),PT(polyML,m,1,n-1)); // last
		
	    if ( p == pl) { // first and last vertex of polygon are identical (within epsilon), so
	        n--; // one less point in polygon
	        assert( n > 1 ); // must have at least two unique vertices to form a polygon.
	    }
	}
	
	// Create the first vertex node of the polygon.
	
	Poly *new_poly = new Poly( p );
	
	// Create the rest of the vertices of the polygon.
	
	if ( m >= n ) // matrix ordered as one vertex per row
	              // if m == n == 2. assume vertices are one per row.
		for ( i=1; i < m; i++ )
				new_poly->add( Point(PT(polyML,m,i,0),PT(polyML,m,i,1)) );
	else // matrix ordered as one vertex per column
		for ( i=1; i < n; i++ )
				new_poly->add( Point(PT(polyML,m,0,i),PT(polyML,m,1,i)) );	
	return new_poly;
}
		
/*istream &
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
		out << iter.point();

	out << POLY_MAGIC << endl;
			
	return out;
}*/

/* Determine the number of total vertices across all polygons in a polygon
   list and pass value back.
   Determine the number of polygons in a polygon list and pass it back.
 */
void
getPolySizes( const PolyPList &pl, int *numVerts, int *numPolys ) //added. gsl 10/29/96
{
	PolyPListIter	iterP(pl);
	
    *numVerts = 0;
    *numPolys = 0;
	while(iterP()) { // move to next polygon in list
		ConstPolyIter iter(*iterP.val());
	
		while(iter()) // move to next vertex in polygon
			++*numVerts;
		++*numVerts; // add one more for wrap-around vertex
		++*numPolys;
	}
}

/* Copies Schutte's polygon list into three MatLab matrices.
   The first matrix contains the vertices of each polygon in the list.
   Where one polygon's vertices end, the next begins.
   A second matrix contains the number of vertices per polygon.
   A third matrix contains the number of polygons.
   Ex: We have three polygons, one with 2 vertices, one with 5 vertices,
       and one with 8 vertices.  The vertices are stored in memory in the
       first matrix with all x-coords of the three polygons first followed
       by all y-coords of the three polygons (Fortran column order).
       
       The next matrix would be 3x1 and would contain 2 in the first 
       element, 5 in the second, and 8 in the third element.
       
       The third and last matrix is 1x1 and its only element contains the
       number of polygons, in this case 3.
 */
void
outPoly( const PolyPList &pl, 
#ifdef MatLabV4 //added. gsl 5/9/97
  Matrix *matVerts, Matrix *matIdx, Matrix *matN, Matrix *matArea
#endif
#ifdef MatLabV5
  mxArray *matVerts, mxArray *matIdx, mxArray *matN, mxArray *matArea
#endif
       ) //added. gsl 10/28/96
{
    int i=0, j=0, k=0, mVerts, mIdx, startPolyIdx;
	PolyPListIter	iterP(pl);
	Point p;
	double *matVertsML, *matIdxML, *matNML, *matAreaML;
	Poly *polyPtr;
	
	/* Point to the MatLab output polygon matrix. */

	matVertsML = mxGetPr(matVerts);

	/* Get its row dimensions. */
	
	mVerts = mxGetM(matVerts);
	
	/* Point to the MatLab output polygon matrix indices. */

	matIdxML = mxGetPr(matIdx);

	/* Get its row dimensions. */
	
	mIdx = mxGetM(matIdx);
	
	/* Point to the MatLab output polygon count matrix. */

	matNML = mxGetPr(matN);

	/* Point to the MatLab output polygon area matrix. */

	matAreaML = mxGetPr(matArea);

	while(iterP()) { // move to next polygon in list
	                 // Note: MatLab stores matrices in Fortran column order.

        polyPtr = iterP.val(); // point to next polygon
		ConstPolyIter iter(*polyPtr); // set up iterator for polygon
		startPolyIdx = i; // save the starting index of the current polygon.	
		while(iter()) { // move to next vertex in polygon
			p = iter.point();
			PT(matVertsML,mVerts,0,i) = p.x(); //copy vertex into matrix.
			PT(matVertsML,mVerts,1,i) = p.y(); // "
			i++;                               // current total number of vertices across all polygons in list
			j++;                               // number of vertices for current polygon
		}
		PT(matVertsML,mVerts,0,i) = PT(matVertsML,mVerts,0,startPolyIdx); //copy last wrap-around vertex into matrix.
		PT(matVertsML,mVerts,1,i) = PT(matVertsML,mVerts,1,startPolyIdx); // "
		i++;
		
		PT(matAreaML,mIdx,0,k) = polyPtr->area(); // store area for this polygon.		
		
		PT(matIdxML,mIdx,0,k++) = ++j; // store number of vertices for this polygon.
		j = 0;
	}
	*matNML = k; // store number of polygons.
}

/*ostream &
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
}  not used in MatLab MEX function. gsl 10/25/96 */
