﻿/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2022 Amebis
    Copyright © 2016 GÉANT
*/

#pragma once

#include "common.h"

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: WXWIDGETS_CODE_ANALYSIS_WARNINGS)
#include <wx/string.h>
#include <wx/buffer.h>
#pragma warning(pop)


// ----------------------------------------------------------------------------
// Encoding Functions
// ----------------------------------------------------------------------------

/// \addtogroup wxExtend
/// @{

///
/// Return the size needed for the buffer containing the encoded representation
/// of a buffer of given length
///
/// \param[in] len  Length of the buffer
///
/// \returns Maximum encoded representation size (in characters)
///
inline constexpr size_t wxHexEncodedSize(size_t len) noexcept
{
    return 2*len;
}


///
/// Raw hex encoding function which encodes the contents of a buffer of the
/// specified length into the buffer of the specified size
///
/// \param[out] dst     Destination buffer to receive Hex encoded data
/// \param[in]  dstLen  Length of \p dst buffer (in characters)
/// \param[in]  src     Source buffer to encode
/// \param[in]  srcLen  Length of \p src buffer (in bytes)
///
/// \returns The length of the encoded data or wxCONV_FAILED if the buffer is not
/// large enough; to determine the needed size you can either allocate a buffer
/// of `wxHexEncodedSize(srcLen)` size or call the function with NULL buffer in
/// which case the required size will be returned
///
size_t WXEXTEND_API wxHexEncode(char *dst, size_t dstLen, const void *src, size_t srcLen);


///
/// Hex encoding function which encodes the contents of a buffer of the
/// specified length into the wxString
///
/// \param[in]  src     Source buffer to encode
/// \param[in]  srcLen  Length of \p src buffer (in bytes)
///
/// \returns The hex encoded string
///
inline wxString wxHexEncode(const void *src, size_t srcLen)
{
    const size_t dstLen = wxHexEncodedSize(srcLen);
    wxCharBuffer dst(dstLen);
    wxHexEncode(dst.data(), dstLen, src, srcLen);

    return dst;
}


///
/// Hex encoding function which encodes the contents of a buffer into the wxString
///
/// \param[in]  buf  Source buffer to encode
///
/// \returns The hex encoded string
///
inline wxString wxHexEncode(const wxMemoryBuffer& buf)
{
    return wxHexEncode(buf.GetData(), buf.GetDataLen());
}


// ----------------------------------------------------------------------------
// Decoding Functions
// ----------------------------------------------------------------------------

///
/// Elements of this enum specify the possible behaviours of wxHexDecode()
/// when an invalid character is encountered.
///
enum class wxHexDecodeMode
{
    Strict,     ///< Normal behaviour: stop at any invalid characters
    SkipWS,     ///< Skip whitespace characters
    Relaxed,    ///< The most lenient behaviour: simply ignore all invalid characters
};


///
/// Return the buffer size necessary for decoding a hex string of the given
/// length
///
/// \param[in] len  Length of the hex encoded string
///
/// \returns Maximum decoded representation size (in bytes)
///
inline constexpr size_t wxHexDecodedSize(size_t len) noexcept
{
    return (len + 1)/2;
}

///
/// Raw decoding function which decodes the contents of the string of specified
/// length (or zero terminated by default) into the provided buffer of the given
/// size
///
/// The function normally stops at any character invalid inside a hex-encoded
/// string (i.e. not numeric nor 'A-Z' nor 'a-z') but can be made to skip the
/// whitespace or all invalid characters using its \p mode argument
///
/// \param[out] dst     Destination buffer to receive decoded data
/// \param[in]  dstLen  Length of \p dst buffer (in bytes)
/// \param[in]  src     Source buffer to decode
/// \param[in]  srcLen  Length of \p src buffer (in characters) or wxNO_LEN for zero terminated strings
/// \param[in]  mode    Desired behaviour on invalid characters (one of `wxHexDecodeMode` constants)
/// \param[out] posErr  Error offset in source buffer (in characters)
///
/// \returns The length of the decoded data or wxCONV_FAILED if an error occurs
/// such as the buffer is too small or the encoded string is invalid; in the
/// latter case the \p posErr is filled with the position where the decoding
/// stopped if it is not NULL
///
size_t WXEXTEND_API wxHexDecode(void *dst, size_t dstLen, const char *src, size_t srcLen = wxNO_LEN, wxHexDecodeMode mode = wxHexDecodeMode::Strict, size_t *posErr = NULL);


///
/// Decoding function which decodes the contents of the string into the provided buffer of the given size
///
/// The function normally stops at any character invalid inside a hex-encoded
/// string (i.e. not numeric nor 'A-Z' nor 'a-z') but can be made to skip the
/// whitespace or all invalid characters using its \p mode argument
///
/// \param[out] dst     Destination buffer to receive decoded data
/// \param[in]  dstLen  Length of \p dst buffer (in bytes)
/// \param[in]  src     Source string to decode
/// \param[in]  mode    Desired behaviour on invalid characters (one of `wxHexDecodeMode` constants)
/// \param[out] posErr  Error offset in source buffer (in characters)
///
/// \returns The length of the decoded data or wxCONV_FAILED if an error occurs
/// such as the buffer is too small or the encoded string is invalid; in the
/// latter case the \p posErr is filled with the position where the decoding
/// stopped if it is not NULL
///
inline size_t wxHexDecode(void *dst, size_t dstLen, const wxString& src, wxHexDecodeMode mode = wxHexDecodeMode::Strict, size_t *posErr = NULL)
{
    // don't use str.length() here as the ASCII buffer is shorter than it is for
    // strings with embedded NULs
    return wxHexDecode(dst, dstLen, src.ToAscii(), wxNO_LEN, mode, posErr);
}


///
/// Decoding function which decodes the contents of the string of specified
/// length (or zero terminated by default) into the buffer
///
/// The function normally stops at any character invalid inside a hex-encoded
/// string (i.e. not numeric nor 'A-Z' nor 'a-z') but can be made to skip the
/// whitespace or all invalid characters using its \p mode argument
///
/// \param[in]  src     Source buffer to decode
/// \param[in]  srcLen  Length of \p src buffer (in characters) or wxNO_LEN for zero terminated strings
/// \param[in]  mode    Desired behaviour on invalid characters (one of `wxHexDecodeMode` constants)
/// \param[out] posErr  Error offset in source buffer (in characters)
///
/// \returns Destination buffer with decoded data or an empty buffer if an error occured during decoding
///
wxMemoryBuffer WXEXTEND_API wxHexDecode(const char *src, size_t srcLen = wxNO_LEN, wxHexDecodeMode mode = wxHexDecodeMode::Strict, size_t *posErr = NULL);


///
/// Decoding function which decodes the contents of the string into the buffer
///
/// The function normally stops at any character invalid inside a hex-encoded
/// string (i.e. not numeric nor 'A-Z' nor 'a-z') but can be made to skip the
/// whitespace or all invalid characters using its \p mode argument
///
/// \param[in]  src     Source string to decode
/// \param[in]  mode    Desired behaviour on invalid characters (one of `wxHexDecodeMode` constants)
/// \param[out] posErr  Error offset in source buffer (in characters)
///
/// \returns Destination buffer with decoded data or an empty buffer if an error occured during decoding
///
inline wxMemoryBuffer wxHexDecode(const wxString& src, wxHexDecodeMode mode = wxHexDecodeMode::Strict, size_t *posErr = NULL)
{
    // don't use str.length() here as the ASCII buffer is shorter than it for
    // strings with embedded NULs
    return wxHexDecode(src.ToAscii(), wxNO_LEN, mode, posErr);
}

/// @}
