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
#include <wx/valnum.h>
#pragma warning(pop)

/// \addtogroup wxExtend
/// @{

///
/// Bit masks used for hexadecimal validator styles.
///
enum wxHexValidatorStyle
{
    // Do not use values used by wxNumValidatorStyle flags, since this is the extension.
    wxNUM_VAL_HEX_LOWERCASE = 0x1000,
};


#ifdef __VISUALC__
// non dll-interface class 'xxx' used as base for dll-interface class 'yyy'
#pragma warning (push)
#pragma warning (disable:4275)
#endif

///
/// Base class for hexadecimal validator
///
class WXEXTEND_API wxHexValidatorBase : public wxIntegerValidatorBase
{
protected:
    ///
    /// Constructs new hexadecimal validator
    ///
    wxHexValidatorBase(int style);

    ///
    /// Copies a hexadecimal validator
    ///
    wxHexValidatorBase(const wxHexValidatorBase& other);

    ///
    /// Tests whether minus is acceptable at given position
    ///
    /// \returns Always `false`
    ///
    bool IsMinusOk(const wxString& val, int pos) const;

    ///
    /// Converts string to long
    ///
    static bool FromString(const wxString& s, long *value);

#ifdef wxHAS_LONG_LONG_T_DIFFERENT_FROM_LONG
    ///
    /// Converts string to long long
    ///
    static bool FromString(const wxString &s, wxLongLong_t *value);
#endif

    ///
    /// Converts number to string
    ///
    wxString ToString(LongestValueType value) const;

protected:
    /// \cond internal
    void DoSetWidth(unsigned int width) { m_width = width; }
    /// \endcond

private:
    /// \cond internal
    virtual bool IsCharOk(const wxString& val, int pos, wxChar ch) const;
    /// \endcond

private:
    unsigned int m_width;    ///< Preferred width of the string - zero padding (<=1 disables padding)
};

#ifdef __VISUALC__
#pragma warning(pop)
#endif


///
/// Validator for hexadecimal entries
///
template <typename T>
class wxHexValidator : public wxPrivate::wxNumValidator<wxHexValidatorBase, T>
{
public:
    typedef wxPrivate::wxNumValidator<wxHexValidatorBase, T> Base; ///< Base class type

    ///
    /// Constructs new hexadecimal validator
    ///
    wxHexValidator(T *value = NULL, int style = wxNUM_VAL_DEFAULT, unsigned int width = 0) : Base(value, style)
    {
        this->DoSetWidth(width);
        this->DoSetMin(std::numeric_limits<T>::min());
        this->DoSetMax(std::numeric_limits<T>::max());
    }

    ///
    /// Clones this validator
    ///
    virtual wxObject *Clone() const { return new wxHexValidator(*this); }

private:
    wxDECLARE_NO_ASSIGN_CLASS(wxHexValidator);
};

/// @}
