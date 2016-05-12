/*
    Copyright 2015-2016 Amebis

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

#include <wx/valnum.h>


///
/// Bit masks used for hexadecimal validator styles.
///
enum wxHexValidatorStyle
{
    // Do not use values used by wxNumValidatorStyle flags, since this is the extension.
    wxNUM_VAL_HEX_LOWERCASE = 0x1000,
};


///
/// Base class for hexadecimal validator
///
class WXEXTEND_API wxHexValidatorBase : public wxIntegerValidatorBase
{
protected:
    wxHexValidatorBase(int style);
    wxHexValidatorBase(const wxHexValidatorBase& other);

    bool IsMinusOk(const wxString& val, int pos) const;

    static bool FromString(const wxString& s, long *value);
#ifdef wxHAS_LONG_LONG_T_DIFFERENT_FROM_LONG
    static bool FromString(const wxString &s, wxLongLong_t *value);
#endif
    wxString ToString(LongestValueType value) const;

private:
    virtual bool IsCharOk(const wxString& val, int pos, wxChar ch) const;
};


///
/// Validator for hexadecimal entries
///
template <typename T>
class wxHexValidator : public wxPrivate::wxNumValidator<wxHexValidatorBase, T>
{
public:
    typedef wxPrivate::wxNumValidator<wxHexValidatorBase, T> Base;

    wxHexValidator(ValueType *value = NULL, int style = wxNUM_VAL_DEFAULT) : Base(value, style)
    {
        this->DoSetMin(std::numeric_limits<ValueType>::min());
        this->DoSetMax(std::numeric_limits<ValueType>::max());
    }

    virtual wxObject *Clone() const { return new wxHexValidator(*this); }

private:
    wxDECLARE_NO_ASSIGN_CLASS(wxHexValidator);
};
