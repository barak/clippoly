static const char rcs_id[] = "$Header: /iue/cvsroot/vproject/wafer/mkwafer/clippoly/poly/String.cc,v 1.1.1.1 2000/09/12 09:34:32 binder Exp $";

// $Log: String.cc,v $
// Revision 1.1.1.1  2000/09/12 09:34:32  binder
//
//
// polygon clipper from gregg leichtman
//

#ifdef __GNUG__
#pragma implementation
#endif

#include	<string.h>
#include	<iostream.h>

#include "String.h"

static const char h_rcs_id[] = _String_h;

String::~String()
{
  delete [] ptr;
}

String::String(void)
    : ptr(new char[1])
{
  ptr[0] = 0;
}

int
  String::operator!=(const char *cmp) const
{
  return strcmp(ptr,cmp);
}

istream &
  operator>>(istream &in, String &s)
{
  char	buffer[256];
  buffer[0] = 0;
  in.get(buffer,256);
  delete [] s.ptr;
  s.ptr = new char [strlen(buffer) + 1];
  strcpy(s.ptr,buffer);
  return in;
}


