﻿/*
    ​​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2016-2022 Amebis
    Copyright © 2016 GÉANT
*/

#pragma once

#include "common.h"

#include "crypto.h"

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: WXWIDGETS_CODE_ANALYSIS_WARNINGS)
#include <wx/string.h>
#include <wx/xml/xml.h>
#pragma warning(pop)

/// \addtogroup wxExtend
/// @{

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

    for (auto i = str.begin(); i != str.end(); ++i) {
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

    for (auto i = str.begin(); i != str.end(); ++i) {
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
bool WXEXTEND_API wxXmlHashNode(_In_ wxCryptoHash &hash, _In_ const wxXmlNode *node);

/// @}
