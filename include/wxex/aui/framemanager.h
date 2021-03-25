/*
    Copyright © 2015-2021 Amebis
    Copyright © 2016 GÉANT

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
