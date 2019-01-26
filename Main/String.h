// $Log$

#ifndef _String_h
#define _String_h "$Header$"

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
