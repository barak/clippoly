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
 *	$Log: err.h,v $
 * Revision 1.5  1992/06/01  15:37:48  klamer
 * Made prototypes gcc compatible.
 *
 * Revision 1.4  1991/11/15  14:55:03  klamer
 * Merged with /usr/local/include/err.h
 *
 * Revision 1.3  1991/11/15  14:52:04  klamer
 * Made K&R C compatible as well.
 *
 * Revision 1.2  1991/10/11  09:55:58  klamer
 * added prototype for warning.
 *
 * Revision 1.1  1991/09/16  12:59:45  klamer
 * Initial revision
 *
 */
#ifdef mac_h
#include <stdlib.h>
#endif
#ifndef	_ERROR
#define	_ERROR	"$Id: err.h,v 1.5 1992/06/01 15:37:48 klamer Exp $"

#ifdef __cplusplus
#define	EC	extern "C"
#define	P(x)	x
#define	CDOTS	, ... // added "," since Mac MW CodeWarrior requires it. gsl 10/15/96
#else
#define	EC	/* nothing */
#ifdef __STDC__
#define	P(x)	x
#define	CDOTS	, ...
#else
#define	P(x)	(/* x */)
#endif
#endif

extern int	err_nr_errors, err_nr_warnings;
/* what is the type of a pointer to a jmp_buf? On sun4 int * will do */
#ifndef err_c //not external in err.c file. gsl 10/15/96
#ifdef mac_h
extern long	**err_warning_jmpbuf, **err_error_jmpbuf, **err_fatal_jmpbuf;
#else
extern int	*err_warning_jmpbuf, *err_error_jmpbuf, *err_fatal_jmpbuf;
#endif
#endif

#ifdef mac_h
EC void	warning P((const char *fmt CDOTS ));
EC void	error P((const char *fmt CDOTS ));
EC void fatal_exit_nr P((int nr, const char *fmt CDOTS )); //added prototype. gsl 10/17/96
EC void	fatal P((const char *fmt CDOTS ));
#else
EC void	warning P((char *fmt CDOTS ));
EC void	error P((char *fmt CDOTS ));
EC void fatal_exit_nr P((int nr, char *fmt CDOTS )); /* added prototype. gsl 10/17/96 */
EC void	fatal P((char *fmt CDOTS ));
#endif

#undef EC
#undef P
#undef CDOTS

#endif	/* _ERROR */

