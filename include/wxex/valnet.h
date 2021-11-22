/*
    ​​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2016-2021 Amebis
    Copyright © 2016 GÉANT
*/

#pragma once

#include "common.h"

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: WXWIDGETS_CODE_ANALYSIS_WARNINGS)
#include <wx/arrstr.h>
#include <wx/textctrl.h>
#include <wx/validate.h>
#pragma warning(pop)

/// \addtogroup wxExtend
/// @{

#ifdef __VISUALC__
// non dll-interface class 'xxx' used as base for dll-interface class 'yyy'
#pragma warning (push)
#pragma warning (disable:4275)
#endif

///
/// Validator for host name
///
class WXEXTEND_API wxHostNameValidator : public wxValidator
{
public:
    ///
    /// Construct the validator with a value to store data
    ///
    wxHostNameValidator(wxString *val = NULL);

    ///
    /// Copies this validator
    ///
    virtual wxObject* Clone() const;

    ///
    /// Validates the value
    ///
    virtual bool Validate(wxWindow *parent);

    ///
    /// Transfers the value to the window
    ///
    virtual bool TransferToWindow();

    ///
    /// Transfers the value from the window
    ///
    virtual bool TransferFromWindow();

    ///
    /// Parses FQDN value
    ///
    static bool Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, wxString *val_out = NULL);

protected:
    wxString *m_val; ///< Pointer to variable to receive control's parsed value

private:
    wxDECLARE_DYNAMIC_CLASS(wxHostNameValidator);
    wxDECLARE_NO_ASSIGN_CLASS(wxHostNameValidator);
};


///
/// Validator for FQDN
///
class WXEXTEND_API wxFQDNValidator : public wxValidator
{
public:
    ///
    /// Construct the validator with a value to store data
    ///
    wxFQDNValidator(wxString *val = NULL);

    ///
    /// Copies this validator
    ///
    virtual wxObject* Clone() const;

    ///
    /// Validates the value
    ///
    virtual bool Validate(wxWindow *parent);

    ///
    /// Transfers the value to the window
    ///
    virtual bool TransferToWindow();

    ///
    /// Transfers the value from the window
    ///
    virtual bool TransferFromWindow();

    ///
    /// Parses FQDN value
    ///
    static bool Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, wxString *val_out = NULL);

protected:
    wxString *m_val; ///< Pointer to variable to receive control's parsed value

private:
    wxDECLARE_DYNAMIC_CLASS(wxFQDNValidator);
    wxDECLARE_NO_ASSIGN_CLASS(wxFQDNValidator);
};


///
/// Validator for FQDN lists
///
class WXEXTEND_API wxFQDNListValidator : public wxValidator
{
public:
    ///
    /// Construct the validator with a value to store data
    ///
    wxFQDNListValidator(wxArrayString *val = NULL);

    ///
    /// Copies this validator
    ///
    virtual wxObject* Clone() const;

    ///
    /// Validates the value
    ///
    virtual bool Validate(wxWindow *parent);

    ///
    /// Transfers the value to the window
    ///
    virtual bool TransferToWindow();

    ///
    /// Transfers the value from the window
    ///
    virtual bool TransferFromWindow();

    ///
    /// Parses FQDN list value
    ///
    static bool Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, wxArrayString *val_out = NULL);

protected:
    wxArrayString *m_val;  ///< Pointer to variable to receive control's parsed value

private:
    wxDECLARE_DYNAMIC_CLASS(wxFQDNListValidator);
    wxDECLARE_NO_ASSIGN_CLASS(wxFQDNListValidator);
};

#ifdef __VISUALC__
#pragma warning(pop)
#endif

/// @}
