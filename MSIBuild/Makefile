#
#    Copyright 1991-2018 Amebis
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

!INCLUDE "..\..\..\include\MSIBuildCfg.mak"

!IFNDEF MSIBUILD_LANGID
!ERROR Parameter MSIBUILD_LANGID is undefined.
!ENDIF

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
compwxExtend.dll.Win32	{8D93D165-26AE-4066-9FBE-C37349BCEBAF}	$(WXEXTEND_BIN_DIR)	0		filewxExtend.dll.Win32
!ENDIF
!IF "$(PLAT)" == "x64"
compwxExtend.dll.x64	{5CC39463-FEBE-496F-8EFB-F4F0AC4BCAB4}	$(WXEXTEND_BIN_DIR)	256		filewxExtend.dll.x64
!ENDIF
!IF "$(PLAT)" == "ARM64"
compwxExtend.dll.ARM64	{E1848B00-9E07-45CC-8BB4-5AE36DCB4174}	$(WXEXTEND_BIN_DIR)	256		filewxExtend.dll.ARM64
!ENDIF
!ENDIF
!IF "$(LANG)" == "bg_BG"
compwxExtend.mo.bg_BG	{08F3D750-73F1-4D53-ADE6-4F4C5AFF24C1}	WXEXTENDLOCBGBGDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.bg_BG
!ENDIF
!IF "$(LANG)" == "ca_ES"
compwxExtend.mo.ca_ES	{EEC3A2FA-C1F1-45BD-A407-91A5083879FC}	WXEXTENDLOCCAESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.ca_ES
!ENDIF
!IF "$(LANG)" == "cs_CZ"
compwxExtend.mo.cs_CZ	{6DBD1DFC-8266-467A-AE3B-F7ED9100BA8C}	WXEXTENDLOCCSCZDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.cs_CZ
!ENDIF
!IF "$(LANG)" == "cy_UK"
compwxExtend.mo.cy_UK	{8875B6EF-C0AB-4557-80D9-32F49925F79F}	WXEXTENDLOCCYUKDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.cy_UK
!ENDIF
!IF "$(LANG)" == "de_DE"
compwxExtend.mo.de_DE	{5CCA52DE-D4A9-4986-9D7D-D00EA6560D2F}	WXEXTENDLOCDEDEDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.de_DE
!ENDIF
!IF "$(LANG)" == "el_GR"
compwxExtend.mo.el_GR	{4617F1A6-BB15-4FF8-8CC8-C0D5C3B9DA63}	WXEXTENDLOCELGRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.el_GR
!ENDIF
!IF "$(LANG)" == "es_ES"
compwxExtend.mo.es_ES	{1469FC38-FF9B-4E5E-9F4C-998A86A4A1E0}	WXEXTENDLOCESESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.es_ES
!ENDIF
!IF "$(LANG)" == "eu_ES"
compwxExtend.mo.eu_ES	{8EAF1DF8-E7DB-4AC0-A627-423380BAE39F}	WXEXTENDLOCEUESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.eu_ES
!ENDIF
!IF "$(LANG)" == "fi_FI"
compwxExtend.mo.fi_FI	{4705881C-6A69-48C1-A1E1-D649F042DD77}	WXEXTENDLOCFIFIDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.fi_FI
!ENDIF
!IF "$(LANG)" == "fr_CA"
compwxExtend.mo.fr_CA	{1D90EA4B-EFC5-447C-9CB5-FBF3FD00388C}	WXEXTENDLOCFRCADIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.fr_CA
!ENDIF
!IF "$(LANG)" == "fr_FR"
compwxExtend.mo.fr_FR	{CC5336F8-9522-48C9-82DE-6D719C6F729B}	WXEXTENDLOCFRFRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.fr_FR
!ENDIF
!IF "$(LANG)" == "gl_ES"
compwxExtend.mo.gl_ES	{D7590042-3256-480F-ACAA-2CF9221FB666}	WXEXTENDLOCGLESDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.gl_ES
!ENDIF
!IF "$(LANG)" == "hr_HR"
compwxExtend.mo.hr_HR	{03BF1A96-BD07-475C-895D-BF367B8EAB44}	WXEXTENDLOCHRHRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.hr_HR
!ENDIF
!IF "$(LANG)" == "hu_HU"
compwxExtend.mo.hu_HU	{5C8C4A78-B95A-4A99-B115-BD90001A6A3C}	WXEXTENDLOCHUHUDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.hu_HU
!ENDIF
!IF "$(LANG)" == "is_IS"
compwxExtend.mo.is_IS	{17013596-7B9B-4893-8C75-7A5C5F76F2B3}	WXEXTENDLOCISISDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.is_IS
!ENDIF
!IF "$(LANG)" == "it_IT"
compwxExtend.mo.it_IT	{81EE1891-9774-465B-8079-B86C1511A4BF}	WXEXTENDLOCITITDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.it_IT
!ENDIF
!IF "$(LANG)" == "ko_KR"
compwxExtend.mo.ko_KR	{9B36C0D2-D4B3-4A4E-9FC8-BBC7E4E0101E}	WXEXTENDLOCKOKRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.ko_KR
!ENDIF
!IF "$(LANG)" == "lt_LT"
compwxExtend.mo.lt_LT	{4FF5FEB7-AECC-45A9-A81C-85D6D9B55A9C}	WXEXTENDLOCLTLTDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.lt_LT
!ENDIF
!IF "$(LANG)" == "nb_NO"
compwxExtend.mo.nb_NO	{D970A1E8-66B8-430E-93E2-34CE2A49FBCB}	WXEXTENDLOCNBNODIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.nb_NO
!ENDIF
!IF "$(LANG)" == "nl_NL"
compwxExtend.mo.nl_NL	{F9BE9502-CFAB-4D90-8150-446B5C092D5F}	WXEXTENDLOCNLNLDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.nl_NL
!ENDIF
!IF "$(LANG)" == "pl_PL"
compwxExtend.mo.pl_PL	{E0B0C10B-84D5-4E1F-9B78-51215B5BFB38}	WXEXTENDLOCPLPLDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.pl_PL
!ENDIF
!IF "$(LANG)" == "pt_PT"
compwxExtend.mo.pt_PT	{34F22826-EF6E-44E5-8BF8-AC509C4336FA}	WXEXTENDLOCPTPTDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.pt_PT
!ENDIF
!IF "$(LANG)" == "ru_RU"
compwxExtend.mo.ru_RU	{DD18920B-1755-4D08-B670-CD669576258D}	WXEXTENDLOCRURUDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.ru_RU
!ENDIF
!IF "$(LANG)" == "sk_SK"
compwxExtend.mo.sk_SK	{82DF7307-E848-4AFB-8BE7-E792BC51FDF3}	WXEXTENDLOCSKSKDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sk_SK
!ENDIF
!IF "$(LANG)" == "sl_SI"
compwxExtend.mo.sl_SI	{2CC6A48A-4B96-4530-B95E-450357B2FB23}	WXEXTENDLOCSLSIDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sl_SI
!ENDIF
!IF "$(LANG)" == "sr_RS"
compwxExtend.mo.sr_RS	{6F9F08AC-A9A4-4E3C-8E38-5C1BEB543401}	WXEXTENDLOCSRRSDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sr_RS
!ENDIF
!IF "$(LANG)" == "sv_SE"
compwxExtend.mo.sv_SE	{9C84C8E8-535C-4C09-91C9-BD83100E0050}	WXEXTENDLOCSVSEDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.sv_SE
!ENDIF
!IF "$(LANG)" == "tr_TR"
compwxExtend.mo.tr_TR	{A0A90268-99D7-4E4C-B275-7D3174458516}	WXEXTENDLOCTRTRDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.tr_TR
!ENDIF
!IF "$(LANG)" == "vi_VN"
compwxExtend.mo.vi_VN	{E7E317CD-C7AB-4043-8C4B-58E31569753A}	WXEXTENDLOCVIVNDIR	$(MSIBUILD_COMPONENT_ATTRIB_FILE)		filewxExtend.mo.vi_VN
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
!IF "$(LANG)" == "bg_BG"
WXEXTENDLOCBGBGDIR	$(WXEXTEND_LOC_DIR)	bg_BG
!ENDIF
!IF "$(LANG)" == "ca_ES"
WXEXTENDLOCCAESDIR	$(WXEXTEND_LOC_DIR)	ca_ES
!ENDIF
!IF "$(LANG)" == "cs_CZ"
WXEXTENDLOCCSCZDIR	$(WXEXTEND_LOC_DIR)	cs_CZ
!ENDIF
!IF "$(LANG)" == "cy_UK"
WXEXTENDLOCCYUKDIR	$(WXEXTEND_LOC_DIR)	cy_UK
!ENDIF
!IF "$(LANG)" == "de_DE"
WXEXTENDLOCDEDEDIR	$(WXEXTEND_LOC_DIR)	de_DE
!ENDIF
!IF "$(LANG)" == "el_GR"
WXEXTENDLOCELGRDIR	$(WXEXTEND_LOC_DIR)	el_GR
!ENDIF
!IF "$(LANG)" == "es_ES"
WXEXTENDLOCESESDIR	$(WXEXTEND_LOC_DIR)	es_ES
!ENDIF
!IF "$(LANG)" == "eu_ES"
WXEXTENDLOCEUESDIR	$(WXEXTEND_LOC_DIR)	eu_ES
!ENDIF
!IF "$(LANG)" == "fi_FI"
WXEXTENDLOCFIFIDIR	$(WXEXTEND_LOC_DIR)	fi_FI
!ENDIF
!IF "$(LANG)" == "fr_CA"
WXEXTENDLOCFRCADIR	$(WXEXTEND_LOC_DIR)	fr_CA
!ENDIF
!IF "$(LANG)" == "fr_FR"
WXEXTENDLOCFRFRDIR	$(WXEXTEND_LOC_DIR)	fr_FR
!ENDIF
!IF "$(LANG)" == "gl_ES"
WXEXTENDLOCGLESDIR	$(WXEXTEND_LOC_DIR)	gl_ES
!ENDIF
!IF "$(LANG)" == "hr_HR"
WXEXTENDLOCHRHRDIR	$(WXEXTEND_LOC_DIR)	hr_HR
!ENDIF
!IF "$(LANG)" == "hu_HU"
WXEXTENDLOCHUHUDIR	$(WXEXTEND_LOC_DIR)	hu_HU
!ENDIF
!IF "$(LANG)" == "is_IS"
WXEXTENDLOCISISDIR	$(WXEXTEND_LOC_DIR)	is_IS
!ENDIF
!IF "$(LANG)" == "it_IT"
WXEXTENDLOCITITDIR	$(WXEXTEND_LOC_DIR)	it_IT
!ENDIF
!IF "$(LANG)" == "ko_KR"
WXEXTENDLOCKOKRDIR	$(WXEXTEND_LOC_DIR)	ko_KR
!ENDIF
!IF "$(LANG)" == "lt_LT"
WXEXTENDLOCLTLTDIR	$(WXEXTEND_LOC_DIR)	lt_LT
!ENDIF
!IF "$(LANG)" == "nb_NO"
WXEXTENDLOCNBNODIR	$(WXEXTEND_LOC_DIR)	nb_NO
!ENDIF
!IF "$(LANG)" == "nl_NL"
WXEXTENDLOCNLNLDIR	$(WXEXTEND_LOC_DIR)	nl_NL
!ENDIF
!IF "$(LANG)" == "pl_PL"
WXEXTENDLOCPLPLDIR	$(WXEXTEND_LOC_DIR)	pl_PL
!ENDIF
!IF "$(LANG)" == "pt_PT"
WXEXTENDLOCPTPTDIR	$(WXEXTEND_LOC_DIR)	pt_PT
!ENDIF
!IF "$(LANG)" == "ru_RU"
WXEXTENDLOCRURUDIR	$(WXEXTEND_LOC_DIR)	ru_RU
!ENDIF
!IF "$(LANG)" == "sk_SK"
WXEXTENDLOCSKSKDIR	$(WXEXTEND_LOC_DIR)	sk_SK
!ENDIF
!IF "$(LANG)" == "sl_SI"
WXEXTENDLOCSLSIDIR	$(WXEXTEND_LOC_DIR)	sl_SI
!ENDIF
!IF "$(LANG)" == "sr_RS"
WXEXTENDLOCSRRSDIR	$(WXEXTEND_LOC_DIR)	sr_RS
!ENDIF
!IF "$(LANG)" == "sv_SE"
WXEXTENDLOCSVSEDIR	$(WXEXTEND_LOC_DIR)	sv_SE
!ENDIF
!IF "$(LANG)" == "tr_TR"
WXEXTENDLOCTRTRDIR	$(WXEXTEND_LOC_DIR)	tr_TR
!ENDIF
!IF "$(LANG)" == "vi_VN"
WXEXTENDLOCVIVNDIR	$(WXEXTEND_LOC_DIR)	vi_VN
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
