head	1.1;
access;
symbols;
locks
	klamer:1.1; strict;
comment	@// @;


1.1
date	95.04.27.07.19.20;	author klamer;	state Exp;
branches;
next	;


desc
@@


1.1
log
@Initial revision
@
text
@static const char rcs_id[] = "$Header$";

// $Log$

#include	"set.h"
#include	"poly.h"

template class SetIter<Poly *>;
template class Set<Poly *>;
template class  RSet<NodePEdge>;
@
