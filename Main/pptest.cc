char PPTEST_CC_ID [] = "$Id: pptest.cc,v 1.1.1.1 2000/09/12 09:34:32 binder Exp $";


#include <iostream>

#include "poly.h"
#include "polyio.h"
#include "nclip.h"

static void clear(PolyPList &l);
static void case_core();
static void case_error();


int main()
{
	case_error();
}

	
static void case_error()
{
	Poly*	p1 = new Poly(PolyPoint(0.8, 0.2));
	p1->add(PolyPoint(-1., 0.8));
	p1->add(PolyPoint(1., 0.8));
	p1->add(PolyPoint(1., -0.7));
	p1->add(PolyPoint(-1., -0.7));
	p1->add(PolyPoint(0., 0.));
	p1->add(PolyPoint(0.8, 0.));
	
	Poly*	p2 = new Poly(PolyPoint(-0.2, -0.14));
	p2->add(PolyPoint(-0.2, -0.7));
	p2->add(PolyPoint(-0.5, -0.7));
	p2->add(PolyPoint(-0.5, -0.35));
	
	PolyPList	a_min_b, b_min_a, a_and_b;
	
	clip_poly(*p1, *p2, a_min_b, b_min_a, a_and_b);

	cout << "a_and_b: " << endl << a_and_b << endl;
	cout << "a_min_b: " << endl << a_min_b << endl;
	cout << "b_min_a: " << endl << b_min_a << endl;
	
	clear(a_min_b);
	clear(b_min_a);
	clear(a_and_b);

	delete p1;
	delete p2;
}




static void case_core()
{
	Poly*	p1 = new Poly(PolyPoint(0, 2));
	p1->add(PolyPoint(1, 2));
	p1->add(PolyPoint(1, 1));
	p1->add(PolyPoint(0, 1));

	Poly*	p2 = new Poly(PolyPoint(1, 1));
	p2->add(PolyPoint(2, 1));
	p2->add(PolyPoint(2, 2));
	p2->add(PolyPoint(1, 2));
	p2->add(PolyPoint(1, 1));
	p2->add(PolyPoint(0, 1));
	p2->add(PolyPoint(0, 3));
	p2->add(PolyPoint(3, 3));
	p2->add(PolyPoint(3, 0));
	p2->add(PolyPoint(1, 0));

	
	PolyPList	a_min_b, b_min_a, a_and_b;
	
	clip_poly(*p1, *p2, a_min_b, b_min_a, a_and_b);
	
	clear(a_min_b);
	clear(b_min_a);
	clear(a_and_b);
	
	delete p1;
	delete p2;
}


static void clear(PolyPList &l)
{
	PolyPListIter	i(l);
	while(i())
		delete i.val();
}

