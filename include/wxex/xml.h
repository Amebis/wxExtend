/*
    Copyright 2016 Amebis

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

#include "crypto.h"
#include "common.h"

#include <wx/string.h>
#include <wx/xml/xml.h>


///
/// Escapes text string for XML insertion
///
/// \param[in] str  Text string
/// \returns Escaped string
///
inline wxString wxXmlEscapeText(_In_ const wxString& str)
{
    wxString escaped;
    escaped.reserve(str.length());

    for (wxString::const_iterator i = str.begin(); i != str.end(); ++i) {
        const wxChar c = *i;
        switch (c) {
            case wxS('<'):
                escaped.append(wxS("&lt;"));
                break;
            case wxS('>'):
                escaped.append(wxS("&gt;"));
                break;
            case wxS('&'):
                escaped.append(wxS("&amp;"));
                break;
            case wxS('\r'):
                escaped.append(wxS("&#xD;"));
                break;
            default:
                escaped.append(c);
        }
    }

    return escaped;
}


///
/// Escapes attribute value string for XML insertion
///
/// \param[in] str  Attribute value
///
/// \returns Escaped string
///
inline wxString wxXmlEscapeAttr(_In_ const wxString& str)
{
    wxString escaped;
    escaped.reserve(str.length());

    for (wxString::const_iterator i = str.begin(); i != str.end(); ++i) {
        const wxChar c = *i;
        switch (c) {
            case wxS('<'):
                escaped.append(wxS("&lt;"));
                break;
            case wxS('>'):
                escaped.append(wxS("&gt;"));
                break;
            case wxS('&'):
                escaped.append(wxS("&amp;"));
                break;
            case wxS('\r'):
                escaped.append(wxS("&#xD;"));
                break;
            case wxS('"'):
                escaped.append(wxS("&quot;"));
                break;
            case wxS('\t'):
                escaped.append(wxS("&#x9;"));
                break;
            case wxS('\n'):
                escaped.append(wxS("&#xA;"));
                break;
            default:
                escaped.append(c);
        }
    }

    return escaped;
}



///
/// Calculates hash of the node and all its children
///
/// \param[in] hash  Handle of a hash object
/// \param[in] node  Root node
///
///
bool WXEXTEND_API wxXmlHashNode(_In_ wxCryptoHash &hash, const wxXmlNode *node);
