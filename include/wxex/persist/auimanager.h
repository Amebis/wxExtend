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

#pragma once

#include "../common.h"

#include "../aui/framemanager.h"

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: WXWIDGETS_CODE_ANALYSIS_WARNINGS)
#include <wx/persist.h>
#include <wx/aui/framemanager.h>
#pragma warning(pop)


/// \addtogroup wxExtend
/// @{

///
/// `wxPersistentAuiManager` kind for persistent storage
///
#define wxPERSIST_AUIMGR_KIND "AuiManager"

///
/// Name of the persistent storage variable for saving Aui manager state
///
#define wxPERSIST_AUIMGR_PERSPECTIVE "perspective"

///
/// Supports saving/restoring wxAuiManager state
///
class wxPersistentAuiManager : public wxPersistentObject
{
public:
    ///
    /// Constructs a persistent Aui manager object
    ///
    wxPersistentAuiManager(wxAuiManager *mgr) : wxPersistentObject(mgr)
    {
    }

    ///
    /// \returns `wxT(wxPERSIST_AUIMGR_KIND)`
    ///
    virtual wxString GetKind() const wxOVERRIDE
    {
        return wxT(wxPERSIST_AUIMGR_KIND);
    }

    ///
    /// Returns name of the window
    ///
    virtual wxString GetName() const wxOVERRIDE
    {
        // Borrow the name of wxAguiManager from its window.
        return GetManager()->GetManagedWindow()->GetName();
    }

    ///
    /// Saves Aui manager state
    ///
    virtual void Save() const wxOVERRIDE
    {
        // Save perspective string to configuration.
        SaveValue(wxT(wxPERSIST_AUIMGR_PERSPECTIVE), GetManager()->SavePerspective());
    }

    ///
    /// Restores Aui manager state
    ///
    virtual bool Restore() wxOVERRIDE
    {
        // Load perspective string from configuration.
        wxString persp;
        if (!RestoreValue(wxT(wxPERSIST_AUIMGR_PERSPECTIVE), &persp))
            return false;

        // Update captions (see http://trac.wxwidgets.org/ticket/12528).
        wxAuiManager* mgr = GetManager();
        wxCHECK(wxAuiManagerUpdatePerspectiveCaptions(*mgr, persp), false);

        // Restore perspective.
        return mgr->LoadPerspective(persp);
    }

protected:
    /// \cond internal
    wxAuiManager *GetManager() const
    {
        return static_cast<wxAuiManager*>(GetObject());
    }
    /// \endcond

private:
    wxDECLARE_NO_COPY_CLASS(wxPersistentAuiManager);
};


///
/// wxAuiManager's instantiation of wxCreatePersistentObject template
///
inline wxPersistentObject *wxCreatePersistentObject(wxAuiManager *mgr)
{
    return new wxPersistentAuiManager(mgr);
}

/// @}
