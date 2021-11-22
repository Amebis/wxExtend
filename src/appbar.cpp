/*
    ​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2021 Amebis
    Copyright © 2016 GÉANT
    Based on code written by Jeffrey Richter.
*/

#include "pch.h"


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
