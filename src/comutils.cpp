/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2022 Amebis
    Copyright © 2016 GÉANT
*/

#include "pch.h"


//////////////////////////////////////////////////////////////////////////
// wxCoInitializer
//////////////////////////////////////////////////////////////////////////

wxCoInitializer::wxCoInitializer(DWORD dwCoInit)
{
    HRESULT hr = ::CoInitializeEx(NULL, dwCoInit);

    m_initialized = SUCCEEDED(hr);
    m_ok          = SUCCEEDED(hr) || hr == RPC_E_CHANGED_MODE;
}


wxCoInitializer::~wxCoInitializer()
{
    if (m_initialized)
        ::CoUninitialize();
}
