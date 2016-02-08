/*
    Copyright 2016 Amebis

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

#include "common.h"

#include <wx/app.h>
#include <wx/intl.h>


///
/// Extended application
///
class wxAppEx : public wxApp
{
public:
    ///
    /// Called when application initializes.
    ///
    /// \returns
    /// - true if initialization succeeded
    /// - false otherwise
    virtual bool OnInit();

protected:
    wxLocale m_locale; ///< Current locale
};