﻿/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2022 Amebis
    Copyright © 2016 GÉANT
*/

#include "pch.h"
#pragma comment(lib, "Crypt32.lib")


static bool wxGetHashValue(HCRYPTHASH h, DWORD length, wxMemoryBuffer &hash)
{
    // Prepare buffer.
    hash.SetBufSize(length);

    // Query hash value.
    if (::CryptGetHashParam(h, HP_HASHVAL, (BYTE*)hash.GetData(), &length, 0)) {
        hash.SetDataLen(length);
        return true;
    } else
        wxLogLastError(wxT("CryptGetHashParam(HP_HASHVAL)"));

    hash.Clear();
    return false;
}


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


_Use_decl_annotations_
bool wxCryptoHash::Hash(const void *data, size_t size)
{
    wxASSERT_MSG(m_h, wxT("object uninitialized"));
    wxASSERT_MSG(data || !size, wxT("invalid parameter"));
    wxASSERT_MSG(size <= MAXDWORD, wxT("4 GiB exceeded"));

    if (!::CryptHashData(m_h, (const BYTE*)data, (DWORD)size, 0)) {
        wxLogLastError(wxT("CryptHashData"));
        return false;
    }

    return true;
}


_Use_decl_annotations_
bool wxCryptoHash::GetValue(wxMemoryBuffer &hash)
{
    wxASSERT_MSG(m_h, wxT("object uninitialized"));

    // Query hash size first.
    DWORD size, length = sizeof(size);
    if (::CryptGetHashParam(m_h, HP_HASHSIZE, (BYTE*)&size, &length, 0)) {
        wxASSERT(length == sizeof(size));
        return wxGetHashValue(m_h, size, hash);
    } else
        wxLogLastError(wxT("CryptGetHashParam(HP_HASHSIZE)"));

    hash.Clear();
    return false;
}


_Use_decl_annotations_
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


_Use_decl_annotations_
bool wxCryptoHashSHA1::GetValue(wxMemoryBuffer &hash)
{
    wxASSERT_MSG(m_h, wxT("object uninitialized"));
    return wxGetHashValue(m_h, 20, hash);
}


#if (NTDDI_VERSION > NTDDI_WINXPSP2)

//////////////////////////////////////////////////////////////////////////
// wxCryptoHashSHA256
//////////////////////////////////////////////////////////////////////////

wxCryptoHashSHA256::wxCryptoHashSHA256(wxCryptoSession &session)
{
    if (!::CryptCreateHash(session, CALG_SHA_256, 0, 0, &m_h))
        wxLogLastError(wxT("CryptCreateHash(CALG_SHA_256)"));
}


_Use_decl_annotations_
bool wxCryptoHashSHA256::GetValue(wxMemoryBuffer &hash)
{
    wxASSERT_MSG(m_h, wxT("object uninitialized"));
    return wxGetHashValue(m_h, 32, hash);
}

#endif


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


_Use_decl_annotations_
bool wxCryptoKey::ImportPrivate(wxCryptoSession &session, const void *data, size_t size)
{
    wxASSERT_MSG(!m_h, wxT("object initialized"));
    wxASSERT_MSG(session.IsOk(), wxT("invalid session"));
    wxASSERT_MSG(data || !size, wxT("invalid parameter"));
    wxASSERT_MSG(size <= MAXDWORD, wxT("4 GiB exceeded"));

    PUBLICKEYSTRUC *key_data = NULL;
    DWORD key_size = 0;
    if (!::CryptDecodeObjectEx(X509_ASN_ENCODING, PKCS_RSA_PRIVATE_KEY, (const BYTE*)data, (DWORD)size, CRYPT_DECODE_ALLOC_FLAG, NULL, &key_data, &key_size)) {
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


_Use_decl_annotations_
bool wxCryptoKey::ImportPublic(wxCryptoSession &session, const void *data, size_t size)
{
    wxASSERT_MSG(!m_h, wxT("object initialized"));
    wxASSERT_MSG(session.IsOk(), wxT("invalid session"));
    wxASSERT_MSG(data || !size, wxT("invalid parameter"));
    wxASSERT_MSG(size <= MAXDWORD, wxT("4 GiB exceeded"));

    CERT_PUBLIC_KEY_INFO *keyinfo_data = NULL;
    DWORD keyinfo_size = 0;
    if (!::CryptDecodeObjectEx(X509_ASN_ENCODING, X509_PUBLIC_KEY_INFO, (const BYTE*)data, (DWORD)size, CRYPT_DECODE_ALLOC_FLAG, NULL, &keyinfo_data, &keyinfo_size)) {
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

_Use_decl_annotations_
bool WXEXTEND_API wxCryptoVerifySignature(const wxCryptoHash &hash, const void *signature_data, size_t signature_size, const wxCryptoKey &key)
{
    wxASSERT_MSG(hash.IsOk()                      , wxT("invalid hash"));
    wxASSERT_MSG(signature_data || !signature_size, wxT("invalid parameter"));
    wxASSERT_MSG(signature_size <= MAXDWORD       , wxT("4 GiB exceeded"));
    wxASSERT_MSG(key.IsOk()                       , wxT("invalid key"));

    // Reverse byte order, for consistent OpenSSL experience.
    wxMemoryBuffer signature(signature_size);
    BYTE *data = (BYTE*)signature.GetData();
    for (size_t i = 0, j  = signature_size - 1; i < signature_size; i++, j--)
        data[i] = ((const BYTE*)signature_data)[j];

    if (!::CryptVerifySignature(hash, data, (DWORD)signature_size, key, NULL, 0)) {
        wxLogLastError(wxT("CryptVerifySignature"));
        return false;
    }

    return true;
}
