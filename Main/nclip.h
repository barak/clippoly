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

#ifndef	NCLIP_H
#define	NCLIP_H	"$Header: /iue/cvsroot/vproject/wafer/mkwafer/clippoly/poly/nclip.h,v 1.1.1.1 2000/09/12 09:34:32 binder Exp $"

// $Log: nclip.h,v $
// Revision 1.1.1.1  2000/09/12 09:34:32  binder
//
//
// polygon clipper from gregg leichtman
//
// Revision 1.1  1993/10/27  14:43:51  klamer
// Initial revision
//
// Revision 1.1  1993/10/27  14:43:51  klamer
// Initial revision
//
// Revision 1.1  1992/12/07  10:46:35  klamer
// Initial revision
//

#ifdef _GNUG__
#pragma interface
#endif

class	Poly;
// class	PolyPList;
class	Edge;
class	DirPolyIter;
// class	PolyNodePList;
class	PolyPoint;
// class	NodePEdgeList;

void	clip_poly( const Poly &a, const Poly &b, 
			PolyPList &a_min_b, PolyPList &b_min_a, PolyPList &a_and_b );
int		intersect( const Edge &a, const Edge &b, PolyPoint &p1, PolyPoint &p2 );
int		intersect( Poly &a, Poly &b );
void	label_shared( Poly & a, const Poly & b );
void    label_shared2( PolyIter &pi, const PolyPoint &p1, const PolyPoint &p2, const PolyNode &pn ); //added prototype. gsl 10/16/96
void	make_poly( const PolyPoint &point, DirPolyIter &follow, 
			PolyPList &polylist, NodePEdgeList &done );
int 	make_poly( const PolyPoint &start_point, const PolyPoint &point, 
			DirPolyIter &follow, NodePEdgeList &done, 
			Poly * new_poly );
void    iter_mesh( const Poly &a, const Poly &b, NodePEdgeList &done,PolyPList &polylist ); //added prototype. gsl 10/16/96
void	assign_polys( const Poly &a, const Poly &b, const PolyPList &in_list, 
			PolyPList &a_min_b, PolyPList &b_min_a, PolyPList &a_and_b );
void	poly_min_poly( const Poly &a, const Poly &b, PolyPList &a_min_b );
void	add_until( Poly *, const PolyPoint &, DirPolyIter & );

#endif	/* NCLIP_H */
