/*
    ​​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2016-2022 Amebis
    Copyright © 2016 GÉANT
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
