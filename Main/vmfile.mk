; -*- lisp -*-
;;- $Id: vmfile.mk,v 1.1.1.1 2000/09/12 09:34:32 binder Exp $

;;- we define a name for the directory
(Module-Directory Poly2DExternalClipLibrary)

(C++-Target CxxExternalClipPolyObjects
	            :source "String.cc" "nclip.cc" "posadder.cc" "graphadd.cc" 
		            "graphmat.cc" "poly.cc" "templats.cc" "grphmtpp.cc"
			    "polyio.cc" "primitvs.cc")

;; here we would need -std0 for Tru64's CC and -traditional-cpp for GNU-CC
(CC-Target CExternalClipPolyObjects
	            :source "err.c"
		    :flags ("-std0" :cond  CxxUseKRFlag) 
		           ("-traditional-cpp" else))

(C++-Target CxxExternalClipPolyTest
	            :source "test.cc")

(C++-Target CxxExternalPClipPolyTest
		      :source "pptest.cc")

(Library-Target Polygon2DExternalClipLib
		      :libname "peclip"
		      :objects CxxExternalClipPolyObjects 
			       CExternalClipPolyObjects
		      :depends BucketQuadTreeLibrary
		      :shared)

(Program-Target CxxExternalPClipPolyTestProgram
		   :progname 	"cptest"
		   :objects	CxxExternalPClipPolyTest
		   :libraries   Polygon2DExternalClipLib)

(Program-Target CxxExternalClipPolyTestProgram
		  :progname 	"cliptest"
		  :objects	CxxExternalClipPolyTest
		  :libraries    Polygon2DExternalClipLib)

(Include-Target	:include "poly.h" "nclip.h" "polyio.h" "primitvs.h")