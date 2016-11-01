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

#include "common.h"

#include <wx/object.h>


///
/// Helper template for event user data
///
template <class T>
class wxObjectWithData : public wxObject
{
public:
    ///
    /// Default constructor
    ///
    inline wxObjectWithData() {}

    ///
    /// Construct object with data
    ///
    /// \param[in] data  Data to initialize object with
    ///
    inline wxObjectWithData(const T &data) : m_data(data) {}

    ///
    /// Construct object with data
    ///
    /// \param[in] data  Data to move to object
    ///
    inline wxObjectWithData(T &&data) : m_data(std::move(data)) {}

public:
    T m_data;   ///< Data
};
