@echo off  
rem INTELF13MSVS2012ENGMATOPTS.BAT
rem
rem    Compile and link options used for building stand-alone engine or MAT
rem    programs using the Intel? Visual Fortran Compiler 13.0 with the
rem    Microsoft? Visual Studio? 2012 SP1 Professional Edition linker.
rem    
rem    $Revision: 1.1.6.1 $  $Date: 2012/09/25 18:19:59 $
rem
rem ********************************************************************
rem General parameters
rem ********************************************************************
set MATLAB=%MATLAB%
set IFORT_COMPILER13=%IFORT_COMPILER13%
set VSINSTALLDIR=%VS110COMNTOOLS%\..\..
set VCINSTALLDIR=%VSINSTALLDIR%\VC
set LINKERDIR='.registry_lookup("SOFTWARE\Wow6432Node\Microsoft\Microsoft SDKs\Windows\v8.0" , "InstallationFolder").'
set PATH=%IFORT_COMPILER13%\Bin\ia32;%VCINSTALLDIR%\BIN\;%VSINSTALLDIR%\VC\bin;%LINKERDIR%\bin;%LINKERDIR%\bin\x86;%VSINSTALLDIR%\Common7\IDE;%VSINSTALLDIR%\Common7\Tools;%VSINSTALLDIR%\Common7\Tools\bin;%VCINSTALLDIR%\VCPackages;%MATLAB_BIN%;%PATH%
set INCLUDE=%IFORT_COMPILER13%\compiler\Include;%LINKERDIR%\include;%VCINSTALLDIR%\ATLMFC\INCLUDE;%VCINSTALLDIR%\INCLUDE;%LINKERDIR%\include\um;%LINKERDIR%\include\shared;%LINKERDIR%\include\winrt;%INCLUDE%
set LIB=%IFORT_COMPILER13%\compiler\Lib\ia32;%VCINSTALLDIR%\ATLMFC\LIB;%VCINSTALLDIR%\LIB;%LINKERDIR%\lib;%LINKERDIR%\lib\win8\um\x86;%VSINSTALLDIR%\SDK\v2.0\lib;%MATLAB%\extern\lib\win32;%LIB%
set MW_TARGET_ARCH=win32

rem ********************************************************************
rem Compiler parameters
rem ********************************************************************
set COMPILER=ifort
set COMPFLAGS=/fpp /Qprec /I"%MATLAB%/extern/include" /c /nologo /fixed /fp:source /MD /assume:bscc
set OPTIMFLAGS=/O2 /DNDEBUG
set DEBUGFLAGS=/Z7
set NAME_OBJECT=/Fo

rem ********************************************************************
rem Linker parameters
rem ********************************************************************
set LIBLOC=%MATLAB%\extern\lib\win32\microsoft
set LINKER=link
set LINKFLAGS=/LIBPATH:"%LIBLOC%" libmx.lib libmat.lib libeng.lib /nologo /manifest /subsystem:console
set LINKOPTIMFLAGS=
set LINKDEBUGFLAGS=/debug /PDB:"%OUTDIR%%MEX_NAME%.pdb" /INCREMENTAL:NO
set LINK_FILE=
set LINK_LIB=
set NAME_OUTPUT=/out:"%OUTDIR%%MEX_NAME%.exe"
set RSP_FILE_INDICATOR=@

rem ********************************************************************
rem Resource compiler parameters
rem ********************************************************************
set RC_COMPILER=
set RC_LINKER=
set POSTLINK_CMDS1=mt -outputresource:"%OUTDIR%%MEX_NAME%.exe";1 -manifest "%OUTDIR%%MEX_NAME%.exe.manifest" 
set POSTLINK_CMDS2=del "%OUTDIR%%MEX_NAME%.exe.manifest" 
