#
#    Copyright 1991-2016 Amebis
#
#    This file is part of ZRCola.
#
#    ZRCola is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    ZRCola is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with ZRCola. If not, see <http://www.gnu.org/licenses/>.
#

!INCLUDE "..\..\..\include\MSIBuildCfg.mak"

!IFNDEF WXEXTEND_BIN_DIR
!ERROR Parameter WXEXTEND_BIN_DIR is undefined.
!ENDIF

!IFNDEF WXEXTEND_LOC_DIR
!ERROR Parameter WXEXTEND_LOC_DIR is undefined.
!ENDIF


######################################################################
# Component

All :: "$(LANG).$(PLAT).$(CFG).Component-1.idt"

"$(LANG).$(PLAT).$(CFG).Component-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Component	ComponentId	Directory_	Attributes	Condition	KeyPath
s$(MSIBUILD_LENGTH_ID)	S38	s$(MSIBUILD_LENGTH_ID)	i2	S255	S$(MSIBUILD_LENGTH_ID)
Component	Component
!IFNDEF WXEXTEND_STATIC
!IF "$(PLAT)" == "Win32"
compwxExtend.dll.Win32	{7645D753-4A8C-40C6-BD6F-6DDE54F2B8F8}	$(WXEXTEND_BIN_DIR)	0		filewxExtend.dll.Win32
!ENDIF
!IF "$(PLAT)" == "x64"
compwxExtend.dll.x64	{919135CB-B106-467E-A3DA-CBC463FBB7FF}	$(WXEXTEND_BIN_DIR)	256		filewxExtend.dll.x64
!ENDIF
!ENDIF
!IF "$(LANG)" == "ru_RU"
compwxExtend.mo.ru_RU	{53ED87E7-83E9-44B2-8969-A6B7059466F5}	WXEXTENDLOCRURUDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.ru_RU
!ENDIF
!IF "$(LANG)" == "sl_SI"
compwxExtend.mo.sl_SI	{08656BB6-0887-4605-B6D3-20B0444624BA}	WXEXTENDLOCSLSIDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sl_SI
!ENDIF
<<NOKEEP


######################################################################
# Directory

All :: "$(LANG).$(PLAT).$(CFG).Directory-1.idt"

"$(LANG).$(PLAT).$(CFG).Directory-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Directory	Directory_Parent	DefaultDir
s$(MSIBUILD_LENGTH_ID)	S$(MSIBUILD_LENGTH_ID)	l255
Directory	Directory
!IF "$(LANG)" == "ru_RU"
WXEXTENDLOCRURUDIR	$(WXEXTEND_LOC_DIR)	ru_RU
!ENDIF
!IF "$(LANG)" == "sl_SI"
WXEXTENDLOCSLSIDIR	$(WXEXTEND_LOC_DIR)	sl_SI
!ENDIF
<<NOKEEP


######################################################################
# File

All :: "$(LANG).$(PLAT).$(CFG).File-1.idt"

"$(LANG).$(PLAT).$(CFG).File-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
File	Component_	FileName	FileSize	Version	Language	Attributes	Sequence
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)	l255	i4	S$(MSIBUILD_LENGTH_ID)	S20	I2	i2
File	File
!IFNDEF WXEXTEND_STATIC
!IF "$(PLAT)" == "Win32"
!IF "$(CFG)" == "Release"
filewxExtend.dll.Win32	compwxExtend.dll.Win32	WXEXTE~2.DLL|wxExtend13u_vc100.dll	0		0	1536	1
!ENDIF
!IF "$(CFG)" == "Debug"
filewxExtend.dll.Win32	compwxExtend.dll.Win32	WXEXTE~4.DLL|wxExtend13ud_vc100.dll	0		0	1536	1
!ENDIF
!ENDIF
!IF "$(PLAT)" == "x64"
!IF "$(CFG)" == "Release"
filewxExtend.dll.x64	compwxExtend.dll.x64	WXEXTE~6.DLL|wxExtend13u_vc100_x64.dll	0		0	1536	1
!ENDIF
!IF "$(CFG)" == "Debug"
filewxExtend.dll.x64	compwxExtend.dll.x64	WXEXTE~8.DLL|wxExtend13ud_vc100_x64.dll	0		0	1536	1
!ENDIF
!ENDIF
!ENDIF
!IF "$(LANG)" == "ru_RU"
filewxExtend.mo.ru_RU	compwxExtend.mo.ru_RU	WXEXTE~1.MO|wxExtend13.mo	0		1060	0	1
!ENDIF
!IF "$(LANG)" == "sl_SI"
filewxExtend.mo.sl_SI	compwxExtend.mo.sl_SI	WXEXTE~1.MO|wxExtend13.mo	0		1060	0	1
!ENDIF
<<NOKEEP


######################################################################
# Build MSM module!
######################################################################

!INCLUDE "..\..\..\MSI\MSIBuild\MSM.mak"
