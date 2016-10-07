/*
    Copyright 2016 Amebis
    Copyright 2016 G�ANT

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


//////////////////////////////////////////////////////////////////////
// wxHostNameValidator
//////////////////////////////////////////////////////////////////////

wxIMPLEMENT_DYNAMIC_CLASS(wxHostNameValidator, wxValidator);


wxHostNameValidator::wxHostNameValidator(wxString *val) :
    m_val(val),
    wxValidator()
{
}


wxObject* wxHostNameValidator::Clone() const
{
    return new wxHostNameValidator(*this);
}


bool wxHostNameValidator::Validate(wxWindow *parent)
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();
    if (!ctrl->IsEnabled()) return true;

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, parent);
}


bool wxHostNameValidator::TransferToWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));

    if (m_val)
        ((wxTextCtrl*)GetWindow())->SetValue(*m_val);

    return true;
}


bool wxHostNameValidator::TransferFromWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, NULL, m_val);
}


bool wxHostNameValidator::Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, wxString *val_out)
{
    const wxStringCharType *buf = val_in;

    size_t i = i_start;
    for (;;) {
        if (i >= i_end) {
            // End of host name found.
            if (val_out) val_out->assign(val_in.c_str() + i_start, i - i_start);
            return true;
        } else if (buf[i] == _T('-') || buf[i] == _T('_') || buf[i] == _T('*') || _istalnum(buf[i])) {
            // Valid character found.
            i++;
        } else {
            // Invalid character found.
            ctrl->SetFocus();
            ctrl->SetSelection(i, i + 1);
            wxMessageBox(wxString::Format(_("Invalid character in host name found: %c"), buf[i]), _("Validation conflict"), wxOK | wxICON_EXCLAMATION, parent);
            return false;
        }
    }
}


//////////////////////////////////////////////////////////////////////
// wxFQDNValidator
//////////////////////////////////////////////////////////////////////

wxIMPLEMENT_DYNAMIC_CLASS(wxFQDNValidator, wxValidator);


wxFQDNValidator::wxFQDNValidator(wxString *val) :
    m_val(val),
    wxValidator()
{
}


wxObject* wxFQDNValidator::Clone() const
{
    return new wxFQDNValidator(*this);
}


bool wxFQDNValidator::Validate(wxWindow *parent)
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();
    if (!ctrl->IsEnabled()) return true;

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, parent);
}


bool wxFQDNValidator::TransferToWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));

    if (m_val)
        ((wxTextCtrl*)GetWindow())->SetValue(*m_val);

    return true;
}


bool wxFQDNValidator::TransferFromWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, NULL, m_val);
}


bool wxFQDNValidator::Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, wxString *val_out)
{
    const wxStringCharType *buf = val_in;

    size_t i = i_start;
    for (;;) {
        const wxStringCharType *buf_next;
        if ((buf_next = wmemchr(buf + i, L'.', i_end - i)) != NULL) {
            // FQDN separator found.
            if (!wxHostNameValidator::Parse(val_in, i, buf_next - buf, ctrl, parent))
                return false;
            i = buf_next - buf + 1;
        } else if (wxHostNameValidator::Parse(val_in, i, i_end, ctrl, parent)) {
            // The rest of the FQDN parsed succesfully.
            if (val_out) val_out->assign(val_in.c_str() + i_start, i_end - i_start);
            return true;
        } else
            return false;
    }
}


//////////////////////////////////////////////////////////////////////
// wxFQDNListValidator
//////////////////////////////////////////////////////////////////////

wxIMPLEMENT_DYNAMIC_CLASS(wxFQDNListValidator, wxValidator);


wxFQDNListValidator::wxFQDNListValidator(wxArrayString *val) :
    m_val(val),
    wxValidator()
{
}


wxObject* wxFQDNListValidator::Clone() const
{
    return new wxFQDNListValidator(*this);
}


bool wxFQDNListValidator::Validate(wxWindow *parent)
{
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();
    if (!ctrl->IsEnabled()) return true;

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, parent);
}


bool wxFQDNListValidator::TransferToWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));

    if (m_val) {
        wxString str;
        for (wxArrayString::const_iterator name = m_val->begin(), name_end = m_val->end(); name != name_end; ++name) {
            if (!str.IsEmpty()) str += wxT("; ");
            str += *name;
        }
        ((wxTextCtrl*)GetWindow())->SetValue(str);
    }

    return true;
}


bool wxFQDNListValidator::TransferFromWindow()
{
    wxASSERT(GetWindow()->IsKindOf(CLASSINFO(wxTextCtrl)));
    wxTextCtrl *ctrl = (wxTextCtrl*)GetWindow();

    wxString val(ctrl->GetValue());
    return Parse(val, 0, val.Length(), ctrl, NULL, m_val);
}


bool wxFQDNListValidator::Parse(const wxString &val_in, size_t i_start, size_t i_end, wxTextCtrl *ctrl, wxWindow *parent, wxArrayString *val_out)
{
    const wxStringCharType *buf = val_in;
    wxString _fqdn, *fqdn = val_out ? &_fqdn : NULL;
    wxArrayString _val_out;

    size_t i = i_start;
    for (;;) {
        // Skip initial white-space.
        for (; i < i_end && _istspace(buf[i]); i++);

        const wxStringCharType *buf_next;
        if ((buf_next = wmemchr(buf + i, L';', i_end - i)) != NULL) {
            // FQDN list separator found.

            // Skip trailing white-space.
            size_t i_next = buf_next - buf;
            for (; i < i_next && _istspace(buf[i_next - 1]); i_next--);

            if (!wxFQDNValidator::Parse(val_in, i, i_next, ctrl, parent, fqdn))
                return false;
            if (fqdn && !fqdn->empty()) _val_out.push_back(std::move(*fqdn));

            i = buf_next - buf + 1;
        } else {
            // Skip trailing white-space.
            for (; i < i_end && _istspace(buf[i_end - 1]); i_end--);

            if (wxFQDNValidator::Parse(val_in, i, i_end, ctrl, parent, fqdn)) {
                // The rest of the FQDN list parsed succesfully.
                if (fqdn && !fqdn->empty()) _val_out.push_back(std::move(*fqdn));
                if (val_out) *val_out = std::move(_val_out);
                return true;
            } else
                return false;
        }
    }
}
