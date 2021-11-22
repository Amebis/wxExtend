/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2021 Amebis
    Copyright © 2016 GÉANT
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
