ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -I. -DGEN_TEMPLATES
AM_CXXFLAGS = -Wall
AM_CFLAGS = -Wall

lib_LTLIBRARIES = libclippoly.la

libclippoly_la_SOURCES =

# OBJ
libclippoly_la_SOURCES += nclip.cc poly.cc poly_io.cc posadder.cc	\
primitives.cc templates.cc version.c

# LIBOBJ
libclippoly_la_SOURCES += graphadd.cc graphmat.c graphmat++.cc

check_PROGRAMS = clippolytest

clippolytest_SOURCES = clippolytest.cc

clippolytest_LDADD = libclippoly.la

TESTS = test0 test1 test2

dist_man_MANS = graphadd.3 graphmat.3 graphmat++.3

dist_doc_DATA = CLASSES README

cpincludedir = $(includedir)/clippoly

cpinclude_HEADERS = graphadd.h graphmat.h graphmat++.h nclip.h poly.h	\
poly_io.h posadder.h primitives.h set.h version.h

EXTRA_DIST = case1 case2 case3 in_file in_file.test in_file.wrong	\
lgpl.texinfo out_file.dist t1 t1.out t2 t2.out test0 test1 test2

clippoly.pc:
	echo 'prefix=$(prefix)'			>  $@
	echo 'exec_prefix=$(exec_prefix)'	>> $@
	echo 'includedir=$(includedir)'		>> $@
	echo 'libdir=$(libdir)'			>> $@
	echo					>> $@
	echo 'Name: $(PACKAGE_TARNAME)'		>> $@
	echo 'Description: $(PACKAGE_NAME)'	>> $@
	echo 'URL: $(PACKAGE_URL)'		>> $@
	echo 'Version: $(PACKAGE_VERSION)'	>> $@
	echo 'Cflags: -I${includedir}'		>> $@
	echo 'Libs: -L${libdir} -lclippoly'	>> $@
	echo 'Libs.private: $(LDFLAGS) $(LIBS)'	>> $@

pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA = clippoly.pc
