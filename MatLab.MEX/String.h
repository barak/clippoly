// $Log$

#ifndef _String_h
#define _String_h "$Header$"

#ifdef __GNUG__
#pragma interface
#endif

//class istream; not used for MatLab MEX function. gsl 10/29/96
//
//	Class name : String
//
//	Description :
//
class String {
	//friend	istream &operator>>(istream &, String &); not used for MatLab MEX function. gsl 10/29/96
	
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
