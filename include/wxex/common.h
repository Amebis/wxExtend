/*
    ​​​SPDX-License-Identifier: GPL-3.0-or-later
    Copyright © 2015-2021 Amebis
    Copyright © 2016 GÉANT
*/

#if !defined(__wxEXTEND_common_h__)
#define __wxEXTEND_common_h__

/// \addtogroup wxExtend
/// @{

///
/// wxExtend Version
///
#define wxEXTEND_VERSION        0x01050300

#define wxEXTEND_VERSION_MAJ    1       ///< wxExtend Major Version
#define wxEXTEND_VERSION_MIN    5       ///< wxExtend Minor Version
#define wxEXTEND_VERSION_REV    3       ///< wxExtend Revision
#define wxEXTEND_VERSION_BUILD  0       ///< wxExtend Build

#define wxEXTEND_VERSION_STR    "1.5.3" ///< wxExtend Displayable Version
#define wxEXTEND_BUILD_YEAR_STR "2020"  ///< wxExtend Build Year

#define wxExtendVersion         "15"    ///< wxExtend API Version


#if !defined(RC_INVOKED) && !defined(MIDL_PASS)

#define _WINSOCKAPI_    // Prevent inclusion of winsock.h in windows.h.
#include <Windows.h>

#include <codeanalysis\warnings.h>
#ifndef WXWIDGETS_CODE_ANALYSIS_WARNINGS
#define WXWIDGETS_CODE_ANALYSIS_WARNINGS ALL_CODE_ANALYSIS_WARNINGS 26812 26814
#endif

#pragma warning(push)
#pragma warning(disable: WXWIDGETS_CODE_ANALYSIS_WARNINGS)
#include <wx/config.h>
#include <wx/debug.h>
#include <wx/defs.h>
#include <wx/intl.h>
#pragma warning(pop)

///
/// Public function calling convention
///
#ifndef WXEXTEND_API
#if defined(WXEXTEND_DLL)
#define WXEXTEND_API      __declspec(dllexport)
#elif defined(WXEXTEND_DLLIMP)
#define WXEXTEND_API      __declspec(dllimport)
#else
#define WXEXTEND_API
#endif
#endif


///
/// Test if condition is true. When not true, raise debug assertion with the given message.
///
#if wxDEBUG_LEVEL
#define wxVERIFY_MSG(cond, msg)                                           \
    wxSTATEMENT_MACRO_BEGIN                                               \
        if ( !(cond) && wxTheAssertHandler &&                             \
                (wxOnAssert(__FILE__, __LINE__, __WXFUNCTION__,           \
                            #cond, msg), wxTrapInAssert) )                \
        {                                                                 \
            wxTrapInAssert = false;                                       \
            wxTrap();                                                     \
        }                                                                 \
    wxSTATEMENT_MACRO_END
#endif


///
/// Test if condition is true. When not true, raise debug assertion.
///
#if wxDEBUG_LEVEL
#define wxVERIFY(cond) wxVERIFY_MSG(cond, (const char*)NULL)
#else
#define wxVERIFY(cond) (cond)
#endif


///
/// Returns whether windows animation is enabled.
///
/// \returns
/// - \c true when window animation is enabled
/// - \c false otherwise
///
inline bool wxGetDoWndAnimation()
{
    ANIMATIONINFO ai = { sizeof(ai) };
    wxCHECK(SystemParametersInfo(SPI_GETANIMATION, sizeof(ai), &ai, 0), false);
    return ai.iMinAnimate ? true : false;
}


///
/// Modifies window extended style.
///
/// \param[in] hWnd      Handle of the window to modify.
/// \param[in] dwRemove  Set of extended styles to remove.
/// \param[in] dwAdd     Set of extended styles to add.
/// \param[in] nFlags    Additional SWP_ flags to pass to SetWindowPos(). If zero, SetWindowPos() is not called.
///
/// \returns
/// - \c true when the window extended style was modified
/// - \c false if the window extended style was not neccessary
///
inline bool wxModifyStyleEx(_In_ WXHWND hWnd, _In_ DWORD dwRemove, _In_ DWORD dwAdd, _In_ UINT nFlags = 0)
{
    wxASSERT(IsWindow(hWnd));

    const DWORD dwStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
    const DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
    if(dwStyle == dwNewStyle)
        return false;

    SetWindowLong(hWnd, GWL_EXSTYLE, dwNewStyle);
    if(nFlags != 0)
        SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);

    return true;
}


///
/// Inizializes wxWidgets localization scheme
///
/// The language identifier is read from `Language` configuration string ("ll_CC" form expected).
/// The path to folder containing localization catalogue PO files is read from `LocalizationRepositoryPath` configuration string.
///
/// \param[inout] locale    Locale to initialize
/// \param[out  ] language  Translation language
///
/// \returns
/// - \c true when initialization succeeded
/// - \c false otherwise
///
#pragma warning(suppress: 26812) // wxLanguage is unscoped
inline bool wxInitializeLocale(wxLocale &locale, wxLanguage *language = NULL)
{
    // Read language from configuration.
    wxLanguage lang_code = wxLANGUAGE_DEFAULT;
    wxString lang;
    if (wxConfigBase::Get()->Read(wxT("Language"), &lang)) {
        const wxLanguageInfo *lang_info = wxLocale::FindLanguageInfo(lang);
        lang_code = lang_info ? (wxLanguage)lang_info->Language : wxLANGUAGE_DEFAULT;
    }

    if (language)
        *language = lang_code;

    if (wxLocale::IsAvailable(lang_code)) {
        // Language is "available". Well... Known actually.
        wxString sPath;
        if (wxConfigBase::Get()->Read(wxT("LocalizationRepositoryPath"), &sPath))
            locale.AddCatalogLookupPathPrefix(sPath);
        return locale.Init(lang_code);
    }

    return false;
}

#endif // !defined(RC_INVOKED) && !defined(MIDL_PASS)

/// @}

#endif // !defined(__wxEXTEND_common_h__)
