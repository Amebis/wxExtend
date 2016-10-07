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
compwxExtend.mo.bg_BG	{CF5725EF-F683-4673-8523-5502B57C0C9F}	WXEXTENDLOCBGBGDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.bg_BG
compwxExtend.mo.ca_ES	{80493A96-C77A-4F92-8B3E-35BE9127EBBE}	WXEXTENDLOCCAESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.ca_ES
compwxExtend.mo.cs_CZ	{EECC383F-CBFF-4675-ABB9-16D77AD25D5C}	WXEXTENDLOCCSCZDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.cs_CZ
compwxExtend.mo.cy_UK	{9601C64F-4C99-4F2D-95CA-F2DF150F1982}	WXEXTENDLOCCYUKDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.cy_UK
compwxExtend.mo.de_DE	{9C3D448E-E6F3-45B9-BFF9-8E12A7B5AB53}	WXEXTENDLOCDEDEDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.de_DE
compwxExtend.mo.el_GR	{51A8EA7F-709F-4C3B-A94D-3BEC3899C80B}	WXEXTENDLOCELGRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.el_GR
compwxExtend.mo.es_ES	{D11A4B09-D9CF-4350-8B26-D9CF117E2980}	WXEXTENDLOCESESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.es_ES
compwxExtend.mo.eu_ES	{C93CEE38-3602-4FF2-8319-6125F91EE03C}	WXEXTENDLOCEUESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.eu_ES
compwxExtend.mo.fi_FI	{6F6F463B-7013-4453-8224-6AEA6B2EBDBC}	WXEXTENDLOCFIFIDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.fi_FI
compwxExtend.mo.fr_CA	{39D0AB42-9AB6-45FB-990F-5525D1004332}	WXEXTENDLOCFRCADIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.fr_CA
compwxExtend.mo.fr_FR	{5E68D9D9-AAF3-4194-9675-2C484A3B5E7C}	WXEXTENDLOCFRFRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.fr_FR
compwxExtend.mo.gl_ES	{CA353D77-B09A-4588-AF5E-A0B2E3742B1B}	WXEXTENDLOCGLESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.gl_ES
compwxExtend.mo.hr_HR	{F096E922-C060-49A1-81F0-A5FEC68F3873}	WXEXTENDLOCHRHRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.hr_HR
compwxExtend.mo.hu_HU	{8B377B6C-5B05-4D7C-B1F5-7A40E2BB7BD4}	WXEXTENDLOCHUHUDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.hu_HU
compwxExtend.mo.is_IS	{10C23840-30DE-4014-9F82-80FAC55243D2}	WXEXTENDLOCISISDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.is_IS
compwxExtend.mo.it_IT	{C5733B34-3315-44BC-B568-F6EDEDD6EA92}	WXEXTENDLOCITITDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.it_IT
compwxExtend.mo.ko_KR	{668C27C4-C799-46B4-A8D7-DB4C2E5DBCBC}	WXEXTENDLOCKOKRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.ko_KR
compwxExtend.mo.lt_LT	{3EEECA40-96BB-4F14-9E4F-2B4176D849A5}	WXEXTENDLOCLTLTDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.lt_LT
compwxExtend.mo.nb_NO	{5CC24C7D-E928-4CAB-BA91-EB4D11BC2A4B}	WXEXTENDLOCNBNODIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.nb_NO
compwxExtend.mo.nl_NL	{8E9F03EF-E808-4AB8-B136-CC2622E29BD1}	WXEXTENDLOCNLNLDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.nl_NL
compwxExtend.mo.pl_PL	{F7994ACB-60DD-4722-8E8E-65B071664A78}	WXEXTENDLOCPLPLDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.pl_PL
compwxExtend.mo.pt_PT	{3157094C-A5A7-420D-AB47-80A721560DED}	WXEXTENDLOCPTPTDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.pt_PT
compwxExtend.mo.ru_RU	{3B4C86C3-ABFF-4272-B8E4-2E9B59DC7867}	WXEXTENDLOCRURUDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.ru_RU
compwxExtend.mo.sk_SK	{6E14CF20-6D82-4A23-9FED-E68C1C2FC92A}	WXEXTENDLOCSKSKDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sk_SK
compwxExtend.mo.sl_SI	{E970685D-7997-40C9-A95C-95F1204BD534}	WXEXTENDLOCSLSIDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sl_SI
compwxExtend.mo.sr_RS	{74E368AA-79B0-407D-9A05-E42002300EE7}	WXEXTENDLOCSRRSDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sr_RS
compwxExtend.mo.sv_SE	{084986BC-EB55-4BA3-B8E5-FF0714F1C8A3}	WXEXTENDLOCSVSEDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sv_SE
compwxExtend.mo.tr_TR	{519F85E4-8B31-42EF-BCDD-9B3B907C0762}	WXEXTENDLOCTRTRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.tr_TR
compwxExtend.mo.vi_VN	{738F9C8C-2084-4003-91EA-55CA4B851343}	WXEXTENDLOCVIVNDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.vi_VN
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
WXEXTENDLOCBGBGDIR	$(WXEXTEND_LOC_DIR)	bg_BG
WXEXTENDLOCCAESDIR	$(WXEXTEND_LOC_DIR)	ca_ES
WXEXTENDLOCCSCZDIR	$(WXEXTEND_LOC_DIR)	cs_CZ
WXEXTENDLOCCYUKDIR	$(WXEXTEND_LOC_DIR)	cy_UK
WXEXTENDLOCDEDEDIR	$(WXEXTEND_LOC_DIR)	de_DE
WXEXTENDLOCELGRDIR	$(WXEXTEND_LOC_DIR)	el_GR
WXEXTENDLOCESESDIR	$(WXEXTEND_LOC_DIR)	es_ES
WXEXTENDLOCEUESDIR	$(WXEXTEND_LOC_DIR)	eu_ES
WXEXTENDLOCFIFIDIR	$(WXEXTEND_LOC_DIR)	fi_FI
WXEXTENDLOCFRCADIR	$(WXEXTEND_LOC_DIR)	fr_CA
WXEXTENDLOCFRFRDIR	$(WXEXTEND_LOC_DIR)	fr_FR
WXEXTENDLOCGLESDIR	$(WXEXTEND_LOC_DIR)	gl_ES
WXEXTENDLOCHRHRDIR	$(WXEXTEND_LOC_DIR)	hr_HR
WXEXTENDLOCHUHUDIR	$(WXEXTEND_LOC_DIR)	hu_HU
WXEXTENDLOCISISDIR	$(WXEXTEND_LOC_DIR)	is_IS
WXEXTENDLOCITITDIR	$(WXEXTEND_LOC_DIR)	it_IT
WXEXTENDLOCKOKRDIR	$(WXEXTEND_LOC_DIR)	ko_KR
WXEXTENDLOCLTLTDIR	$(WXEXTEND_LOC_DIR)	lt_LT
WXEXTENDLOCNBNODIR	$(WXEXTEND_LOC_DIR)	nb_NO
WXEXTENDLOCNLNLDIR	$(WXEXTEND_LOC_DIR)	nl_NL
WXEXTENDLOCPLPLDIR	$(WXEXTEND_LOC_DIR)	pl_PL
WXEXTENDLOCPTPTDIR	$(WXEXTEND_LOC_DIR)	pt_PT
WXEXTENDLOCRURUDIR	$(WXEXTEND_LOC_DIR)	ru_RU
WXEXTENDLOCSKSKDIR	$(WXEXTEND_LOC_DIR)	sk_SK
WXEXTENDLOCSLSIDIR	$(WXEXTEND_LOC_DIR)	sl_SI
WXEXTENDLOCSRRSDIR	$(WXEXTEND_LOC_DIR)	sr_RS
WXEXTENDLOCSVSEDIR	$(WXEXTEND_LOC_DIR)	sv_SE
WXEXTENDLOCTRTRDIR	$(WXEXTEND_LOC_DIR)	tr_TR
WXEXTENDLOCVIVNDIR	$(WXEXTEND_LOC_DIR)	vi_VN
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
filewxExtend.mo.bg_BG	compwxExtend.mo.bg_BG	WXEXTE~1.MO|wxExtend14.mo	0		1026	0	1
filewxExtend.mo.ca_ES	compwxExtend.mo.ca_ES	WXEXTE~1.MO|wxExtend14.mo	0		1027	0	1
filewxExtend.mo.cs_CZ	compwxExtend.mo.cs_CZ	WXEXTE~1.MO|wxExtend14.mo	0		1029	0	1
filewxExtend.mo.cy_UK	compwxExtend.mo.cy_UK	WXEXTE~1.MO|wxExtend14.mo	0		1106	0	1
filewxExtend.mo.de_DE	compwxExtend.mo.de_DE	WXEXTE~1.MO|wxExtend14.mo	0		1031	0	1
filewxExtend.mo.el_GR	compwxExtend.mo.el_GR	WXEXTE~1.MO|wxExtend14.mo	0		1032	0	1
filewxExtend.mo.es_ES	compwxExtend.mo.es_ES	WXEXTE~1.MO|wxExtend14.mo	0		1034	0	1
filewxExtend.mo.eu_ES	compwxExtend.mo.eu_ES	WXEXTE~1.MO|wxExtend14.mo	0		1069	0	1
filewxExtend.mo.fi_FI	compwxExtend.mo.fi_FI	WXEXTE~1.MO|wxExtend14.mo	0		1035	0	1
filewxExtend.mo.fr_CA	compwxExtend.mo.fr_CA	WXEXTE~1.MO|wxExtend14.mo	0		3084	0	1
filewxExtend.mo.fr_FR	compwxExtend.mo.fr_FR	WXEXTE~1.MO|wxExtend14.mo	0		1036	0	1
filewxExtend.mo.gl_ES	compwxExtend.mo.gl_ES	WXEXTE~1.MO|wxExtend14.mo	0		1110	0	1
filewxExtend.mo.hr_HR	compwxExtend.mo.hr_HR	WXEXTE~1.MO|wxExtend14.mo	0		1050	0	1
filewxExtend.mo.hu_HU	compwxExtend.mo.hu_HU	WXEXTE~1.MO|wxExtend14.mo	0		1038	0	1
filewxExtend.mo.is_IS	compwxExtend.mo.is_IS	WXEXTE~1.MO|wxExtend14.mo	0		1039	0	1
filewxExtend.mo.it_IT	compwxExtend.mo.it_IT	WXEXTE~1.MO|wxExtend14.mo	0		1040	0	1
filewxExtend.mo.ko_KR	compwxExtend.mo.ko_KR	WXEXTE~1.MO|wxExtend14.mo	0		1042	0	1
filewxExtend.mo.lt_LT	compwxExtend.mo.lt_LT	WXEXTE~1.MO|wxExtend14.mo	0		1063	0	1
filewxExtend.mo.nb_NO	compwxExtend.mo.nb_NO	WXEXTE~1.MO|wxExtend14.mo	0		1044	0	1
filewxExtend.mo.nl_NL	compwxExtend.mo.nl_NL	WXEXTE~1.MO|wxExtend14.mo	0		1043	0	1
filewxExtend.mo.pl_PL	compwxExtend.mo.pl_PL	WXEXTE~1.MO|wxExtend14.mo	0		1045	0	1
filewxExtend.mo.pt_PT	compwxExtend.mo.pt_PT	WXEXTE~1.MO|wxExtend14.mo	0		2070	0	1
filewxExtend.mo.ru_RU	compwxExtend.mo.ru_RU	WXEXTE~1.MO|wxExtend14.mo	0		1049	0	1
filewxExtend.mo.sk_SK	compwxExtend.mo.sk_SK	WXEXTE~1.MO|wxExtend14.mo	0		1051	0	1
filewxExtend.mo.sl_SI	compwxExtend.mo.sl_SI	WXEXTE~1.MO|wxExtend14.mo	0		1060	0	1
filewxExtend.mo.sr_RS	compwxExtend.mo.sr_RS	WXEXTE~1.MO|wxExtend14.mo	0		2074	0	1
filewxExtend.mo.sv_SE	compwxExtend.mo.sv_SE	WXEXTE~1.MO|wxExtend14.mo	0		1053	0	1
filewxExtend.mo.tr_TR	compwxExtend.mo.tr_TR	WXEXTE~1.MO|wxExtend14.mo	0		1055	0	1
filewxExtend.mo.vi_VN	compwxExtend.mo.vi_VN	WXEXTE~1.MO|wxExtend14.mo	0		1066	0	1
<<NOKEEP


######################################################################
# Build MSM module!
######################################################################

!INCLUDE "..\..\..\MSI\MSIBuild\MSM.mak"
