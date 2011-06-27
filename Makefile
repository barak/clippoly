CPPFLAGS += -DGEN_TEMPLATES
CPPFLAGS += -I.
CFLAGS += -Wall
CXXFLAGS += -Wall

OBJ	= nclip.o primitives.o posadder.o poly.o test.o poly_io.o templates.o
LIBOBJ	= err.o graphadd.o graphmat.o graphmat++.o 

prog:	${OBJ} ${LIBOBJ}
	${CXX} -o prog ${OBJ} ${LIBOBJ} -lm

test:	prog
	./prog < in_file | diff --ignore-space-change out_file.dist -
	./prog < t1 | diff --ignore-space-change t1.out -
	./prog < t2 | diff --ignore-space-change t2.out -

clean:
	rm -f *.o prog core

.PHONY: test clean
