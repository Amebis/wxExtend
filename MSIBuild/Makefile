#
#    Copyright 1991-2020 Amebis
#    Copyright 2016 GÉANT
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

!INCLUDE "..\..\..\include\$(PKG)MSIBuildCfg.mak"

!IFNDEF MSIBUILD_LANGID
!ERROR Parameter MSIBUILD_LANGID is undefined.
!ENDIF

!IFNDEF MSIBUILD_PLAT_GUID
!ERROR Parameter MSIBUILD_PLAT_GUID is undefined.
!ENDIF

!IFNDEF MSIBUILD_LANG_GUID
!ERROR Parameter MSIBUILD_LANG_GUID is undefined.
!ENDIF

!IFNDEF WXEXTEND_BIN_DIR
!ERROR Parameter WXEXTEND_BIN_DIR is undefined.
!ENDIF

!IFNDEF WXEXTEND_LOC_DIR
!ERROR Parameter WXEXTEND_LOC_DIR is undefined.
!ENDIF


######################################################################
# Component

All :: "$(PKG)$(LANG).$(PLAT).$(CFG).Component-1.idt"

"$(PKG)$(LANG).$(PLAT).$(CFG).Component-1.idt" : "Makefile" "..\..\..\include\$(PKG)MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Component	ComponentId	Directory_	Attributes	Condition	KeyPath
s$(MSIBUILD_LENGTH_ID)	S38	s$(MSIBUILD_LENGTH_ID)	i2	S255	S$(MSIBUILD_LENGTH_ID)
Component	Component
!IFNDEF WXEXTEND_STATIC
compwxExtend.dll.$(PLAT)	{8D93D165-26AE-4066-9FB$(MSIBUILD_PLAT_GUID)-C37349BCEBAF}	$(WXEXTEND_BIN_DIR)	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.dll.$(PLAT)
!ENDIF
!IF "$(LANG)" != "en_US"
compwxExtend.mo.$(LANG)	{08F3D750-73F1-4D53-$(MSIBUILD_LANG_GUID)-4F4C5AFF24C1}	WXEXTENDLOC$(MSIBUILD_LANG_GUID)DIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.$(LANG)
!ENDIF
<<NOKEEP


######################################################################
# Directory

All :: "$(PKG)$(LANG).$(PLAT).$(CFG).Directory-1.idt"

"$(PKG)$(LANG).$(PLAT).$(CFG).Directory-1.idt" : "Makefile" "..\..\..\include\$(PKG)MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Directory	Directory_Parent	DefaultDir
s$(MSIBUILD_LENGTH_ID)	S$(MSIBUILD_LENGTH_ID)	l255
Directory	Directory
!IF "$(LANG)" != "en_US"
WXEXTENDLOC$(MSIBUILD_LANG_GUID)DIR	$(WXEXTEND_LOC_DIR)	$(LANG)
!ENDIF
<<NOKEEP


######################################################################
# File

All :: "$(PKG)$(LANG).$(PLAT).$(CFG).File-1.idt"

"$(PKG)$(LANG).$(PLAT).$(CFG).File-1.idt" : "Makefile" "..\..\..\include\$(PKG)MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
File	Component_	FileName	FileSize	Version	Language	Attributes	Sequence
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)	l255	i4	S$(MSIBUILD_LENGTH_ID)	S20	I2	i2
File	File
!IFNDEF WXEXTEND_STATIC
!IF "$(PLAT)" == "Win32"
!IF "$(CFG)" == "Release"
filewxExtend.dll.Win32	compwxExtend.dll.Win32	WXEXTE~2.DLL|wxExtend15u_vc100.dll	0		0	1536	1
!ENDIF
!IF "$(CFG)" == "Debug"
filewxExtend.dll.Win32	compwxExtend.dll.Win32	WXEXTE~4.DLL|wxExtend15ud_vc100.dll	0		0	1536	1
!ENDIF
!ENDIF
!IF "$(PLAT)" == "x64"
!IF "$(CFG)" == "Release"
filewxExtend.dll.x64	compwxExtend.dll.x64	WXEXTE~6.DLL|wxExtend15u_vc100_x64.dll	0		0	1536	1
!ENDIF
!IF "$(CFG)" == "Debug"
filewxExtend.dll.x64	compwxExtend.dll.x64	WXEXTE~8.DLL|wxExtend15ud_vc100_x64.dll	0		0	1536	1
!ENDIF
!ENDIF
!IF "$(PLAT)" == "ARM64"
!IF "$(CFG)" == "Release"
filewxExtend.dll.ARM64	compwxExtend.dll.ARM64	WXEXTE~8.DLL|wxExtend15u_vc100_arm64.dll	0		0	1536	1
!ENDIF
!IF "$(CFG)" == "Debug"
filewxExtend.dll.ARM64	compwxExtend.dll.ARM64	WXEXT~10.DLL|wxExtend15ud_vc100_arm64.dll	0		0	1536	1
!ENDIF
!ENDIF
!ENDIF
!IF "$(LANG)" != "en_US"
filewxExtend.mo.$(LANG)	compwxExtend.mo.$(LANG)	WXEXTE~1.MO|wxExtend15.mo	0		$(MSIBUILD_LANGID)	0	1
!ENDIF
<<NOKEEP


######################################################################
# Build MSM module!
######################################################################

!INCLUDE "..\..\..\MSI\MSIBuild\MSM.mak"
