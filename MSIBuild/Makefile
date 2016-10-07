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
compwxExtend.dll.Win32	{37C6943E-B5D0-4C22-B039-29FEE015D0E8}	$(WXEXTEND_BIN_DIR)	0		filewxExtend.dll.Win32
!ENDIF
!IF "$(PLAT)" == "x64"
compwxExtend.dll.x64	{F323428B-B329-4492-943C-0F2387C80DC9}	$(WXEXTEND_BIN_DIR)	256		filewxExtend.dll.x64
!ENDIF
!ENDIF
compwxExtend.mo.ru_RU	{3B4C86C3-ABFF-4272-B8E4-2E9B59DC7867}	WXEXTENDLOCRURUDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.ru_RU
compwxExtend.mo.sl_SI	{E970685D-7997-40C9-A95C-95F1204BD534}	WXEXTENDLOCSLSIDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sl_SI
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
WXEXTENDLOCRURUDIR	$(WXEXTEND_LOC_DIR)	ru_RU
WXEXTENDLOCSLSIDIR	$(WXEXTEND_LOC_DIR)	sl_SI
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
filewxExtend.dll.Win32	compwxExtend.dll.Win32	WXEXTE~2.DLL|wxExtend14u_vc100.dll	0		0	1536	1
!ENDIF
!IF "$(CFG)" == "Debug"
filewxExtend.dll.Win32	compwxExtend.dll.Win32	WXEXTE~4.DLL|wxExtend14ud_vc100.dll	0		0	1536	1
!ENDIF
!ENDIF
!IF "$(PLAT)" == "x64"
!IF "$(CFG)" == "Release"
filewxExtend.dll.x64	compwxExtend.dll.x64	WXEXTE~6.DLL|wxExtend14u_vc100_x64.dll	0		0	1536	1
!ENDIF
!IF "$(CFG)" == "Debug"
filewxExtend.dll.x64	compwxExtend.dll.x64	WXEXTE~8.DLL|wxExtend14ud_vc100_x64.dll	0		0	1536	1
!ENDIF
!ENDIF
!ENDIF
filewxExtend.mo.ru_RU	compwxExtend.mo.ru_RU	WXEXTE~1.MO|wxExtend14.mo	0		1049	0	1
filewxExtend.mo.sl_SI	compwxExtend.mo.sl_SI	WXEXTE~1.MO|wxExtend14.mo	0		1060	0	1
<<NOKEEP


######################################################################
# Build MSM module!
######################################################################

!INCLUDE "..\..\..\MSI\MSIBuild\MSM.mak"
