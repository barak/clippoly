static char rcs_id[] = "$Header: /iue/cvsroot/vproject/wafer/mkwafer/clippoly/poly/graphmat.cc,v 1.1.1.1 2000/09/12 09:34:32 binder Exp $";
/*
  $Log: graphmat.cc,v $
  Revision 1.1.1.1  2000/09/12 09:34:32  binder


  polygon clipper from gregg leichtman

 * Revision 1.8  1993/01/28  15:25:47  klamer
 * Changed scaxis: now is scaled along the axis; the line-mirror behaviour
 * is now deleted.
 *
 * Revision 1.7  1993/01/18  16:28:54  klamer
 * added inclusion of err.h.
 * Added return value to mm_add3
 * Simplified v_norm3
 * Changed prjorthaxis3. Tricky -- check for results.
 * Deleted unused variables in prjpersaxis.
 *
 * Revision 1.6  1992/03/26  16:33:05  klamer
 * prjpersaxis corrected for Z_AXIS (implemented proper).
 *
 * Revision 1.5  1992/03/25  15:13:41  klamer
 * made lint complain less.
 *
 * Revision 1.4  1992/01/29  16:19:41  aartjan
 * bugs in rot3() and vv_inprod3() fixed
 *
 * Revision 1.3  1992/01/29  08:45:21  aartjan
 * sv_mul bug fixed; vv_inprod optimized
 *

  graphmat.c - 3d graphics and associated matrix and vector
               routines in homogeneous coordinates.
   Author : Hans Gringhuis
*/

/* WARNING: It appears that memory is allocated in these routines but is never released.
            => a lot of memory leaks. gsl 10/17/96
            I have found that I read the code in error. There do not appear to be
            any memory leaks. gsl 1/27/97
 */

#include "err.h"   /* use local path not <xxx>. gsl 10/31/96 */

#include "graphmat.h"   /* use local path not <xxx>. gsl 10/31/96 */

#ifndef mac_h /* gsl 10/15/96 */
static int   default_gm_error(gm_error_t, const char *);
int (*gm_error)(gm_error_t, const char *) = default_gm_error;
#else
int (*gm_error)( gm_error_t, const char * ) = default_gm_error;
#endif

/***** initialisation of general error-routine ******/

/****** General error-routine ******/
/*static gsl 10/18/96*/ static int
#ifdef __cplusplus /* gsl 10/15/96 */
default_gm_error(gm_error_t gm_errno, const char *gm_func) /* changed char *gm_func to const char *gm_func. gsl 10/15/96 */
#else
default_gm_error(gm_errno, gm_func)
gm_error_t  gm_errno;
char   *gm_func;
#endif
{
  switch(gm_errno)
  {
     case NOMEM : fatal("Graphmat-error : Memory allocation failure in function : %s\n", gm_func);
     case DIV0 : fatal("Graphmat-error : Division by zero in function : %s\n", gm_func);
     case MATSING : fatal("Graphmat-error : Matrix is singular in function : %s\n", gm_func);
     default : fatal("Graphmat-error : Undefined error in function : %s\n", gm_func);
  };
  return 1; /* added to satisfy compiler. gsl 10/16/96 */
}

/****** Level 2 : Data initialisation ******/
hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
m_cpy2(const hmat2_t *m_source, hmat2_t *m_result)
#else
m_cpy2(m_source, m_result)
hmat2_t *m_source;
hmat2_t *m_result;
#endif
{
   
   m_result = gm_ALLOC(hmat2_t, m_result, "m_cpy2()");

   *m_result = *m_source;

   return m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
m_unity2(hmat2_t *m_result)
#else
m_unity2(m_result)
hmat2_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat2_t, m_result, "m_unity2()");

   for(i=0; i<3; i++)
     for(j=0; j<3; j++)
       m_elem(*m_result, i, j) = (i != j) ? 0.0 : 1.0;

   return m_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_cpy2(const hvec2_t *v_source, hvec2_t *v_result)
#else
v_cpy2(v_source, v_result)
hvec2_t *v_source;
hvec2_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec2_t, v_result, "v_cpy2");

   *v_result = *v_source;

   return v_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_fill2(double x, double y, double w, hvec2_t *v_result)
#else
v_fill2(x, y, w, v_result)
double  x, y, w;
hvec2_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec2_t, v_result, "v_fill2()");

   v_x(*v_result) = x;
   v_y(*v_result) = y;
   v_w(*v_result) = w;

   return v_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_unity2(b_axis  axis, hvec2_t *v_result)
#else
v_unity2(axis, v_result)
b_axis  axis;
hvec2_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec2_t, v_result, "v_unity2()");

   if(axis == X_AXIS)
   {
     v_x(*v_result) = 1.0;
     v_y(*v_result) = 0.0;
   }
   else
   {
     v_x(*v_result) = 0.0;
     v_y(*v_result) = 1.0;
   };
   v_w(*v_result) = 1.0;

   return v_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_zero2(hvec2_t *v_result)
#else
v_zero2(v_result)
hvec2_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec2_t, v_result, "v_zero2()");

   v_x(*v_result) = v_y(*v_result) = 0.0;
   v_w(*v_result) = 1.0;

   return v_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
m_cpy3(const hmat3_t *m_source, hmat3_t *m_result)
#else
m_cpy3(m_source, m_result)
hmat3_t *m_source;
hmat3_t *m_result;
#endif
{
   m_result = gm_ALLOC(hmat3_t, m_result, "m_cpy3()");

   *m_result = *m_source;

   return m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
m_unity3(hmat3_t *m_result)
#else
m_unity3(m_result)
hmat3_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat3_t, m_result, "m_unity3()");

   for(i=0; i<4; i++)
     for(j=0; j<4; j++)
          m_elem(*m_result, i, j) = (i != j) ? 0.0 : 1.0;

   return m_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_cpy3(const hvec3_t *v_source, hvec3_t *v_result)
#else
v_cpy3(v_source, v_result)
hvec3_t *v_source;
hvec3_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec3_t, v_result, "v_cpy3()");

   *v_result = *v_source;

   return v_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_fill3(double x, double y, double z, double w, hvec3_t *v_result)
#else
v_fill3(x, y, z, w, v_result)
double  x, y, z, w;
hvec3_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec3_t, v_result, "v_fill3()");

   v_x(*v_result) = x;
   v_y(*v_result) = y;
   v_z(*v_result) = z;
   v_w(*v_result) = w;

   return v_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_unity3(b_axis  axis, hvec3_t *v_result)
#else
v_unity3(axis, v_result)
b_axis  axis;
hvec3_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec3_t, v_result, "v_unity3()");

   switch(axis)
   {
     case X_AXIS : v_x(*v_result) = 1.0;
                   v_y(*v_result) = v_z(*v_result) = 0.0;
                   break;
     case Y_AXIS : v_y(*v_result) = 1.0;
                   v_x(*v_result) = v_z(*v_result) = 0.0;
                   break;
     default : v_z(*v_result) = 1.0;
               v_x(*v_result) = v_y(*v_result) = 0.0;
               break;
   };
   v_w(*v_result) = 1.0;

   return v_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_zero3(hvec3_t *v_result)
#else
v_zero3(v_result)
hvec3_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec3_t, v_result, "v_zero3()");

   v_x(*v_result) = v_y(*v_result) = v_z(*v_result) = 0.0;
   v_w(*v_result) = 1.0;

   return v_result;
}

/****** Level 3 : Basic lineair algebra : 2D homogeneous coordinates ******/
double
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
m_det2(const hmat2_t *matrix)
#else
m_det2(matrix)
hmat2_t *matrix;
#endif
{

   return /* Schutte obviously isn't using this function. gsl 10/16/96 */
	m_elem(*matrix,0,0) * (m_elem(*matrix,1,1) *
	m_elem(*matrix,2,2) -
	m_elem(*matrix,1,2) * m_elem(*matrix,2,1)) -
	m_elem(*matrix,1,0) * (m_elem(*matrix,0,1) *
	m_elem(*matrix,2,2) -
	m_elem(*matrix,0,2) * m_elem(*matrix,2,1)) +
	m_elem(*matrix,2,0) * (m_elem(*matrix,0,1) *
	m_elem(*matrix,1,2) -
	m_elem(*matrix,0,2) * m_elem(*matrix,1,1));

}

double
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_len2(const hvec2_t *vector)
#else
v_len2(vector)
hvec2_t *vector;
#endif
{
   double  result;

   result = ((sqrt(v_x(*vector) * v_x(*vector) + 
              v_y(*vector) * v_y(*vector))));

   return v_w(*vector) != 0.0 ? result / v_w(*vector) : result;
}

double
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vtmv_mul2(const hvec2_t *vector, const hmat2_t *matrix)
#else
vtmv_mul2(vector, matrix)
hvec2_t *vector;
hmat2_t *matrix;
#endif
{

   return
     ((v_x(*vector) * m_elem(*matrix, 0, 0) +
      v_y(*vector) * m_elem(*matrix, 1, 0) +
      v_w(*vector) * m_elem(*matrix, 2, 0)) * 
      v_x(*vector)) +
      ((v_x(*vector) * m_elem(*matrix, 0, 1) +
      v_y(*vector) * m_elem(*matrix, 1, 1) +
      v_w(*vector) * m_elem(*matrix, 2, 1)) *
      v_y(*vector)) +
      ((v_x(*vector) * m_elem(*matrix, 0, 2) +
      v_y(*vector) * m_elem(*matrix, 1, 2) +
      v_w(*vector) * m_elem(*matrix, 2, 2)) *
      v_w(*vector));
}

double
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vv_inprod2(const hvec2_t *vectorA, const hvec2_t *vectorB)
#else
vv_inprod2(vectorA, vectorB)
hvec2_t *vectorA;
hvec2_t *vectorB;
#endif
{  double  result, div;

   result = v_x(*vectorA) * v_x(*vectorB) + 
            v_y(*vectorA) * v_y(*vectorB); 
   div = 1.0;
   if(v_w(*vectorA) != 0.0 && v_w(*vectorA) != 1.0)
     div *= v_w(*vectorA);
   if(v_w(*vectorB) != 0.0 && v_w(*vectorB) != 1.0)
     div *= v_w(*vectorB);
   if(div!=1.0) return result/div;

   return result;
}

/* Used by "m_inv2()" */
static void 
#ifdef __cplusplus /* changed to handle prototypes. gsl 10/16/96 */
submultiples2(hmat2_t *m_input, hmat2_t *m_result, int rownr, int workingrow)
#else
submultiples2(m_input, m_result, rownr, workingrow)
hmat2_t *m_input, *m_result;
int  rownr, workingrow;
#endif
{
   int i;
   double  subtractionfactor;
   
   if((subtractionfactor = m_elem(*m_input, workingrow, rownr)) != 0.0)
   {
     for(i=rownr; i<3; i++)
        m_elem(*m_input,workingrow,i) -= m_elem(*m_input,rownr,i) * subtractionfactor;

     for(i=0; i<3; i++)
        m_elem(*m_result,workingrow,i) -= m_elem(*m_result,rownr,i) * subtractionfactor;
   };
} 

/* Used by "m_inv2()" */
static void
#ifdef __cplusplus /* changed to handle prototypes. gsl 10/16/96 */
interchangerow2(hmat2_t *m_input, hmat2_t *m_result, int rownr)
#else
interchangerow2(m_input, m_result, rownr)
hmat2_t *m_input, *m_result;
int rownr;
#endif
{
   int nextelement = rownr+1, i;
   double  buffer;

   while(m_elem(*m_input, nextelement, rownr) == 0.0) 
     if(++nextelement == 3)
        gm_error(MATSING, "m_inv2()");

   /* interchange one rowelement with an element of */
   /* a row with a nonzeroentry in the same column */
   for(i=0; i<3; i++)
   {
     buffer = m_elem(*m_input, nextelement, i);
     m_elem(*m_input, nextelement, i) = m_elem(*m_input, rownr, i);
     m_elem(*m_input, rownr, i) = buffer;
     
     buffer = m_elem(*m_result, nextelement, i);
     m_elem(*m_result, nextelement, i) = m_elem(*m_result, rownr, i);
     m_elem(*m_result, rownr, i) = buffer;
   };
}

/* Used by m_inv2()" */
static  void
#ifdef __cplusplus /* changed to handle prototypes. gsl 10/16/96 */
reduce_row2(hmat2_t *m_input, hmat2_t *m_result, int rownr)
#else
reduce_row2(m_input, m_result, rownr)
hmat2_t *m_input, *m_result;
int rownr;
#endif
{
   int i;
   double  factor;

   if(m_elem(*m_input, rownr, rownr) == 0.0)
     /* interchange this row with another row to  
       bring a nonzero entry in the main diagonal */
     interchangerow2(m_input, m_result, rownr);

   /* introduce a leading one by dividing the whole row */
   factor = m_elem(*m_input, rownr, rownr);
   for(i=rownr; i<3; i++)
     m_elem(*m_input, rownr, i) /= factor;
   for(i=0; i<3; i++)
     m_elem(*m_result, rownr, i) /= factor;
     

   for(i=0; i<3; i++)
        if(i != rownr)
     /* subtract suitable multiples of this row to the other rows */
     /* so that all other entries in this column become zeros.  */
        submultiples2(m_input, m_result, rownr, i); 
} 


/******
   Based on invmatrix.c, project ESPRIT 612 by Th. Koster.
******/
hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
m_inv2(const hmat2_t *matrix, hmat2_t *m_result)
#else
m_inv2(matrix, m_result)
hmat2_t *matrix;
hmat2_t *m_result; 
#endif
{
   hmat2_t m_input;
   int i, j;

   m_result = gm_ALLOC(hmat2_t, m_result, "m_inv2()");

   for(i=0; i<3; i++)
     for(j=0; j<3; j++)
        m_elem(*m_result, i, j) = (i!=j) ? 0.0 : 1.0;

   /* save contence of matrix */
   m_input = *matrix;

   /* reduce row for row to transform the */
   /* input matrix to an elementary matrix */
   for(i=0;i<3;i++)
        /* reduce this row to a row of an elementary matrix */
     reduce_row2(&m_input, m_result, i);

   return  m_result;
} 

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
m_tra2(const hmat2_t *matrix, hmat2_t *m_result)
#else
m_tra2(matrix, m_result)
hmat2_t *matrix;
hmat2_t *m_result;
#endif
{
   m_result = gm_ALLOC(hmat2_t, m_result, "m_tra2()");

   if(m_result != matrix)
   {
     int i,j;

     for(i=0; i<3; i++)
        for(j=0; j<3; j++)
          m_elem(*m_result, i, j) = m_elem(*matrix, j, i);
   }
   else
   {
     double  buf[3];

     buf[0] = m_elem(*matrix, 1, 0);
     buf[1] = m_elem(*matrix, 2, 0);
     buf[2] = m_elem(*matrix, 2, 1);

     m_elem(*m_result, 1, 0) = m_elem(*matrix, 0, 1);
     m_elem(*m_result, 2, 0) = m_elem(*matrix, 0, 2);
     m_elem(*m_result, 2, 1) = m_elem(*matrix, 1, 2);

     m_elem(*m_result, 0, 1) = buf[0]; 
     m_elem(*m_result, 0, 2) = buf[1];
     m_elem(*m_result, 1, 2) = buf[2];

   };

   return m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mm_add2(const hmat2_t *matrixA, const hmat2_t *matrixB, hmat2_t *m_result)
#else
mm_add2(matrixA, matrixB, m_result)
hmat2_t *matrixA;
hmat2_t *matrixB;
hmat2_t *m_result;
#endif
{
   int row, col;

   m_result = gm_ALLOC(hmat2_t, m_result, "mm_add2()");

   for(row=0; row<3; row++)
     for(col=0; col<3; col++)
        m_elem(*m_result, row, col) = m_elem(*matrixA, row, col) + m_elem(*matrixB, row, col);

	return m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mm_mul2( hmat2_t *matrixA,  hmat2_t *matrixB, hmat2_t *m_result)
#else
mm_mul2(matrixA, matrixB, m_result)
hmat2_t *matrixA;
hmat2_t *matrixB;
hmat2_t *m_result;
#endif
{
   int row, col, which_matrix; /* Is m_result used in place \
                and if which matrix equals \
                m_result */
   hmat2_t buf;

   if(m_result == matrixA)
   { 
     m_result = &buf;
     which_matrix = 1;
   }
   else
     if(m_result == matrixB)
     {
        m_result = &buf;
        which_matrix = 2;
     }
     else 
     {
        m_result = gm_ALLOC(hmat2_t, m_result, "mm_mul2()");
        which_matrix = 0;
     };

   for(row=0; row<3; row++)
     for(col=0; col<3; col++)
        m_elem(*m_result, row, col) = m_elem(*matrixA, row, 0) * m_elem(*matrixB, 0, col) +
                  m_elem(*matrixA, row, 1) * m_elem(*matrixB, 1, col) + m_elem(*matrixA, row, 2) *
	 	  m_elem(*matrixB, 2, col); 

   switch(which_matrix)
   {
     case 0 : return  m_result;
     case 1 : /* m_cpy2(m_result, matrixA); */
              *matrixA = *m_result;
              return  matrixA;
     case 2 : /* m_cpy2(m_result, matrixB); */
              *matrixB = *m_result;
              return matrixB;
   };
	error("This should not happen! %s %d\n", __FILE__, __LINE__ );
	return m_result;	/* garbage... */
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mm_sub2(const hmat2_t *matrixA, const hmat2_t *matrixB, hmat2_t *m_result)
#else
mm_sub2(matrixA, matrixB, m_result)
hmat2_t *matrixA;
hmat2_t *matrixB;
hmat2_t *m_result;
#endif
{
   int row, col;

   m_result = gm_ALLOC(hmat2_t, m_result, "mm_sub2()");

   for(row=0; row<3; row++)
     for(col=0; col<3; col++)
        m_elem(*m_result, row, col) = m_elem(*matrixA, row, col) - m_elem(*matrixB, row, col);

   return  m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mtmm_mul2(const hmat2_t *matrixA, const hmat2_t *matrixB, hmat2_t *m_result)
#else
mtmm_mul2(matrixA, matrixB, m_result)
hmat2_t *matrixA;
hmat2_t *matrixB;
hmat2_t *m_result;
#endif
{
   hmat2_t help;
   hmat2_t *matA=NULL; /* added to avoid implicit const pointer conversion problem. gsl 10/17/96 */
   hmat2_t *matB=NULL; /* " */

   m_result = gm_ALLOC(hmat2_t, m_result, "mtmm_mul2()");

   m_tra2(matrixA, &help);

   m_cpy2(matrixA,matA); /* added to avoid implicit const pointer conversion problem. gsl 10/17/96 */
   m_cpy2(matrixB,matB); /* " */
   mm_mul2(&help, matB, &help);
   mm_mul2(&help, matA, m_result);
   /*mm_mul2(&help, matrixB, &help);    removed. gsl 10/17/96
   mm_mul2(&help, matrixA, m_result);*/

   return  m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
sm_mul2(double  scalar, const hmat2_t *matrix, hmat2_t *m_result)
#else
sm_mul2(scalar, matrix, m_result)
double  scalar;
hmat2_t *matrix;
hmat2_t *m_result;
#endif
{
   int row, col;

   m_result = gm_ALLOC(hmat2_t, m_result, "sm_mul2()");

   for(row=0; row<3; row++)
     for(col=0; col<3; col++)
        m_elem(*m_result, row, col) = scalar * m_elem(*matrix, row, col);

   return  m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vvt_mul2(const hvec2_t *vectorA, const hvec2_t *vectorB, hmat2_t *m_result)
#else
vvt_mul2(vectorA, vectorB, m_result)
hvec2_t *vectorA;
hvec2_t *vectorB;
hmat2_t *m_result;
#endif
{
   int row, col;

   m_result = gm_ALLOC(hmat2_t, m_result, "vvt_mul2()");

   for(row=0; row<3; row++)
     for(col=0; col<3; col++)
        m_elem(*m_result, row, col) = v_elem(*vectorA, row) * v_elem(*vectorB, col);

   return  m_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mv_mul2(const hmat2_t *matrix, hvec2_t *vector, hvec2_t *v_result)
#else
mv_mul2(matrix, vector, v_result)
hmat2_t *matrix;
hvec2_t *vector;
hvec2_t *v_result;
#endif
{
   int row, inplace;
   hvec2_t buf;

   if(v_result == vector)
   {
     v_result = &buf;
     inplace = 1;
   }
   else
   {
     v_result = gm_ALLOC(hvec2_t, v_result, "mv_mul2()");
     inplace = 0;
   };

   for(row=0; row<3; row++)
        v_elem(*v_result, row) = m_elem(*matrix, row, 0) * v_elem(*vector, 0) +
                                 m_elem(*matrix, row, 1) * v_elem(*vector, 1) +
               			 m_elem(*matrix, row, 2) * v_elem(*vector, 2); 
   
   if(inplace)
   {
     /* v_cpy2(v_result, vector); */
     *vector = *v_result;

     return  vector;
   };

   return  v_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
sv_mul2(double scalar, const hvec2_t *vector, hvec2_t *v_result)
#else
sv_mul2(scalar, vector, v_result)
double  scalar;
hvec2_t *vector;
hvec2_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec2_t, v_result, "sv_mul2()");

   v_x(*v_result) = v_x(*vector) * scalar;
   v_y(*v_result) = v_y(*vector) * scalar;
   v_w(*v_result) = v_w(*vector);

   return  v_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_homo2(const hvec2_t *vector, hvec2_t *v_result)
#else
v_homo2(vector, v_result)
hvec2_t *vector;
hvec2_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec2_t, v_result, "v_homo2()");

   v_x(*v_result) = gm_DIV(v_x(*vector), v_w(*vector), "v_homo2()");
   v_y(*v_result) = v_y(*vector) / v_w(*vector);
   v_w(*v_result) = 1.0;

   return v_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_norm2(const hvec2_t *vector, hvec2_t *v_result)
#else
v_norm2(vector, v_result)
hvec2_t *vector;
hvec2_t *v_result;
#endif
{
   double  length = sqrt(v_x(*vector) * v_x(*vector) +
           v_y(*vector) * v_y(*vector));

   v_result = gm_ALLOC(hvec2_t, v_result, "v_norm2()");

   v_x(*v_result) = gm_DIV(v_x(*vector), length, "v_norm2()");
   v_y(*v_result) = v_y(*vector) / length;
   v_w(*v_result) = v_w(*vector) / length;

   return  v_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vv_add2(const hvec2_t *vectorA, const hvec2_t *vectorB, hvec2_t *v_result)
#else
vv_add2(vectorA, vectorB, v_result)
hvec2_t *vectorA;
hvec2_t *vectorB;
hvec2_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec2_t, v_result, "vv_add2()");

   v_x(*v_result) = v_x(*vectorA) + v_x(*vectorB);
   v_y(*v_result) = v_y(*vectorA) + v_y(*vectorB);
   v_w(*v_result) = v_w(*vectorA) + v_w(*vectorB);

   return  v_result;
}

hvec2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vv_sub2(const hvec2_t *vectorA, const hvec2_t *vectorB, hvec2_t *v_result)
#else
vv_sub2(vectorA, vectorB, v_result)
hvec2_t *vectorA;
hvec2_t *vectorB;
hvec2_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec2_t, v_result, "vv_sub2()");

   v_x(*v_result) = v_x(*vectorA) - v_x(*vectorB);
   v_y(*v_result) = v_y(*vectorA) - v_y(*vectorB);
   v_w(*v_result) = v_w(*vectorA) - v_w(*vectorB);

   return  v_result;
}


/****** Level 3 : Basic lineair algebra : 3D homogeneous
coordinates ******/

/***** Function is optimized, see below !!!
double
m_det3(matrix)
hmat3_t *matrix;
{
   hmat2_t det2;
   double  result=0.0;
   int col, count, row, row_det2, factor=1.0;

   for(count=0; count<4; count++)
   {
     row_det2 = 0;
     for(row=0; row<4; row++)
        if(count != row)
        {
          for(col=1; col<4; col++)
             m_elem(det2, row_det2, col-1) = m_elem(*matrix, row, col);
          row_det2++;
        };
     result += m_elem(*matrix, count, 0) * m_det2(&det2) * factor;
     factor = -factor;
   };
   return  result;
}
*/

/* used by m_det3() */
/* return the under-determinant of a 4*4 matrix */
/*static  double
#ifdef __cplusplus //changed to handle prototypes. gsl 10/16/96
det2_dyn(hmat3_t *matrix, int row_not)
#else
det2_dyn(matrix, row_not)
hmat3_t *matrix;
int row_not;
#endif
{
   int row[3], count, help=0;

   for(count=0; count<4; count++)
     if(count != row_not)
        row[help++] = count;

   return  //Schutte does not appear to be using this function. gsl 10/16/96
   m_elem(*matrix,row[0],1) * (m_elem(*matrix,row[1],2) *
   m_elem(*matrix,row[2],3) -
   m_elem(*matrix,row[1],3) * m_elem(*matrix,row[2],2)) -
   m_elem(*matrix,row[1],1) * (m_elem(*matrix,row[0],2) *
   m_elem(*matrix,row[2],3) -
   m_elem(*matrix,row[0],3) * m_elem(*matrix,row[2],2)) + 
   m_elem(*matrix,row[2],1) * (m_elem(*matrix,row[0],2) *
   m_elem(*matrix,row[1],3) -
   m_elem(*matrix,row[0],3) * m_elem(*matrix,row[1],2));
}

double
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
/*m_det3(const hmat3_t *matrix)
#else
m_det3(matrix) //Schutte does not appear to use this function, since det2_dyn does not return a value. gsl 10/16/96
hmat3_t *matrix;
#endif
{
   double  result=0.0;
   int row, factor=-1;

   for(row=0; row<4; row++)
     result += m_elem(*matrix, row, 0) * det2_dyn(matrix, row) *
         (factor *= -1);

   return result;
}  not used by Schutte. gsl 10/17/96 */

double
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_len3(const hvec3_t *vector)
#else
v_len3(vector)
hvec3_t *vector;
#endif
{
   double  result;

   result = ((sqrt(v_x(*vector) * v_x(*vector) + 
            v_y(*vector) * v_y(*vector) +
            v_z(*vector) * v_z(*vector))));

   return v_w(*vector) != 0.0 ? result / v_w(*vector) : result;
}

double
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vtmv_mul3(const hvec3_t *vector, const hmat3_t *matrix)
#else
vtmv_mul3(vector, matrix)
hvec3_t *vector;
hmat3_t *matrix;
#endif
{

   return /* Schutte does not appear to use this function. gsl 10/16/96 */
     ((v_x(*vector) * m_elem(*matrix, 0, 0) +
      v_y(*vector) * m_elem(*matrix, 1, 0) +
      v_z(*vector) * m_elem(*matrix, 2, 0) +
      v_w(*vector) * m_elem(*matrix, 3, 0)) * 
      v_x(*vector)) +
     ((v_x(*vector) * m_elem(*matrix, 0, 1) +
      v_y(*vector) * m_elem(*matrix, 1, 1) +
      v_z(*vector) * m_elem(*matrix, 2, 1) +
      v_w(*vector) * m_elem(*matrix, 3, 1)) *
      v_y(*vector)) +
     ((v_x(*vector) * m_elem(*matrix, 0, 2) +
      v_y(*vector) * m_elem(*matrix, 1, 2) +
      v_z(*vector) * m_elem(*matrix, 2, 2) +
      v_w(*vector) * m_elem(*matrix, 3, 2)) *
      v_z(*vector)) +
     ((v_x(*vector) * m_elem(*matrix, 0, 3) +
      v_y(*vector) * m_elem(*matrix, 1, 3) +
      v_z(*vector) * m_elem(*matrix, 2, 3) +
      v_w(*vector) * m_elem(*matrix, 3, 3)) *
      v_w(*vector));
}

double
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vv_inprod3(const hvec3_t *vectorA, const hvec3_t *vectorB)
#else
vv_inprod3(vectorA, vectorB)
hvec3_t *vectorA;
hvec3_t *vectorB;
#endif
{  double  result, div;

   result = v_x(*vectorA) * v_x(*vectorB) + 
            v_y(*vectorA) * v_y(*vectorB) +
            v_z(*vectorA) * v_z(*vectorB); 
   div = 1.0;
   if(v_w(*vectorA) != 0.0 && v_w(*vectorA) != 1.0)
     div *= v_w(*vectorA);
   if(v_w(*vectorB) != 0.0 && v_w(*vectorB) != 1.0)
     div *= v_w(*vectorB);
   if (div != 1.0) return result/div;

   return result;
}

/* Used by "m_inv3()" */
static void 
#ifdef __cplusplus /* changed to handle prototypes. gsl 10/16/96 */
submultiples3(hmat3_t *m_input, hmat3_t *m_result, int rownr, int workingrow)
#else
submultiples3(m_input, m_result, rownr, workingrow)
hmat3_t *m_input, *m_result;
int  rownr, workingrow;
#endif
{
   int i;
   double  subtractionfactor;
   
   if((subtractionfactor = m_elem(*m_input, workingrow, rownr)) != 0.0)
   {
     for(i=rownr; i<4; i++)
        m_elem(*m_input,workingrow,i) -= m_elem(*m_input,rownr,i) * subtractionfactor;


     for(i=0; i<4; i++)
        m_elem(*m_result,workingrow,i) -= m_elem(*m_result,rownr,i) * subtractionfactor;

   };
} 

/* Used by "m_inv3()" */
static  void
#ifdef __cplusplus /* changed to handle prototypes. gsl 10/16/96 */
interchangerow3(hmat3_t *m_input, hmat3_t *m_result, int rownr)
#else
interchangerow3(m_input, m_result, rownr)
hmat3_t *m_input, *m_result;
int rownr;
#endif
{
   int nextelement = rownr+1, i;
   double  buffer;

   while(m_elem(*m_input, nextelement, rownr) == 0.0) 
     if(++nextelement == 4)
        gm_error(MATSING, "m_inv3()");

   /* interchange one rowelement with an element of */
   /* a row with a nonzeroentry in the same column */
   for(i=0; i<4; i++)
   {
     buffer = m_elem(*m_input, nextelement, i);
     m_elem(*m_input, nextelement, i) = m_elem(*m_input, rownr, i);
     m_elem(*m_input, rownr, i) = buffer;
     
     buffer = m_elem(*m_result, nextelement, i);
     m_elem(*m_result, nextelement, i) = m_elem(*m_result, rownr, i);
     m_elem(*m_result, rownr, i) = buffer;
   };
}

/* Used by "m_inv3()" */
static  void
#ifdef __cplusplus /* changed to handle prototypes. gsl 10/16/96 */
reduce_row3(hmat3_t *m_input, hmat3_t *m_result, int rownr)
#else
reduce_row3(m_input, m_result, rownr)
hmat3_t *m_input, *m_result;
int rownr;
#endif
{
   int i;
   double  factor;

   if(m_elem(*m_input, rownr, rownr) == 0.0)
     /* interchange this row with another row to  
       bring a nonzero entry in the main diagonal */
     interchangerow3(m_input, m_result, rownr);

   /* introduce a leading one by dividing the whole row */
   factor = m_elem(*m_input, rownr, rownr);
   for(i=rownr; i<4; i++)
     m_elem(*m_input, rownr, i) /= factor;
   for(i=0; i<4; i++)
     m_elem(*m_result, rownr, i) /= factor;
     

   for(i=0; i<4; i++)
        if(i != rownr)
     /* subtract suitable multiples of this row to the other rows */
     /* so that all other entries in this column become zeros.  */
        submultiples3(m_input, m_result, rownr, i); 
} 


/******
   Based on invmatrix.c, project ESPRIT 612 by Th. Koster.
******/
hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
m_inv3(const hmat3_t *matrix, hmat3_t *m_result)
#else
m_inv3(matrix, m_result)
hmat3_t *matrix;
hmat3_t *m_result; 
#endif
{
   hmat3_t m_input;
   int i;

   m_result = m_unity3(m_result);

   /* save contence of matrix */
   m_input = *matrix;

   /* reduce row for row to transform the */
   /* input matrix to an elementary matrix */
   for(i=0;i<4;i++)
        /* reduce this row to a row of an elementary matrix */
     reduce_row3(&m_input, m_result, i);

   return  m_result;
} 

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
m_tra3(const hmat3_t *matrix, hmat3_t *m_result)
#else
m_tra3(matrix, m_result)
hmat3_t *matrix;
hmat3_t *m_result;
#endif
{
   m_result = gm_ALLOC(hmat3_t, m_result, "m_tra3()");

   if(m_result != matrix)
   {
     int i, j;

     m_result = gm_ALLOC(hmat3_t, m_result, "m_tra3()");

     for(i=0; i<4; i++)
        for(j=0; j<4; j++)
          m_elem(*m_result, i, j) = m_elem(*matrix, j, i);
   }
   else
   {
     double  buf[6];

     buf[0] = m_elem(*matrix, 1, 0);
     buf[1] = m_elem(*matrix, 2, 0);
     buf[2] = m_elem(*matrix, 2, 1);
     buf[3] = m_elem(*matrix, 3, 0);
     buf[4] = m_elem(*matrix, 3, 1);
     buf[5] = m_elem(*matrix, 3, 2);


     m_elem(*m_result, 1, 0) = m_elem(*matrix, 0, 1);
     m_elem(*m_result, 2, 0) = m_elem(*matrix, 0, 2);
     m_elem(*m_result, 2, 1) = m_elem(*matrix, 1, 2);
     m_elem(*m_result, 3, 0) = m_elem(*matrix, 0, 3);
     m_elem(*m_result, 3, 1) = m_elem(*matrix, 1, 3);
     m_elem(*m_result, 3, 2) = m_elem(*matrix, 2, 3);

     m_elem(*m_result, 0, 1) = buf[0]; 
     m_elem(*m_result, 0, 2) = buf[1];
     m_elem(*m_result, 0, 3) = buf[3];
     m_elem(*m_result, 1, 2) = buf[2];
     m_elem(*m_result, 1, 3) = buf[4];
     m_elem(*m_result, 2, 3) = buf[5];
   };

   return m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mm_add3(const hmat3_t *matrixA, const hmat3_t *matrixB, hmat3_t *m_result)
#else
mm_add3(matrixA, matrixB, m_result)
hmat3_t *matrixA;
hmat3_t *matrixB;
hmat3_t *m_result;
#endif
{
   int row, col;

   m_result = gm_ALLOC(hmat3_t, m_result, "mm_add3()");

   for(row=0; row<4; row++)
     for(col=0; col<4; col++)
        m_elem(*m_result, row, col) = m_elem(*matrixA, row, col) + m_elem(*matrixB, row, col);

	return m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mm_mul3( hmat3_t *matrixA, hmat3_t *matrixB, hmat3_t *m_result)
#else
mm_mul3(matrixA, matrixB, m_result)
hmat3_t *matrixA;
hmat3_t *matrixB;
hmat3_t *m_result;
#endif
{
   int row, col, which_matrix;
   hmat3_t buf;

   if(m_result == matrixA)
   { 
     m_result = &buf;
     which_matrix = 1;
   }
   else
     if(m_result == matrixB)
     {
        m_result = &buf;
        which_matrix = 2;
     }
     else 
     {
        m_result = gm_ALLOC(hmat3_t, m_result, "mm_mul3()");
        which_matrix = 0;
     };

   for(row=0; row<4; row++)
     for(col=0; col<4; col++)
        m_elem(*m_result, row, col) = m_elem(*matrixA, row, 0) * m_elem(*matrixB, 0, col) +
                  m_elem(*matrixA, row, 1) * m_elem(*matrixB, 1, col) + m_elem(*matrixA, row, 2) *
		  m_elem(*matrixB, 2, col) + m_elem(*matrixA, row, 3) * m_elem(*matrixB, 3, col); 

   switch(which_matrix)
   {
     case 0 : return  m_result;
     case 1 : /* m_cpy3(m_result, matrixA); */
              *matrixA = *m_result;
              return  matrixA;
     case 2 : /* m_cpy3(m_result, matrixB); */
              *matrixB = *m_result;
              return matrixB;
   };
	error("This should not happen! %s %d\n", __FILE__, __LINE__ );
	return m_result;	/* garbage... */
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mm_sub3(const hmat3_t *matrixA, const hmat3_t *matrixB, hmat3_t *m_result)
#else
mm_sub3(matrixA, matrixB, m_result)
hmat3_t *matrixA;
hmat3_t *matrixB;
hmat3_t *m_result;
#endif
{
   int row, col;

   m_result = gm_ALLOC(hmat3_t, m_result, "mm_sub3()");

   for(row=0; row<4; row++)
     for(col=0; col<4; col++)
        m_elem(*m_result, row, col) = m_elem(*matrixA, row, col) - m_elem(*matrixB, row, col);

   return  m_result;
}

/*hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
/*mtmm_mul3(const hmat3_t *matrixA, const hmat3_t *matrixB, hmat3_t *m_result)
#else
mtmm_mul3(matrixA, matrixB, m_result)
hmat3_t *matrixA;
hmat3_t *matrixB;
hmat3_t *m_result;
#endif
{
   hmat3_t help;

   m_result = gm_ALLOC(hmat3_t, m_result, "mtmm_mul3()");

   m_tra3(matrixA, &help);

   mm_mul3(&help, matrixB, &help);
   mm_mul3(&help, matrixA, m_result);

   return  m_result;
} not used by Schutte. gsl 10/17/96 */

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
sm_mul3(double scalar, const hmat3_t *matrix, hmat3_t *m_result)
#else
sm_mul3(scalar, matrix, m_result)
double  scalar;
hmat3_t *matrix;
hmat3_t *m_result;
#endif
{
   int row, col;

   m_result = gm_ALLOC(hmat3_t, m_result, "sm_mul3()");

   for(row=0; row<4; row++)
     for(col=0; col<4; col++)
        m_elem(*m_result, row, col) = scalar * m_elem(*matrix, row, col);

   return  m_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mv_mul3(const hmat3_t *matrix, const hvec3_t *vector, hvec3_t *v_result)
#else
mv_mul3(matrix, vector, v_result)
hmat3_t *matrix;
hvec3_t *vector;
hvec3_t *v_result;
#endif
{
   int row, inplace;
   hvec3_t buf;
   hvec3_t *vec = NULL;
   
   if(v_result == vector)
   {
     v_result = &buf;
     inplace = 1;
   }
   else
   {
     v_result = gm_ALLOC(hvec3_t, v_result, "mv_mul3()");
     inplace = 0;
   };

   for(row=0; row<4; row++)
        v_elem(*v_result, row) = m_elem(*matrix, row, 0) *
	v_elem(*vector, 0) + m_elem(*matrix, row, 1) *
	v_elem(*vector, 1) + m_elem(*matrix, row, 2) *
	v_elem(*vector, 2) + m_elem(*matrix, row, 3) *
	v_elem(*vector, 3); 
   
   if(inplace)
   {
     v_cpy3(v_result, vec/*tor gsl*/); /* added to avoid illegal implicit pointer conversion error. gsl 10/18/96 */
     return  vec/*tor gsl*/;
   };

   return  v_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
sv_mul3(double scalar, const hvec3_t *vector, hvec3_t *v_result)
#else
sv_mul3(scalar, vector, v_result)
double scalar;
hvec3_t *vector;
hvec3_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec3_t, v_result, "sv_mul3()");

   v_x(*v_result) = v_x(*vector) * scalar;
   v_y(*v_result) = v_y(*vector) * scalar;
   v_z(*v_result) = v_z(*vector) * scalar;
   v_w(*v_result) = v_w(*vector);

   return  v_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_homo3(const hvec3_t *vector, hvec3_t *v_result)
#else
v_homo3(vector, v_result)
hvec3_t *vector;
hvec3_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec3_t, v_result, "v_homo3()");

   v_x(*v_result) = gm_DIV(v_x(*vector), v_w(*vector), "v_homo3()");
   v_y(*v_result) = v_y(*vector) / v_w(*vector);
   v_z(*v_result) = v_z(*vector) / v_w(*vector);
   v_w(*v_result) = 1.0;

   return v_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
v_norm3(const hvec3_t *vector, hvec3_t *v_result)
#else
v_norm3(vector, v_result)
hvec3_t *vector;
hvec3_t *v_result;
#endif
{
   double  length = sqrt(v_x(*vector) * v_x(*vector) + 
   	                 v_y(*vector) * v_y(*vector) +
           		 v_z(*vector) * v_z(*vector));

   v_result = gm_ALLOC(hvec3_t, v_result, "v_norm3()");

/*   length = sqrt(v_x(*vector) * v_x(*vector) + 
//        	 v_y(*vector) * v_y(*vector) +
//        	 v_z(*vector) * v_z(*vector));			*/

   v_x(*v_result) = gm_DIV(v_x(*vector), length, "v_norm2()");
   v_y(*v_result) = v_y(*vector) / length;
   v_z(*v_result) = v_z(*vector) / length;
   v_w(*v_result) = v_w(*vector) / length;

   return  v_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vv_add3(const hvec3_t *vectorA, const hvec3_t *vectorB, hvec3_t *v_result)
#else
vv_add3(vectorA, vectorB, v_result)
hvec3_t *vectorA;
hvec3_t *vectorB;
hvec3_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec3_t, v_result, "vv_add3()");

   v_x(*v_result) = v_x(*vectorA) + v_x(*vectorB);
   v_y(*v_result) = v_y(*vectorA) + v_y(*vectorB);
   v_z(*v_result) = v_z(*vectorA) + v_z(*vectorB);
   v_w(*v_result) = v_w(*vectorA) + v_w(*vectorB);

   return  v_result;
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vv_cross3(hvec3_t *vectorA, hvec3_t *vectorB, hvec3_t *v_result)
#else
vv_cross3(vectorA, vectorB, v_result)
hvec3_t *vectorA;
hvec3_t *vectorB;
hvec3_t *v_result;
#endif
{
   int which_vec; /* Is v_result used in place, if so which \
		     vectors are equal ? */
         
   hvec3_t buf;

   if(v_result == vectorA)
   {
     v_result = &buf;
     which_vec = 1;
   }
   else
     if(v_result == vectorB)
     {
        v_result = &buf;
        which_vec = 2;
     }
     else
     {
        v_result = gm_ALLOC(hvec3_t, v_result, "vv_cross3()");
        which_vec = 0;
     };

   v_x(*v_result) = v_y(*vectorA) * v_z(*vectorB) -
            v_z(*vectorA) * v_y(*vectorB);
   v_y(*v_result) = v_z(*vectorA) * v_x(*vectorB) -
            v_x(*vectorA) * v_z(*vectorB);
   v_z(*v_result) = v_x(*vectorA) * v_y(*vectorB) -
            v_y(*vectorA) * v_x(*vectorB);
   v_w(*v_result) = v_w(*vectorA) * v_w(*vectorB);

   switch(which_vec)
   {
     case 0 : return v_result;
     case 1 : /* v_cpy3(v_result, vectorA); */
              *vectorA = *v_result;
              return vectorA;
     case 2 : /* v_cpy3(v_result, vectorB); */
              *vectorB = *v_result;
              return vectorB;
   };
	error("This should not happen! %s %d\n", __FILE__, __LINE__ );
	return v_result;	/* garbage... */
}

hvec3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vv_sub3(const hvec3_t *vectorA, const hvec3_t *vectorB, hvec3_t *v_result)
#else
vv_sub3(vectorA, vectorB, v_result)
hvec3_t *vectorA;
hvec3_t *vectorB;
hvec3_t *v_result;
#endif
{
   v_result = gm_ALLOC(hvec3_t, v_result, "vv_sub3()");

   v_x(*v_result) = v_x(*vectorA) - v_x(*vectorB);
   v_y(*v_result) = v_y(*vectorA) - v_y(*vectorB);
   v_z(*v_result) = v_z(*vectorA) - v_z(*vectorB);
   v_w(*v_result) = v_w(*vectorA) - v_w(*vectorB);

   return  v_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
vvt_mul3(const hvec3_t *vectorA, const hvec3_t *vectorB, hmat3_t *m_result)
#else
vvt_mul3(vectorA, vectorB, m_result)
hvec3_t *vectorA;
hvec3_t *vectorB;
hmat3_t *m_result;
#endif
{
   int row, col;

   m_result = gm_ALLOC(hmat3_t, m_result, "vvt_mul3()");

   for(row=0; row<4; row++)
     for(col=0; col<4; col++)
        m_elem(*m_result, row, col) = v_elem(*vectorA, row) * v_elem(*vectorB, col);

   return  m_result;
}


/****** Level 4 : Elementary transformations ******/
hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
miraxis2(b_axis axis, hmat2_t *m_result)
#else
miraxis2(axis, m_result)
b_axis axis;
hmat2_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat2_t, m_result, "miraxis2()");

   for(i=0; i<3; i++)
     for(j=0; j<3; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : 1.0;

   if(axis == X_AXIS)
     m_elem(*m_result, 1, 1) = -1.0;
   else
     m_elem(*m_result, 0, 0) = -1.0;
   
   return  m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mirorig2(hmat2_t *m_result)
#else
mirorig2(m_result)
hmat2_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat2_t, m_result, "mirorig()");

   for(i=0; i<3; i++)
     for(j=0; j<3; j++)
       m_elem(*m_result, i, j) = (i != j) ? 0.0 : -1.0;

   m_elem(*m_result, 2, 2) = 1.0;

  return m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
rot2(double rotation, hmat2_t *m_result)
#else
rot2(rotation, m_result)
double rotation;
hmat2_t *m_result;
#endif
{
   m_result = gm_ALLOC(hmat2_t, m_result, "rot2()");

   m_elem(*m_result, 0, 0) = m_elem(*m_result, 1, 1) = cos(rotation);
   m_elem(*m_result, 1, 0) = sin(rotation);
   m_elem(*m_result, 0, 1) = -m_elem(*m_result, 1, 0);

   m_elem(*m_result, 2, 0) = m_elem(*m_result, 2, 1) = 
   m_elem(*m_result, 0, 2) = m_elem(*m_result, 1, 2) = 0.0;
   m_elem(*m_result, 2, 2) = 1.0;

   return m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
scaorig2(double scale, hmat2_t *m_result)
#else
scaorig2(scale, m_result)
double scale;
hmat2_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat2_t, m_result, "scaorig2()");

   for(i=0; i<3; i++)
     for(j=0; j<3; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : scale;

   m_elem(*m_result, 2, 2) = 1.0;

   return m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
scaxis2(double scale, b_axis axis, hmat2_t *m_result)
#else
scaxis2(scale, axis, m_result)
double scale;
b_axis axis;
hmat2_t *m_result;
#endif
{
#ifdef notdef
   int i, j;

   m_result = gm_ALLOC(hmat2_t, m_result, "miraxis2()");

   for(i=0; i<3; i++)
     for(j=0; j<3; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : scale;
#else
	m_result = m_unity2(m_result);
#endif

   if(axis == X_AXIS)
     m_elem(*m_result, 1, 1) = scale;
   else
     m_elem(*m_result, 0, 0) = scale;
   
   return  m_result;
}

hmat2_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
transl2(const hvec2_t *translation, hmat2_t *m_result)
#else
transl2(translation, m_result)
hvec2_t *translation;
hmat2_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat2_t, m_result, "transl2()");

   for(i=0; i<3; i++)
     for(j=0; j<2; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : 1.0;

   m_elem(*m_result, 0, 2) = v_x(*translation);
   m_elem(*m_result, 1, 2) = v_y(*translation);
   m_elem(*m_result, 2, 2) = 1.0;

   return  m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
miraxis3(b_axis axis, hmat3_t *m_result)
#else
miraxis3(axis, m_result)
b_axis axis;
hmat3_t *m_result;
#endif
{
   int i,j;

   m_result = gm_ALLOC(hmat3_t, m_result, "miraxis3()");

   for(i=0; i<4; i++)
     for(j=0; j<4; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : (i != (int)axis) ? 1.0 : -1.0;

   m_elem(*m_result, 3, 3) = 1.0;

   return  m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mirorig3(hmat3_t *m_result)
#else
mirorig3(m_result)
hmat3_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat3_t, m_result, "mirorig3()");

   for(i=0; i<4; i++)
     for(j=0; j<4; j++)
       m_elem(*m_result, i, j) = (i != j) ? 0.0 : -1.0;

   m_elem(*m_result, 3, 3) = 1.0;

   return m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
mirplane3(b_axis plane, hmat3_t *m_result)
#else
mirplane3(plane, m_result)
b_axis plane;
hmat3_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat3_t, m_result, "mirplane3()");
   for(i=0; i<4; i++)
     for(j=0; j<4; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : 1.0;

   m_elem(*m_result, (int)plane, (int)plane) = -1.0;

   return  m_result;
}
        
/*hmat3_t * Does not appear to be used by Schutte. gsl 10/18/96
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
/*prjorthaxis(b_axis axis, hmat3_t *m_result)
#else
prjorthaxis(axis, m_result)
b_axis axis;
hmat3_t *m_result;
#endif
{
#ifndef notdef*/
	/* An orthographic projection, handled similar to a perspective
	 * projection, is a unity operator!
	 * So the coordinate of the axis over which is projected is the
	 * distance from the projection plane to the input vector
	 */
	/*m_result = m_unity3(m_result);
#else*/	/* notdef */
   /*int i, j;

   m_result = gm_ALLOC(hmat3_t, m_result, "prjorthaxis()");

   for(i=0; i<4; i++)
     for(j=0; j<4; j++)
        m_elem(*m_result, i, j) = (i!=j) ? 0.0 : 1.0;

   m_elem(*m_result, (int)axis, (int)axis) = 0.0;
#endif*/	/* notdef */

   /*return  m_result;
}*/

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
prjpersaxis(b_axis axis, hmat3_t *m_result)
#else
prjpersaxis(axis, m_result)
b_axis axis;
hmat3_t *m_result;
#endif
{
#ifdef notdef
   hvec3_t x, y, z, viewdir;
   int i;
#endif

   m_result = m_unity3(m_result);

	m_elem(*m_result,3,3) = 0.0;

   switch(axis)
   {
     case X_AXIS :
		m_elem(*m_result,3,0) = 1.0;
                   break;
     case Y_AXIS :
		m_elem(*m_result,3,1) = 1.0;
                   break;
     case Z_AXIS : 
		m_elem(*m_result,3,2) = 1.0;
                   break;
   };

   return m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
rot3(double rotation, b_axis axis, hmat3_t *m_result)
#else
rot3(rotation, axis, m_result)
double rotation;
b_axis axis;
hmat3_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat3_t, m_result, "rot3()");

   for(i=0; i<4; i++)
     for(j=0; j<4; j++)
        m_elem(*m_result, i, j) = (i!=j) ? 0.0 : 1.0; 

   i = ((int)axis + 1)%3;
   j = ((int)axis + 2)%3;
   m_elem(*m_result, i, i) = m_elem(*m_result, j, j) = cos(rotation);
   m_elem(*m_result, j, i) = sin(rotation);
   m_elem(*m_result, i, j) = -m_elem(*m_result, j, i);

   return  m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
scaorig3(double scale, hmat3_t *m_result)
#else
scaorig3(scale, m_result)
double scale;
hmat3_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat3_t, m_result, "scaorig2()");

   for(i=0; i<4; i++)
     for(j=0; j<4; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : scale;

   m_elem(*m_result, 3, 3) = 1.0;

   return  m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
scaplane3(double scale, b_axis plane, hmat3_t *m_result)
#else
scaplane3(scale, plane, m_result)
double scale;
b_axis plane;
hmat3_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat3_t, m_result, "scaplane3()");
   for(i=0; i<4; i++)
     for(j=0; j<4; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : 1.0;

   m_elem(*m_result, (int)plane, (int)plane) = scale;

   return  m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
scaxis3(double scale, b_axis axis, hmat3_t *m_result)
#else
scaxis3(scale, axis, m_result)
double scale;
b_axis axis;
hmat3_t *m_result;
#endif
{
#ifdef notdef
   int i,j;

   m_result = gm_ALLOC(hmat3_t, m_result, "scaxis3()");

   for(i=0; i<4; i++)
     for(j=0; j<4; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : (i != (int)axis) ? -1.0 : scale;

   m_elem(*m_result, 3, 3) = 1.0;
#else
	m_result = m_unity3(m_result);

	m_elem(*m_result, axis, axis) = scale;
#endif

   return  m_result;
}

hmat3_t *
#ifdef __cplusplus /* made consistent with definition in graphmat.h gsl 10/16/96 */
transl3(const hvec3_t *translation, hmat3_t *m_result)
#else
transl3(translation, m_result)
hvec3_t *translation;
hmat3_t *m_result;
#endif
{
   int i, j;

   m_result = gm_ALLOC(hmat3_t, m_result, "transl2()");

   for(i=0; i<4; i++)
     for(j=0; j<3; j++)
        m_elem(*m_result, i, j) = (i != j) ? 0.0 : 1.0;

   m_elem(*m_result, 0, 3) = v_x(*translation);
   m_elem(*m_result, 1, 3) = v_y(*translation);
   m_elem(*m_result, 2, 3) = v_z(*translation);
   m_elem(*m_result, 3, 3) = 1.0;

   return  m_result;
}

