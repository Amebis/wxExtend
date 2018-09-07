/*
    Copyright 2015-2018 Amebis
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

/// \addtogroup wxExtend
/// @{

///
/// `wxPersistentDialog` kind for persistent storage
///
#define wxPERSIST_DIALOG_KIND "Dialog"

///
/// Supports saving/restoring wxDialog state
///
class wxPersistentDialog :
    public wxPersistentWindow<wxDialog>,
    private wxTopLevelWindow::GeometrySerializer
{
public:
    ///
    /// Constructs a persistent dialog object
    ///
    wxPersistentDialog(wxDialog *mgr) : wxPersistentWindow<wxDialog>(mgr)
    {
    }

    ///
    /// \returns `wxT(wxPERSIST_DIALOG_KIND)`
    ///
    virtual wxString GetKind() const wxOVERRIDE
    {
        return wxT(wxPERSIST_DIALOG_KIND);
    }

    ///
    /// Saves dialog state
    ///
    virtual void Save() const wxOVERRIDE
    {
        const wxDialog * const wnd = Get();

        // Code copied from wxPersistentTLW::Save()
        wnd->SaveGeometry(*this);
    }

    ///
    /// Restores dialog state
    ///
    virtual bool Restore() wxOVERRIDE
    {
        wxDialog * const wnd = Get();

        return wnd->RestoreToGeometry(*this);
    }

private:
    wxDECLARE_NO_COPY_CLASS(wxPersistentDialog);

private:
    virtual bool SaveField(const wxString& name, int value) const wxOVERRIDE
    {
        return SaveValue(name, value);
    }

    virtual bool RestoreField(const wxString& name, int* value) wxOVERRIDE
    {
        return RestoreValue(name, value);
    }
};


///
/// wxDialog's instantiation of wxCreatePersistentObject template
///
inline wxPersistentObject *wxCreatePersistentObject(wxDialog *mgr)
{
    return new wxPersistentDialog(mgr);
}

/// @}
