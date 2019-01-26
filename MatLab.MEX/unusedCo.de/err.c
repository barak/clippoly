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
 *	error.c				Klamer Schutte 25/7/90
 *
 *	handle errors in a consistent way.
 */

#ifndef err_c  /* gsl 10/15/96 */
#define err_c 1
#endif

#include	<stdio.h>
#ifdef mac_h
#include    <stdarg.h>
#include    "err.h"
#else
#include	<varargs.h>
#endif
#include	<setjmp.h>

/* WARNING: setjmp is never called anywhere in clippoly code as far as I can tell.
            => longjmp's are non-functional and will probably crash code, if they are
            executed. gsl 10/17/96
 */

int	err_nr_errors=0, err_nr_warnings=0; /*added init. to 0. gsl 10/15/96*/
/* what is the type of a pointer to a jmp_buf? On sun4 int * will do */
#ifdef mac_h
long **err_warning_jmpbuf, **err_error_jmpbuf, **err_fatal_jmpbuf;
#else
int	*err_warning_jmpbuf, *err_error_jmpbuf, *err_fatal_jmpbuf;
#endif

/*VARARGS1*/
#ifdef mac_h
void warning( const char *fmt, ... ) /* added void return. gsl 10/17/96 */
 {
	va_list	args;

	va_start( args, fmt );
	vfprintf(stderr, fmt, args );
	va_end(args );

	err_nr_warnings++;

	if (err_warning_jmpbuf != NULL)
		longjmp( err_warning_jmpbuf, 1 );
}	
#else
void warning( fmt, va_alist )
char	*fmt;
va_dcl
{
	va_list	args;

	va_start( args );
	vfprintf(stderr, fmt, args );
	va_end(args );

	err_nr_warnings++;

	if (err_warning_jmpbuf != NULL)
		longjmp( err_warning_jmpbuf, 1 );
}
#endif	

/*VARARGS1*/
#ifdef mac_h
void error( const char *fmt, ... ) /* added void return. gsl 10/17/96 */
{
	va_list	args;

	va_start( args, fmt );
	vfprintf(stderr, fmt, args );
	va_end(args );

	err_nr_errors++;

	if (err_error_jmpbuf != NULL)
		longjmp( err_error_jmpbuf, 1 );
}	
#else
void error( fmt, va_alist )
char	*fmt;
va_dcl
{
	va_list	args;

	va_start( args );
	vfprintf(stderr, fmt, args );
	va_end(args );

	err_nr_errors++;

	if (err_error_jmpbuf != NULL)
		longjmp( err_error_jmpbuf, 1 );
}	
#endif

/*VARARGS2*/
#ifdef mac_h
void fatal_exit_nr( int nr, const char *fmt, ... ) /* added void return. gsl 10/17/96 */
{
	va_list	args;

	va_start( args, fmt );
	vfprintf(stderr, fmt, args );
	va_end(args );

	if (err_fatal_jmpbuf != NULL)
		longjmp( err_fatal_jmpbuf, 1 );

	exit( nr );
}	
#else
void fatal_exit_nr( nr, fmt, va_alist )
int	nr;
char	*fmt;
va_dcl
{
	va_list	args;

	va_start( args );
	vfprintf(stderr, fmt, args );
	va_end(args );

	if (err_fatal_jmpbuf != NULL)
		longjmp( err_fatal_jmpbuf, 1 );

	exit( nr );
}	
#endif

/*VARARGS1*/
#ifdef mac_h
void fatal( const char *fmt, ... ) /* added void return. gsl 10/17/96 */
{
	va_list	args;

	va_start( args, fmt );
	vfprintf(stderr, fmt, args );
	va_end(args );

	if (err_fatal_jmpbuf != NULL)
		longjmp( err_fatal_jmpbuf, 1 );

	exit( 1 );
}	
#else
void fatal( fmt, va_alist )
char	*fmt;
va_dcl
{
	va_list	args;

	va_start( args );
	vfprintf(stderr, fmt, args );
	va_end(args );

	if (err_fatal_jmpbuf != NULL)
		longjmp( err_fatal_jmpbuf, 1 );

	exit( 1 );
}	
#endif

#undef err_c
