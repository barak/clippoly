// $Log$
// Revision 1.2  2005/02/28 17:00:30  klamer
// PL 7
//

#ifndef _String_h
#define _String_h "$Header$"

#ifdef __GNUG__
#pragma interface
#endif

class istream;
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
