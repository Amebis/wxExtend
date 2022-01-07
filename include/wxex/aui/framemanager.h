/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2022 Amebis
    Copyright © 2016 GÉANT
*/

#pragma once

#include "../common.h"

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: WXWIDGETS_CODE_ANALYSIS_WARNINGS)
#include <wx/aui/framemanager.h>
#include <wx/string.h>
#pragma warning(pop)

/// \addtogroup wxExtend
/// @{

///
/// Updates perspective captions with matching captions from panes.
///
/// \param[in   ] mgr          wxAUI manager
/// \param[inout] perspective  Perspective string to update captions in
///
/// \returns
/// - \c true when update succeeded
/// - \c false otherwise
///
bool WXEXTEND_API wxAuiManagerUpdatePerspectiveCaptions(wxAuiManager& mgr, wxString& perspective);

/// @}
