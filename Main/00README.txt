FROM GREGG LEICHTMAN (See file Manifest.txt for release date and version.)

gsl@gandalf.tjh.tju.edu
Thomas Jefferson University
Neurosensory Institute
Medical College, Suite 511E
1025 Walnut St.
Philadelphia, PA 19107, USA
 
Clippoly Purpose

This code takes two, possibly concave, non-self-intersecting planar
input polygons A and B and outputs the clipped regions A - B, B - A, and
A & B. In certain pathological cases, self-intersecting polygons may be
output. Clippoly also outputs the areas of each of these region's
polygons with a sign that indicates clockwise (negative sign) or
counter-clockwise (positive sign) traversal of the vertices.

Port

Using MetroWerks (MW) CodeWarrior (CW) 9.0 (projects for CW 9 through
Pro R1 (i.e. CW 12) are included in the distribution, see heading
"Compilation" below), I have ported Klamer Schutte's polygon clipping
code from its UNIX origin to a Macintosh PowerPC 8100/80AV (601 CPU) and
a Power Computing PowerCenter 210 (604e CPU). It should be possible to
compile the code on any Macintosh with little or no change, but these
are the only Mac systems I have compiled and run it on. The code is now
split into two different versions. The first version compiles into a
standalone application called clippoly.exe on either a UNIX or Mac
system. On the Macintosh it uses the MW SIOUX library to put up a window
for input and output. You will find data test cases in the folder
Main/testCase. The files with an "out" extension are the output files,
those without are the input files. Copy the entire input file's contents
and paste it into the SIOUX window and then press return. You should see
the output for the entered test case appear below what you pasted.

This version of the code (clippoly.exe executable included and compiled
for Power PC using the latest CW version I have) will also compile and
link on a UNIX system. I have successfully run it on an HP Series 9000
Model 715, HP UNIX 9.0.7 using HP's C++ version A.03.72 and on an SGI
Indigo2 R10000, IRIX 6.2 using SGI C++ included in the ProDev Workshop
package. See (FROM KLAMER SCHUTTE) below for other platforms and
compilers.

The second version is a MatLab MEX function named clippoly.mex (included
and compiled for Power PC using latest CW version I have). The included
code will compile on a Macintosh PPC and on an IBM PC system using
Watcom C (the compiled clippoly.dll is included) under MatLab 5.xx when
a compiler switch is set (see Compilation below). A syntax problem
currently prevents the code from compiling and linking successfully for
the MatLab 4.x version (if you succeed in getting it to compile and link
for the MatLab 4.x version, let me know and I'll include the changes in
the distribution). I have not tested it on a UNIX system as a MEX
function, since I do not have access to a UNIX copy of MatLab. It is
likely that some minor changes will have to be made to turn this code
into a UNIX MatLab MEX function.

The code worked correctly for the included test cases using MatLab
version 4.2c.1 and 5.0.0.4064 (use ver command in MatLab command
window). The test cases are primarily a rogues gallery of difficult
cases. They can be found in the folder MatLab.MEX/testCase. They are
stored as "mat" files. You can load these files into the MatLab
workspace using MatLab's "Load Workspace..." command in the File menu,
or you can place the folder inside the testCase folder in the root
MatLab folder and then use the command "load FILENAME" in the command
window, where FILENAME is one of the test "mat" files. You can also
double click on the "mat" file to load it. I find the latter method the
most efficient for my use. Each of these files contains both the input
data and the output data, so you can load them, store the output
matrices under different names and compare them to the output you are
getting. However, you should be able to tell visually if all is well.

John Kolen has also made an extensive file of polygons available for
testing clippoly. The gzipped file is available through anonymous ftp
at:

ftp://www.coginst.uwf.edu/pub/jkolen/polygon.log.gz

Once you install the MEX function into the MatLab folder, you can call
it at the MatLab command prompt as shown:

[AminusB,AminusBIdx,AminusBn,AminusBarea, ...
 BminusA,BminusAIdx,BminusAn,BminusAarea, ...
 AandB,AandBIdx,AandBn,AandBarea]=clippoly(polyA,polyB)
 
The two input polygon matrices are:
polyA, polyB - a 2 x N sequential list of polygon vertices; N is the 
               total count of all vertices for all polygons passed in
                
The output matrices are:
AminusB     - a 2 x N sequential list of polygon vertices; N is the 
              total count of all vertices for all polygons passed out 
              for the set A - B
AminusBIdx  - 1 x AminusBn vector where each element contains the 
              number of vertices for each polygon in the set A - B; 
              the sum of all these elements equals N
AminusBn    - scalar containing the number of polygons for the set 
              A - B
AminusBarea - 1 x AminusBn vector where each element contains the area
              for each polygon in the set A - B; the sign indicates 
              clockwise (negative) or counter-clockwise (positive)

BminusA     - a 2 x N sequential list of polygon vertices; N is the 
              total count of all vertices for all polygons passed out 
              for the set B - A
BminusAIdx  - 1 x BminusAn vector where each element contains the 
              number of vertices for each polygon in the set B - A; 
              the sum of all these elements equals N
BminusAn    - scalar containing the number of polygons for the set 
              B - A
BminusAarea - 1 x BminusAn vector where each element contains the area
              for each polygon in the set B - A; the sign indicates 
              clockwise (negative) or counter-clockwise (positive)
              
AandB       - a 2 x N sequential list of polygon vertices; N is the 
              total count of all vertices for all polygons passed out 
              for the set A & B
AandBIdx    - 1 x AandBn vector where each element contains the number 
              of vertices for each polygon in the set A & B; the sum of 
              all these elements equals N
AandBn      - scalar containing the number of polygons for the set A & B
AandBarea   - 1 x AandBn vector where each element contains the area
              for each polygon in the set A & B; the sign indicates 
              clockwise (negative) or counter-clockwise (positive)

I have included some MatLab functions that will allow you to test the
clippoly MEX function in MatLab. They are located in the folder
MatLab.MEX/MatLabCo.de. The plotClip function will clip ONE polygon
against another and display the output. You can call it by typing 

[AminusB,AminusBIdx,AminusBn,AminusBarea, ...
 BminusA,BminusAIdx,BminusAn,BminusAarea, ...
 AandB,AandBIdx,AandBn,AandBarea]=plotClip(polyA,polyB)
 
at the command prompt.

The plotMClp function will clip one SET of polygons against another SET
and display the output per pair of clipped polygons. It currently does
not provide any output beyond plots. You can call it by typing

plotMClp(polyA,polyAidx,polyAn,polyB,polyBidx,polyBn)

at the command prompt. If you load test cases into the workspace they
can be used as input for these functions. I have also included a MatLab
function called polyArea that can be used to quickly calculate the area
of a non-intersecting, possibly concave, planar polygon. MatLab 5.0 will
probably obviate the need for this function, since it will include its
own polygon area calculation function.

NOTE:
plotMClp, with additional input matrices, will plot all polygon pairs or
sets that plotClip will plot. However, the twostars.mat test case will
not work with the MatLab function plotClip, since it contains two
overlapping polygons for A and two overlapping polygons for B. It is
meant to be used with function plotMClp only.  All "mat" files can be
used with plotMClp.

If you run either plotClip or plotMClp before loading a test case by
just typing plotClip or plotMClp at the command prompt, then a default
test case built into the functions is used as input. The default test
case is the 6-pointed Star of David formed from two overlapping
triangles.

This code will NOT run on a 68k based Macintosh at this time, because
MathWorks does not currently provide a 68k compatable CW library for
their external interface. They may provide this library in MatLab
version 5.0. (Update: I have confirmed through the pre-release of MatLab
5.0, that the necessary CW 68K library and include files are in the
MathWorks distribution. There also is a mex command that can be run from
the MatLab command line that allows you to compile MEX functions using
CW. When I have some time, I plan on porting the code to include 68k systems.)

Compilation

  Macintosh
  
A separate CW project has been included along with the executable for
both the standalone executable and MEX function versions of clippoly in
order to make compilation and execution on the Macintosh easier. A
project file for CW version 9 through Pro R1 (CW 12) is included and is
denoted within the file name by _CW# where # is the left zero filled
version number. To compile any version, debinhex and uncompress the
stuffit archive clippoly.hqx and then the archives mac.hqx and mex.hqx
inside Main and MatLab.MEX respectively. Old CW version projects are
located in folder: MatLab.MEX/OldProj. Note that, unlike older projects,
the CW 11 and later projects do not use an export file (file with
extension .exp).

You will most likely have to change the following to achieve a
successful compilation and link:

Access Paths to match your directory structure so that the various 
MatLab and Metrowerks libraries can be found: under Project/Access Paths;

Instruction Scheduling to match your cpu: under Code Generation/PPC
                                          Processor/Optimizations.
                                          (Optional, but should increase
                                          computational speed.)

Location of MEX file: Place the clippoly.mex file in the root MatLab 
                      folder or in a folder that is known to be in the 
                      MatLab path. If you place it in the MatLab toolbox 
                      folder, you will need to run        
matlabpath(matlabpath) 
                      to update the cache so that MatLab can see the 
                      new MEX function.

For the MEX file, you can safely ignore:
Link Warning : ignored 'qd' (data) in MWCRuntime.Lib
Previously defined in MATLAB.xcoff

in older projects and

Link Warning : ignored Œqd¹ (data) in MSL RuntimePPC.Lib
Previously defined in MATLAB

Link Warning : A Œcfrg¹(0) resource was found.  It will override some project settings.

in newer projects.

For the standalone application, an executable called clippoly.exe will
be created upon successful compilation and linking.

Each project is distributed with all optimizations turned on except
inlining in CW 9. You will have to turn on inlining yourself if you want it, since I no longer have CW 9 on my system. Inlining previously caused clippoly to crash; however, I appear to have resolved the problem (another MEX function independent of clippoly was interacting badly), so I have turned it back on.

Instruction scheduling is currently set for the 604 CPU in all
projects from CW 11 on and should be changed to match your CPU.

If you need to debug the code, you will need to change the following:

Select the appropriate project file (either _CW009, _CW010, etc.). Old
project files are located in folder: MatLab.MEX/OldProj. Note
that you will have to replace file graphmat.c with graphmat.cc and file
test.cc with clippoly.cc, in the CW9 project, since these file names
have changed, I no longer have CW9 on my system, and therefore I cannot
change it myself. If you use an old project, move the file up to the respective Main or MatLab.MEX directory before attempting compilation.

To compile a MatLab MEX file you must select the version of MatLab (either 4.x or 5.x) that you wish to compile for by setting the switch in the precompiled header file: prcomppp.pch

Set inlining: under Language Settings/C/C++ Language - off.
Set instruction scheduling: under Code Generation/PPC Processor - off.
Set Peephole and Global Optimizations: under Code Generation/PPC Processor - off.

  UNIX

To uncompress and untar the archive, use the commands:
uncompress clippoly.tar.Z
tar xvf clippoly.tar

This will create a clippoly directory tree under the directory you are
currently in.

Change to the clippoly/Main directory and type

make

at the terminal prompt.

An executable called clippoly.exe will be created upon successful 
compilation and linking.

To test the executable type

make test

at the terminal prompt. This runs your executable using a test case
called inFile, creates an output file called outFile and does a diff on
outFile and a distribution file called outFile.dst.  If they are
identical then you will see no output and all is well, otherwise
compile, link, run, debug, compile, link, run, debug ...

NOTE: The clippoly MEX function source has not been ported to UNIX
MatLab. If you port this code to run under UNIX MatLab, I would like to
include your changes in the distribution. Please, notate all changes
consistently with something like /* modified by gsl 6/6/97 */ and let me
know through e-mail. I'll contact you and make arrangements to
incorporate the changes.

  IBM PC/Clone
  
Uncompress the zip archive with pkunzip -d clippoly.zip.

A batch file named CPPMEX.BAT is included in directory MATLAB.MEX/4IBM_PC to facilitate MEX file compilation on the PC. Read what is in this file before attempting compilation.

Move IBMPC.H into the MATLAB.MEX directory. To compile a MatLab MEX file
you must select the version of MatLab (either 4.x or 5.x) that you wish
to compile by setting the switch in this header file (currently only the
5.x version compiles and links successfully under Watcom C).

Valid Input

Either version of the code and MatLab scripts will accept polygons that
either do or do not wrap the first vertex to the last vertex. Polygons
cannot be self intersecting or co-linear but they can be concave.
Duplicate vertices are not allowed either, since this is a degenerate
form of self-intersection. If the A or the B polygons are self
intersecting or contain holes then they must be clipped into disjoint
polygons before being sent in to be clipped by clippoly.

If a set of A polygons and a set of B polygons are passed into the
plotMClp MatLab script, then the set of A polygons should not overlap
each other and the set of B polygons should not overlap each other. The
test case file twostars demonstrates this type of overlapping set of
polygons. If the polygons do overlap, clipping will be performed
properly; however, the total area calculated and returned for each of
the three regions A - B, B - A, and A & B will be incorrect, since
portions of overlapping regions will be added into the total more than
once. The way around this difficulty is to pass the A polygons through
the clipping code and take the output as the true A input polygons and
repeat this for the B polygons. This way only disjoint polygons are
passed into the polygon clipper. If more than two polygons overlap in
any portion of the plane, it is necessary to iterate until no polygons
remain that overlap each other before passing the polygon pairs in for
clipping.

Support

I and Klamer would both appreciate hearing of any bugs you find in the
code. Unfortunately, I am quite busy and cannot promise to provide any
support; however, if you send e-mail, I will endeavor to help when
possible.

If you do send in a bug report, please FIRST confirm that neither
polygon is self-intersecting or co-linear. If they are not then include
the following information:

(1) A MatLab MAT file (preferred method) as an e-mail attachment with
    one polygon stored in variable polyA and the other polygon stored in    
    variable polyB with x-coordinates in the first row and y-coordinates 
    in the second row OR the polygon list formatted as
    
ax1 ay1
ax2 ay2
...
axN ayN
PolyMagic
bx1 by1
bx2 by2
...
bxM byM
PolyMagic

(2) The specific error message you received.

(3) The computer platform, operating system and its version.

(4) The version of clippoly you are using. See RevHist.txt file.

(5) The compiler and its version.


Users Group

I have established an e-mailing list of clippoly users. This list will be used solely to inform users of updates and bug fixes to clippoly. I have made it a policy to add users to this list when they e-mail me with a problem.  If you would like to be added or removed from the list, please e-mail me at the address listed at the top of this document.

Code Availability

I have made my port of Klamer's code available through anonymous ftp at:

ftp://gandalf.tjh.tju.edu/pub/source/clip*{version #}.*

Select the appropriate archive for your system. The source code is
identical in each archive. Some binary files do vary amongst the
archives.

  Macintosh: clippoly{version #}.sit.hqx - binhexed stuffit-compressed
                                           archive
  UNIX: clippoly{version #}.tar.Z        - UNIX tar-compress archive
  IBM PC/Clone: clip_{version #}.zip     - zip compressed archive
                                           

Klamer's original code, as of this date, can be obtained from:

http://www.ph.tn.tudelft.nl/~klamer/clippoly_entry.html

A file named docs/Manifest.txt lists all files in the distribution.

A file named docs/RevHist.txt contains the clippoly revision history.

Some man pages from Klamer are in docs/*.3.


INSTALLATION (Thomas Binder)

I added  a GNU Makefile (Makefile.Linux) which  should work on  most of he newer
UNIX plattforms. It was tested under Linux (RedHat 6.2) with gcc/g++ 2.95 and on
DEC UNIX 4.0 with gcc/g++ and the  native compilers. If  you have any troubles I
suggest  you first  remove    the parts   marked with  automatically   generated
dependencies.


FROM KLAMER SCHUTTE

If you don't have g++, but a cfront based compiler like Sun C++ 3.0,
then you should compile the files from the CC subdirectory to this
directory. The String.{cc,h} files are not a complete implementation of
a String class; they only provide what is used in the file poly_io.cc.
For a good String class you can try the libg++ library (which I assume
is installed if you have g++.) Also, rename Makefile.CC to Makefile. If
you don't have g++ nor a cfront based compiler then you are on your own.
Compilers which are know to work:
g++ 2.4 -> 2.6.0 g++ 2.6.1 has a bug in constructor sysntax which break
this code.
Sun C++ 2.1, 3, 4
Irix CC on Irix 5.2
A bug which reveals itself on Ultrix mips machines is known. The fix will
be incorporated in this code some day.

Before compiling, skim through the Makefile. Three differences can be made:
- Changing the C compiler. Standard is cc. gcc -traditional can be used on
  systems with proper header files (this excludes SunOS 4.1.X). Ansi C
  compilers give warnings on the C files, as they are in K&R C, and the
  header files are ANSI C / C++.
- Adding the notion of a .cc file as a C++ source file. Some make's (like
  SGI's) do not standard recognize a .cc file as C++
- Patching libg++. Early versions of libg++ 2.5 (notably, 2.5.1 and 2.5.2)
  suffered a bug which caused the test porgram to hang. If you add
  sbscan.cc to the program (replacing the one in libg++) this bug is fixed.
  Better off course is to upgrade to a more recent libg++!
  Note that libg++ 2.4.X does not have this bug, and can be used without
  (known) problems.

In this directory you can find the test program for the nclip library.
In this directory is:

lgpl.texinfo: texinfo style version of the copyright statement.

test.cc: The wrapper in which we can test. Reads two clockwise
	oriented polygons from stdin, and clips those. Results
	comes on stdout. Examples format for input can be found in
	in_file.

nclip.cc:	The actual clip routine. Only file in the nclip
	library which is decent documented.

nclip.h nclip.cc poly.cc poly.h poly_io.cc poly_io.h posadder.cc
posadder.h primitives.cc primitives.h set.h:
	The rest of the nclip library. Not of real interest, but needed to
	get nclip running.

sbscan.cc:
	Part of libg++. It is a patched version of a file from libg++ 2.5.1

err.* graph*:
	files, part of our standard , in-house library. Not likely to
	have big errors. They even come with documentation!
	(*.3, nroff (== UNIX man) format)
	They should be compiled with a K&R C compiler (like gcc -traditional.)

CLASSES:
	Some documentation about the classes used.
