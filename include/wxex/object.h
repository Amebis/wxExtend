/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2022 Amebis
    Copyright © 2016 GÉANT
*/

#pragma once

#include "common.h"

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: WXWIDGETS_CODE_ANALYSIS_WARNINGS)
#include <wx/object.h>
#pragma warning(pop)


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
