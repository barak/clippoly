#CCC	= g++ -B/usr/local/lib/gcc-lib/sparc-sun-solaris2.3/rotd/
#CCC	= g++ -Wall -ansi -pedantic
CCC	= g++
#CCC	= CC
# You can use gcc as a C compiler if cc doesn't work
CC	= gcc -traditional
#CC	= cc -cckr
CCFLAGS	= -Wall -Wno-unused -Wno-reorder -g -I. 
#CCFLAGS	= -g -I. 
CFLAGS	= -g -I.

# Uncomment the next four lines if your make does not know about .cc
# C++ files (like the SGI make)

.SUFFIXES:	.o .c .cc

.cc.o:
	$(CCC) $(CCFLAGS) -c $<

# add sbscan.o to OBJ if you use libg++ 2.5.1 or libg++ 2.5.2
# libg++ 2.5.3 does not need it. libg++ 2.4.X can be use as it is.
OBJ	= nclip.o primitives.o posadder.o poly.o test.o poly_io.o String.o templates.o
LIBOBJ	= err.o graphadd.o graphmat.o graphmat++.o 

prog:	${OBJ} ${LIBOBJ}
	${CCC} $(CCFLAGS) -o prog ${OBJ} ${LIBOBJ} -lm

purify:	${OBJ} ${LIBOBJ}
	purify -collector=/usr/local/lib/gcc-lib/sun4/2.4.5/ld \
	${CCC} -o prog ${OBJ} ${LIBOBJ} -lm

test:	prog
	prog < in_file > out_file
	diff out_file.dist out_file

clean:
	rm -f *.o prog core out_file

