#CCC	= g++ -B/usr/local/lib/gcc-lib/sparc-sun-solaris2.3/rotd/
CCC	= g++ -fno-implicit-templates
#CCC	= CC
# You can use gcc as a C compiler if cc doesn't work
CC	= gcc 
#CC	= cc -cckr
CCFLAGS	= -Wall -g -I. -DGEN_TEMPLATES
#CCFLAGS	= -g -I. 
CFLAGS	= -g -I.

# Uncomment the next four lines if your make does not know about .cc
# C++ files (like the SGI make)

.SUFFIXES:	.o .c .cc

.cc.o:
	$(CCC) $(CCFLAGS) -c $<

OBJ	= nclip.o primitives.o posadder.o poly.o test.o poly_io.o templates.o
LIBOBJ	= err.o graphadd.o graphmat.o graphmat++.o 

prog:	${OBJ} ${LIBOBJ}
	${CCC} $(CCFLAGS) -o prog ${OBJ} ${LIBOBJ} -lm

purify:	${OBJ} ${LIBOBJ}
	purify -collector=/usr/local/lib/gcc-lib/sun4/2.4.5/ld \
	${CCC} -o prog ${OBJ} ${LIBOBJ} -lm

test:	prog
	prog < in_file > out_file
	diff -b out_file.dist out_file

clean:
	rm -f *.o prog core out_file

