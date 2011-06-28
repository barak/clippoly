CPPFLAGS += -DGEN_TEMPLATES
CPPFLAGS += -I.
CFLAGS += -Wall
CXXFLAGS += -Wall

OBJ	= nclip.o primitives.o posadder.o poly.o poly_io.o templates.o
LIBOBJ	= err.o graphadd.o graphmat.o graphmat++.o 

clippolytest:  clippolytest.o ${OBJ} ${LIBOBJ}
	${CXX} ${LDFLAGS} -o $@ $^ ${LOADLIBES} ${LDLIBS}

test:	clippolytest
	./clippolytest < in_file | diff --ignore-space-change out_file.dist -
	./clippolytest < t1 | diff --ignore-space-change t1.out -
	./clippolytest < t2 | diff --ignore-space-change t2.out -

clean:
	rm -f *.o clippolytest core

.PHONY: test clean
