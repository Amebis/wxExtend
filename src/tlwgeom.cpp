/*
    ​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2022 Amebis
    Copyright © 2016 GÉANT
    Based on code written by Jeffrey Richter.
*/

#include "pch.h"


#if wxUSE_DYNLIB_CLASS
wxDynamicLibrary wxTLWGeometryEx::s_dllUser32(wxT("user32.dll"));
wxDynamicLibrary wxTLWGeometryEx::s_dllShCore(wxT("shcore.dll"), wxDL_DEFAULT | wxDL_QUIET);
#endif
