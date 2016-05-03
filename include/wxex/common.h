/*
    Copyright 2015-2016 Amebis

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

#if !defined(__wxEXTEND_common_h__)
#define __wxEXTEND_common_h__

///
/// wxExtend Version
///
#define wxEXTEND_VERSION        0x01000100

#define wxEXTEND_VERSION_MAJ    1
#define wxEXTEND_VERSION_MIN    0
#define wxEXTEND_VERSION_REV    1
#define wxEXTEND_VERSION_BUILD  0

#define wxEXTEND_VERSION_STR    "1.0.1"
#define wxEXTEND_BUILD_YEAR_STR "2016"


#if !defined(RC_INVOKED) && !defined(MIDL_PASS)

#include <Windows.h>
#include <wx/debug.h>
#include <wx/defs.h>


///
/// Public function calling convention
///
#ifdef WXEXTEND
#define WXEXTEND_API    __declspec(dllexport)
#else
#define WXEXTEND_API    __declspec(dllimport)
#endif


///
/// Debug macros
///
#if wxDEBUG_LEVEL
#define wxVERIFY(x) wxASSERT((x))
#else
#define wxVERIFY(x) (x)
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

    DWORD dwStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
    DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
    if(dwStyle == dwNewStyle)
        return false;

    SetWindowLong(hWnd, GWL_EXSTYLE, dwNewStyle);
    if(nFlags != 0)
        SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);

    return true;
}

#endif // !defined(RC_INVOKED) && !defined(MIDL_PASS)
#endif // !defined(__wxEXTEND_common_h__)
