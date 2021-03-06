﻿/*
    Copyright 2016-2020 Amebis
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

#include "common.h"

/// \addtogroup wxExtend
/// @{

///
/// Create an object of this class on stack to initialize/cleanup the COM automatically.
///
class WXEXTEND_API wxCoInitializer
{
public:
    ///
    /// Initialize the COM
    ///
    /// \param[in] dwCoInit  The concurrency model and initialization options for the thread to pass to `CoInitializeEx()`
    ///
    wxCoInitializer(DWORD dwCoInit = COINIT_MULTITHREADED);

    ///
    /// Dtor clean up
    ///
    virtual ~wxCoInitializer();
    
    ///
    /// Has the initialization been successful? (explicit test)
    ///
    /// \returns
    /// - \c true if initialization succeeded
    /// - \c false otherwise
    ///
    bool IsOk() const { return m_ok; }

    ///
    /// Has the initialization been successful? (implicit test)
    ///
    /// \returns
    /// - \c true if initialization succeeded
    /// - \c false otherwise
    ///
    operator bool() const { return m_ok; }

private:
    bool m_ok, m_initialized;
};

/// @}
