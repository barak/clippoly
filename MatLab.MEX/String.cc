static const char rcs_id[] = "$Header$";

// $Log$

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

/* istream & not used for MatLab MEX function. gsl 10/29/96
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
*/

