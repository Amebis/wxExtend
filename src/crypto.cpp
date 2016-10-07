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

#include "stdafx.h"
#pragma comment(lib, "Crypt32.lib")


//////////////////////////////////////////////////////////////////////////
// wxCryptoSession
//////////////////////////////////////////////////////////////////////////

wxCryptoSession::wxCryptoSession() : m_h(NULL)
{
}


wxCryptoSession::~wxCryptoSession()
{
    if (m_h)
        ::CryptReleaseContext(m_h, 0);
}


//////////////////////////////////////////////////////////////////////////
// wxCryptoSessionRSAAES
//////////////////////////////////////////////////////////////////////////

wxCryptoSessionRSAAES::wxCryptoSessionRSAAES()
{
    if (!::CryptAcquireContext(&m_h, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
        wxLogLastError(wxT("CryptAcquireContext(PROV_RSA_AES, CRYPT_VERIFYCONTEXT)"));
}


//////////////////////////////////////////////////////////////////////////
// wxCryptoHash
//////////////////////////////////////////////////////////////////////////

wxCryptoHash::wxCryptoHash() : m_h(NULL)
{
}


wxCryptoHash::~wxCryptoHash()
{
    if (m_h)
        ::CryptDestroyHash(m_h);
}


bool wxCryptoHash::Hash(const void *data, size_t size)
{
    wxASSERT_MSG(m_h, wxT("object uninitialized"));
    wxASSERT_MSG(data || !size, wxT("invalid parameter"));

    if (!::CryptHashData(m_h, (const BYTE*)data, size, 0)) {
        wxLogLastError(wxT("CryptHashData"));
        return false;
    }

    return true;
}


bool wxCryptoHash::GetValue(wxMemoryBuffer &hash)
{
    wxASSERT_MSG(m_h, wxT("object uninitialized"));

    // Query hash size first.
    DWORD size, length = sizeof(size);
    if (::CryptGetHashParam(m_h, HP_HASHSIZE, (BYTE*)&size, &length, 0)) {
        wxASSERT(length == sizeof(size));

        // Prepare buffer.
        length = size;
        hash.SetBufSize(length);

        // Query hash value.
        if (::CryptGetHashParam(m_h, HP_HASHVAL, (BYTE*)hash.GetData(), &length, 0)) {
            hash.SetDataLen(length);
            return true;
        } else
            wxLogLastError(wxT("CryptGetHashParam(HP_HASHVAL)"));
    } else
        wxLogLastError(wxT("CryptGetHashParam(HP_HASHSIZE)"));

    hash.Clear();
    return false;
}


bool wxCryptoHash::Sign(wxMemoryBuffer &signature)
{
    // Try with the current buffer size first.
    DWORD size = (DWORD)signature.GetBufSize();
    BYTE *data = (BYTE*)signature.GetWriteBuf(size);
    if (::CryptSignHash(m_h, AT_SIGNATURE, NULL, 0, data, &size)) {
        // The buffer was large enough. Set the actual size.
        signature.SetDataLen(size);
    } else {
        DWORD dwError = ::GetLastError();
        if (dwError == ERROR_MORE_DATA) {
            // The buffer was not big enough. Variable size contains the actual required size. Realloc and retry one more time.
            wxCHECK(::CryptSignHash(m_h, AT_SIGNATURE, NULL, 0, data = (BYTE*)signature.GetWriteBuf(size), &size), false);
            signature.SetDataLen(size);
        } else {
            wxLogApiError(wxT("CryptSignHash"), dwError);
            signature.Clear();
            return false;
        }
    }

    // Reverse byte order, for consistent OpenSSL experience.
    for (DWORD i = 0, j = size - 1; i < j; i++, j--)
        wxSwap(data[i], data[j]);

    return true;
}


//////////////////////////////////////////////////////////////////////////
// wxCryptoHashSHA1
//////////////////////////////////////////////////////////////////////////

wxCryptoHashSHA1::wxCryptoHashSHA1(wxCryptoSession &session)
{
    if (!::CryptCreateHash(session, CALG_SHA1, 0, 0, &m_h))
        wxLogLastError(wxT("CryptCreateHash(CALG_SHA1)"));
}


bool wxCryptoHashSHA1::GetValue(wxMemoryBuffer &hash)
{
    wxASSERT_MSG(m_h, wxT("object uninitialized"));

    // Prepare buffer.
    DWORD length = 20;
    hash.SetBufSize(length);

    // Query hash value.
    if (::CryptGetHashParam(m_h, HP_HASHVAL, (BYTE*)hash.GetData(), &length, 0)) {
        hash.SetDataLen(length);
        return true;
    } else
        wxLogLastError(wxT("CryptGetHashParam(HP_HASHVAL)"));

    hash.Clear();
    return false;
}


//////////////////////////////////////////////////////////////////////////
// wxCryptoKey
//////////////////////////////////////////////////////////////////////////

wxCryptoKey::wxCryptoKey() : m_h(NULL)
{
}


wxCryptoKey::~wxCryptoKey()
{
    if (m_h)
        ::CryptDestroyKey(m_h);
}


bool wxCryptoKey::ImportPrivate(wxCryptoSession &session, const void *data, size_t size)
{
    wxASSERT_MSG(!m_h, wxT("object initialized"));
    wxASSERT_MSG(session.IsOk(), wxT("invalid session"));
    wxASSERT_MSG(data || !size, wxT("invalid parameter"));

    PUBLICKEYSTRUC *key_data = NULL;
    DWORD key_size = 0;
    if (!::CryptDecodeObjectEx(X509_ASN_ENCODING, PKCS_RSA_PRIVATE_KEY, (const BYTE*)data, size, CRYPT_DECODE_ALLOC_FLAG, NULL, &key_data, &key_size)) {
        wxLogLastError(wxT("CryptDecodeObjectEx(PKCS_RSA_PRIVATE_KEY)"));
        return false;
    }

    // See: http://pumka.net/2009/12/16/rsa-encryption-cplusplus-delphi-cryptoapi-php-openssl-2/comment-page-1/#comment-429
    key_data->aiKeyAlg = CALG_RSA_SIGN;

    if (!::CryptImportKey(session, (const BYTE*)key_data, key_size, NULL, 0, &m_h)) {
        wxLogLastError(wxT("CryptImportKey"));
        ::LocalFree(key_data);
        return false;
    }
    ::LocalFree(key_data);

    return true;
}


bool wxCryptoKey::ImportPublic(wxCryptoSession &session, const void *data, size_t size)
{
    wxASSERT_MSG(!m_h, wxT("object initialized"));
    wxASSERT_MSG(session.IsOk(), wxT("invalid session"));
    wxASSERT_MSG(data || !size, wxT("invalid parameter"));

    CERT_PUBLIC_KEY_INFO *keyinfo_data = NULL;
    DWORD keyinfo_size = 0;
    if (!::CryptDecodeObjectEx(X509_ASN_ENCODING, X509_PUBLIC_KEY_INFO, (const BYTE*)data, size, CRYPT_DECODE_ALLOC_FLAG, NULL, &keyinfo_data, &keyinfo_size)) {
        wxLogLastError(wxT("CryptDecodeObjectEx(X509_PUBLIC_KEY_INFO)"));
        return false;
    }

    if (!::CryptImportPublicKeyInfo(session, X509_ASN_ENCODING, keyinfo_data, &m_h)) {
        wxLogLastError(wxT("CryptImportPublicKeyInfo"));
        ::LocalFree(keyinfo_data);
        return false;
    }
    ::LocalFree(keyinfo_data);

    return true;
}


//////////////////////////////////////////////////////////////////////////
// wxCryptoVerifySignature
//////////////////////////////////////////////////////////////////////////

bool WXEXTEND_API wxCryptoVerifySignature(const wxCryptoHash &hash, const void *signature_data, size_t signature_size, const wxCryptoKey &key)
{
    wxASSERT_MSG(hash.IsOk()                      , wxT("invalid hash"));
    wxASSERT_MSG(signature_data || !signature_size, wxT("invalid parameter"));
    wxASSERT_MSG(key.IsOk()                       , wxT("invalid key"));

    // Reverse byte order, for consistent OpenSSL experience.
    wxMemoryBuffer signature(signature_size);
    BYTE *data = (BYTE*)signature.GetData();
    for (size_t i = 0, j  = signature_size - 1; i < signature_size; i++, j--)
        data[i] = ((const BYTE*)signature_data)[j];

    if (!::CryptVerifySignature(hash, data, signature_size, key, NULL, 0)) {
        wxLogLastError(wxT("CryptVerifySignature"));
        return false;
    }

    return true;
}
