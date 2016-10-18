/*
    Copyright 2015-2016 Amebis
    Copyright 2016 G�ANT

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

#include <wx/aui/framemanager.h>
#include <wx/string.h>


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