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

#include "common.h"

#include <wx/buffer.h>
#include <wx/string.h>

#include <Wincrypt.h>


///
/// Cryptographics Session Base Class
///
class WXEXTEND_API wxCryptoSession
{
protected:
    HCRYPTPROV m_h; ///< Session Handle

public:
    wxCryptoSession();
    virtual ~wxCryptoSession();


    ///
    /// Has the session creation been successful?
    ///
    /// \returns
    /// - true if creation succeeded
    /// - false otherwise
    ///
    inline bool IsOk() const
    {
        return m_h != NULL;
    }


    ///
    /// \returns Session handle to be used in native API calls.
    ///
    inline operator HCRYPTPROV() const
    {
        return m_h;
    }
};


///
/// RSA AES Cryptographics Session
///
class WXEXTEND_API wxCryptoSessionRSAAES : public wxCryptoSession
{
public:
    wxCryptoSessionRSAAES();
};


///
/// Cryptographics Hash Base
///
class WXEXTEND_API wxCryptoHash
{
protected:
    HCRYPTHASH m_h; ///< Hash Handle

public:
    wxCryptoHash();
    virtual ~wxCryptoHash();


    ///
    /// Has the hash creation been successful?
    ///
    /// \returns
    /// - true if creation succeeded
    /// - false otherwise
    ///
    inline bool IsOk() const
    {
        return m_h != NULL;
    }


    ///
    /// \returns Hash handle to be used in native API calls.
    ///
    inline operator HCRYPTHASH() const
    {
        return m_h;
    }


    ///
    /// Hashes given block of data
    ///
    /// \param[in] data  Pointer to memory block
    /// \param[in] size  Size of memory block in bytes
    ///
    /// \returns
    /// - true if hashing succeeded
    /// - false otherwise
    ///
    bool Hash(const void *data, size_t size);


    ///
    /// Hashes given block of data
    ///
    /// \param[in] data  Memory block
    ///
    /// \returns
    /// - true if hashing succeeded
    /// - false otherwise
    ///
    inline bool Hash(const wxMemoryBuffer &data)
    {
        return Hash(data.GetData(), data.GetDataLen());
    }


    ///
    /// Converts string to UTF-8 and hashes it.
    ///
    /// \param[in] str  String to hash
    ///
    /// \returns
    /// - true if hashing succeeded
    /// - false otherwise
    ///
    inline bool HashAsUTF8(const wxString &str)
    {
        const wxScopedCharBuffer buf(str.ToUTF8());
        return Hash((const char*)buf.data(), buf.length());
    }


    ///
    /// Finish hashing and return hash data.
    ///
    /// \param[out] hash  Hash data
    ///
    /// \returns
    /// - true if succeeded
    /// - false otherwise
    ///
    virtual bool GetValue(wxMemoryBuffer &hash);


    ///
    /// Signs the hash using session key
    ///
    /// \param[out] signature  Digital signature
    ///
    /// \returns
    /// - true if signing succeeded
    /// - false otherwise
    ///
    bool Sign(wxMemoryBuffer &signature);


    ///
    /// Signs the hash using session key
    ///
    /// \returns Digital Signature
    ///
    inline wxMemoryBuffer Sign()
    {
        wxMemoryBuffer signature;
        wxVERIFY(Sign(signature));
        return signature;
    }
};


///
/// SHA-1 Cryptographics Hash
///
class WXEXTEND_API wxCryptoHashSHA1 : public wxCryptoHash
{
public:
    wxCryptoHashSHA1(wxCryptoSession &session);


    ///
    /// Finish hashing and return hash data.
    ///
    /// \param[out] hash  Hash data
    ///
    /// \returns
    /// - true if succeeded
    /// - false otherwise
    ///
    virtual bool GetValue(wxMemoryBuffer &hash);
};


///
/// Cryptographics Key Base
///
class WXEXTEND_API wxCryptoKey
{
public:
    wxCryptoKey();
    virtual ~wxCryptoKey();


    ///
    /// Has the key creation been successful?
    ///
    /// \returns
    /// - true if creation succeeded
    /// - false otherwise
    ///
    inline bool IsOk() const
    {
        return m_h != NULL;
    }


    ///
    /// \returns Key handle to be used in native API calls.
    ///
    inline operator HCRYPTKEY() const
    {
        return m_h;
    }


    bool ImportPrivate(wxCryptoSession &session, const void *data, size_t size);
    bool ImportPublic(wxCryptoSession &session, const void *data, size_t size);

protected:
    HCRYPTKEY m_h;
};


///
/// Verifies if the hash matches signature and the public key
///
/// \param[in] hash            Hash
/// \param[in] signature_data  Pointer to signature data
/// \param[in] signature_size  Signature data size in bytes
/// \param[in] key             Public key
///
/// \returns
/// - true if verification succeeded and the hash matches
/// - false otherwise
///
bool WXEXTEND_API wxCryptoVerifySignature(const wxCryptoHash &hash, const void *signature_data, size_t signature_size, const wxCryptoKey &key);


///
/// Verifies if the hash matches signature and the public key
///
/// \param[in] hash       Hash
/// \param[in] signature  Signature data
/// \param[in] key        Public key
///
/// \returns
/// - true if verification succeeded and the hash matches
/// - false otherwise
///
inline bool wxCryptoVerifySignature(const wxCryptoHash &hash, const wxMemoryBuffer &signature, const wxCryptoKey &key)
{
    return wxCryptoVerifySignature(hash, signature.GetData(), signature.GetDataLen(), key);
}
