/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2022 Amebis
    Copyright © 2016 GÉANT
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
