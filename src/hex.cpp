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


size_t WXEXTEND_API wxHexEncode(char *dst, size_t dstLen, const void *src_, size_t srcLen)
{
    wxCHECK_MSG( src_, wxCONV_FAILED, wxT("NULL input buffer") );

    const unsigned char *src = reinterpret_cast<const unsigned char *>(src_);

    static const char bhex[] = "0123456789ABCDEF";

    size_t encLen = 0;

    for ( ; srcLen; srcLen--, src++) {
        encLen += 2;
        if ( dst )
        {
            if ( encLen > dstLen )
                return wxCONV_FAILED;

            *dst++ = bhex[src[0] >> 4];
            *dst++ = bhex[src[0] & 0x0f];
        }
    }

    return encLen;
}


size_t WXEXTEND_API wxHexDecode(void *dst_, size_t dstLen, const char *src, size_t srcLen, wxHexDecodeMode mode, size_t *posErr)
{
    wxCHECK_MSG( src, wxCONV_FAILED, wxT("NULL input buffer") );

    unsigned char *dst = reinterpret_cast<unsigned char *>(dst_);

    size_t decLen = 0;

    if ( srcLen == wxNO_LEN )
        srcLen = strlen(src);

    // we decode input by groups of 2 characters but things are complicated by
    // the fact that there can be whitespace and other junk in it too so keep
    // record of where exactly we're inside the current pair in this var
    int n = 0;
    unsigned char in = 0; // current pair
    const char *p;
    for ( p = src; srcLen; p++, srcLen-- )
    {
        const unsigned char c = *reinterpret_cast<const unsigned char*>(p);
             if ( '0' <= c && c <= '9' ) in = (in << 4) | (c - '0')     , n++;
        else if ( 'A' <= c && c <= 'F' ) in = (in << 4) | (c - 'A' + 10), n++;
        else if ( 'a' <= c && c <= 'f' ) in = (in << 4) | (c - 'a' + 10), n++;
        else {
            if ( mode == wxHexDecodeMode::Relaxed ||
                 mode == wxHexDecodeMode::SkipWS && isspace(c) )
                continue;

            if ( posErr )
                *posErr = p - src;

            return wxCONV_FAILED;
        }

        if ( n == 2 )
        {
            // got entire block, save
            decLen++;
            if ( dst )
            {
                if ( decLen > dstLen )
                    return wxCONV_FAILED;

                *dst++ = in;
            }

            in = 0;
            n = 0;
        }
    }

    return decLen;
}


wxMemoryBuffer WXEXTEND_API wxHexDecode(const char *src, size_t srcLen, wxHexDecodeMode mode, size_t *posErr)
{
    wxMemoryBuffer buf;
    wxCHECK_MSG( src, buf, wxT("NULL input buffer") );

    if ( srcLen == wxNO_LEN )
        srcLen = strlen(src);

    size_t len = wxHexDecodedSize(srcLen);
    len = wxHexDecode(buf.GetWriteBuf(len), len, src, srcLen, mode, posErr);
    if ( len == wxCONV_FAILED )
        len = 0;

    buf.SetDataLen(len);

    return buf;
}
