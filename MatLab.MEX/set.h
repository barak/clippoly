#ifndef	SET_H
#define	SET_H	"$Header: /home/schutte/src_tree/util/c++/RCS/set.h,v 1.3 1994/11/09 08:08:23 schutte Exp schutte $"

// $Log: set.h,v $
// Revision 1.3  1994/11/09  08:08:23  schutte
// constness fixes.
// Code cleanup.
//
// Revision 1.2  1994/01/04  12:55:37  klamer
// Made default size 64 instead of 16.
// Renamed len to _len.
//
// Revision 1.1  1993/10/27  14:43:58  klamer
// Initial revision
//
// Revision 1.3  1993/10/27  14:28:05  klamer
// Version as used in itool.
//
// Revision 1.2  1993/01/18  14:56:18  klamer
// Spie version.
//
// Revision 1.1  1992/12/07  10:46:35  klamer
// Initial revision
//

#ifdef __GNUG__
#ifndef GEN_TEMPLATES
#pragma interface
#endif
#endif
//#ifndef assert
//#include	<assert.h> removed. added assert in precompiled header. gsl 10/29/96
//#endif

#ifdef sgi
#ifdef __GNUG__
#define	INLINE	inline
#else
#define	INLINE	// Nothing
// The CC with Irix 5.2 is too stupid for these inline's
#endif
#else
#ifdef hp
#define	INLINE	// Nothing. The CC with HP's 9.0.7 OS does not handle these inline's. gsl 10/10/96
#else
#define	INLINE	inline
#endif
#endif

template <class T> class SetIter;
template <class T> class RSetIter;

template <class T>
class Set
{
	friend class	SetIter<T>;
	
	T			*data;      // the array.
	int			_len, used; // max length of the array; number of elements currently used.
	T			operator[](int cnt) const
				{ return data[cnt]; }
	void		operator=(const Set<T> &);	// Don't use it!
	void		_resize();
	
public:
	Set( int size = 64 ) // Default number of array elements.
	                     // In Schutte's primary use, this argument
	                     // determines how many polygons can be stored
	                     // in a list of polygons. Each list is
	                     // doubly-linked to each array element. gsl 10/29/96
		: data( new T [size] ), _len(size), used(0)
		{ }
	~Set()
		{	delete [] data; }
	
	int 		contains( T elem ) const 
				{	return seek( elem ) >= 0; }
	int			seek( T elem ) const
				{	SetIter<T>	iter(*this);
					while(iter())
						if (iter.val() == elem)
							return iter.cnt();
					return -1;	}
	void		add( T elem )
				{	if (!contains(elem))
					{	if (used + 1 >= _len)
							_resize();
						data[used] = elem;
						used++; 	} }
	void		del( T elem )
			{	int	i = seek(elem);
				if (i >= 0)
				{	data[i] = data[used-1];
					used--;	} }
	int			empty() const
				{	return used == 0; }
	T			first()
				{	assert(used > 0);
					return data[0]; }
	int			length() const
				{	return used; }
};

template <class T> void
Set<T>::_resize()
{
	T	*new_data = new T [_len * 2];
	for(int i = 0; i < _len; i++)
		new_data[i] = data[i];
	delete [] data;
	data = new_data;
	_len *= 2;
}

template <class T>
class SetIter
{
	int			_cnt;
	const Set<T>	&_set;
	const Set<T>	&set()
					{ return _set; }
				
public:
	SetIter( const Set<T> &set )
		: _cnt(-1), _set(set)
		{ }
	
	INLINE int			operator() ();
#ifdef notdef
				{	if (cnt() >= (_set.used-1))
						return 0;
					_cnt++;
					return 1;	}
#endif
	inline T			val() const;
#ifdef notdef
				{ return _set[_cnt]; }
#endif
	int			cnt() const
				{ return _cnt; }
};
	
template <class T> INLINE int
SetIter<T>::operator() ()
{
	if (cnt() >= (_set.used-1))
		return 0;
	_cnt++;
	return 1;
}

template <class T> inline T
  SetIter<T>::val() const
{
  return _set[_cnt];
}


template <class T>
class RSet
{
	friend class	RSetIter<T>;
	
	T			*data;
	int			_len, used;
	T			&operator[](int cnt)
				{ return data[cnt]; }
	void		operator=(const RSet<T> &);	// Don't use it!
	void		_resize();
	
public:
	RSet( int size = 64 )
		: data( new T [size] ), _len(size), used(0)
		{ }
	~RSet()
		{	delete [] data; }
	
	int 		contains( const T &elem ) const 
				{	return seek( elem ) >= 0; }
	int			seek( const T &elem ) const
				{	for(int i = 0; i < used; i++)
						if (data[i] == elem)
							return i;
					return -1;	}
	void		add( const T &elem )
				{	if (!contains(elem))
					{	if (used +1 >= _len)
							_resize();
						data[used] = elem;
						used++; 	} }
	int			length() const
				{	return used; }
	void		clear()
			{	used = 0; }
};

template <class T> void
RSet<T>::_resize()
{
	T	*new_data = new T [_len * 2];
	for(int i = 0; i < _len; i++)
		new_data[i] = data[i];
	delete [] data;
	data = new_data;
	_len *= 2;
}

template <class T>
class RSetIter
{
	int			_cnt;
	const RSet<T>	&_set;
	const RSet<T>	&set()
					{ return _set; }
				
public:
	RSetIter( const RSet<T> &set )
		: _cnt(-1), _set(set)
		{ }
	
	INLINE int			operator() ();
#ifdef notdef
				{	if (_cnt >= (_set.used-1))
						return 0;
					_cnt++;
					return 1;	}
#endif
	const T			&val() const
				{ return _set.data[_cnt]; }
	int			cnt() const
				{ return _cnt; }
};

template <class T> INLINE int
  RSetIter<T>::operator() ()
{       
  if (_cnt >= (_set.used-1))
    return 0;
  _cnt++;
  return 1;     
}


#endif	/* SET_H */
