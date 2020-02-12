/*
    Copyright 2015-2020 Amebis
    Copyright 2016 GÉANT

    This file is part of wxExtend.

    wxExtend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    wxExtend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with wxExtend. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Since including <wx/app.h> introduces wrong include order in 3.0.2,
// include the grand <wx/wx.h> at a cost of longer pre-compilation phase.
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS 26812)
#include <wx/wx.h>
#pragma warning(pop)

#include "../include/wxex/aui/framemanager.h"

#include "../include/wxex/persist/auimanager.h"
#include "../include/wxex/persist/toplevel.h"

#include "../include/wxex/appbar.h"
#include "../include/wxex/comutils.h"
#include "../include/wxex/crypto.h"
#include "../include/wxex/hex.h"
#include "../include/wxex/object.h"
#include "../include/wxex/url.h"
#include "../include/wxex/valhex.h"
#include "../include/wxex/valnet.h"
#include "../include/wxex/xml.h"

#include "../include/wxex/common.h"

#include "../include/wxex/private/tlwgeom.h"
