/*
    Copyright 2016-2020 Amebis
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

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable: WXWIDGETS_CODE_ANALYSIS_WARNINGS)
#include <wx/buffer.h>
#include <wx/ffile.h>
#include <wx/log.h>
#include <wx/string.h>
#pragma warning(pop)

#include <Wincrypt.h>

/// \addtogroup wxExtend
/// @{

///
/// Cryptographics Session Base Class
///
class WXEXTEND_API wxCryptoSession
{
protected:
    HCRYPTPROV m_h; ///< Session Handle

public:
    ///
    /// Creates a new cryptographics session
    ///
    wxCryptoSession();


    ///
    /// Destructor
    ///
    virtual ~wxCryptoSession();


    ///
    /// Has the session creation been successful?
    ///
    /// \returns
    /// - \c true if creation succeeded
    /// - \c false otherwise
    ///
    inline bool IsOk() const noexcept
    {
        return m_h != NULL;
    }


    ///
    /// \returns Session handle to be used in native API calls.
    ///
    inline operator HCRYPTPROV() const noexcept
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
    ///
    /// Creates a new RSA AES cryptographics session
    ///
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
    ///
    /// Creates a new cryptographics hash
    ///
    wxCryptoHash();


    ///
    /// Destructor
    ///
    virtual ~wxCryptoHash();


    ///
    /// Has the hash creation been successful?
    ///
    /// \returns
    /// - \c true if creation succeeded
    /// - \c false otherwise
    ///
    inline bool IsOk() const noexcept
    {
        return m_h != NULL;
    }


    ///
    /// \returns Hash handle to be used in native API calls.
    ///
    inline operator HCRYPTHASH() const noexcept
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
    /// - \c true if hashing succeeded
    /// - \c false otherwise
    ///
    _Success_(return != 0) bool Hash(_In_reads_bytes_(size) const void *data, _In_ size_t size);


    ///
    /// Hashes given block of data
    ///
    /// \param[in] data  Memory block
    ///
    /// \returns
    /// - \c true if hashing succeeded
    /// - \c false otherwise
    ///
    inline _Success_(return != 0) bool Hash(_In_ const wxMemoryBuffer &data)
    {
        return Hash(data.GetData(), data.GetDataLen());
    }


    ///
    /// Converts string to UTF-8 and hashes it.
    ///
    /// \param[in] str  String to hash
    ///
    /// \returns
    /// - \c true if hashing succeeded
    /// - \c false otherwise
    ///
    inline _Success_(return != 0) bool HashAsUTF8(_In_ const wxString &str)
    {
        const wxScopedCharBuffer buf(str.ToUTF8());
        return Hash(buf.data(), buf.length());
    }


    ///
    /// Hashes a file
    ///
    /// \param[in] fileName  The path of the file to calculate hash of
    ///
    /// \returns
    /// - \c true if hashing succeeded
    /// - \c false otherwise
    ///
    inline _Success_(return != 0) bool HashFile(_In_ const wxString &fileName)
    {
        wxFFile file(fileName, wxT("rb"));
        if (file.IsOpened()) {
            wxMemoryBuffer buf(4*1024);
            void *data = buf.GetData();
            const size_t nBlock = buf.GetBufSize();
            while (!file.Eof())
                Hash(data, file.Read(data, nBlock));

            return true;
        } else {
            wxLogError(wxT("Can not open %s file for reading."), fileName);
            return false;
        }
    }


    ///
    /// Finish hashing and return hash data.
    ///
    /// \param[out] hash  Hash data
    ///
    /// \returns
    /// - \c true if succeeded
    /// - \c false otherwise
    ///
    virtual _Success_(return != 0) bool GetValue(_Out_ wxMemoryBuffer &hash);


    ///
    /// Signs the hash using session key
    ///
    /// \param[inout] signature  Digital signature
    ///
    /// \returns
    /// - \c true if signing succeeded
    /// - \c false otherwise
    ///
    _Success_(return != 0) bool Sign(_Inout_ wxMemoryBuffer &signature);


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
    ///
    /// Creates a new cryptographics SHA-1 hash
    ///
    wxCryptoHashSHA1(wxCryptoSession &session);


    ///
    /// Finish hashing and return hash data.
    ///
    /// \param[out] hash  Hash data
    ///
    /// \returns
    /// - \c true if succeeded
    /// - \c false otherwise
    ///
    virtual _Success_(return != 0) bool GetValue(_Out_ wxMemoryBuffer &hash);
};


#if (NTDDI_VERSION > NTDDI_WINXPSP2)

///
/// SHA-256 Cryptographics Hash
///
class WXEXTEND_API wxCryptoHashSHA256 : public wxCryptoHash
{
public:
    ///
    /// Creates a new cryptographics SHA-256 hash
    ///
    wxCryptoHashSHA256(wxCryptoSession &session);


    ///
    /// Finish hashing and return hash data.
    ///
    /// \param[out] hash  Hash data
    ///
    /// \returns
    /// - \c true if succeeded
    /// - \c false otherwise
    ///
    virtual _Success_(return != 0) bool GetValue(_Out_ wxMemoryBuffer &hash);
};

#endif


///
/// Cryptographics Key Base
///
class WXEXTEND_API wxCryptoKey
{
protected:
    HCRYPTKEY m_h;  ///< Key Handle

public:
    ///
    /// Creates a new cryptographics key
    ///
    wxCryptoKey();


    ///
    /// Destructor
    ///
    virtual ~wxCryptoKey();


    ///
    /// Has the key creation been successful?
    ///
    /// \returns
    /// - \c true if creation succeeded
    /// - \c false otherwise
    ///
    inline bool IsOk() const noexcept
    {
        return m_h != NULL;
    }


    ///
    /// \returns Key handle to be used in native API calls.
    ///
    inline operator HCRYPTKEY() const noexcept
    {
        return m_h;
    }


    ///
    /// Imports private key
    ///
    _Success_(return != 0) bool ImportPrivate(_Inout_ wxCryptoSession &session, _In_reads_bytes_(size) const void *data, _In_ size_t size);


    ///
    /// Imports public key
    ///
    _Success_(return != 0) bool ImportPublic(_Inout_ wxCryptoSession &session, _In_reads_bytes_(size) const void *data, _In_ size_t size);
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
/// - \c true if verification succeeded and the hash matches
/// - \c false otherwise
///
_Success_(return != 0) bool WXEXTEND_API wxCryptoVerifySignature(_In_ const wxCryptoHash &hash, _In_reads_bytes_(signature_size) const void *signature_data, _In_ size_t signature_size, _In_ const wxCryptoKey &key);


///
/// Verifies if the hash matches signature and the public key
///
/// \param[in] hash       Hash
/// \param[in] signature  Signature data
/// \param[in] key        Public key
///
/// \returns
/// - \c true if verification succeeded and the hash matches
/// - \c false otherwise
///
inline _Success_(return != 0) bool wxCryptoVerifySignature(_In_ const wxCryptoHash &hash, _In_ const wxMemoryBuffer &signature, _In_ const wxCryptoKey &key)
{
    return wxCryptoVerifySignature(hash, signature.GetData(), signature.GetDataLen(), key);
}

/// @}
