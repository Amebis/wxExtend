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
#include "../private/tlwgeom.h"

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: WXWIDGETS_CODE_ANALYSIS_WARNINGS)
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/window.h>
#include <wx/toplevel.h>
#pragma warning(pop)

/// \addtogroup wxExtend
/// @{

///
/// Supports saving/restoring wxTopLevelWindow state
///
class wxPersistentTLWEx :
    public wxPersistentWindow<wxTopLevelWindow>,
    private wxTopLevelWindow::GeometrySerializer
{
public:
    ///
    /// Constructs a persistent dialog object
    ///
    wxPersistentTLWEx(wxTopLevelWindow *mgr) : wxPersistentWindow<wxTopLevelWindow>(mgr)
    {
    }

    ///
    /// \returns `wxT(wxPERSIST_TLW_KIND)`
    ///
    virtual wxString GetKind() const wxOVERRIDE
    {
        return wxT(wxPERSIST_TLW_KIND);
    }

    ///
    /// Saves dialog state
    ///
    virtual void Save() const wxOVERRIDE
    {
        const wxTopLevelWindow * const wnd = Get();

        wxTLWGeometryEx geom;
        if (geom.GetFrom(wnd))
            geom.Save(*this);
    }

    ///
    /// Restores dialog state
    ///
    virtual bool Restore() wxOVERRIDE
    {
        wxTopLevelWindow * const wnd = Get();

        wxTLWGeometryEx geom;
        if (!geom.Restore(*this))
            return false;

        return geom.ApplyTo(wnd);
    }

private:
    wxDECLARE_NO_COPY_CLASS(wxPersistentTLWEx);

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

/// @}
