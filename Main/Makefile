#CCC	= g++ -B/usr/local/lib/gcc-lib/sparc-sun-solaris2.3/rotd/
##CCC	= g++ -fno-implicit-templates
CCC	= CC
# You can use gcc as a C compiler if cc doesn't work
#CC	= gcc -traditional
#CC	= cc -cckr
##CCFLAGS	= -Wall -Wno-unused -Wno-reorder -g -I. 
CFLAGS	= -g -I.
#Use this for hp.
CCFLAGS = -g -I. -Dhp
#Use this for non hp.
#CCFLAGS	= -g -I.
#This is the location of all test case files.
dataDir = testCase/

# Uncomment the next four lines if your make does not know about .cc
# C++ files (like the SGI make)

.SUFFIXES:	.o .c .cc

.cc.o:
	$(CCC) $(CCFLAGS) -c $<

# add sbscan.o to OBJ if you use libg++ 2.5.1 or libg++ 2.5.2
# libg++ 2.5.3 does not need it. libg++ 2.4.X can be use as it is.
OBJ	= nclip.o primitvs.o posadder.o poly.o test.o polyio.o String.o
# templats.o
LIBOBJ	= err.o graphadd.o graphmat.o grphmtpp.o 

clippoly.exe:	${OBJ} ${LIBOBJ}
	${CCC} $(CCFLAGS) -o clippoly.exe ${OBJ} ${LIBOBJ} -lm

purify:	${OBJ} ${LIBOBJ}
	purify -collector=/usr/local/lib/gcc-lib/sun4/2.4.5/ld \
	${CCC} -o clippoly.exe ${OBJ} ${LIBOBJ} -lm

test:	clippoly.exe
	clippoly.exe < ${dataDir}inFile > ${dataDir}outFile
	diff ${dataDir}outFile.dst ${dataDir}outFile

clean:
	rm -f *.o clippoly.exe core ${dataDir}outFile
