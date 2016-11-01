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

#pragma once

#include "../common.h"

#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/window.h>
#include <wx/dialog.h>


// ----------------------------------------------------------------------------
// string constants used by wxPersistentDialog
// ----------------------------------------------------------------------------

#define wxPERSIST_DIALOG_KIND "Dialog"


///
/// Supports saving/restoring wxDialog state
///
class wxPersistentDialog : public wxPersistentWindow<wxDialog>
{
public:
    wxPersistentDialog(wxDialog *mgr) : wxPersistentWindow<wxDialog>(mgr)
    {
    }

    virtual wxString GetKind() const
    {
        return wxT(wxPERSIST_DIALOG_KIND);
    }

    virtual void Save() const
    {
        const wxDialog * const wnd = Get();

        // Code copied from wxPersistentTLW::Save()
        const wxPoint pos = wnd->GetScreenPosition();
        SaveValue(wxPERSIST_TLW_X, pos.x);
        SaveValue(wxPERSIST_TLW_Y, pos.y);
    }

    virtual bool Restore()
    {
        wxDialog * const wnd = Get();

        // Code copied from wxPersistentTLW::Restore()
        long
            x wxDUMMY_INITIALIZE(-1),
            y wxDUMMY_INITIALIZE(-1);
        const wxSize size = wnd->GetSize();
        const bool hasPos = RestoreValue(wxPERSIST_TLW_X, &x) &&
                            RestoreValue(wxPERSIST_TLW_Y, &y);

        if (hasPos) {
            // to avoid making the window completely invisible if it had been
            // shown on a monitor which was disconnected since the last run
            // (this is pretty common for notebook with external displays)
            //
            // NB: we should allow window position to be (slightly) off screen,
            //     it's not uncommon to position the window so that its upper
            //     left corner has slightly negative coordinate
            if (wxDisplay::GetFromPoint(wxPoint(x         , y         )) != wxNOT_FOUND ||
                wxDisplay::GetFromPoint(wxPoint(x + size.x, y + size.y)) != wxNOT_FOUND)
            {
                wnd->Move(x, y, wxSIZE_ALLOW_MINUS_ONE);
            }
        }

        return true;
    }

private:
    wxDECLARE_NO_COPY_CLASS(wxPersistentDialog);
};


///
/// wxDialog's instantiation of wxCreatePersistentObject template
///
inline wxPersistentObject *wxCreatePersistentObject(wxDialog *mgr)
{
    return new wxPersistentDialog(mgr);
}
