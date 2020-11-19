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

#include "pch.h"


size_t WXEXTEND_API wxURLEncode(char *dst, size_t dstLen, const char *src, size_t srcLen)
{
    wxCHECK_MSG(src, wxCONV_FAILED, wxT("NULL input buffer"));

    static const char bhex[] = "0123456789ABCDEF";

    size_t encLen = 0;

    for (size_t i = 0; i < srcLen && src[i]; i++) {
        if (wxURLIsProtected(src[i])) {
            encLen += 3;
            if ( dst )
            {
                if ( encLen > dstLen )
                    return wxCONV_FAILED;

                *dst++ = '%';
                *dst++ = bhex[((unsigned char)src[i]) >> 4];
                *dst++ = bhex[((unsigned char)src[i]) & 0x0f];
            }
        } else {
            encLen ++;
            if ( dst )
            {
                if ( encLen > dstLen )
                    return wxCONV_FAILED;

                *dst++ = src[i];
            }
        }
    }

    // Zero terminate.
    if ( dst && encLen < dstLen )
        *dst++ = 0;

    return encLen;
}


size_t WXEXTEND_API wxURLDecode(char *dst, size_t dstLen, const char *src, size_t srcLen)
{
    wxCHECK_MSG(src, wxCONV_FAILED, wxT("NULL input buffer"));

    static const char bhex[] = "0123456789ABCDEF";

    size_t i, decLen = 0;

    for (i = 0 ; i < srcLen && src[i];) {
        decLen ++;
        if (src[i] == '%') {
            // Decode % escaped hex value to character.
            char c = 0;
            size_t j = i + 1;
            for (size_t j_max = i + 3; j < j_max && j < srcLen; j++) {
                char x = src[j];
                c <<= 4;
                     if ('0' <= x && x <= '9') c += x - '0';
                else if ('A' <= x && x <= 'F') c += x - 'A' + 10;
                else if ('a' <= x && x <= 'f') c += x - 'a' + 10;
                else break;
            }

            if (c) {
                if ( dst )
                {
                    if ( decLen > dstLen )
                        return wxCONV_FAILED;

                    *dst++ = c;
                }

                i = j;
                continue;
            }
        }

        if ( dst )
        {
            if ( decLen > dstLen )
                return wxCONV_FAILED;

            *dst++ = src[i];
        }
        i++;
    }

    // Zero terminate.
    if ( dst && decLen < dstLen )
        *dst++ = 0;

    return decLen;
}


wxMemoryBuffer WXEXTEND_API wxURLDecode(const char *src, size_t srcLen)
{
    wxMemoryBuffer buf;
    wxCHECK_MSG( src, buf, wxT("NULL input buffer") );

    if ( srcLen == wxNO_LEN )
        srcLen = strlen(src);

    size_t len = wxURLDecodedSize(srcLen);
    len = wxURLDecode(reinterpret_cast<char*>(buf.GetWriteBuf(len)), len, src, srcLen);
    if ( len == wxCONV_FAILED )
        len = 0;

    buf.SetDataLen(len);

    return buf;
}
