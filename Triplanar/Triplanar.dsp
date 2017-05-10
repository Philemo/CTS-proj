# Microsoft Developer Studio Project File - Name="Checker" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Checker - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Checker.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Checker.mak" CFG="Checker - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Checker - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Checker - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/SDK/KwakSDK/Samples/Shaders/Checker", UTSAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Checker - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CHECKER_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\Include\Common" /I "..\..\..\Include\Carrara" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CHECKER_EXPORTS" /YX /FD @..\..\..\Build\CPFlags.opt /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib vfw32.lib mpr.lib ../../../lib/Win/Release/CommonLibrary.lib ../../../lib/Win/Release/SafeLibrary.lib /nologo /dll /machine:I386 /out:"Release/Checker.mcx"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=call ..\..\..\Build\BuildDTA Release Checker	call ..\..\..\Build\CopyMCX Release Checker
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Checker - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CHECKER_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MT /W3 /Gm /GX /ZI /Od /I "..\..\..\Include\Common" /I "..\..\..\Include\Carrara" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CHECKER_EXPORTS" /FR /YX /FD /GZ @..\..\..\Build\CPFlags.opt /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mpr.lib version.lib vfw32.lib ../../../lib/Win/Debug/CommonLibrary.lib ../../../lib/Win/Debug/SafeLibrary.lib /nologo /dll /debug /machine:I386 /out:"Debug/Checker.mcx" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=call ..\..\..\Build\BuildDTA Debug Checker	call ..\..\..\Build\CopyMCX Debug Checker
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Checker - Win32 Release"
# Name "Checker - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Checker.cpp
# End Source File
# Begin Source File

SOURCE=.\Checker.def
# End Source File
# Begin Source File

SOURCE=.\Checker.h
# End Source File
# Begin Source File

SOURCE=.\CheckerDef.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Checker.r
# End Source File
# Begin Source File

SOURCE=.\Checker.rsr
# End Source File
# End Group
# Begin Group "SDK Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Include\MCCommon\BasicCOMExtImplementations.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\MCCommon\BasicCOMImplementations.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\Carrara\BasicShader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\COMUtilities.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\MCCommon\COMUtilities.h
# End Source File
# End Group
# End Target
# End Project
