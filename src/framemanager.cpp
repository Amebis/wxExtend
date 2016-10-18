/*
    Copyright 2015-2016 Amebis
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

#include "stdafx.h"


bool WXEXTEND_API wxAuiManagerUpdatePerspectiveCaptions(wxAuiManager& mgr, wxString& perspective)
{
    wxString input = perspective;
    wxString output;
    wxString part;

    // check layout string version
    //    'layout1' = wxAUI 0.9.0 - wxAUI 0.9.2
    //    'layout2' = wxAUI 0.9.2 (wxWidgets 2.8)
    part = input.BeforeFirst(wxT('|'));
    input = input.AfterFirst(wxT('|'));
    part.Trim(true);
    part.Trim(false);
    if (part != wxT("layout2"))
        return false;
    output += part;
    output += wxT('|');

    // replace escaped characters so we can
    // split up the string easily
    input.Replace(wxT("\\|"), wxT("\a"));
    input.Replace(wxT("\\;"), wxT("\b"));

    while (1)
    {
        wxString pane_part = input.BeforeFirst(wxT('|'));
        input = input.AfterFirst(wxT('|'));
        pane_part.Trim(true);

        // if the string is empty, we're done parsing
        if (pane_part.empty())
            break;

        // Undo our escaping
        pane_part.Replace(wxT("\a"), wxT("|"));
        pane_part.Replace(wxT("\b"), wxT(";"));

        if (pane_part.Left(9) == wxT("dock_size"))
        {
            output += pane_part;
            output += wxT('|');
            continue;
        }

        wxAuiPaneInfo pane;
        mgr.LoadPaneInfo(pane_part, pane);

        wxAuiPaneInfo& p = mgr.GetPane(pane.name);
        if (!p.IsOk())
        {
            // the pane window couldn't be found
            // in the existing layout -- skip it
            continue;
        }

        // Update caption.
        pane.caption = p.caption;

        output += mgr.SavePaneInfo(pane);
        output += wxT('|');
    }

    perspective = output;
    return true;
}
