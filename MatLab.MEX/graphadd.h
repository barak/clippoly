/*
 *    tutvis library

 *    Copyright (C) 1993  University of Twente

 *    klamer@mi.el.utwente.nl

 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Library General Public
 *    License as published by the Free Software Foundation; either
 *    version 2 of the License, or (at your option) any later version.

 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Library General Public License for more details.

 *    You should have received a copy of the GNU Library General Public
 *    License along with this library; if not, write to the Free
 *    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* $Log: graphadd.h,v $
 * Revision 1.3  1992/10/20  13:48:39  klamer
 * Made input arguments of v_inters const.
 *
// Revision 1.2  1992/09/09  15:49:10  klamer
// split C and C++ parts.
// Added ANSI C support.
//
//
// 				     GRAPHADD.H
//
//
// author        : G.H.J. Hilhorst
//
// created       : 16-04-1992
// last modified : 21-05-1992
*/

#ifndef GRAPHADD_H
#define	GRAPHADD_H	"$Header: /usr/local/include/RCS/graphadd.h,v 1.3 1992/10/20 13:48:39 klamer Exp $"

#ifndef GRAPHMAT_INCLUDE
#include	"graphmat.h"   // use local path not <xxx>. gsl 10/31/96
#endif

#define	v_print2(vec,vec_name)(mexPrintf(/*fprintf(stderr, changed to mexPrintf gsl 4/28/97*/ \
	"vec2 %s:\tx=%g\t y=%g\tw=%g\n",\
	vec_name,v_x(vec),v_y(vec),v_w(vec)))

#define	v_print3(vec,vec_name)(mexPrintf(/*fprintf(stderr, changed to mexPrintf gsl 4/28/97*/ \
	"vec3 %s:\tx=%g\t y=%g\tz=%g\tw=%g\n",\
	vec_name,v_x(vec),v_y(vec),v_z(vec),v_w(vec)))

#define	m_print2(mat,vec_name) if(&(mat)!=NULL) mexPrintf(/*fprintf(stderr, changed to mexPrintf gsl 4/28/97*/ \
	"mat2 %s:\n%g\t%g\t%g\n%g\t%g\t%g\n%g\t%g\t%g\n", \
	vec_name,m_elem(mat,0,0),m_elem(mat,0,1),m_elem(mat,0,2), \
	m_elem(mat,1,0),m_elem(mat,1,1),m_elem(mat,1,2), \
	m_elem(mat,2,0),m_elem(mat,2,1),m_elem(mat,2,2))

#define	m_print3(mat,vec_name) if(&(mat)!=NULL) mexPrintf(/*fprintf(stderr, changed to mexPrintf gsl 4/28/97*/ \
 "mat3 %s:\n%g\t%g\t%g\t%g\n%g\t%g\t%g\t%g\n%g\t%g\t%g\t%g\n%g\t%g\t%g\t%g\n",\
     vec_name,m_elem(mat,0,0),m_elem(mat,0,1),m_elem(mat,0,2),m_elem(mat,0,3),\
	m_elem(mat,1,0),m_elem(mat,1,1),m_elem(mat,1,2),m_elem(mat,1,3), \
	m_elem(mat,2,0),m_elem(mat,2,1),m_elem(mat,2,2),m_elem(mat,2,3), \
	m_elem(mat,3,0),m_elem(mat,3,1),m_elem(mat,3,2),m_elem(mat,3,3))

/*#define v_scan2(vec)(scanf("%lf %lf %lf",&v_x(*vec),&v_y(*vec),&v_w(*vec)))

#define v_scan3(vec)(scanf("%lf %lf %lf %lf",&v_x(*vec),&v_y(*vec),\
	&v_z(*vec),&v_w(*vec)))
	
removed. gsl 4/28/97
*/

#ifdef __cplusplus

int v_inters2(
	const hvec2_t &p1,
	const hvec2_t &p2,
	const hvec2_t &q1,
	const hvec2_t &q2,
	hvec2_t *S1,
	hvec2_t *S2
	);

extern "C" {
#endif


void	v_dupl2(hvec2_t *, hvec2_t *);
void	v_dupl3(hvec3_t *, hvec3_t *);
void	m_dupl2(hmat2_t *, hmat2_t *);
void	m_dupl3(hmat3_t *, hmat3_t *);

#ifdef __cplusplus
} //; removed syntactically incorrect ";" gsl 10/10/96
#endif

#endif

