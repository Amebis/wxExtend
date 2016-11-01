/*
    Copyright 2015-2016 Amebis
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

#pragma once

#include "common.h"

#include "wx/string.h"
#include "wx/buffer.h"

/// \addtogroup wxExtend
/// @{

///
/// Test if given character should be protected for URL encoding
///
/// \param[in] chr  ASCII character
///
/// \returns
/// - \c true if character should be protected
/// - \c false otherwise
///
inline bool wxURLIsProtected(char chr)
{
    switch (chr) {
        case ' ':
        case '!':
        case '*':
        case '\'':
        case '(':
        case ')':
        case ';':
        case ':':
        case '@':
        case '&':
        case '=':
        case '+':
        case '$':
        case ',':
        case '/':
        case '?':
        case '#':
        case '[':
        case ']': return true;
    }

    return chr < 0x20;
}


///
/// Return the size needed for the buffer containing the encoded representation
/// of a string of given length
///
/// \param[in] len  Length of string (in bytes)
///
/// \returns Maximum encoded representation size (in characters)
///
inline size_t wxURLEncodedSize(size_t len)
{
    return len*3;
}


///
/// Raw URL encoding function which encodes the contents of a string of the
/// specified length into the buffer of the specified size
///
/// \param[out] dst     Destination buffer to receive URL encoded data
/// \param[in]  dstLen  Length of \p dst buffer (in characters)
/// \param[in]  src     Source string to encode
/// \param[in]  srcLen  Length of \p src string (in bytes)
///
/// \returns The length of the encoded data or wxCONV_FAILED if the buffer is not
/// large enough; to determine the needed size you can either allocate a buffer
/// of `wxURLEncodedSize(srcLen)` size or call the function with NULL string in
/// which case the required size will be returned
///
size_t WXEXTEND_API wxURLEncode(char *dst, size_t dstLen, const char *src, size_t srcLen);


///
/// URL encoding function which encodes the contents of a string of the
/// specified length into the wxString
///
/// \param[in]  src     Source string to encode
/// \param[in]  srcLen  Length of \p src string (in bytes)
///
/// \returns The URL encoded string
///
inline wxString wxURLEncode(const char *src, size_t srcLen)
{
    const size_t dstLen = wxURLEncodedSize(srcLen);
    wxCharBuffer dst(dstLen);
    dst.shrink(wxURLEncode(dst.data(), dstLen, src, srcLen));

    return dst;
}


///
/// URL encoding function which encodes the contents of a string into the wxString
///
/// \param[in]  str  Source string to encode
///
/// \returns The URL encoded string
///
inline wxString wxURLEncode(const wxString& str)
{
    return wxURLEncode(str.GetData(), str.Length());
}


///
/// URL encoding function which encodes the contents of a buffer into the wxString
///
/// \param[in]  buf  Source buffer to encode
///
/// \returns The URL encoded string
///
inline wxString wxURLEncode(const wxMemoryBuffer& buf)
{
    return wxURLEncode(reinterpret_cast<const char*>(buf.GetData()), buf.GetDataLen());
}


// ----------------------------------------------------------------------------
// Decoding Functions
// ----------------------------------------------------------------------------

///
/// Return the buffer size necessary for decoding a URL string of the given
/// length
///
/// \param[in] len  Length of the URL encoded string
///
/// \returns Maximum decoded representation size (in bytes)
///
inline size_t wxURLDecodedSize(size_t len)
{
    return len;
}

///
/// Raw decoding function which decodes the contents of the string of specified
/// length (or zero terminated by default) into the provided buffer of the given
/// size
///
/// \param[out] dst     Destination buffer to receive decoded data
/// \param[in]  dstLen  Length of \p dst buffer (in bytes)
/// \param[in]  src     Source buffer to decode
/// \param[in]  srcLen  Length of \p src buffer (in characters) or wxNO_LEN for zero terminated strings
///
/// \returns The length of the decoded data or wxCONV_FAILED if the buffer is not
/// large enough; to determine the needed size you can either allocate a buffer
/// of `wxURLDecodedSize(srcLen)` size or call the function with NULL string in
/// which case the required size will be returned
///
size_t WXEXTEND_API wxURLDecode(char *dst, size_t dstLen, const char *src, size_t srcLen = wxNO_LEN);


///
/// Decoding function which decodes the contents of the string into the provided buffer of the given size
///
/// \param[out] dst     Destination buffer to receive decoded data
/// \param[in]  dstLen  Length of \p dst buffer (in bytes)
/// \param[in]  src     Source string to decode
///
/// \returns The length of the decoded data or wxCONV_FAILED if the buffer is not
/// large enough; to determine the needed size you can either allocate a buffer
/// of `wxURLDecodedSize(srcLen)` size or call the function with NULL string in
/// which case the required size will be returned
///
inline size_t wxURLDecode(char *dst, size_t dstLen, const wxString& src)
{
    // don't use str.length() here as the ASCII buffer is shorter than it is for
    // strings with embedded NULs
    return wxURLDecode(dst, dstLen, src.ToAscii(), wxNO_LEN);
}


///
/// Decoding function which decodes the contents of the string of specified
/// length (or zero terminated by default) into the buffer
///
/// \param[in]  src     Source buffer to decode
/// \param[in]  srcLen  Length of \p src buffer (in characters) or wxNO_LEN for zero terminated strings
///
/// \returns Destination buffer with decoded data or an empty buffer if an error occured during decoding
///
wxMemoryBuffer WXEXTEND_API wxURLDecode(const char *src, size_t srcLen = wxNO_LEN);


///
/// Decoding function which decodes the contents of the string into the buffer
///
/// \param[in]  src     Source string to decode
///
/// \returns Destination buffer with decoded data or an empty buffer if an error occured during decoding
///
inline wxMemoryBuffer wxURLDecode(const wxString& src)
{
    // don't use str.length() here as the ASCII buffer is shorter than it for
    // strings with embedded NULs
    return wxURLDecode(src.ToAscii(), wxNO_LEN);
}

/// @}
