
@echo off
rem
rem  CMEX.BAT - Batch file for building MATLAB V.4 MEX-files
rem
rem     Using:  Microsoft C/C++ 7.0/ Visual C++ 1.0  (DLL MEX-files)
rem             Borland C++ 3.1                          (DLL MEX-files)
rem             Metaware High C/C++ V3.03                (REX MEX-files)
rem             Watcom C V10.0, V10.5                      (REX MEX-files)
rem
rem     USAGE:  cmex [source_files] [object_files] [libraries]
rem
rem             Mounil Patel  September 24, 1993
rem
rem             Copyright (C) 1992-1993 The MathWorks, Inc.
rem             All Rights Reserved
                                
set ORIG_PATH=%PATH%
set ORIG_INCLUDE=%INCLUDE%
if "%1"=="" goto USAGE
if "%1"=="-help" goto HELP

rem ********************************************************************
rem Edit the following to reflect where you installed MATLAB
rem ********************************************************************
SET MAT_ROOT=C:\BIN\MATH\MATLAB42

rem ********************************************************************
rem Set MEX_TYPE to one of the following:
rem     MSCMEX  if using Microsoft C            (DLL MEX-files)
rem     BCCMEX  if using Borland C++            (DLL MEX-files)
rem     METMEX  if using Metaware High C        (REX MEX-files)
rem     WATMEX  if using Watcom C               (REX MEX-files)
rem
rem     Make sure that you use all CAPITAL letters!
rem ********************************************************************
SET MEX_TYPE=WATMEX

rem ********************************************************************
rem Edit the following to reflect where you installed your compiler
rem ********************************************************************
SET COMP_ROOT=D:\BIN\WATCOM

rem ********************************************************************
rem Edit the following to reflect where you installed your Phar Lap
rem linker if you are making REX MEX-Files with the METAWARE C Compiler
rem ********************************************************************
rem set PL_ROOT=C:\PHAR386

rem ********************************************************************
rem Edit the following to reflect where you installed your MS Windows
rem SDK if you are making DLL MEX-Files
rem ********************************************************************
SET SDK_ROOT=D:\BIN\WATCOM


rem Set the INCLUDE environment variable for cmex usage
set INCLUDE=%MAT_ROOT%\simulink\include;%INCLUDE%

echo "step 1a"

rem Check to see if we're to make a stand-alone program for debugging
rem and if we're compiling a V3.5 MEX-file
set MEX_DBG=FALSE
set DBG_OPT=
set V35_FLAG=
echo "step1b"
if "%1"=="-DEBUG" set MEX_DBG=TRUE
if "%1"=="-debug" set MEX_DBG=TRUE
if "%1"=="-V3.5" set V35_FLAG=-DOLDSTYLE
if "%1"=="-v3.5" set V35_FLAG=-DOLDSTYLE
echo "step1c"
if "%MEX_DBG%"=="TRUE" goto check_arg2
echo "step1d"
if not "%V35_FLAG%"=="" goto check_arg2
echo "step1e"
goto save_name
echo "xx1"

rem Do it all again so we can accept these options in either order
:check_arg2
echo "xx2'
if "%2"=="-DEBUG" set MEX_DBG=TRUE
if "%2"=="-debug" set MEX_DBG=TRUE
if "%2"=="-V3.5" set V35_FLAG=-DOLDSTYLE
if "%2"=="-v3.5" set V35_FLAG=-DOLDSTYLE
if "%MEX_DBG%"=="TRUE" shift
if not "%V35_FLAG%"=="" shift

echo "step 2"

:save_name
rem Save the name of the first argument
set MEXFILENAME=%1
echo"a1"

if "%MEX_TYPE%"=="MSCMEX" goto CHECKMSC
if "%MEX_TYPE%"=="BCCMEX" goto CHECKBCC
if "%MEX_TYPE%"=="METMEX" goto CHECKMET
if "%MEX_TYPE%"=="WATMEX" goto CHECKWAT


echo    You must set MEX_TYPE to either BCCMEX, MSCMEX, METMEX or WATMEX!
echo    Make your corrections to cmex.bat and try again.
goto EXIT

:CHECKMSC
if not exist %COMP_ROOT%\binw\cl.exe goto SETUP1
if not exist %COMP_ROOT%\binw\link.exe goto SETUP1
if not exist %SDK_ROOT%\binw\rc.exe goto SETUP2

if not exist cmexdll.lnk goto COMPILE
del cmexdll.lnk
if not exist cmexdll.def goto COMPILE
del cmexdll.def

goto COMPILE

:CHECKBCC
if not exist %COMP_ROOT%\binw\bcc.exe goto SETUP1
if not exist %COMP_ROOT%\binw\tlink.exe goto SETUP1
if not exist %SDK_ROOT%\binw\rc.exe goto SETUP2

if not exist cmexdll.lnk goto COMPILE
del cmexdll.lnk
if not exist cmexdll.def goto COMPILE
del cmexdll.def

goto COMPILE

:CHECKMET
if not exist %COMP_ROOT%\binw\hc386.exe goto SETUP1
if not exist %PL_ROOT%\binw\386link.exe goto SETUP3

set PATH=%COMP_ROOT%\binw;%PL_ROOT%\binw;%PATH%

rem Create the link response file
echo -twocase                            > hcmex.rsp
echo -nomap                             >> hcmex.rsp
if "%MEX_DBG%"=="TRUE" goto METEXE
%MAT_ROOT%\binw\basefnam "-relexe %1"    >> hcmex.rsp
echo .mex                               >> hcmex.rsp
goto COMPILE

:METEXE
%MAT_ROOT%\binw\basefnam "-exe %1"       >> hcmex.rsp
echo .exe                               >> hcmex.rsp
echo -defstubname gorun386.exe          >> hcmex.rsp
echo -attributes group CGROUP er        >> hcmex.rsp
echo -attributes group DGROUP rw        >> hcmex.rsp
echo -cvsymbols                         >> hcmex.rsp
set DBG_OPT=-g
goto COMPILE

:CHECKWAT
echo  %COMP_ROOT%\binnt\wlink.exe
if not exist %COMP_ROOT%\binnt\wlink.exe goto SETUP1
set WAT_LINK=%COMP_ROOT%\binnt\wlink.exe
echo "tttt"

rem ---- The 10.0, and 10.5 Watcom compiler reside in different directories
set WAT_CMPLR=%COMP_ROOT%\binw\wpp386.exe
echo "p1"
if exist %COMP_ROOT%\binw\wpp386.exe goto CHECKEDWAT
echo "p2"

set WAT_CMPLR=%COMP_ROOT%\binnt\wpp386.exe
if not exist %COMP_ROOT%\binnt\wpp386.exe goto SETUP1
echo "step 5"

:CHECKEDWAT
echo "pp"

set PATH=%COMP_ROOT%/binnt;%COMP_ROOT%/binnt;%PATH%
set WATCOM=%COMP_ROOT%
echo "p3"

rem Create the link response file
echo option caseexact                            > wcmex.rsp
%MAT_ROOT%\bin\basefnam "name %1"               >> wcmex.rsp
if "%MEX_DBG%"=="TRUE" goto WATEXE
echo .mex                                       >> wcmex.rsp
         
echo format pharlap rex                         >> wcmex.rsp

echo "p4"
goto COMPILE

:WATEXE
echo .exe                                       >> wcmex.rsp
echo format os2 le                              >> wcmex.rsp
echo debug all                                  >> wcmex.rsp
echo option stack=64000                         >> wcmex.rsp
echo option stub=%COMP_ROOT%\binnt\wstub.exe     >> wcmex.rsp
set DBG_OPT=-d2
goto COMPILE

:COMPILE

if "%MEX_TYPE%"=="MSCMEX" goto PROC_MSC
if "%MEX_TYPE%"=="BCCMEX" goto PROC_BCC
if "%MEX_TYPE%"=="METMEX" goto PROC_MET
if "%MEX_TYPE%"=="WATMEX" goto PROC_WAT

:PROC_MSC

%MAT_ROOT%\binw\is_ext %1 .c
if not errorlevel 1 goto COMPMSC

%MAT_ROOT%\binw\is_ext %1 .obj
if not errorlevel 1 goto MSC_OBJ

%MAT_ROOT%\binw\is_ext %1 .lib
if not errorlevel 1 goto MSC_LIBS

:COMPMSC

rem Set environment variable for INCLUDE

set INCLUDE=%SDK_ROOT%\include;%COMP_ROOT%\include;%MAT_ROOT%\extern\include

rem Compile the Mex file module

@echo on
%COMP_ROOT%\binnt\cl -c -ALw -Zip -FPi87 -G2D -Od -W3 -DDLLMEX %V35_FLAG% %1
@echo off
if errorlevel 1 goto EXIT

:MSC_OBJ
%MAT_ROOT%\binw\basefnam %1      >> cmexdll.lnk
echo .obj +                     >> cmexdll.lnk

goto END_OF_LOOP

:PROC_BCC

%MAT_ROOT%\binw\is_ext %1 .c
if not errorlevel 1 goto COMPBCC

%MAT_ROOT%\binw\is_ext %1 .obj
if not errorlevel 1 goto BCC_OBJ

%MAT_ROOT%\binw\is_ext %1 .lib
if not errorlevel 1 goto BCC_LIBS

:COMPBCC

rem Set environment variable for INCLUDE

set INCLUDE=%SDK_ROOT%\include;%COMP_ROOT%\include;%MAT_ROOT%\extern\include

rem Compile the Mex file module

@echo on
%COMP_ROOT%\binw\bcc /c /WDE /ml! /f287 /2 /Od /DDLLMEX %V35_FLAG% /I%MAT_ROOT%
\extern\include %1
@echo off
if errorlevel 1 goto EXIT

:BCC_OBJ
%MAT_ROOT%\binw\basefnam %1      >> cmexdll.lnk
echo .obj +                     >> cmexdll.lnk

goto END_OF_LOOP

:PROC_MET

%MAT_ROOT%\binw\is_ext %1 .c
if not errorlevel 1 goto COMPMET

%MAT_ROOT%\binw\is_ext %1 .obj
if not errorlevel 1 goto MET_OBJ

%MAT_ROOT%\binw\is_ext %1 .lib
if not errorlevel 1 goto MET_LIBS

:COMPMET
@echo on
set INCLUDE=%COMP_ROOT%\inc;%MAT_ROOT%\extern\include;%INCLUDE%
%COMP_ROOT%\binw\hc386 -c -DMATLAB_MEX_FILE -Hipname=INCLUDE -f387 %1 %DBG_OPT%
 %V35_FLAG%
@echo off
if errorlevel 1 goto EXIT

:MET_OBJ
%MAT_ROOT%\binw\basefnam %1      >> hcmex.rsp
echo .obj                       >> hcmex.rsp

goto END_OF_LOOP

:PROC_WAT

%MAT_ROOT%\bin\is_ext %1 .c
if not errorlevel 1 goto COMPWAT

%MAT_ROOT%\bin\is_ext %1 .obj
if not errorlevel 1 goto WAT_OBJ

%MAT_ROOT%\bin\is_ext %1 .lib
if not errorlevel 1 goto WAT_LIBS

:COMPWAT
@echo on
set INCLUDE_PATH=-I%COMP_ROOT%\h -I%MAT_ROOT%\extern\include
%WAT_CMPLR% -7 -3s -DMATLAB_MEX_FILE @INCLUDE_PATH %1 %DBG_OPT% %V35_FLAG%
@echo off
if errorlevel 1 goto EXIT

:WAT_OBJ
%MAT_ROOT%\bin\basefnam "file %1"       >> wcmex.rsp
echo .obj                               >> wcmex.rsp

goto END_OF_LOOP

:END_OF_LOOP
shift
if not "%1" == "" goto COMPILE
if "%MEX_TYPE%"=="WATMEX" goto LINK
if "%MEX_TYPE%"=="METMEX" goto LINK

:MSC_LIBS
echo.,                                  >> cmexdll.lnk
%MAT_ROOT%\binw\basefnam %MEXFILENAME%   >> cmexdll.lnk
echo .dll                               >> cmexdll.lnk
%MAT_ROOT%\binw\basefnam %MEXFILENAME%   >> cmexdll.lnk
echo .map                               >> cmexdll.lnk

if "%1" == "" goto LINK

:MSC_LIB_LOOP
%MAT_ROOT%\binw\is_ext %1 .lib
if errorlevel 1 goto LIB_ERROR
echo %1 +                               >> cmexdll.lnk
shift
if "%1" == "" goto LINK
goto :MSC_LIB_LOOP

:BCC_LIBS
echo.,                                  >> cmexdll.lnk
%MAT_ROOT%\binw\basefnam %MEXFILENAME%   >> cmexdll.lnk
echo .dll                               >> cmexdll.lnk
%MAT_ROOT%\binw\basefnam %MEXFILENAME%   >> cmexdll.lnk
echo .map                               >> cmexdll.lnk

if "%1" == "" goto LINK

:BCC_LIB_LOOP
%MAT_ROOT%\binw\is_ext %1 .lib
if errorlevel 1 goto LIB_ERROR
echo %1 +                               >> cmexdll.lnk
shift
if "%1" == "" goto LINK
goto :BCC_LIB_LOOP

:MET_LIBS
%MAT_ROOT%\binw\is_ext %1 .lib
if errorlevel 1 goto LIB_ERROR
echo -lib       >> hcmex.rsp
echo %1         >> hcmex.rsp
shift
if "%1" == "" goto LINK
goto :MET_LIBS

:WAT_LIBS
%MAT_ROOT%\bin\is_ext %1 .lib
if errorlevel 1 goto LIB_ERROR
echo library  %1  >> wcmex.rsp
shift
if "%1" == "" goto LINK
goto :WAT_LIBS

:LINK
if "%MEX_TYPE%"=="MSCMEX" goto LINKMSC
if "%MEX_TYPE%"=="BCCMEX" goto LINKBCC
if "%MEX_TYPE%"=="METMEX" goto LINKMET
if "%MEX_TYPE%"=="WATMEX" goto LINKWAT

:LINKMSC
rem Set enviroment variable for LIB
set LIB=%SDK_ROOT%\lib;%COMP_ROOT%\lib

rem Create the module definition file
%MAT_ROOT%\binw\basefnam "LIBRARY %MEXFILENAME%"  > cmexdll.def
echo .dll                                       >> cmexdll.def
echo EXETYPE   WINDOWS                          >> cmexdll.def
echo STUB      '%COMP_ROOT%\binw\WINSTUB.EXE'    >> cmexdll.def
echo CODE      PRELOAD MOVEABLE DISCARDABLE     >> cmexdll.def
echo DATA      PRELOAD MOVEABLE SINGLE          >> cmexdll.def
echo HEAPSIZE  1024                             >> cmexdll.def
echo EXPORTS                                    >> cmexdll.def
echo     WEP                @1 RESIDENTNAME     >> cmexdll.def
echo     set_entry_point    @2                  >> cmexdll.def
echo     mexFunction            @3                  >> cmexdll.def
echo     mexAtExitFcn       @4                  >> cmexdll.def

echo %MAT_ROOT%\extern\lib\libmexms.lib +       >> cmexdll.lnk
echo ldllcew.lib +                              >> cmexdll.lnk
echo libw.lib                                   >> cmexdll.lnk
echo cmexdll.def                                >> cmexdll.lnk

rem Link the Mex file
rem
@echo on
%COMP_ROOT%\binw\link /align:32 /CO /NOD /NOE @cmexdll.lnk
@echo off
if errorlevel 1 goto EXIT

rem Resource compile the Mex file
rem
%MAT_ROOT%\binw\basefnam "%SDK_ROOT%\binw\rc %MEXFILENAME%" > cmexdll.bat
echo .dll       >> cmexdll.bat
call cmexdll.bat

rem Cleanup temporary files
rem
del cmexdll.lnk
del cmexdll.def
del cmexdll.bat
goto EXIT

:LINKBCC
rem Set enviroment variable for LIB
set LIB=%SDK_ROOT%\lib;%COMP_ROOT%\lib

rem Create the module definition file
echo EXETYPE   WINDOWS                          >> cmexdll.def
echo STUB      '%COMP_ROOT%\binw\WINSTUB.EXE'    >> cmexdll.def
echo CODE      PRELOAD MOVEABLE DISCARDABLE     >> cmexdll.def
echo DATA      PRELOAD MOVEABLE SINGLE          >> cmexdll.def
echo HEAPSIZE  1024                             >> cmexdll.def
echo EXPORTS                                    >> cmexdll.def
echo     WEP                @1 RESIDENTNAME     >> cmexdll.def
echo     set_entry_point    @2                  >> cmexdll.def
echo     mexFunction        @3                  >> cmexdll.def
echo     mexAtExitFcn       @4                  >> cmexdll.def

echo %MAT_ROOT%\extern\lib\libmexbc.lib+        >> cmexdll.lnk
echo cwl.lib +                              >> cmexdll.lnk
echo cl.lib +                              >> cmexdll.lnk
echo import.lib +                                 >> cmexdll.lnk
echo mathwl.lib +                                 >> cmexdll.lnk
echo mathl.lib +                                 >> cmexdll.lnk
echo fp87.lib +                                 >> cmexdll.lnk
echo.,                                 >> cmexdll.lnk
echo cmexdll.def                                >> cmexdll.lnk

rem Link the Mex file
rem
@echo on
%COMP_ROOT%\binw\tlink /A:32 /v /n /e /3 /Twd %COMP_ROOT%\lib\c0dl.obj @cmexdll
.lnk
@echo off
if errorlevel 1 goto EXIT

rem Resource compile the Mex file
rem
%MAT_ROOT%\binw\basefnam "%SDK_ROOT%\binw\rc %MEXFILENAME%" > cmexdll.bat
echo .dll       >> cmexdll.bat
call cmexdll.bat

rem Cleanup temporary files
rem
del cmexdll.lnk
del cmexdll.def
del cmexdll.bat
goto EXIT

:LINKMET

rem Build remainder of link response file

set LIBNAME=libmexhc.lib
if "%MEX_DBG%"=="TRUE" set LIBNAME=libdbghc.LIB

echo -lib                                       >> hcmex.rsp
echo %MAT_ROOT%\extern\lib\%LIBNAME%            >> hcmex.rsp
echo %COMP_ROOT%\small\hc387.lib                >> hcmex.rsp
echo %COMP_ROOT%\small\hc386.lib                >> hcmex.rsp
echo %COMP_ROOT%\small\hcna.lib                 >> hcmex.rsp

@echo on
%PL_ROOT%\binw\386link @hcmex.rsp
@echo off
del hcmex.rsp
goto EXIT

:LINKWAT
echo library %COMP_ROOT%\lib386\plib3s.lib >> wcmex.rsp

rem Build remainder of link response file

if "%MEX_DBG%"=="TRUE" goto WAT_DBG

echo "dum"
echo libpath %COMP_ROOT%\LIB386                   >> wcmex.rsp
echo library %MAT_ROOT%\extern\lib\libmexwc.lib         >> wcmex.rsp
echo library %COMP_ROOT%\lib386\math387s.lib            >> wcmex.rsp
echo library %COMP_ROOT%\lib386\dos\clib3s.lib          >> wcmex.rsp
goto DO_WAT_LINK

:WAT_DBG
echo library %MAT_ROOT%\extern\lib\libdbgwc.lib         >> wcmex.rsp
echo libpath %COMP_ROOT%\lib386                         >> wcmex.rsp
echo libpath %COMP_ROOT%\lib386\dos                     >> wcmex.rsp

:DO_WAT_LINK
@echo on
%WAT_LINK% @wcmex.rsp
@echo off
copy wcmex.rsp wcmex.rs1
del wcmex.rsp
goto EXIT

:USAGE
echo    Usage: cmex [source_files] [object_files] [libaries]
goto EXIT

:HELP
echo    Usage: cmex [options] file.c [addl_src_files] [object_files] [libaries]
echo    ----------------------------------------
echo    cmex will compile and link MEX source files into a relocat-
echo    able executable image.  This image is only executable from
echo    within MATLAB.  The resulting file will have a .mex or .dll
echo    extension.  The first file name given (less any file name
echo    extension) will be the name of the resulting MEX file.
echo    Additional source, object, or library files can be given to
echo    satisfy external references.  Both C and Fortran object files
echo    can be specified when building a MEX file.  The primary
echo    difference between cmex and fmex is that fmex links with the
echo    Fortran system libraries by default whereas cmex does not.
echo    ----------------------------------------
echo    If MATLAB detects a file with a .mex extension in the search
echo    path it will load it before a corresponding M-file in the same
echo    directory.  Thus, it is recommended that MEX-files be installed in
echo    the same directory that the M-file is (or would be if it existed).
echo    ----------------------------------------
echo    Options:
echo        -debug   Compile and link standalone with the debug option.
echo                 Refer to your external interface guide for details.
echo        -v3.5    Compile MATLAB V3.5 based mex-files for use with
echo                 MATLAB 4.x

goto EXIT

:LIB_ERROR
echo    All libraries must be placed at the end of the cmex command line
goto EXIT
                                                                        
:SETUP1
echo    You must edit this batch file to set the environment variable COMP_ROOT
echo    equal to the path where you installed your compiler before you can use
echo    it to create MEX files.
goto EXIT

:SETUP2
echo    You must edit this batch file to set the environment variable SDK_ROOT
echo    equal to the path where you installed the Microsoft Windows SDK 3.x
echo    before you can use it to create MEX files. This is most often included
echo    with your compiler (so you can set SDK_ROOT to the same location as
echo    COMP_ROOT).
goto EXIT

:SETUP3
echo    You must edit this batch file to set the environment variable PL_ROOT
echo    equal to the path where you installed the PharLap linker before you
echo    can use it to create MEX files.
goto EXIT

:EXIT
set PATH=%ORIG_PATH%
set INCLUDE=%ORIG_INCLUDE%
set ORIG_PATH=
set MEX_DBG=
set DBG_OPT=
set MEXFILENAME=
set LIBNAME=


