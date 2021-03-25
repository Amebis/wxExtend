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
