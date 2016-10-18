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

#include "../aui/framemanager.h"

#include <wx/persist.h>
#include <wx/aui/framemanager.h>


// ----------------------------------------------------------------------------
// string constants used by wxPersistentAuiManager
// ----------------------------------------------------------------------------

#define wxPERSIST_AUIMGR_KIND "AuiManager"

// names for persistent options
#define wxPERSIST_AUIMGR_PERSPECTIVE "perspective"


///
/// Supports saving/restoring wxAuiManager state
///
class wxPersistentAuiManager : public wxPersistentObject
{
public:
    wxPersistentAuiManager(wxAuiManager *mgr) : wxPersistentObject(mgr)
    {
    }

    virtual wxString GetKind() const
    {
        return wxT(wxPERSIST_AUIMGR_KIND);
    }

    virtual wxString GetName() const
    {
        // Borrow the name of wxAguiManager from its window.
        return GetManager()->GetManagedWindow()->GetName();
    }

    virtual void Save() const
    {
        // Save perspective string to configuration.
        SaveValue(wxT(wxPERSIST_AUIMGR_PERSPECTIVE), GetManager()->SavePerspective());
    }

    virtual bool Restore()
    {
        // Load perspective string from configuration.
        wxString persp;
        wxCHECK(RestoreValue(wxT(wxPERSIST_AUIMGR_PERSPECTIVE), &persp), false);

        // Update captions (see http://trac.wxwidgets.org/ticket/12528).
        wxAuiManager* mgr = GetManager();
        wxCHECK(wxAuiManagerUpdatePerspectiveCaptions(*mgr, persp), false);

        // Restore perspective.
        return mgr->LoadPerspective(persp);
    }

protected:
    wxAuiManager *GetManager() const
    {
        return static_cast<wxAuiManager*>(GetObject());
    }

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
