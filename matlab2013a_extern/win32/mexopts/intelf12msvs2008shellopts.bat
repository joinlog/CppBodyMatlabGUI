@echo off
rem INTELF12MSVS2008SHELLOPTS.BAT
rem
rem    Compile and link options used for building MEX-files using the
rem    Intel? Fortran Compiler 12.0 with the Microsoft? Visual Studio?
rem    2008 Shell linker.
rem
rem StorageVersion: 1.0
rem FortrankeyFileName: INTELF12MSVS2008SHELLOPTS.BAT
rem FortrankeyName: Intel Visual Fortran
rem FortrankeyManufacturer: Intel
rem FortrankeyVersion: 12.0
rem FortrankeyLanguage: Fortran
rem FortrankeyLinkerName: Microsoft Visual Studio 2008 Shell
rem FortrankeyLinkerVersion: 9.0
rem
rem    $Revision: 1.1.6.3 $  $Date: 2012/07/23 18:50:23 $
rem
rem ********************************************************************
rem General parameters
rem ********************************************************************
set MATLAB=%MATLAB%
set IFORT_COMPILER12=%IFORT_COMPILER12%
set VS90COMNTOOLS=%VS90COMNTOOLS%
set LINKERDIR=%VS90COMNTOOLS%\..\..
set VSINSTALLDIR=%LINKERDIR%
set VCINSTALLDIR=%VSINSTALLDIR%\VC
set VSAENVDIR=%CommonProgramFiles%\Microsoft Shared\VSA\9.0\VsaEnv
set PATH=%IFORT_COMPILER12%\Bin\ia32;%VSAENVDIR%;%VSINSTALLDIR%\Common7\IDE;%VCINSTALLDIR%\BIN;%VSINSTALLDIR%\Common7\Tools;%VSINSTALLDIR%\Common7\Tools\bin;%VCINSTALLDIR%\PlatformSDK\bin;%VCINSTALLDIR%\BIN;%MATLAB_BIN%;%PATH%
set INCLUDE=%IFORT_COMPILER12%\compiler\Include;%VCINSTALLDIR%\atlmfc\include;%VCINSTALLDIR%\include;%VCINSTALLDIR%\PlatformSDK\include;%INCLUDE%
set LIB=%IFORT_COMPILER12%\compiler\Lib\ia32;%VCINSTALLDIR%\lib;%VCINSTALLDIR%\PlatformSDK\lib;%LIB%
set MW_TARGET_ARCH=win32

rem ********************************************************************
rem Compiler parameters
rem ********************************************************************
set COMPILER=ifort
set COMPFLAGS=/fpp /Qprec "/I%MATLAB%/extern/include" -c -nologo -DMATLAB_MEX_FILE /fixed /MD /fp:source /assume:bscc /Qvc9
set OPTIMFLAGS=/O2 /DNDEBUG
set DEBUGFLAGS=/Z7
set NAME_OBJECT=/Fo

rem ********************************************************************
rem Linker parameters
rem ********************************************************************
set LIBLOC=%MATLAB%\extern\lib\win32\microsoft
set LINKER=link
set LINKFLAGS=/dll /export:MEXFUNCTION /LIBPATH:"%LIBLOC%" libmx.lib libmex.lib libmat.lib /implib:"%LIB_NAME%.x" /MAP:"%OUTDIR%%MEX_NAME%%MEX_EXT%.map" /NOLOGO /INCREMENTAL:NO
set LINKOPTIMFLAGS=
set LINKDEBUGFLAGS=/debug /PDB:"%OUTDIR%%MEX_NAME%%MEX_EXT%.pdb"
set LINK_FILE=
set LINK_LIB=
set NAME_OUTPUT=/out:"%OUTDIR%%MEX_NAME%%MEX_EXT%"
set RSP_FILE_INDICATOR=@

rem ********************************************************************
rem Resource compiler parameters
rem ********************************************************************
set RC_COMPILER=rc /fo "%OUTDIR%mexversion.res"
set RC_LINKER=

set POSTLINK_CMDS=del "%LIB_NAME%.x" "%LIB_NAME%.exp"
set POSTLINK_CMDS1=mt -outputresource:"%OUTDIR%%MEX_NAME%%MEX_EXT%";2 -manifest "%OUTDIR%%MEX_NAME%%MEX_EXT%.manifest"
set POSTLINK_CMDS2=del "%OUTDIR%%MEX_NAME%%MEX_EXT%.manifest" 
set POSTLINK_CMDS3=del "%OUTDIR%%MEX_NAME%%MEX_EXT%.map"
