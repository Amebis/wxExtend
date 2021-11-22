/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2021 Amebis
    Copyright © 2016 GÉANT
*/

#include "pch.h"


_Use_decl_annotations_
bool WXEXTEND_API wxXmlHashNode(wxCryptoHash &hash, const wxXmlNode *node)
{
    wxASSERT_MSG(node, wxT("invalid parameter"));

    #pragma warning(suppress: 26812) // wxXmlNodeType is unscoped.
    switch (node->GetType()) {
    case wxXML_ELEMENT_NODE:
        {
            {
                static const BYTE element_in[] = "<";

                // Hash the open tag.
                wxCHECK(hash.Hash(element_in, _countof(element_in) - 1), false);
                wxCHECK(hash.HashAsUTF8(node->GetName()), false);
                for (wxXmlAttribute *attr = node->GetAttributes(); attr; attr = attr->GetNext()) {
                    static const BYTE attrib_sep[] = " ";

                    wxCHECK(hash.Hash(attrib_sep, _countof(attrib_sep) - 1), false);
                    wxCHECK(hash.HashAsUTF8(attr->GetName()), false);
                    wxString value = attr->GetValue();
                    if (!value.IsEmpty()) {
                        static const BYTE
                            attrval_in [] = "=\"",
                            attrval_out[] = "\"";

                        wxCHECK(hash.Hash(attrval_in, _countof(attrval_in) - 1), false);
                        wxCHECK(hash.HashAsUTF8(wxXmlEscapeAttr(value)), false);
                        wxCHECK(hash.Hash(attrval_out, _countof(attrval_out) - 1), false);
                    }
                }
            }

            wxXmlNode *child = node->GetChildren();
            if (child) {
                static const BYTE
                    element_out [] = ">",
                    elemclose_in[] = "</";

                // Hash the open tag closing.
                wxCHECK(hash.Hash(element_out, _countof(element_out) - 1), false);

                // Hash the children.
                for (; child; child = child->GetNext())
                    wxCHECK(wxXmlHashNode(hash, child), false);

                // Hash the closing tag.
                wxCHECK(hash.Hash(elemclose_in, _countof(elemclose_in) - 1), false);
                wxCHECK(hash.HashAsUTF8(node->GetName()), false);
                wxCHECK(hash.Hash(element_out, _countof(element_out) - 1), false);
            } else {
                static const BYTE element_out [] = "/>";

                // Hash the childless element tag closing.
                wxCHECK(hash.Hash(element_out, _countof(element_out) - 1), false);
            }

            break;
        }

    case wxXML_TEXT_NODE:
        {
            wxCHECK(hash.HashAsUTF8(wxXmlEscapeText(node->GetContent())), false);
            break;
        }

    case wxXML_CDATA_SECTION_NODE:
        {
            static const BYTE
                cdata_in [] = "<![CDATA[",
                cdata_out[] = "]]>";

            wxCHECK(hash.Hash(cdata_in, _countof(cdata_in) - 1), false);
            wxCHECK(hash.HashAsUTF8(node->GetContent()), false);
            wxCHECK(hash.Hash(cdata_out, _countof(cdata_out) - 1), false);

            break;
        }

    case wxXML_COMMENT_NODE:
        {
            wxCHECK(hash.HashAsUTF8(node->GetContent()), false);
            break;
        }

    case wxXML_DOCUMENT_NODE:
        {
            // Hash the children.
            for (wxXmlNode *child = node->GetChildren(); child; child = child->GetNext())
                wxCHECK(wxXmlHashNode(hash, child), false);

            break;
        }

    default:
        wxFAIL_MSG(wxT("unsupported XML node type"));
        return false;
    }

    return true;
}
