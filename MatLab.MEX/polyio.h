#ifndef	POLY_IO_H
//#ifdef mac_h
//#define	POLY_IO_H	{"$Header: /home/klamer/src/c++/est_akker/RCS/poly_io.h,v 1.1 1992/12/07 10:46:35 klamer Exp klamer $"}
//#else
#define	POLY_IO_H	"$Header: /home/klamer/src/c++/est_akker/RCS/poly_io.h,v 1.1 1992/12/07 10:46:35 klamer Exp klamer $"
//#endif

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

// $Log: poly_io.h,v $
// Revision 1.1  1992/12/07  10:46:35  klamer
// Initial revision
//

#ifdef __GNUG__
#pragma interface
#endif

#ifndef mac_h // added for IBM PC compatibility. gsl 6/6/97
#include "ibmPc.h"
#endif

#ifndef _IOSTREAM_H
#include	<iostream.h>
#endif

//extern "C" {  //added. gsl 10/25/96
//#include "mex.h"
//}
                       
/* MatLab Input Arguments */

#define	A_IN	prhs[0]
#define	B_IN	prhs[1]

/* MatLab Output Arguments */

#define	AminusB_OUT	    plhs[0]
#define	AminusBIdx_OUT  plhs[1]
#define	AminusBn_OUT    plhs[2]
#define	AminusBarea_OUT plhs[3]

#define	BminusA_OUT	    plhs[4]
#define	BminusAIdx_OUT  plhs[5]
#define	BminusAn_OUT    plhs[6]
#define	BminusAarea_OUT plhs[7]

#define	AandB_OUT       plhs[8]
#define	AandBIdx_OUT    plhs[9]
#define	AandBn_OUT      plhs[10]
#define	AandBarea_OUT   plhs[11]

#define PT(ptr,rowDim,r,c)      *(ptr + (c) * rowDim + (r)) //extract 2D matrix element 
                                                            //from Fortran column oriented
                                                            //array. gsl 10/25/96

//#define	POLY_MAGIC	"PolyMagic" not used in MatLab MEX function. gsl 10/28/96

class Poly;
class Point;
// class PolyPList;
class PolyNode;
union	hvec3_t;

/*Poly 	*read_poly( istream & );

istream &operator>>(istream &, Point &);
ostream	&operator<<(ostream &, const PolyPList &);
ostream	&operator<<(ostream &, const Poly &);
ostream	&operator<<(ostream &, const PolyNode &);
ostream	&operator<<(ostream &, const Point &);
ostream	&operator<<(ostream &, enum EdgeState);
ostream	&operator<<(ostream &, enum LogicStates);
ostream	&operator<<(ostream &, const hvec3_t &); not used in MatLab MEX function. gsl 10/28/96*/
Poly *inPoly( 
#ifdef MatLabV4 //added. gsl 5/9/97
  Matrix
#endif
#ifdef MatLabV5
  const mxArray
#endif
 *mat ); //added. gsl 10/28/96
void getPolySizes( const PolyPList &pl, int *numVerts, int *numPolys ); //added. gsl 10/29/96
void outPoly( const PolyPList &pl,
#ifdef MatLabV4 //added. gsl 5/9/97
  Matrix *matVerts, Matrix *matIdx, Matrix *matN, Matrix *matArea
#endif
#ifdef MatLabV5
  mxArray *matVerts, mxArray *matIdx, mxArray *matN, mxArray *matArea
#endif
            ); //added. gsl 10/28/96

#endif	/* POLY_IO_H */
