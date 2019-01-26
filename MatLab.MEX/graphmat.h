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

/*
	graphmat.h
	Author: Hans Gringhuis

	graphmat - 3d graphics and associated matrix and vector routines
*/
/*
 * $Log: graphmat.h,v $
 * Revision 1.6  1992/10/16  16:16:47  klamer
 * Gave anonymous structures and unions names;
 * This to circumvent bug in gdb4.5.
 *
 * Revision 1.5  1992/09/11  15:08:09  klamer
 * deleted const on first argument of gm_alloc.
 * added const to v_len2() call.
 *
 * Revision 1.4  1992/05/19  07:41:49  klamer
 * gm_dummy is no longer defined if C++ is used.
 * C++ is more efficient now!
 *
 * Revision 1.3  1992/05/11  13:10:54  klamer
 * Added const in prototypes for const arguments.
 *
 * Revision 1.2  1992/05/07  14:48:47  klamer
 * made C++ compatible.
 *
 */

#ifndef GRAPHMAT_INCLUDE
#define GRAPHMAT_INCLUDE

/****** Other includes ******/
/*#ifndef	FILE removed, since output is sent to MatLab command window. gsl 11/2/96
#include <stdio.h>
#endif
*/
#ifdef mac_h /* added. gsl 10/18/96 */
#include <stdlib.h>
#else
#include <assert.h> /* added for IBM PC compatibility. gsl 6/6/97 */
#ifndef __malloc_h
#include <malloc.h>
#endif
#endif

#ifndef __math_h
#include <math.h>
#endif

#ifndef included_mex_h
#include "mex.h" /* added. gsl 5/9/97 */
#endif
#define included_mex_h

/****** DEFINES ******/

/* macro's for accessing the data elements of a vector or a matrix */
#define m_elem(mat, i, j)	((mat).m[(i)][(j)])
#define v_elem(vec, i) 		((vec).a[(int)(i)]) 
#define v_x(vec)		((vec).s.x)
#define v_y(vec)		((vec).s.y)
#define v_z(vec)		((vec).s.z)
#define v_w(vec)		((vec).s.w)

/*
#define gm_NEW(type, ptr, func)  \
		(((gm_dummy = malloc(sizeof(type))) == NULL) ? \
	        ((type *)gm_error(NOMEM, func)) : \
		(type *)gm_dummy)  
*/

/*typedef enum
{
    DIV0, NOMEM, MATSING
} gm_error_t; removed. gsl 10/30/96 */

#ifdef __cplusplus
/*#ifdef mac_h*/ /* gsl 10/18/96  removed. gsl 10/30/96 */
/*int default_gm_error(gm_error_t, const char * );
extern "C" int (*gm_error)( gm_error_t, const char * );
#else
extern "C" void gm_error( int, const char * );
#endif*/

int gsl_error(char *errStr);

#ifdef __GNUG__
#pragma interface
#endif

inline void *
#ifdef __cplusplus
gm_alloc( /*const*/ void *ptr, /*const*/ char *func, int len )
#else
gm_alloc( ptr, func, len )
void *ptr;
char *func;
int len;
#endif
{
	if (ptr != 0)
		return ptr;
	else
	{
		void	*gm_dummy;

		if ((gm_dummy = malloc(len)) == NULL) {
			//return gm_error(NOMEM,func), (void *)0; removed. gsl 10/30/96
			gsl_error(func); // added. gsl 10/30/96
			return NULL; // added to satisfy compiler warning. gsl 10/30/96
		}
		else
			return gm_dummy;
	}
}
#define	gm_ALLOC(type, ptr, func)	((type *) \
					  gm_alloc(ptr, func, sizeof(type))) /* added missing ) at end. gsl 10/16/96 */
#else
/****** Globals ******/
char		*gm_dummy; /* used for memory allocation in gm_ALLOC() */

/* check if ptr is NULL, if so then allocate memory else return ptr */
#define gm_ALLOC(type, ptr, func)  (((ptr) == NULL) ? \
		((gm_dummy = malloc(sizeof(type))) == NULL) ? \
	        //((type *)gm_error(NOMEM, func)) : \ removed. gsl 10/30/96
	        gsl_error(func) : // added. gsl 10/30/96
		(type *)gm_dummy : (ptr)) 
#endif

/* if ptr is NULL then deallocate used space pointed by ptr */
#define gm_FREE(ptr) if((ptr) != NULL) free((char *)(ptr))


/* divide num by div if div != 0 else gm_error() */
//#define gm_DIV(num, div, func) (((div) != 0.0) ? ((num) / (div)) : gm_error(DIV0, (func))) removed. gsl 10/30/96
#define gm_DIV(num, div, func) (((div) != 0.0) ? ((num) / (div)) : gsl_error(func))

/****** Level 1 : data definition ******/
typedef union hvec2_t
{
	double a[3];
	struct hvec2_s
	{
		double	x, y, w; 
	} s;
} hvec2_t;


typedef union hvec3_t
{
	double a[4];
	struct hvec3_s
	{
		double x, y, z, w;
	} s;
} hvec3_t;


typedef struct hmat2_t
{
	double m[3][3];
} hmat2_t;


typedef struct hmat3_t
{
	double m[4][4];
} hmat3_t;


typedef enum
{
	X_AXIS, Y_AXIS, Z_AXIS
} b_axis;


/****** Level 2 : Data initialisation ******/
#define m_free2(matrix)		gm_FREE(matrix)
#define v_free2(vector)		gm_FREE(vector)
#define m_free3(matrix)		gm_FREE(matrix)
#define v_free3(vector)		gm_FREE(vector)

#ifndef __cplusplus
#define m_alloc2(m_result)	gm_ALLOC(hmat2_t, (m_result), "Cannot allocate memory for m_alloc2().")
#define v_alloc2(v_result)	gm_ALLOC(hvec2_t, (v_result), "Cannot allocate memory for v_alloc2().")

#define m_alloc3(m_result)	gm_ALLOC(hmat3_t, (m_result), "Cannot allocate memory for m_alloc3().")
#define v_alloc3(v_result)	gm_ALLOC(hvec3_t, (v_result), "Cannot allocate memory for v_alloc3().")
#else
inline void *
Alloc(unsigned int x )
{
	void	*res;

	res = malloc(x);
	/*if (res == 0)
		gm_error(NOMEM,"Alloc"); removed. gsl 10/30/96 */
    assert(res != 0);

	return res;
}


inline hmat2_t *
m_alloc2(hmat2_t *r)
{
	if (r)
		return r;
	else
		return (hmat2_t *) Alloc(sizeof(hmat2_t));
}

inline hmat3_t *
m_alloc3(hmat3_t *r)
{
	if (r)
		return r;
	else
		return (hmat3_t *) Alloc(sizeof(hmat3_t));
}

inline hvec2_t *
v_alloc2(hvec2_t *r)
{
	if (r)
		return r;
	else
		return (hvec2_t *) Alloc(sizeof(hvec2_t));
}

inline hvec3_t *
v_alloc3(hvec3_t *r)
{
	if (r)
		return r;
	else
		return (hvec3_t *) Alloc(sizeof(hvec3_t));
}
#endif

/****** FUNCTION DEFINITIONS ******/
#if defined(__STDC__) || defined(__cplusplus)
# define P_(s) s
#else
# define P_(s) ()
#endif

#ifdef __cplusplus
extern "C" {
#define	C__	} /*; removed syntactically incorrect ";" gsl 10/15/96 */
#else
#define	C__
#endif

hmat2_t *m_cpy2 P_((const hmat2_t *m_source, hmat2_t *m_result));
hmat2_t *m_unity2 P_((hmat2_t *m_result));
hvec2_t *v_cpy2 P_((const hvec2_t *v_source, hvec2_t *v_result));
hvec2_t *v_fill2 P_((double x, double y, double w, hvec2_t *v_result));
hvec2_t *v_unity2 P_((b_axis axis, hvec2_t *v_result));
hvec2_t *v_zero2 P_((hvec2_t *v_result));
hmat3_t *m_cpy3 P_((const hmat3_t *m_source, hmat3_t *m_result));
hmat3_t *m_unity3 P_((hmat3_t *m_result));
hvec3_t *v_cpy3 P_((const hvec3_t *v_source, hvec3_t *v_result));
hvec3_t *v_fill3 P_((double x, double y, double z, double w, hvec3_t *v_result));
hvec3_t *v_unity3 P_((b_axis axis, hvec3_t *v_result));
hvec3_t *v_zero3 P_((hvec3_t *v_result));
double m_det2 P_((const hmat2_t *matrix));
double v_len2 P_((const hvec2_t *vector));
double vtmv_mul2 P_((const hvec2_t *vector, const hmat2_t *matrix));
double vv_inprod2 P_((const hvec2_t *vectorA, const hvec2_t *vectorB));
hmat2_t *m_inv2 P_((const hmat2_t *matrix, hmat2_t *m_result));
hmat2_t *m_tra2 P_((const hmat2_t *matrix, hmat2_t *m_result));
hmat2_t *mm_add2 P_((const hmat2_t *matrixA, const hmat2_t *matrixB, hmat2_t *m_result));
hmat2_t *mm_mul2 P_((/*const */hmat2_t *matrixA, /*const*/ hmat2_t *matrixB, /*const gsl 10/16/96*/ hmat2_t *m_result));
hmat2_t *mm_sub2 P_((const hmat2_t *matrixA, const hmat2_t *matrixB, hmat2_t *m_result));
hmat2_t *mtmm_mul2 P_((const hmat2_t *matrixA, const hmat2_t *matrixB, hmat2_t *m_result));
hmat2_t *sm_mul2 P_((double scalar, const hmat2_t *matrix, hmat2_t *m_result));
hmat2_t *vvt_mul2 P_((const hvec2_t *vectorA, const hvec2_t *vectorB, hmat2_t *m_result));
hvec2_t *mv_mul2 P_((const hmat2_t *matrix, /*const gsl 10/16/96*/hvec2_t *vector, hvec2_t *v_result));
hvec2_t *sv_mul2 P_((double scalar, const hvec2_t *vector, hvec2_t *v_result));
hvec2_t *v_homo2 P_((const hvec2_t *vector, hvec2_t *v_result));
hvec2_t *v_norm2 P_((const hvec2_t *vector, hvec2_t *v_result));
hvec2_t *vv_add2 P_((const hvec2_t *vectorA, const hvec2_t *vectorB, hvec2_t *v_result));
hvec2_t *vv_sub2 P_((const hvec2_t *vectorA, const hvec2_t *vectorB, hvec2_t *v_result));
/* double m_det3 P_((const hmat3_t *matrix)); not used. gsl 10/17/96 */
double v_len3 P_((const hvec3_t *vector));
double vtmv_mul3 P_((const hvec3_t *vector, const hmat3_t *matrix));
double vv_inprod3 P_((const hvec3_t *vectorA, const hvec3_t *vectorB));
hmat3_t *m_inv3 P_((const hmat3_t *matrix, hmat3_t *m_result));
hmat3_t *m_tra3 P_((const hmat3_t *matrix, hmat3_t *m_result));
hmat3_t *mm_add3 P_((const hmat3_t *matrixA, const hmat3_t *matrixB, hmat3_t *m_result));
hmat3_t *mm_mul3 P_((/*const */hmat3_t *matrixA, /*const gsl 10/17/96*/hmat3_t *matrixB, hmat3_t *m_result));
hmat3_t *mm_sub3 P_((const hmat3_t *matrixA, const hmat3_t *matrixB, hmat3_t *m_result));
/* hmat3_t *mtmm_mul3 P_((const hmat3_t *matrixA, const hmat3_t *matrixB, hmat3_t *m_result)); not used. gsl 10/17/96 */
hmat3_t *sm_mul3 P_((double scalar, const hmat3_t *matrix, hmat3_t *m_result));
hvec3_t *mv_mul3 P_((const hmat3_t *matrix, const hvec3_t *vector, hvec3_t *v_result));
hvec3_t *sv_mul3 P_((double scalar, const hvec3_t *vector, hvec3_t *v_result));
hvec3_t *v_homo3 P_((const hvec3_t *vector, hvec3_t *v_result));
hvec3_t *v_norm3 P_((const hvec3_t *vector, hvec3_t *v_result));
hvec3_t *vv_add3 P_((const hvec3_t *vectorA, const hvec3_t *vectorB, hvec3_t *v_result));
hvec3_t *vv_cross3 P_((/*const */hvec3_t *vectorA, /*const gsl 10/17/96*/hvec3_t *vectorB, hvec3_t *v_result));
hvec3_t *vv_sub3 P_((const hvec3_t *vectorA, const hvec3_t *vectorB, hvec3_t *v_result));
hmat3_t *vvt_mul3 P_((const hvec3_t *vectorA, const hvec3_t *vectorB, hmat3_t *m_result));
hmat2_t *miraxis2 P_((b_axis axis, hmat2_t *m_result));
hmat2_t *mirorig2 P_((hmat2_t *m_result));
hmat2_t *rot2 P_((double rotation, hmat2_t *m_result));
hmat2_t *scaorig2 P_((double scale, hmat2_t *m_result));
hmat2_t *scaxis2 P_((double scale, b_axis axis, hmat2_t *m_result));
hmat2_t *transl2 P_((const hvec2_t *translation, hmat2_t *m_result));
hmat3_t *miraxis3 P_((b_axis axis, hmat3_t *m_result));
hmat3_t *mirorig3 P_((hmat3_t *m_result));
hmat3_t *mirplane3 P_((b_axis plane, hmat3_t *m_result));
hmat3_t *prjorthaxis P_((b_axis axis, hmat3_t *m_result));
hmat3_t *prjpersaxis P_((b_axis axis, hmat3_t *m_result));
hmat3_t *rot3 P_((double rotation, b_axis axis, hmat3_t *m_result));
hmat3_t *scaorig3 P_((double scale, hmat3_t *m_result));
hmat3_t *scaplane3 P_((double scale, b_axis plane, hmat3_t *m_result));
hmat3_t *scaxis3 P_((double scale, b_axis axis, hmat3_t *m_result));
hmat3_t *transl3 P_((const hvec3_t *translation, hmat3_t *m_result));

#ifdef __cplusplus /* added by gsl 10/15/96 */
C__
#endif
#undef C__
#undef P_
#endif
