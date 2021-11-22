/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2021 Amebis
    Copyright © 2016 GÉANT
*/

#pragma once

// Since including <wx/app.h> introduces wrong include order in 3.0.2,
// include the grand <wx/wx.h> at a cost of longer pre-compilation phase.
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS 26812 26814)
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
