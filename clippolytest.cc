//    nclip: a polygon clip library

//    Copyright (C) 1993  University of Twente

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

#include        <cstring>
#include	<iostream>

#include	"poly.h"
#include	"poly_io.h"
#include	"nclip.h"

using
  namespace::std;

void
clear (PolyPList & l)
{
  PolyPListIter
  i (l);
  while (i ())
    delete
      i.
    val ();
}

int
main (int, char *[])
{
  Poly *
    a = read_poly (cin), *b = read_poly (cin);
  PolyPList
    a_min_b,
    b_min_a,
    a_and_b;

  // printf("Area a %g b %g\n", a->area(), b->area());

  clip_poly (*a, *b, a_min_b, b_min_a, a_and_b);

  cout << "a_min_b:\n" << a_min_b;
  cout << "b_min_a:\n" << b_min_a;
  cout << "a_and_b:\n" << a_and_b;

  delete
    a;
  delete
    b;

  clear (a_min_b);
  clear (b_min_a);
  clear (a_and_b);

  return 0;
}
