static const char rcs_id[] = "$Header: /home/klamer/clippoly/clippoly/RCS/templates.cc,v 1.1 1995/04/27 07:19:20 klamer Exp klamer $";

// $Log: templates.cc,v $
// Revision 1.1  1995/04/27  07:19:20  klamer
// Initial revision
//

#include	"set.h"
#include	"poly.h"

template class SetIter<Poly *>;
template class Set<Poly *>;
template class  RSet<NodePEdge>;
