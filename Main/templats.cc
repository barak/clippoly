static const char rcs_id[] = "$Header: /iue/cvsroot/vproject/wafer/mkwafer/clippoly/poly/templats.cc,v 1.1.1.1 2000/09/12 09:34:32 binder Exp $";

// $Log: templats.cc,v $
// Revision 1.1.1.1  2000/09/12 09:34:32  binder
//
//
// polygon clipper from gregg leichtman
//
// Revision 1.1  1995/04/27  07:19:20  klamer
// Initial revision
//

#include	"set.h"
#include	"poly.h"

template class SetIter<Poly *>;
template class Set<Poly *>;
template class  RSet<NodePEdge>;
