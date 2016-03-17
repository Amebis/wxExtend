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

#include "stdafx.h"


static inline BOOL CryptHashData(__in HCRYPTHASH hHash, __in const wxString &str, __in DWORD dwFlags)
{
    const wxScopedCharBuffer buf(str.ToUTF8());
    return ::CryptHashData(hHash, (const BYTE*)buf.data(), buf.length(), dwFlags);
}


void WXEXTEND_API wxXmlHashNode(_In_ HCRYPTHASH hash, const wxXmlNode *node)
{
    wxASSERT_MSG(node, wxT("invalid parameter"));

    switch (node->GetType()) {
    case wxXML_ELEMENT_NODE:
        {
            {
                static const BYTE element_in[] = "<";

                // Hash the open tag.
                wxVERIFY(::CryptHashData(hash, element_in, _countof(element_in) - 1, 0));
                wxVERIFY(::CryptHashData(hash, node->GetName(), 0));
                for (wxXmlAttribute *attr = node->GetAttributes(); attr; attr = attr->GetNext()) {
                    static const BYTE attrib_sep[] = " ";

                    wxVERIFY(::CryptHashData(hash, attrib_sep, _countof(attrib_sep) - 1, 0));
                    wxVERIFY(::CryptHashData(hash, attr->GetName(), 0));
                    wxString value = attr->GetValue();
                    if (!value.IsEmpty()) {
                        static const BYTE
                            attrval_in [] = "=\"",
                            attrval_out[] = "\"";

                        wxVERIFY(::CryptHashData(hash, attrval_in, _countof(attrval_in) - 1, 0));
                        wxVERIFY(::CryptHashData(hash, wxXmlEscapeAttr(value), 0));
                        wxVERIFY(::CryptHashData(hash, attrval_out, _countof(attrval_out) - 1, 0));
                    }
                }
            }

            wxXmlNode *child = node->GetChildren();
            if (child) {
                static const BYTE
                    element_out [] = ">",
                    elemclose_in[] = "</";

                // Hash the open tag closing.
                wxVERIFY(::CryptHashData(hash, element_out, _countof(element_out) - 1, 0));

                // Hash the children.
                for (; child; child = child->GetNext())
                    wxXmlHashNode(hash, child);

                // Hash the closing tag.
                wxVERIFY(::CryptHashData(hash, elemclose_in, _countof(elemclose_in) - 1, 0));
                wxVERIFY(::CryptHashData(hash, node->GetName(), 0));
                wxVERIFY(::CryptHashData(hash, element_out, _countof(element_out) - 1, 0));
            } else {
                static const BYTE element_out [] = "/>";

                // Hash the childless element tag closing.
                wxVERIFY(::CryptHashData(hash, element_out, _countof(element_out) - 1, 0));
            }

            break;
        }

    case wxXML_TEXT_NODE:
        {
            wxVERIFY(::CryptHashData(hash, wxXmlEscapeText(node->GetContent()), 0));
            break;
        }

    case wxXML_CDATA_SECTION_NODE:
        {
            static const BYTE
                cdata_in [] = "<![CDATA[",
                cdata_out[] = "]]>";

            wxVERIFY(::CryptHashData(hash, cdata_in, _countof(cdata_in) - 1, 0));
            wxVERIFY(::CryptHashData(hash, node->GetContent(), 0));
            wxVERIFY(::CryptHashData(hash, cdata_out, _countof(cdata_out) - 1, 0));

            break;
        }

    case wxXML_COMMENT_NODE:
        {
            wxVERIFY(::CryptHashData(hash, node->GetContent(), 0));
            break;
        }

    case wxXML_DOCUMENT_NODE:
        {
            // Hash the children.
            for (wxXmlNode *child = node->GetChildren(); child; child = child->GetNext())
                wxXmlHashNode(hash, child);

            break;
        }

    default:
        wxFAIL_MSG(wxT("unsupported XML node type"));
    }
}
