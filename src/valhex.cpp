/*
    Copyright 2015-2020 Amebis
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

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////////
// wxHexValidatorBase
//////////////////////////////////////////////////////////////////////////

wxHexValidatorBase::wxHexValidatorBase(int style) :
    m_width(0),
    wxIntegerValidatorBase(style)
{
}


wxHexValidatorBase::wxHexValidatorBase(const wxHexValidatorBase& other) :
    m_width(other.m_width),
    wxIntegerValidatorBase(other)
{
}


bool wxHexValidatorBase::IsMinusOk(const wxString& /*val*/, int /*pos*/) const
{
    // Minus is never OK with hexadecimal numbers.
    return false;
}


bool wxHexValidatorBase::FromString(const wxString& s, long *value)
{
    return s.ToLong(value, 16);
}


#ifdef wxHAS_LONG_LONG_T_DIFFERENT_FROM_LONG

bool wxHexValidatorBase::FromString(const wxString &s, wxLongLong_t *value)
{
    return s.ToLongLong(value, 16);
}

#endif // wxHAS_LONG_LONG_T_DIFFERENT_FROM_LONG

wxString wxHexValidatorBase::ToString(LongestValueType value) const
{
    const wxStringCharType hexa = (HasFlag((wxNumValidatorStyle)wxNUM_VAL_HEX_LOWERCASE) ? wxT('a') : wxT('A')) - 0xa;
    unsigned int offset = sizeof(LongestValueType)*8 - 4, offset_s = m_width*4 - 4;
    wxULongLong_t m = ((wxULongLong_t)0xf) << offset;
    unsigned int x = 0;

    // Skip leading zeros.
    while (m && !x && offset >= offset_s) {
        x = (unsigned int)((m & (wxULongLong_t)value) >> offset);
        m >>= 4, offset -= 4;
    }

    // First digit.
    wxString str(1, (wxStringCharType)((x < 0xa ? wxT('0') : hexa) + x));

    // Rest of the digits.
    while (m) {
        x = (unsigned int)((m & (wxULongLong_t)value) >> offset);
        m >>= 4, offset -= 4;
        str += (wxStringCharType)((x < 0xa ? wxT('0') : hexa) + x);
    }

    return str;
}


/// \cond internal
bool wxHexValidatorBase::IsCharOk(const wxString& val, int pos, wxChar ch) const
{
    // We only accept hexadecimal digits here.
    if ((ch < '0' || ch > '9') && (ch < 'A' || ch > 'F') && (ch < 'a' || ch > 'f'))
        return false;

    // And the value after insertion needs to be in the defined range.
    LongestValueType value;
    if (!FromString(GetValueAfterInsertingChar(val, pos, ch), &value))
        return false;

    return IsInRange(value);
}
/// \endcond
