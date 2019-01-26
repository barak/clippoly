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

//    Removed the gm_error error reporting facility and replaced it with
//    assertions and function gsl_error. error reporting has not
//    been extensively checked as of this time. gsl 10/30/96

//    converted to a MatLab MEX function. gsl 10/30/96

//    WARNING: This code has a lot of memory leaks. This is the way I received the
//             code. I have not bothered to fix this problem yet. gsl 11/2/96
//             I have found that I read the code in error. There do not appear to be
//             any memory leaks. gsl 1/27/97
//
//    Added version identifier variable "ident".


#ifndef mac_h // added for IBM PC compatibility. gsl 6/6/97
#include "ibmPc.h"
#endif

#include	<iostream.h>

#include	"mex.h" /* added. gsl 5/9/97 */
#include	"poly.h"
#include	"polyio.h"
#include	"nclip.h"

char ident[] = "@(#)Clippoly by Klamer Schutte,\n@(#)Macintosh port version 1.5 by Gregg Leichtman 8/11/97";

#define	max(A, B)	((A) > (B) ? (A) : (B)) //added. gsl 10/28/96
#define	min(A, B)	((A) < (B) ? (A) : (B)) // "

void clear(PolyPList &l);  //added prototype to make compiler happy. gsl 10/17/96

void
clear(PolyPList &l)
{
	PolyPListIter	i(l);
	while(i())
		delete i.val();
}

//int
//main(int, char *[]) converted to MEX function. gsl 10/25/96
extern "C" {
void mexFunction(
	int		nlhs,
#ifdef MatLabV4 //added. gsl 5/9/97
  Matrix
#endif
#ifdef MatLabV5
  mxArray
#endif
	*plhs[],
	int		nrhs,
#ifdef MatLabV4 //added. gsl 5/9/97
  Matrix
#endif
#ifdef MatLabV5
  const mxArray
#endif
	*prhs[]
	)
{
	//Poly	*a = read_poly(cin), *b = read_poly(cin); Not read from stdin in MatLab MEX function.
	Poly	*a = NULL, *b = NULL; //Polygons are passed in from MatLab. gsl 10/25/96
	PolyPList	a_min_b, b_min_a, a_and_b;
	int m, n, nVerts[1], nPolys[1];

	/* Check for proper number of arguments */
	if (nrhs != 2) {
		mexErrMsgTxt("CLIPPOLY requires two input arguments:\n\n[AminusB,AminusBIdx,AminusBn,AminusBarea,BminusA,BminusAIdx,BminusAn,BminusAarea, ...\n AandB,AandBIdx,AandBn,AandBarea]=clippoly(polyA,polyB).\n\nIf 2x2 vertex input matrix, vertices are assumed to be listed 1 per row.\nX is first column or first row.");
	} else if (nlhs != 12) {
		mexErrMsgTxt("CLIPPOLY requires twelve output arguments:\n\n[AminusB,AminusBIdx,AminusBn,AminusBarea,BminusA,BminusAIdx,BminusAn,BminusAarea, ...\n AandB,AandBIdx,AandBn,AandBarea]=clippoly(polyA,polyB).\n\nIf 2x2 vertex input matrix, vertices are assumed to be listed 1 per row.\nX is first column or first row.");
	}

	/* Check the dimensions of polygon A.  A can be 2 X N or N X 2. It must be at least
	   2 X 2. The last vertex listed is assumed to connect to the first vertex to form the 
	   polygon. If A is 2 X 2, then it is assumed that the vertices are listed one per row. */

	m = mxGetM(A_IN);
	n = mxGetN(A_IN);
	if (!mxIsNumeric(A_IN) || mxIsComplex(A_IN) || 
#ifdef MatLabV4 
		  !mxIsFull(A_IN)
#endif
#ifdef MatLabV5
		  mxIsSparse(A_IN)
#endif
		|| !mxIsDouble(A_IN) ||
		(max(m,n) < 2) || (min(m,n) != 2)) {
		mexErrMsgTxt("CLIPPOLY requires that polygon A be at least 2 X N or N X 2 where N >= 2.");
	}
	if ( m == n)
	    mexPrintf("Since Polygon A matrix is 2x2, assuming that vertices were input one per row.\n");

	/* Check the dimensions of polygon B.  B can be 2 X N or N X 2. It must be at least
	   2 X 2. The last vertex listed is assumed to connect to the first vertex to form the 
	   polygon. If B is 2 X 2, then it is assumed that the vertices are listed one per row. */

	m = mxGetM(B_IN);
	n = mxGetN(B_IN);
	if (!mxIsNumeric(B_IN) || mxIsComplex(B_IN) || 
#ifdef MatLabV4 
		  !mxIsFull(B_IN)
#endif
#ifdef MatLabV5
		  mxIsSparse(B_IN)
#endif
		|| !mxIsDouble(B_IN) ||
		(max(m,n) < 2) || (min(m,n) != 2)) {
		mexErrMsgTxt("CLIPPOLY requires that polygon B be at least 2 X N or N X 2 where N >= 2.");
	}
	if ( m == n)
	    mexPrintf("Since Polygon B matrix is 2x2, assuming that vertices were input one per row.\n");

    /* Transfer the polygons from the Matlab matrix to a "Poly" class object. */
    
    a = inPoly(A_IN);
    b = inPoly(B_IN);

//mexPrintf("Area a %g b %g\n", a->area(), b->area());

	/* Do the actual computations in a subroutine */

	clip_poly( *a, *b, a_min_b, b_min_a, a_and_b );

	//cout << endl << "a_min_b:\n" << a_min_b; removed. Polygons are sent back to MatLab. gsl 10/25/96 
	//cout << "b_min_a:\n" << b_min_a;            "
	//cout << "a_and_b:\n" << a_and_b;            "

	/* Create matrices for the return arguments */

    getPolySizes( a_min_b, nVerts, nPolys );
#ifdef MatLabV4 //added. gsl 5/9/97
	AminusB_OUT = mxCreateFull(2, *nVerts, REAL);     // vertices
	AminusBIdx_OUT = mxCreateFull(1, *nPolys, REAL);  // number of vertices for each polygon
	AminusBn_OUT = mxCreateFull(1, 1, REAL);          // number of polygons
	AminusBarea_OUT = mxCreateFull(1, *nPolys, REAL); // area of each polygon
	
  getPolySizes( b_min_a, nVerts, nPolys );          // "
	BminusA_OUT = mxCreateFull(2, *nVerts, REAL);
	BminusAIdx_OUT = mxCreateFull(1, *nPolys, REAL);
	BminusAn_OUT = mxCreateFull(1, 1, REAL);
	BminusAarea_OUT = mxCreateFull(1, *nPolys, REAL);
	
  getPolySizes( a_and_b, nVerts, nPolys );          // "
	AandB_OUT = mxCreateFull(2, *nVerts, REAL);
	AandBIdx_OUT = mxCreateFull(1, *nPolys, REAL);
	AandBn_OUT = mxCreateFull(1, 1, REAL);
	AandBarea_OUT = mxCreateFull(1, *nPolys, REAL);
#endif
#ifdef MatLabV5
	AminusB_OUT = mxCreateDoubleMatrix(2, *nVerts, mxREAL);     // vertices
	AminusBIdx_OUT = mxCreateDoubleMatrix(1, *nPolys, mxREAL);  // number of vertices for each polygon
	AminusBn_OUT = mxCreateDoubleMatrix(1, 1, mxREAL);          // number of polygons
	AminusBarea_OUT = mxCreateDoubleMatrix(1, *nPolys, mxREAL); // area of each polygon
	
  getPolySizes( b_min_a, nVerts, nPolys );          // "
	BminusA_OUT = mxCreateDoubleMatrix(2, *nVerts, mxREAL);
	BminusAIdx_OUT = mxCreateDoubleMatrix(1, *nPolys, mxREAL);
	BminusAn_OUT = mxCreateDoubleMatrix(1, 1, mxREAL);
	BminusAarea_OUT = mxCreateDoubleMatrix(1, *nPolys, mxREAL);
	
  getPolySizes( a_and_b, nVerts, nPolys );          // "
	AandB_OUT = mxCreateDoubleMatrix(2, *nVerts, mxREAL);
	AandBIdx_OUT = mxCreateDoubleMatrix(1, *nPolys, mxREAL);
	AandBn_OUT = mxCreateDoubleMatrix(1, 1, mxREAL);
	AandBarea_OUT = mxCreateDoubleMatrix(1, *nPolys, mxREAL);
#endif

	/* Load each output matrix with the result. */

  outPoly(a_min_b,AminusB_OUT,AminusBIdx_OUT,AminusBn_OUT,AminusBarea_OUT); // A - B
	outPoly(b_min_a,BminusA_OUT,BminusAIdx_OUT,BminusAn_OUT,BminusAarea_OUT); // B - A
	outPoly(a_and_b,AandB_OUT,AandBIdx_OUT,AandBn_OUT,AandBarea_OUT);         // A and B

	delete	a;
	delete	b;

	clear(a_min_b);
	clear(b_min_a);
	clear(a_and_b);

	return /*0 gsl 10/25/96*/;
}
} /* end of extern "C" */

