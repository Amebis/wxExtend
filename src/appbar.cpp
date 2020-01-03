/*
    Copyright 2015-2020 Amebis
    Copyright 2016 GÉANT
    Based on code written by Jeffrey Richter.

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


//////////////////////////////////////////////////////////////////////////
// wxAppBarFrame
//////////////////////////////////////////////////////////////////////////

wxAppBarFrame::wxAppBarFrame()
{
}


wxAppBarFrame::wxAppBarFrame(wxWindow *parent, wxWindowID id, const wxString& title, wxAppBarState state, int flags, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, title, state, flags, pos, size, style, name);
}


bool wxAppBarFrame::Create(wxWindow *parent, wxWindowID id, const wxString& title, wxAppBarState state, int flags, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    // Modify parameters if required.
    PreCreate(state, flags, size, style);

    // Create frame.
    wxCHECK(wxAppBar<wxFrame>::Create(parent, id, title, pos, size, style, name), false);

    return true;
}


//////////////////////////////////////////////////////////////////////////
// wxAppBarDialog
//////////////////////////////////////////////////////////////////////////

wxAppBarDialog::wxAppBarDialog()
{
}


wxAppBarDialog::wxAppBarDialog(wxWindow *parent, wxWindowID id, const wxString& title, wxAppBarState state, int flags, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    Create(parent, id, title, state, flags, pos, size, style, name);
}


bool wxAppBarDialog::Create(wxWindow *parent, wxWindowID id, const wxString& title, wxAppBarState state, int flags, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
    // Modify parameters if required.
    PreCreate(state, flags, size, style);

    // Create dialog.
    wxCHECK(wxAppBar<wxDialog>::Create(parent, id, title, pos, size, style, name), false);

    return true;
}
