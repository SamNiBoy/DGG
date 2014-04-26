# Microsoft Developer Studio Project File - Name="HRS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HRS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HRS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HRS.mak" CFG="HRS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HRS - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HRS - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HRS - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "HRS - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "HRS - Win32 Release"
# Name "HRS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BoxDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BoxSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BoxView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\DbManger.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBoxLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFindList.cpp
# End Source File
# Begin Source File

SOURCE=.\HRS.cpp
# End Source File
# Begin Source File

SOURCE=.\HRS.rc
# End Source File
# Begin Source File

SOURCE=.\HRSDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\HRSSet.cpp
# End Source File
# Begin Source File

SOURCE=.\HRSView.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemView.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MoneyDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MoneySet.cpp
# End Source File
# Begin Source File

SOURCE=.\MoneyView.cpp
# End Source File
# Begin Source File

SOURCE=.\NavView.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryView.cpp
# End Source File
# Begin Source File

SOURCE=.\SaleDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SaleSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SaleView.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticBox.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\User.cpp
# End Source File
# Begin Source File

SOURCE=.\UserDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\UserSet.cpp
# End Source File
# Begin Source File

SOURCE=.\UserView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BoxDoc.h
# End Source File
# Begin Source File

SOURCE=.\BoxSet.h
# End Source File
# Begin Source File

SOURCE=.\BoxView.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\DbManger.h
# End Source File
# Begin Source File

SOURCE=.\DlgBoxLayout.h
# End Source File
# Begin Source File

SOURCE=.\DlgFindList.h
# End Source File
# Begin Source File

SOURCE=.\HRS.h
# End Source File
# Begin Source File

SOURCE=.\HRSDoc.h
# End Source File
# Begin Source File

SOURCE=.\HRSSet.h
# End Source File
# Begin Source File

SOURCE=.\HRSView.h
# End Source File
# Begin Source File

SOURCE=.\ItemDoc.h
# End Source File
# Begin Source File

SOURCE=.\ItemSet.h
# End Source File
# Begin Source File

SOURCE=.\ItemView.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MoneyDoc.h
# End Source File
# Begin Source File

SOURCE=.\MoneySet.h
# End Source File
# Begin Source File

SOURCE=.\MoneyView.h
# End Source File
# Begin Source File

SOURCE=.\NavView.h
# End Source File
# Begin Source File

SOURCE=.\QueryView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SaleDoc.h
# End Source File
# Begin Source File

SOURCE=.\SaleSet.h
# End Source File
# Begin Source File

SOURCE=.\SaleView.h
# End Source File
# Begin Source File

SOURCE=.\StaticBox.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\User.h
# End Source File
# Begin Source File

SOURCE=.\UserDoc.h
# End Source File
# Begin Source File

SOURCE=.\UserSet.h
# End Source File
# Begin Source File

SOURCE=.\UserView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\box.bmp
# End Source File
# Begin Source File

SOURCE=.\res\box1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor_h.cur
# End Source File
# Begin Source File

SOURCE=.\res\customer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\customer2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\customer3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HRS.ico
# End Source File
# Begin Source File

SOURCE=.\res\HRS.rc2
# End Source File
# Begin Source File

SOURCE=.\res\HRSDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\icn_ok.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_hrst.ico
# End Source File
# Begin Source File

SOURCE=.\res\item.bmp
# End Source File
# Begin Source File

SOURCE=.\res\item1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\item2.bmp
# End Source File
# Begin Source File

SOURCE=.\mdi.ico
# End Source File
# Begin Source File

SOURCE=.\res\money1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\money_mo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sale1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\user1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\user2..bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section HRS : {B541C03D-63BC-11CE-920C-08002B369A33}
# 	2:5:Class:CrdoTable
# 	2:10:HeaderFile:rdotable.h
# 	2:8:ImplFile:rdotable.cpp
# End Section
# Section HRS : {5E71F04D-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoConnection
# 	2:10:HeaderFile:_rdoconnection.h
# 	2:8:ImplFile:_rdoconnection.cpp
# End Section
# Section HRS : {5E71F051-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoEnvironment
# 	2:10:HeaderFile:_rdoenvironment.h
# 	2:8:ImplFile:_rdoenvironment.cpp
# End Section
# Section HRS : {2E746495-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoParameters
# 	2:10:HeaderFile:rdoparameters.h
# 	2:8:ImplFile:rdoparameters.cpp
# End Section
# Section HRS : {00028C00-0000-0000-0000-000000000046}
# 	2:21:DefaultSinkHeaderFile:msdgridctrl1.h
# 	2:16:DefaultSinkClass:CMsDgridCtrl
# End Section
# Section HRS : {5E71F050-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:CrdoPreparedStatement
# 	2:10:HeaderFile:rdopreparedstatement.h
# 	2:8:ImplFile:rdopreparedstatement.cpp
# End Section
# Section HRS : {2E7464A0-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoErrors
# 	2:10:HeaderFile:rdoerrors.h
# 	2:8:ImplFile:rdoerrors.cpp
# End Section
# Section HRS : {5D545B93-97CA-11CF-8171-00AA00A40C25}
# 	2:5:Class:CrdoPreparedStatements
# 	2:10:HeaderFile:rdopreparedstatements.h
# 	2:8:ImplFile:rdopreparedstatements.cpp
# End Section
# Section HRS : {2E746494-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoConnections
# 	2:10:HeaderFile:rdoconnections.h
# 	2:8:ImplFile:rdoconnections.cpp
# End Section
# Section HRS : {43478D71-78E0-11CF-8E78-00A0D100038E}
# 	2:5:Class:CRdc
# 	2:10:HeaderFile:rdc.h
# 	2:8:ImplFile:rdc.cpp
# End Section
# Section HRS : {5E71F04B-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoEngine
# 	2:10:HeaderFile:_rdoengine.h
# 	2:8:ImplFile:_rdoengine.cpp
# End Section
# Section HRS : {2E746498-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoQueries
# 	2:10:HeaderFile:rdoqueries.h
# 	2:8:ImplFile:rdoqueries.cpp
# End Section
# Section HRS : {B541C034-63BC-11CE-920C-08002B369A33}
# 	2:5:Class:CrdoError
# 	2:10:HeaderFile:rdoerror.h
# 	2:8:ImplFile:rdoerror.cpp
# End Section
# Section HRS : {2E746493-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoTables
# 	2:10:HeaderFile:rdotables.h
# 	2:8:ImplFile:rdotables.cpp
# End Section
# Section HRS : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section HRS : {5E71F04F-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoResultset
# 	2:10:HeaderFile:_rdoresultset.h
# 	2:8:ImplFile:_rdoresultset.cpp
# End Section
# Section HRS : {5E71F053-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:CrdoEnvironments
# 	2:10:HeaderFile:rdoenvironments.h
# 	2:8:ImplFile:rdoenvironments.cpp
# End Section
# Section HRS : {00028C02-0000-0000-0000-000000000046}
# 	2:5:Class:CMsDgridCtrl
# 	2:10:HeaderFile:msdgridctrl.h
# 	2:8:ImplFile:msdgridctrl.cpp
# End Section
# Section HRS : {2E746492-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoColumns
# 	2:10:HeaderFile:rdocolumns.h
# 	2:8:ImplFile:rdocolumns.cpp
# End Section
# Section HRS : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section HRS : {5E71F052-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:CrdoParameter
# 	2:10:HeaderFile:rdoparameter.h
# 	2:8:ImplFile:rdoparameter.cpp
# End Section
# Section HRS : {5E71F04E-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoColumn
# 	2:10:HeaderFile:_rdocolumn.h
# 	2:8:ImplFile:_rdocolumn.cpp
# End Section
# Section HRS : {43478D73-78E0-11CF-8E78-00A0D100038E}
# 	2:21:DefaultSinkHeaderFile:rdc.h
# 	2:16:DefaultSinkClass:CRdc
# End Section
# Section HRS : {2E746496-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoResultsets
# 	2:10:HeaderFile:rdoresultsets.h
# 	2:8:ImplFile:rdoresultsets.cpp
# End Section
