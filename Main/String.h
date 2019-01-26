// $Log: String.h,v $
// Revision 1.1.1.1  2000/09/12 09:34:32  binder
//
//
// polygon clipper from gregg leichtman
//

#ifndef _String_h
#define _String_h "$Header: /iue/cvsroot/vproject/wafer/mkwafer/clippoly/poly/String.h,v 1.1.1.1 2000/09/12 09:34:32 binder Exp $"

#ifdef __GNUG__
#pragma interface
#endif

//class istream; removed. gsl 5/1/97
//
//	Class name : String
//
//	Description :
//
class String {
	friend	istream &operator>>(istream &, String &);
	
  public:
	String();
	String(const String &);
	~String();
	const String	&operator=(const String &);
	int		operator!=(const char *) const;
			operator const char *() const
			{ return ptr; }
			
  protected:
  private:
    	char	*ptr;
};

#endif
