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

#include	<stdio.h>
#include	<varargs.h>
#include	<setjmp.h>

int	err_nr_errors, err_nr_warnings;
/* what is the type of a pointer to a jmp_buf? On sun4 int * will do */
int	*err_warning_jmpbuf, *err_error_jmpbuf, *err_fatal_jmpbuf;

/*VARARGS1*/
warning( fmt, va_alist )
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

/*VARARGS1*/
error( fmt, va_alist )
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

/*VARARGS2*/
fatal_exit_nr( nr, fmt, va_alist )
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

/*VARARGS1*/
fatal( fmt, va_alist )
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
