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

#include "stdafx.h"


bool WXEXTEND_API wxAuiManagerUpdatePerspectiveCaptions(wxAuiManager& mgr, wxString& perspective)
{
    wxString input = perspective;
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

    wxString result;
    result.Alloc(500);
    result = wxT("layout2|");

    // replace escaped characters so we can
    // split up the string easily
    input.Replace(wxT("\\|"), wxT("\a"));
    input.Replace(wxT("\\;"), wxT("\b"));

    wxSize ppi = wxClientDC(mgr.GetManagedWindow()).GetPPI();
    wxSize ppi_on_save(96, 96);
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

        if (pane_part.Left(3) == wxT("ppi"))
        {
            wxString value = pane_part.AfterFirst(wxT('='));

            long ppi_horz, ppi_vert;
            value.BeforeFirst(wxT(',')).ToLong(&ppi_horz);
            value.AfterFirst(wxT(',')).ToLong(&ppi_vert);

            ppi_on_save.x = ppi_horz;
            ppi_on_save.y = ppi_vert;
            result += wxString::Format(wxT("ppi=%d,%d|"),
                                       ppi.x, ppi.y);
            continue;
        }
        else if (pane_part.Left(9) == wxT("dock_size"))
        {
            wxString val_name = pane_part.BeforeFirst(wxT('='));
            wxString value = pane_part.AfterFirst(wxT('='));

            long dir, layer, row, size;
            wxString piece = val_name.AfterFirst(wxT('('));
            piece = piece.BeforeLast(wxT(')'));
            piece.BeforeFirst(wxT(',')).ToLong(&dir);
            piece = piece.AfterFirst(wxT(','));
            piece.BeforeFirst(wxT(',')).ToLong(&layer);
            piece.AfterFirst(wxT(',')).ToLong(&row);
            value.ToLong(&size);

            wxAuiDockInfo dock;
            dock.dock_direction = dir;
            dock.dock_layer = layer;
            dock.dock_row = row;
            dock.size = size == -1          ? -1 :
                        dock.IsHorizontal() ? wxMulDivInt32(size, ppi.x, ppi_on_save.x) :
                                              wxMulDivInt32(size, ppi.y, ppi_on_save.y);

            result += wxString::Format(wxT("dock_size(%d,%d,%d)=%d|"),
                                       dock.dock_direction, dock.dock_layer,
                                       dock.dock_row, dock.size);
            continue;
        }

        wxAuiPaneInfo pane;
        mgr.LoadPaneInfo(pane_part, pane, ppi_on_save);

        wxAuiPaneInfo& p = mgr.GetPane(pane.name);
        if (!p.IsOk())
        {
            // the pane window couldn't be found
            // in the existing layout -- skip it
            continue;
        }

        // Update caption.
        pane.caption = p.caption;

        // Reset best/min/max sizes to allow resize on GUI changes across different versions.
        pane.best_size = p.best_size;
        pane.min_size  = p.min_size;
        pane.max_size  = p.max_size;

        if ((pane.state & wxAuiPaneInfo::optionResizable) == 0) {
            // Reset floating size to allow resize on GUI changes across different versions for non-resizeable panes.
            pane.floating_size = p.floating_size;
        }

        // Re-generate and append pane info.
        result += mgr.SavePaneInfo(pane) + wxT('|');
    }

    perspective = result;
    return true;
}
