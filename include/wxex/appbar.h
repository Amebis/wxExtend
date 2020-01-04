/*
    Copyright 2015-2020 Amebis
    Copyright 2016 GÉANT
    Based on code written by Jeffrey Richter.

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

#include <wx/dialog.h>
#include <wx/frame.h>
#include <wx/string.h>

#include <Windows.h>
#include <Windowsx.h>
#include <shellapi.h>
#include <ShlObj.h>


/// \addtogroup wxExtend
/// @{

///
/// Application bar auto-hide timer ID
///
#define wxABT_AUTOHIDETIMERID       1

///
/// Application bar auto-hide timer timeout
///
#define wxABT_AUTOHIDETIME          300

///
/// Application bar auto-hide timer interval
///
#define wxABT_AUTOHIDETIMERINTERVAL 3000

///
/// Posted to notify application bar about system changes
///
/// \param[in] wParam Event identifier. One of the following values
/// - ABN_FULLSCREENAPP Notifies an appbar when a full-screen application is opening or closing. \p lParam is boolean flag specifying whether a full-screen application is opening or closing. This parameter is TRUE if the application is opening or FALSE if it is closing.
/// - ABN_POSCHANGED    Notifies an appbar when an event has occurred that may affect the appbar's size and position. Events include changes in the taskbar's size, position, and visibility state, as well as the addition, removal, or resizing of another appbar on the same side of the screen. \p lParam is not used.
/// - ABN_STATECHANGE   Notifies an appbar that the taskbar's autohide or always-on-top state has changed—that is, the user has selected or cleared the "Always on top" or "Auto hide" check box on the taskbar's property sheet. \p lParam is not used.
/// \param[in] lParam Event specific. See \p wParam for details.
///
#define WM_AB_NOTIFY                    0x6f00


///
/// Dockable application bar states
///
enum class wxAppBarState {
    UNKNOWN = -2,
    FLOAT   = -1,           ///< Application bar is floating on the desktop (normal window)
    LEFT    = ABE_LEFT,     ///< Application bar is docked at the left edge of the desktop
    TOP     = ABE_TOP,      ///< Application bar is docked at the top edge of the desktop
    RIGHT   = ABE_RIGHT,    ///< Application bar is docked at the right edge of the desktop
    BOTTOM  = ABE_BOTTOM,   ///< Application bar is docked at the bottom edge of the desktop
};


///
/// Dockable application bar flags
///
#define wxABF_ALLOWFLOAT                  (1 <<  0)                                                                                 ///< Is floating application bar allowed?
#define wxABF_ALLOWDOCKTOP                (1 <<  1)                                                                                 ///< Is docking on top of the screen allowed?
#define wxABF_ALLOWDOCKBOTTOM             (1 <<  2)                                                                                 ///< Is docking on bottom of the screen allowed?
#define wxABF_ALLOWDOCKLEFT               (1 <<  3)                                                                                 ///< Is docking left of the screen allowed?
#define wxABF_ALLOWDOCKRIGHT              (1 <<  4)                                                                                 ///< Is docking right of the screen allowed?
#define wxABF_ALLOWDOCKANY                (wxABF_ALLOWDOCKTOP | wxABF_ALLOWDOCKBOTTOM | wxABF_ALLOWDOCKLEFT | wxABF_ALLOWDOCKRIGHT) ///< Is docking at any edge of the screen allowed?
#define wxABF_ALLOWDOCKHORIZONTAL         (wxABF_ALLOWDOCKTOP | wxABF_ALLOWDOCKBOTTOM)                                              ///< Is docking on top or bottom of the screen allowed?
#define wxABF_ALLOWDOCKVERTICAL           (wxABF_ALLOWDOCKLEFT | wxABF_ALLOWDOCKRIGHT)                                              ///< Is docking left or right of the screen allowed?
#define wxABF_ALLOWANY                    (wxABF_ALLOWFLOAT | wxABF_ALLOWDOCKANY)                                                   ///< Is floating and docking at any edge of the screen allowed?

#define wxABF_ALWAYSONTOP                 (1 <<  5) ///< Is application bar always on top?
#define wxABF_ALWAYSONTOPTASKBAR          (1 <<  6) ///< Does application bar follow always on top state of the system taskbar?

#define wxABF_AUTOHIDE                    (1 <<  7) ///< Is application bar setup for auto-hide?
#define wxABF_AUTOHIDETASKBAR             (1 <<  8) ///< Does application bar follow auto-hide state of the system taskbar?

#define wxABF_ALLOWSIZING                 (1 <<  9) ///< Is application bar's sizing allowed?

#define wxABF_HIDETASKBARTABWHENFLOATING  (1 << 10)                                                                                 ///< Should application bar's tab on the system taskbar hide when floating?
#define wxABF_HIDETASKBARTABWHENDOCKED    (1 << 11)                                                                                 ///< Should application bar's tab on the system taskbar hide when docked?
#define wxABF_ALWAYSHIDETASKBARTAB        (wxABF_HIDETASKBARTABWHENFLOATING | wxABF_HIDETASKBARTABWHENDOCKED)                       ///< Should application bar's tab on the system taskbar hide always?

// Internal flags
#define wxABF_FULLSCREENAPPOPEN           (1 << 12) ///< Is full-screen application open?
#define wxABF_AUTOHIDDEN                  (1 << 13) ///< Is application bar auto-hidden right now?


///
/// Dockable application bar template
///
template <class W>
class wxAppBar : public W
{
public:
    ///
    /// Creates new application bar
    ///
    wxAppBar();

    ///
    /// Destructor
    ///
    virtual ~wxAppBar();

protected:
    /// \cond internal
    void PreCreate(wxAppBarState& state, int& flags, const wxSize& size, long& style);
    /// \endcond

public:
    /// \name Application bar general management
    /// @{

    ///
    /// Returns current state of the application bar.
    ///
    inline wxAppBarState GetState() const;

    ///
    /// Returns whether application bar is displayed always on top.
    ///
    /// \returns
    /// - \c true when application bar is always on top
    /// - \c false otherwise
    ///
    inline bool IsAlwaysOnTop() const;

    ///
    /// Sets whether application bar is displayed always on top.
    ///
    /// \param[in] alwaysOnTop Logical variable to control whether always-on-top behaviour is to be enabled (\c true) or disabled (\c false).
    ///
    inline bool SetAlwaysOnTop(bool alwaysOnTop = true);

    ///
    /// Returns if application bar is configured for auto-hide.
    ///
    /// \returns
    /// - \c true if application bar is configured for auto-hide
    /// - \c false otherwise
    ///
    inline bool IsAutoHide() const;

    ///
    /// Sets whether application bar is displayed always on top.
    ///
    /// \param[in] autoHide Logical variable to control whether auto-hide behaviour is to be enabled (\c true) or disabled (\c false).
    ///
    inline bool SetAutoHide(bool autoHide = true);

    ///
    /// Returns if sizing of the application bar is allowed.
    ///
    /// \returns
    /// - \c true if sizing of the application bar is allowed
    /// - \c false otherwise
    ///
    inline bool GetAllowSizing() const;

    ///
    /// Sets whether resizing of the application bar is allowed.
    ///
    /// \param[in] allow Logical variable to control whether resizing is to be enabled (\c true) or disabled (\c false).
    ///
    inline bool SetAllowSizing(bool allow = true);

    ///
    /// Returns if application bar is auto-hidden right now.
    ///
    /// \returns
    /// - \c true if application bar is auto-hidden right now
    /// - \c false otherwise
    inline bool GetAutoHidden() const;

    //bool GetAppBarPlacement(LPAPPBARPLACEMENT lpPlacement) const;
    //bool SetAppBarPlacement(LPCAPPBARPLACEMENT lpPlacement);

    ///
    /// Minimize application bar to the edge of the desktop.
    ///
    /// \param[in] edge The edge at which to dock. Must be either of: wxAppBarState::LEFT, wxAppBarState::TOP, wxAppBarState::RIGHT, or wxAppBarState::BOTTOM.
    /// \param[in] wnd When the undocked and docked window is different, this parameter denotes the undocked version.
    ///
    void MinimiseToEdge(wxAppBarState edge, wxWindow* wnd = NULL);

    ///
    /// Restore application bar from the edge of the desktop.
    ///
    /// \param[in] rect The desired coordinates of the restored window. If NULL internally saved coordinates are used.
    ///
    void MaximiseFromEdge(_In_opt_ const RECT* rect = NULL);

    ///
    /// Restore application bar from the edge of the desktop.
    ///
    /// \param[in] wnd When the undocked and docked window is different, this parameter denotes the undocked version.
    ///
    void MaximiseFromEdge(_In_ wxWindow *wnd);

    ///
    /// Shows or hides auto-hide application bar.
    ///
    /// \param[in] show Logical variable to control whether application bar is be shown (\c true) or hidden (\c false).
    ///
    void ShowAutoHideAppBar(bool show = true);

    ///
    /// Hides auto-hide application bar.
    ///
    inline void HideAutoHideAppBar() { ShowAutoHideAppBar(false); }

    /// @}

protected:
    /// \name Notification handlers
    /// @{

    ///
    /// Notification handler when the new state of the application bar is proposed.
    ///
    /// Derived classes can implement their own. However, overriden virtual method should call the parent's implementation too.
    ///
    /// \param[in] stateNew New state about to take effect.
    ///
    virtual void OnChangeState(wxAppBarState stateNew);

    ///
    /// Notification handler when the Windows' taskbar state changes.
    ///
    /// Derived classes can implement their own. However, overriden virtual method should call the parent's implementation too.
    ///
    /// \param[in] state New taskbar state.
    ///
    virtual void OnChangeTaskBarState(UINT_PTR state);

    ///
    /// Notification handler when desktop windows are being arranged (cascaded, tiled, ...)
    ///
    /// Derived classes can implement their own. However, overriden virtual method should call the parent's implementation too.
    ///
    /// \param[in] beginning \c true when windows arrangement starts and \c false when arrangement ends.
    ///
    virtual void OnWindowsArrange(bool beginning);

    ///
    /// Called when application bar was forced from auto-hide to normal docking.
    ///
    /// Default implementation displays a warning dialog.
    ///
    virtual void OnAutoHideDenied();

    /// @}

protected:
    /// \cond internal
    virtual WXLRESULT MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam);
    /// \endcond

private:
    /// \cond internal
    inline _Success_(return != 0) bool DockAppBar(_In_ wxAppBarState state);
    inline _Success_(return != 0) bool UndockAppBar();
    inline _Success_(return != 0) bool RegisterAutoHide(_In_ wxAppBarState state);
    inline _Success_(return != 0) bool UnregisterAutoHide(_In_ wxAppBarState state);
    inline _Success_(return != 0) bool GetDockedRect(_In_ wxAppBarState state, _Out_ LPRECT rect) const;
    inline _Success_(return != 0) bool GetAutoHideRect(_In_ wxAppBarState state, _In_ bool bAutoHidden, _Out_ LPRECT rect) const;
    /// \endcond

protected:
    wxAppBarState m_state;          ///< Current state of the application bar
    wxAppBarState m_stateDesired;   ///< Desired state of the application bar while moving/resizing
    int m_flags;                    ///< Flags describing application bar's behaviour

    SIZE m_sizeFloat;               ///< Window size when floating (we need it to restore floating size, when we undock)
    SIZE m_sizeDocked;              ///< Size of the window when docked (height when wxAppBarState::TOP or wxAppBarState::BOTTOM, width when wxAppBarState::LEFT or wxAppBarState::RIGHT)
    SIZE m_sizeMin;                 ///< Minimum window size

    UINT_PTR m_stateTaskBar;        ///< TaskBar's current state
    UINT_PTR m_timerID;             ///< Application bar's timer id.

    ITaskbarList *m_taskbarList;    ///< Windows's taskbar list interface
};


#ifdef __VISUALC__
// non dll-interface class 'xxx' used as base for dll-interface class 'yyy'
#pragma warning (push)
#pragma warning (disable:4275)
#endif

///
/// Dockable application bar frame
///
class WXEXTEND_API wxAppBarFrame : public wxAppBar<wxFrame>
{
public:
    ///
    /// Creates application bar frame
    ///
    wxAppBarFrame();

    ///
    /// Creates application bar frame
    ///
    wxAppBarFrame(wxWindow *parent,
        wxWindowID id,
        const wxString& title,
        wxAppBarState state = wxAppBarState::FLOAT,
        int flags = wxABF_ALLOWANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE,
        const wxString& name = wxFrameNameStr);

    ///
    /// Creates application bar frame
    ///
    bool Create(wxWindow *parent,
        wxWindowID id,
        const wxString& title,
        wxAppBarState state = wxAppBarState::FLOAT,
        int flags = wxABF_ALLOWANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE,
        const wxString& name = wxFrameNameStr);
};


///
/// Dockable application bar dialog
///
class WXEXTEND_API wxAppBarDialog : public wxAppBar<wxDialog>
{
public:
    ///
    /// Creates application bar dialog
    ///
    wxAppBarDialog();

    ///
    /// Creates application bar dialog
    ///
    wxAppBarDialog(wxWindow *parent,
        wxWindowID id,
        const wxString& title,
        wxAppBarState state = wxAppBarState::FLOAT,
        int flags = wxABF_ALLOWANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxDialogNameStr);

    ///
    /// Creates application bar dialog
    ///
    bool Create(wxWindow *parent,
        wxWindowID id,
        const wxString& title,
        wxAppBarState state = wxAppBarState::FLOAT,
        int flags = wxABF_ALLOWANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxDialogNameStr);
};

#ifdef __VISUALC__
#pragma warning(pop)
#endif


///
/// Returns if the application bar state represents docked state.
///
/// \param[in] state The state of the application bar
///
/// \returns
/// - \c true if the application bar state represents docked state
/// - \c false otherwise
///
inline bool wxAppBarIsDocked(wxAppBarState state)
{
    return wxAppBarState::LEFT <= state && state <= wxAppBarState::BOTTOM;
}


///
/// Returns if the application bar state represents vertically docked state.
///
/// \param[in] state The state of the application bar
///
/// \returns
/// - \c true if the application bar state represents vertically docked state
/// - \c false otherwise
///
inline bool wxAppBarIsDockedVert(wxAppBarState state)
{
    return state == wxAppBarState::LEFT || state == wxAppBarState::RIGHT;
}


///
/// Returns if the application bar state represents horizontally docked state.
///
/// \param[in] state The state of the application bar
///
/// \returns
/// - \c true if the application bar state represents horizontally docked state
/// - \c false otherwise
///
inline bool wxAppBarIsDockedHoriz(wxAppBarState state)
{
    return state == wxAppBarState::TOP || state == wxAppBarState::BOTTOM;
}


///
/// Returns the window above which to Z-order the application bar.
///
/// \param[in] state The state of the application bar
/// \param[in] flags The flags of the application bar
///
/// \returns
/// The handle of the window
///
inline WXHWND wxAppBarGetZWnd(wxAppBarState state, int flags)
{
    if (flags & wxABF_FULLSCREENAPPOPEN) {
        // If full screen app is open, clear the always-on-top flag.
        return HWND_NOTOPMOST;
    }

    //_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
    //if (::IsWindow(pThreadState->m_hTrackingWindow)) {
    //    // We're tracking another window/menu, position behind it.
    //    return pThreadState->m_hTrackingWindow;
    // }

    if (state == wxAppBarState::FLOAT) {
        // When floating, decide according to the flags.
        return (flags & wxABF_ALWAYSONTOP) ? HWND_TOPMOST : HWND_NOTOPMOST;
    } else if (wxAppBarIsDocked(state)) {
        if (flags & wxABF_AUTOHIDE) {
            // Auto-hidden docked application bar is always on top.
            return HWND_TOPMOST;
        }
        
        if (flags & wxABF_ALWAYSONTOP) {
            // Regular docked always-on-top application bar.
            WXHWND hWndTaskbar = ::FindWindow(_T("Shell_TrayWnd"), _T(""));
            if (hWndTaskbar) {
                // We found the taskbar window. Position directly after it. Otherwise our window overlaps Vista's Start button orb.
                return hWndTaskbar;
            } else {
                // Only always-on-top windows are allowed to resize properly outside the desktop rect.
                // If window is docked and not always on top, resizing a window to smaller size is obstructed by desktop rect limit.
                return HWND_TOPMOST;
            }
        }


        // Regular docked non-always-on-top application bar.
        return HWND_NOTOPMOST;
    } else {
        // Unknown state. Do nothing.
        wxFAIL_MSG(wxT("unknown application bar state"));
        return HWND_TOP;
    }
}


///
/// Returns the current taskbar state.
///
/// \returns
/// The taskbar state
///
/// \sa [SHAppBarMessage function](https://msdn.microsoft.com/en-us/library/windows/desktop/bb762108.aspx)
///
inline UINT_PTR wxAppBarGetTaskBarState()
{
    APPBARDATA abd = { sizeof(abd) };
    return ::SHAppBarMessage(ABM_GETSTATE, &abd);
}


/// @}

//////////////////////////////////////////////////////////////////////////
// wxAppBar
//////////////////////////////////////////////////////////////////////////

template <class W>
wxAppBar<W>::wxAppBar() :
    m_state(wxAppBarState::UNKNOWN),
    m_stateDesired(wxAppBarState::UNKNOWN),
    m_flags(0),
    m_stateTaskBar(0),
    m_timerID(0),
    m_taskbarList(NULL)
{
    m_sizeFloat .cx = -1;
    m_sizeFloat .cy = -1;
    m_sizeDocked.cx = -1;
    m_sizeDocked.cy = -1;
    m_sizeMin   .cx = -1;
    m_sizeMin   .cy = -1;
}


template <class W>
wxAppBar<W>::~wxAppBar()
{
    if (m_taskbarList)
        m_taskbarList->Release();
}


/// \cond internal
template <class W>
void wxAppBar<W>::PreCreate(wxAppBarState& state, int& flags, const wxSize& size, long& style)
{
    wxASSERT_MSG(!m_taskbarList || !m_timerID, wxT("application bar is already initialized"));

    // Save initial floating window size.
    m_sizeFloat.cx = size.x;
    m_sizeFloat.cy = size.y;

    // Save initial docked window width/height.
    m_sizeDocked.cx = size.x;
    m_sizeDocked.cy = size.y;

    // Save initial state and flags.
    m_state        = state;
    m_stateDesired = wxAppBarState::UNKNOWN;
    m_flags        = flags;

    // If any taskbar list tab's hiding is in affect, set application bar's style as tool window to avoid being displayed on the taskbar initially.
    if (state == wxAppBarState::FLOAT) {
        if (flags & wxABF_HIDETASKBARTABWHENFLOATING) {
            // Hide our application bar's entry on the Windows's taskbar.
            style |= wxFRAME_TOOL_WINDOW;
        } else if (flags & wxABF_HIDETASKBARTABWHENDOCKED) {
            // Show our application bar's entry on the Windows's taskbar.
            style &= ~wxFRAME_TOOL_WINDOW;
        }
    } else if (wxAppBarIsDocked(state)) {
        if (flags & wxABF_HIDETASKBARTABWHENDOCKED) {
            // Hide our application bar's entry on the Windows's taskbar.
            style |= wxFRAME_TOOL_WINDOW;
        } else if (flags & wxABF_HIDETASKBARTABWHENFLOATING) {
            // Show our application bar's entry on the Windows's taskbar.
            style &= ~wxFRAME_TOOL_WINDOW;
        }
    } else {
        // Unknown state.
        wxFAIL_MSG(wxT("unknown application bar state"));
    }

    // Find the taskbar list's interface.
    HRESULT hr = ::CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList, (LPVOID*)&m_taskbarList);
    if (SUCCEEDED(hr)) {
        hr = m_taskbarList->HrInit();
        if (FAILED(hr)) {
            wxFAIL_MSG(wxString::Format(wxT("ITaskbarList::HrInit() failed 0x%x"), hr));
            m_taskbarList->Release();
            m_taskbarList = NULL;
        }
    } else
        wxFAIL_MSG(wxString::Format(wxT("TaskbarList creation failed 0x%x"), hr));
}
/// \endcond


template <class W>
inline wxAppBarState wxAppBar<W>::GetState() const
{
    return m_stateDesired != wxAppBarState::UNKNOWN ? m_stateDesired : m_state;
}


template <class W>
inline bool wxAppBar<W>::IsAlwaysOnTop() const
{
    return (m_flags & wxABF_ALWAYSONTOP) ? true : false;
}


template <class W>
inline bool wxAppBar<W>::SetAlwaysOnTop(bool alwaysOnTop)
{
    if (alwaysOnTop)
        m_flags |= wxABF_ALWAYSONTOP;
    else
        m_flags &= ~wxABF_ALWAYSONTOP;

    if (::IsWindowVisible(m_hWnd)) {
        // Set the Z-order.
        wxCHECK(::SetWindowPos(m_hWnd, wxAppBarGetZWnd(m_state, m_flags), 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOSENDCHANGING), false);
    }

    return true;
}


template <class W>
inline bool wxAppBar<W>::IsAutoHide() const
{
    return (m_flags & wxABF_AUTOHIDE) ? true : false;
}


template <class W>
inline bool wxAppBar<W>::SetAutoHide(bool autoHide)
{
    bool autoHidePrev = IsAutoHide();

    if (autoHide)
        m_flags |= wxABF_AUTOHIDE;
    else
        m_flags &= ~wxABF_AUTOHIDE;

    if (autoHidePrev != autoHide && wxAppBarIsDocked(m_state) && ::IsWindowVisible(m_hWnd)) {
        if (autoHide) {
            // Application bar should be auto-hidden. Try to setup it so.

            // We undock to free the space before registering auto-hide, otherwise system will leave application bar's space reserved.
            UndockAppBar();

            // Register auto-hide application bar.
            if (!RegisterAutoHide(m_state)) {
                // Auto-hide failed; some other application bar must be hidden on this edge already. Dock back instead.
                DockAppBar(m_state);
                return false;
            }
        } else {
            // Unregister the auto-hidden application bar and dock.
            UnregisterAutoHide(m_state);
            DockAppBar(m_state);
        }
    }

    return true;
}


template <class W>
inline bool wxAppBar<W>::GetAllowSizing() const
{
    return (m_flags & wxABF_ALLOWSIZING) ? true : false;
}


template <class W>
inline bool wxAppBar<W>::SetAllowSizing(bool allow)
{
    if (allow)
        m_flags |= wxABF_ALLOWSIZING;
    else
        m_flags &= ~wxABF_ALLOWSIZING;

    return true;
}


template <class W>
inline bool wxAppBar<W>::GetAutoHidden() const
{
    return (m_flags & wxABF_AUTOHIDDEN) ? true : false;
}


//template <class W>
//bool wxAppBar<W>::GetAppBarPlacement(LPAPPBARPLACEMENT lpPlacement) const
//{
//    wxASSERT(lpPlacement);
//
//    if (lpPlacement->dwSize >= sizeof(APPBARPLACEMENT1)) {
//        lpPlacement->dwState = (DWORD)m_state;
//        lpPlacement->dwFlags = m_flags;
//        if (m_state == wxAppBarState::FLOAT) {
//            // Current application bar's rect is floating rect.
//            lpPlacement->rcFloat = m_rect;
//        } else if (wxAppBarIsDocked(m_state)) {
//            // Application bar is docked. Calc floating rect from m_sizeFloat.
//            lpPlacement->rcFloat.left   = 0;
//            lpPlacement->rcFloat.top    = 0;
//            lpPlacement->rcFloat.right  = m_sizeFloat.cx;
//            lpPlacement->rcFloat.bottom = m_sizeFloat.cy;
//        } else {
//            // Application bar's state is unknown.
//            return false;
//        }
//        lpPlacement->szDocked = m_sizeDocked;
//    }
//
//    lpPlacement->dwSize = sizeof(*lpPlacement);
//
//    return true;
//}
//
//
//template <class W>
//bool wxAppBar<W>::SetAppBarPlacement(LPCAPPBARPLACEMENT lpPlacement)
//{
//    wxASSERT(lpPlacement);
//
//    if (lpPlacement->dwSize >= sizeof(APPBARPLACEMENT1)) {
//        if (lpPlacement->dwState != wxAppBarState::FLOAT && !wxAppBarIsDocked(lpPlacement->dwState)) {
//            // The state is unknown. Abort, before we mix up internal state.
//            return false;
//        }
//
//        // Clean previous docking/auto-hide settings if required.
//        if (wxAppBarIsDocked(m_state) &&
//            (lpPlacement->dwState == wxAppBarState::FLOAT || lpPlacement->dwState != m_state && wxAppBarIsDocked(lpPlacement->dwState)))
//        {
//            if (IsAutoHide())
//                UnregisterAutoHide(m_state);
//            else if (lpPlacement->dwState == wxAppBarState::FLOAT)
//                UndockAppBar();
//        }
//
//        // Update application bar's flags, size and position.
//        m_flags |= wxABF_POSITIONSET;
//        m_sizeDocked = lpPlacement->szDocked;
//        if (lpPlacement->dwState == wxAppBarState::FLOAT) {
//            m_rect = lpPlacement->rcFloat;
//        } else if (wxAppBarIsDocked(lpPlacement->dwState)) {
//            m_sizeFloat.cx = lpPlacement->rcFloat.right  - lpPlacement->rcFloat.left;
//            m_sizeFloat.cy = lpPlacement->rcFloat.bottom - lpPlacement->rcFloat.top;
//            GetDockedRect(lpPlacement->dwState, &m_rect);
//        } else {
//            // Application bar's state is unknown.
//            wxFAIL;
//            return false;
//        }
//
//        // Notify about the change of state.
//        OnChangeState(lpPlacement->dwState);
//        m_state = lpPlacement->dwState;
//
//        SetAutoHide(lpPlacement->dwFlags & wxABF_AUTOHIDE);
//        SetAlwaysOnTop(lpPlacement->dwFlags & wxABF_ALWAYSONTOP);
//    }
//
//    return true;
//}


template <class W>
void wxAppBar<W>::MinimiseToEdge(wxAppBarState edge, wxWindow *wnd)
{
    wxASSERT(wxAppBarIsDocked(edge));

    WXHWND hWnd;
    if (!wnd) {
        // No other window was specified. Minimize ourself.
        wnd  = this;
        hWnd = m_hWnd;
    } else
        hWnd = wnd->GetHWND();

    // If our window is hidden, there's nothing we can do.
    if (hWnd == m_hWnd && !::IsWindowVisible(m_hWnd))
        return;

    if (m_state == wxAppBarState::FLOAT) {
        // Remember the last floating size.
        RECT rect = {};
        wxVERIFY(::GetWindowRect(hWnd, &rect));
        m_sizeFloat.cx = rect.right  - rect.left;
        m_sizeFloat.cy = rect.bottom - rect.top;
    }

    RECT rectTo;
    if (IsAutoHide())
        GetAutoHideRect(edge, false, &rectTo);
    else
        GetDockedRect(edge, &rectTo);

    if (::wxGetDoWndAnimation()) {
        // Do the animation.
        RECT rectFrom;
        wxVERIFY(::GetWindowRect(hWnd, &rectFrom));
        wxVERIFY(::DrawAnimatedRects(hWnd, IDANI_CAPTION, &rectFrom, &rectTo));
    }

    // Notify about the change of state.
    OnChangeState(edge);
    m_state = edge;

    if (hWnd != m_hWnd) {
        // Hide the source window.
        wnd->Hide();
        // ::SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) &~ WS_VISIBLE);

        // Show the application bar.
        Show();
    } else {
        if (IsAutoHide()) {
            // Register auto-hide application bar.
            RegisterAutoHide(edge);
        } else {
            // Auto-hide failed or wasn't desired at all.
            DockAppBar(edge);
        }
    }

    ::SetActiveWindow(m_hWnd);
}


template <class W>
void wxAppBar<W>::MaximiseFromEdge(_In_opt_ const RECT* rect)
{
    wxASSERT(::IsWindowVisible(m_hWnd));

    RECT rectTo;

    if (!rect) {
        // Calculate the destination rect.
        rectTo.left   = (::GetSystemMetrics(SM_CXSCREEN) - m_sizeFloat.cx) / 2;
        rectTo.top    = (::GetSystemMetrics(SM_CYSCREEN) - m_sizeFloat.cy) / 2;
        rectTo.right  = rectTo.left + m_sizeFloat.cx;
        rectTo.bottom = rectTo.top  + m_sizeFloat.cy;

        rect = &rectTo;
    } else {
        m_sizeFloat.cx = rect->right  - rect->left;
        m_sizeFloat.cy = rect->bottom - rect->top;
    }

    if (::wxGetDoWndAnimation()) {
        // Do the animation.
        RECT rectFrom;
        wxVERIFY(::GetWindowRect(m_hWnd, &rectFrom));
        wxVERIFY(::DrawAnimatedRects(m_hWnd, IDANI_CAPTION, &rectFrom, rect));
    }

    // Clean previous docking/auto-hide settings if required.
    if (wxAppBarIsDocked(m_state)) {
        if (IsAutoHide())
            UnregisterAutoHide(m_state);
        else
            UndockAppBar();
    }

    // Notify about the change of state.
    OnChangeState(wxAppBarState::FLOAT);
    m_state = wxAppBarState::FLOAT;

    wxVERIFY(::SetWindowPos(m_hWnd, wxAppBarGetZWnd(wxAppBarState::FLOAT, m_flags), rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top, SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_FRAMECHANGED));
}


template <class W>
void wxAppBar<W>::MaximiseFromEdge(_In_ wxWindow *wnd)
{
    wxASSERT(wnd);
    wxASSERT(::IsWindowVisible(m_hWnd));

    WXHWND hWnd = wnd->GetHWND();

    RECT rectTo = {};
    wxVERIFY(::GetWindowRect(hWnd, &rectTo));
    m_sizeFloat.cx = rectTo.right  - rectTo.left;
    m_sizeFloat.cy = rectTo.bottom - rectTo.top;

    if (::wxGetDoWndAnimation()) {
        // Do the animation.
        RECT rectFrom;
        wxVERIFY(::GetWindowRect(m_hWnd, &rectFrom));
        wxVERIFY(::DrawAnimatedRects(hWnd, IDANI_CAPTION, &rectFrom, &rectTo));
    }

    // Hide our window and show the destination window.
    Hide();
    wnd->Show();
    // ::SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) | WS_VISIBLE);
    wxVERIFY(::SetForegroundWindow(hWnd));
    ::SetActiveWindow(hWnd);
    // wxVERIFY(::RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_FRAME | RDW_INVALIDATE | RDW_ERASE));
}


template <class W>
void wxAppBar<W>::ShowAutoHideAppBar(bool show)
{
    RECT rcEnd;
    bool
        bFullDragOn,
        bHidden = GetAutoHidden(),
        bVisible = ::IsWindowVisible(m_hWnd) ? true : false;

    if (!IsAutoHide() || bHidden != show) {
        // We're not setup for auto-hide or already in the desired state.
        return;
    }

    // Get our end window location.
    GetAutoHideRect(m_state, !bHidden, &rcEnd);

    if (bVisible) {
        RECT rcStart;

        // Only slide the window if the user has FullDrag turned on.
        if (!::SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &bFullDragOn, 0))
            bFullDragOn = false;

        // Get our start window location.
        GetAutoHideRect(m_state, bHidden, &rcStart);

        if (bFullDragOn && (rcStart.left != rcEnd.left || rcStart.top != rcEnd.top || rcStart.right != rcEnd.right || rcStart.bottom != rcEnd.bottom)) {
            #pragma warning(push)
            #pragma warning(disable: 28159)

            // Get our starting and ending time.
            DWORD dwTimeStart = ::GetTickCount();
            DWORD dwTimeElapsed;
            RECT rcDelta;

            // Calculate difference between ending and starting rectangle.
            rcDelta.left   = rcEnd.left   - rcStart.left;
            rcDelta.top    = rcEnd.top    - rcStart.top;
            rcDelta.right  = rcEnd.right  - rcStart.right;
            rcDelta.bottom = rcEnd.bottom - rcStart.bottom;

            while ((dwTimeElapsed = ::GetTickCount() - dwTimeStart) < wxABT_AUTOHIDETIME) {
                // Do the linear interpolation.
                RECT rect;
                rect.left   = rcStart.left   + ::MulDiv(rcDelta.left,   dwTimeElapsed, wxABT_AUTOHIDETIME);
                rect.top    = rcStart.top    + ::MulDiv(rcDelta.top,    dwTimeElapsed, wxABT_AUTOHIDETIME);
                rect.right  = rcStart.right  + ::MulDiv(rcDelta.right,  dwTimeElapsed, wxABT_AUTOHIDETIME);
                rect.bottom = rcStart.bottom + ::MulDiv(rcDelta.bottom, dwTimeElapsed, wxABT_AUTOHIDETIME);

                // Show the window at its changed position
                wxVERIFY(::SetWindowPos(m_hWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOACTIVATE));
                wxVERIFY(::UpdateWindow(m_hWnd));
            }

            #pragma warning(pop)
        }
    }

    if (show)
        m_flags &= ~wxABF_AUTOHIDDEN;
    else
        m_flags |= wxABF_AUTOHIDDEN;

    if (bVisible) {
        wxVERIFY(::SetWindowPos(m_hWnd, NULL, rcEnd.left, rcEnd.top, rcEnd.right - rcEnd.left, rcEnd.bottom - rcEnd.top, SWP_NOZORDER | SWP_NOACTIVATE));
        wxVERIFY(::UpdateWindow(m_hWnd));
        // Reset auto-hide timer.
        m_timerID = ::SetTimer(m_hWnd, wxABT_AUTOHIDETIMERID, wxABT_AUTOHIDETIMERINTERVAL, NULL);
    }
}


template <class W>
void wxAppBar<W>::OnChangeState(wxAppBarState stateNew)
{
    if (stateNew == wxAppBarState::FLOAT) {
        if (m_flags & wxABF_HIDETASKBARTABWHENFLOATING) {
            // Hide our application bar's entry on the Windows's taskbar.
            wxModifyStyleEx(m_hWnd, 0, WS_EX_TOOLWINDOW);
            if (m_taskbarList)
                wxVERIFY(SUCCEEDED(m_taskbarList->DeleteTab(m_hWnd)));
        } else if (m_flags & wxABF_HIDETASKBARTABWHENDOCKED) {
            // Show our application bar's entry on the Windows's taskbar.
            wxModifyStyleEx(m_hWnd, WS_EX_TOOLWINDOW, 0);
            if (m_taskbarList)
                wxVERIFY(SUCCEEDED(m_taskbarList->AddTab(m_hWnd)));
        }
    } else if (wxAppBarIsDocked(stateNew)) {
        if (m_flags & wxABF_HIDETASKBARTABWHENDOCKED) {
            // Hide our application bar's entry on the Windows's taskbar.
            wxModifyStyleEx(m_hWnd, 0, WS_EX_TOOLWINDOW);
            if (m_taskbarList)
                wxVERIFY(SUCCEEDED(m_taskbarList->DeleteTab(m_hWnd)));
        } else if (m_flags & wxABF_HIDETASKBARTABWHENFLOATING) {
            // Show our application bar's entry on the Windows's taskbar.
            wxModifyStyleEx(m_hWnd, WS_EX_TOOLWINDOW, 0);
            if (m_taskbarList)
                wxVERIFY(SUCCEEDED(m_taskbarList->AddTab(m_hWnd)));
        }
    } else {
        // Unknown state.
        wxFAIL_MSG(wxT("unknown application bar state"));
    }
}


template <class W>
void wxAppBar<W>::OnChangeTaskBarState(UINT_PTR state)
{
    if (state != m_stateTaskBar) {
        // No change, no fun.
        return;
    }

    if ((m_flags & wxABF_ALWAYSONTOPTASKBAR) &&
        (m_stateTaskBar & ABS_ALWAYSONTOP) != (state & ABS_ALWAYSONTOP)) {
        // Always-on-top state of the taskbar changed and we're supposed to mimic it.
        SetAlwaysOnTop((state & ABS_ALWAYSONTOP) ? true : false);
    }

    if ((m_flags & wxABF_AUTOHIDETASKBAR) &&
        (m_stateTaskBar & ABS_AUTOHIDE) != (state & ABS_AUTOHIDE)) {
        // Auto-hide state of the taskbar changed and we're supposed to mimic it.
        SetAutoHide((state & ABS_AUTOHIDE) ? true : false);
    }

    // Remember the state.
    m_stateTaskBar = state;
}


template <class W>
void wxAppBar<W>::OnWindowsArrange(bool WXUNUSED(beginning))
{
}


template <class W>
void wxAppBar<W>::OnAutoHideDenied()
{
    wxMessageBox(_("There is already an auto hidden bar on this edge.\nOnly one auto hidden bar is allowed on each edge.\nAuto-hide feature is now off."), _("Warning"), wxOK | wxICON_WARNING, this);
}


/// \cond internal
template <class W>
WXLRESULT wxAppBar<W>::MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam)
{
    switch (message) {
    case WM_CREATE: {
        WXLRESULT lResult = W::MSWWindowProc(message, wParam, lParam);

        // Register our application bar.
        APPBARDATA abd = { sizeof(abd), m_hWnd, WM_AB_NOTIFY, static_cast<UINT>(m_state) };
        wxCHECK(::SHAppBarMessage(ABM_NEW, &abd), false);

        // Get the state of the Windows taskbar.
        m_stateTaskBar = wxAppBarGetTaskBarState();

        if (m_flags & wxABF_AUTOHIDETASKBAR) {
            // Mimic the auto-hide state of taskbar.
            SetAutoHide((m_stateTaskBar & ABS_AUTOHIDE) ? true : false);
        }

        if (m_flags & wxABF_ALWAYSONTOPTASKBAR) {
            // Mimic the always-on-top state of taskbar.
            SetAlwaysOnTop((m_stateTaskBar & ABS_ALWAYSONTOP) ? true : false);
        }

        return lResult;
    }

    case WM_DESTROY: {
        wxASSERT_MSG(m_timerID == 0, wxT("timer still active"));

        // Remove the application bar.
        APPBARDATA abd = { sizeof(abd), m_hWnd };
        wxVERIFY(::SHAppBarMessage(ABM_REMOVE, &abd));

        return W::MSWWindowProc(message, wParam, lParam);
    }

    case WM_SHOWWINDOW:
        if (wParam) {
            // Do the false change of state notification, to allow initialization.
            OnChangeState(m_state);

            if (wxAppBarIsDocked(m_state)) {
                if (IsAutoHide()) {
                    // Register auto-hide application bar.
                    RegisterAutoHide(m_state);
                } else {
                    // Auto-hide failed or wasn't desired at all.
                    DockAppBar(m_state);
                }
            }

            // We're all set. Show the window now.
            return W::MSWWindowProc(message, wParam, lParam);
        } else {
            // Hide the window first, to avoid flicker.
            WXLRESULT lResult = W::MSWWindowProc(message, wParam, lParam);

            // Clean previous docking/auto-hide settings if required.
            if (wxAppBarIsDocked(m_state)) {
                if (IsAutoHide())
                    UnregisterAutoHide(m_state);
                else
                    UndockAppBar();
            }

            return lResult;
        }

    case WM_WINDOWPOSCHANGING: {
        if (m_state != m_stateDesired && wxAppBarIsDocked(m_stateDesired)) {
            wxASSERT(lParam);
            LPWINDOWPOS lpwndpos = (LPWINDOWPOS)lParam;
            if (lpwndpos) {
                // When about to get docked, fix position and size to avoid Aero Snap interfering with window size.
                RECT rect;
                GetDockedRect(m_stateDesired, &rect);
                lpwndpos->x  = rect.left;
                lpwndpos->y  = rect.top;
                lpwndpos->cx = rect.right  - rect.left;
                lpwndpos->cy = rect.bottom - rect.top;
                lpwndpos->flags &= ~(SWP_NOMOVE | SWP_NOSIZE);
            }
        }

        return W::MSWWindowProc(message, wParam, lParam);
    }

    case WM_WINDOWPOSCHANGED: {
        WXLRESULT lResult = W::MSWWindowProc(message, wParam, lParam);

        if (wxAppBarIsDocked(m_state)) {
            // When our window changes position, tell the Shell so that any
            // auto-hidden application bar on our edge stays on top of our window making it
            // always accessible to the user.
            APPBARDATA abd = { sizeof(abd), m_hWnd };
            wxVERIFY(::SHAppBarMessage(ABM_WINDOWPOSCHANGED, &abd));
        }

        return lResult;
    }

    case WM_ENTERSIZEMOVE:
        m_stateDesired = m_state;
        return W::MSWWindowProc(message, wParam, lParam);

    case WM_EXITSIZEMOVE: {
        WXLRESULT lResult = W::MSWWindowProc(message, wParam, lParam);

        // Clean previous docking/auto-hide settings if required.
        if (wxAppBarIsDocked(m_state) &&
            (m_stateDesired == wxAppBarState::FLOAT || m_stateDesired != m_state && wxAppBarIsDocked(m_stateDesired)))
        {
            if (IsAutoHide())
                UnregisterAutoHide(m_state);
            else if (m_stateDesired == wxAppBarState::FLOAT)
                UndockAppBar();
        }

        // Setup new docking/auto-hide settings.
        if (wxAppBarIsDocked(m_stateDesired)) {
            if (IsAutoHide()) {
                // Application bar should be auto-hide. Try to setup it as so.
                // Register auto-hide application bar.
                RegisterAutoHide(m_stateDesired);
            } else {
                // Auto-hide failed or wasn't desired at all.
                DockAppBar(m_stateDesired);
            }
        }

        // Notify about the change of state.
        OnChangeState(m_stateDesired);
        m_state = m_stateDesired;
        m_stateDesired = wxAppBarState::UNKNOWN;

        return lResult;
    }

    case WM_MOVING: {
        WXLRESULT lResult = W::MSWWindowProc(message, wParam, lParam);

        wxASSERT(lParam);
        LPRECT lpRect = (LPRECT)lParam;

        // Phase 1. - Determine the desired state (which screen edge or floating) according to the mouse position.

        wxAppBarState uStateDesiredPrev = m_stateDesired;
        DWORD dwPoint = ::GetMessagePos();
        wxPoint ptMouse(GET_X_LPARAM(dwPoint), GET_Y_LPARAM(dwPoint));

        m_stateDesired = wxAppBarState::UNKNOWN;

        if ((m_flags & wxABF_ALLOWFLOAT) && (::GetKeyState(VK_CONTROL) < 0 || !(m_flags & wxABF_ALLOWDOCKANY))) {
            // The application bar's style allows floating and user is holding down the Ctrl key, or docking is disabled anyway, so we'll force float.
            m_stateDesired = wxAppBarState::FLOAT;
        } else {
            RECT rcWorkArea = {};
            INT iDist, iDistMin = INT_MAX;

            // Get the rectangle that bounds the size of the screen
            // minus any docked (but not-autohidden) AppBars.
            wxVERIFY(::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0));

            // Test all four edges, to find the closest one.
            if ((m_flags & wxABF_ALLOWDOCKTOP) && (iDist = ptMouse.y - rcWorkArea.top) < iDistMin) {
                m_stateDesired = wxAppBarState::TOP;
                iDistMin = iDist;
            }
            if ((m_flags & wxABF_ALLOWDOCKBOTTOM) && (iDist = rcWorkArea.bottom - ptMouse.y) < iDistMin) {
                m_stateDesired = wxAppBarState::BOTTOM;
                iDistMin = iDist;
            }
            if ((m_flags & wxABF_ALLOWDOCKLEFT) && (iDist = ptMouse.x - rcWorkArea.left) < iDistMin) {
                m_stateDesired = wxAppBarState::LEFT;
                iDistMin = iDist;
            }
            if ((m_flags & wxABF_ALLOWDOCKRIGHT) && (iDist = rcWorkArea.right - ptMouse.x) < iDistMin) {
                m_stateDesired = wxAppBarState::RIGHT;
                iDistMin = iDist;
            }
            if ((m_flags & wxABF_ALLOWFLOAT) && (iDist = wxMax(::GetSystemMetrics(SM_CXVSCROLL), ::GetSystemMetrics(SM_CYHSCROLL))) < iDistMin) {
                m_stateDesired = wxAppBarState::FLOAT;
                iDistMin = iDist;
            }
        }

        wxASSERT_MSG(m_stateDesired != wxAppBarState::UNKNOWN, wxT("undetermined application bar state"));

        // Phase 2. - Calculate the desired rectangle, according to the desired state.

        if (m_stateDesired == wxAppBarState::FLOAT) {
            if (wxAppBarIsDocked(uStateDesiredPrev)) {
                // We just switched from docked to floating state. Align the window according to the mouse pointer.
                lpRect->left   = ptMouse.x - m_sizeFloat.cx / 2;
                lpRect->top    = ptMouse.y;

                // We also resize back to floating window size.
                lpRect->right  = lpRect->left + m_sizeFloat.cx;
                lpRect->bottom = lpRect->top + m_sizeFloat.cy;
            }
        } else if (wxAppBarIsDocked(m_stateDesired)) {
            if (IsAutoHide()) {
                // Calculate auto-hide window rect.
                GetAutoHideRect(m_stateDesired, false, lpRect);
            } else {
                // Calculate docked window rect.
                GetDockedRect(m_stateDesired, lpRect);
            }
        } else {
            // Window is not floating. It's not docked either. Then what?
            wxFAIL_MSG(wxT("unknown application bar state"));
        }

        if (m_stateDesired != uStateDesiredPrev) {
            // Notify about the proposed change of state, but don't change the state yet.
            OnChangeState(m_stateDesired);
        }

        return lResult;
    }

    case WM_SIZING: {
        wxASSERT(lParam);
        LPRECT lpRect = (LPRECT)lParam;

        if (m_stateDesired == wxAppBarState::FLOAT) {
            // Remember the floating window size.
            m_sizeFloat.cx = lpRect->right  - lpRect->left;
            m_sizeFloat.cy = lpRect->bottom - lpRect->top;
        } else if (wxAppBarIsDocked(m_stateDesired)) {
            // Remember the docked window size.
            if (wxAppBarIsDockedVert(m_stateDesired))
                m_sizeDocked.cx = lpRect->right - lpRect->left;
            else
                m_sizeDocked.cy = lpRect->bottom - lpRect->top;
        } else {
            // Unknown state.
            wxFAIL_MSG(wxT("unknown application bar state"));
        }

        return W::MSWWindowProc(message, wParam, lParam);
    }

    case WM_GETMINMAXINFO: {
        WXLRESULT lResult = W::MSWWindowProc(message, wParam, lParam);

        wxASSERT(lParam);
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;

        // Convert client size to window size.
        RECT rectClient = {};
        wxVERIFY(::GetClientRect(m_hWnd, &rectClient));
        if (rectClient.right - rectClient.left && rectClient.bottom - rectClient.top) {
            RECT rectWindow = {};
            wxVERIFY(::GetWindowRect(m_hWnd, &rectWindow));
            lpMMI->ptMinTrackSize.x = m_sizeMin.cx + (rectWindow.right  - rectWindow.left) - (rectClient.right  - rectClient.left);
            lpMMI->ptMinTrackSize.y = m_sizeMin.cy + (rectWindow.bottom - rectWindow.top ) - (rectClient.bottom - rectClient.top );
        }

        return lResult;
    }

    case WM_NCMOUSEMOVE:
        // If we are a docked, auto-hidden application bar, shown us
        // when the user moves over our non-client area
        ShowAutoHideAppBar(true);

        return W::MSWWindowProc(message, wParam, lParam);

    case WM_NCHITTEST: {
        // Find out what the base class thinks is the hit test code.
        WXLRESULT lResult = W::MSWWindowProc(message, wParam, lParam);

        if (HTSIZEFIRST <= lResult && lResult <= HTSIZELAST) {
            if (GetAllowSizing()) {
                if (wxAppBarIsDocked(m_state)) {
                    // When the application bar is docked, the user can resize only one edge.
                    // This next section determines which edge the user can resize.
                    // To allow resizing, the application bar window must have the WS_THICKFRAME style.

                    RECT rcClient = {};
                    wxPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

                    // Resizing IS allowed for the edge that the application bar is docked on.
                    // Get the location of the appbar's client area in screen coordinates.
                    wxVERIFY(::GetClientRect(m_hWnd, &rcClient));
                    wxVERIFY(::ClientToScreen(m_hWnd, (LPPOINT)&rcClient));
                    wxVERIFY(::ClientToScreen(m_hWnd, ((LPPOINT)&rcClient) + 1));

                    // Assume that we can't resize
                    lResult = HTBORDER;

                    switch (m_state) {
                        case wxAppBarState::LEFT:   if (point.x > rcClient.right)  lResult = HTRIGHT;  break;
                        case wxAppBarState::TOP:    if (point.y > rcClient.bottom) lResult = HTBOTTOM; break;
                        case wxAppBarState::RIGHT:  if (point.x < rcClient.left)   lResult = HTLEFT;   break;
                        case wxAppBarState::BOTTOM: if (point.y < rcClient.top)    lResult = HTTOP;    break;
                    }
                }
            } else {
                // The sizing is locked. Pretend that the mouse is not on a resize border.
                lResult = HTBORDER;
            }
        }

        return lResult;
    }

    case WM_ACTIVATE: {
        WXLRESULT lResult = W::MSWWindowProc(message, wParam, lParam);

        if (wxAppBarIsDocked(m_state)) {
            // When our window changes activation state, tell the Shell so that any
            // auto-hidden application bar on our edge stays on top of our window making it
            // always accessible to the user.
            APPBARDATA abd = { sizeof(abd), m_hWnd };
            wxVERIFY(::SHAppBarMessage(ABM_ACTIVATE, &abd));

            if (LOWORD(wParam) == WA_INACTIVE && IsAutoHide()) {
                // Hide the application bar if we are docked and auto-hidden.
                ShowAutoHideAppBar(false);
            }
        }

        return lResult;
    }

    case WM_TIMER:
        if (wParam == wxABT_AUTOHIDETIMERID) {
            if (!GetAutoHidden() &&
                wxAppBarIsDocked(m_state) &&
                GetActiveWindow() != m_hWnd)
            {
                // Get the position of the mouse and the application bar's position
                // Everything must be in screen coordinates.
                DWORD dwPoint = ::GetMessagePos();
                wxPoint pointMouse(GET_X_LPARAM(dwPoint), GET_Y_LPARAM(dwPoint));
                RECT rect = {};
                wxVERIFY(::GetWindowRect(m_hWnd, &rect));
                wxRect rectBounds(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);

                // Add a little margin around the application bar
                rectBounds.Inflate(2 * ::GetSystemMetrics(SM_CXDOUBLECLK), 2 * ::GetSystemMetrics(SM_CYDOUBLECLK));
                if (!rectBounds.Contains(pointMouse)) {
                    // If the mouse is NOT over or near the application bar, hide it.
                    ShowAutoHideAppBar(false);
                }
            }

            return 0;
        } else
            return W::MSWWindowProc(message, wParam, lParam);

    case WM_AB_NOTIFY:
        switch (wParam) {
            case ABN_FULLSCREENAPP:
                if (lParam)
                    m_flags |= wxABF_FULLSCREENAPPOPEN;
                else
                    m_flags &= ~wxABF_FULLSCREENAPPOPEN;
                OnChangeTaskBarState(wxAppBarGetTaskBarState());

                if (::IsWindowVisible(m_hWnd)) {
                    // Set the Z-order.
                    wxVERIFY(::SetWindowPos(m_hWnd, wxAppBarGetZWnd(m_state, m_flags), 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOSENDCHANGING));
                }
                break;

            case ABN_POSCHANGED:
                if (wxAppBarIsDocked(m_state) && !IsAutoHide())
                    DockAppBar(m_state);
                break;

            case ABN_STATECHANGE:
                // Taskbar's state changed.
                OnChangeTaskBarState(wxAppBarGetTaskBarState());
                break;

            case ABN_WINDOWARRANGE:
                OnWindowsArrange(lParam ? true : false);
                break;

            default:
                // Unknown message.
                wxFAIL_MSG(wxString::Format(wxT("unknown application bar notification 0x%x"), wParam));
                break;
        }

        return 0;

    default:
        return W::MSWWindowProc(message, wParam, lParam);
    }
}
/// \endcond


/// \cond internal

template <class W>
_Use_decl_annotations_
inline bool wxAppBar<W>::DockAppBar(wxAppBarState state)
{
    wxASSERT(wxAppBarIsDocked(state));

    // Calculate docked window rect and dock the window there.
    APPBARDATA abd = { sizeof(abd), m_hWnd, 0, static_cast<UINT>(state) };
    GetDockedRect(state, &(abd.rc));
    wxCHECK(::SHAppBarMessage(ABM_SETPOS, &abd), false);
    wxCHECK(::SetWindowPos(m_hWnd, wxAppBarGetZWnd(state, m_flags), abd.rc.left, abd.rc.top, abd.rc.right - abd.rc.left, abd.rc.bottom - abd.rc.top, SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_FRAMECHANGED), false);

    return true;
}


template <class W>
_Use_decl_annotations_
inline bool wxAppBar<W>::UndockAppBar()
{
    // Free application bar's space to undock.
    APPBARDATA abd = { sizeof(abd), m_hWnd, 0, ABE_LEFT };
    wxASSERT(!abd.rc.left && !abd.rc.top && !abd.rc.right && !abd.rc.bottom);
    wxCHECK(::SHAppBarMessage(ABM_SETPOS, &abd), false);

    return true;
}


template <class W>
_Use_decl_annotations_
inline bool wxAppBar<W>::RegisterAutoHide(wxAppBarState state)
{
    wxASSERT(wxAppBarIsDocked(state));

    // Register application bar as auto-hide.
    APPBARDATA abd = { sizeof(abd), m_hWnd, 0, static_cast<UINT>(state), {}, (LPARAM)true };
    if (::SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd)) {
        // Auto-hide succeeded.
        m_flags |=  wxABF_AUTOHIDE;
        m_flags &= ~wxABF_AUTOHIDDEN;

        // Calculate auto-hidden window rect and move the window there.
        GetAutoHideRect(state, false, &(abd.rc));
        wxCHECK(::SetWindowPos(m_hWnd, wxAppBarGetZWnd(state, m_flags), abd.rc.left, abd.rc.top, abd.rc.right - abd.rc.left, abd.rc.bottom - abd.rc.top, SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_FRAMECHANGED), false);

        // Reset auto-hide timer.
        m_timerID = ::SetTimer(m_hWnd, wxABT_AUTOHIDETIMERID, wxABT_AUTOHIDETIMERINTERVAL, NULL);

        return true;
    } else {
        // Auto-hide failed; some other application bar must be hidden on this edge already.
        m_flags &= ~(wxABF_AUTOHIDE | wxABF_AUTOHIDDEN);

        // Post a message to user.
        OnAutoHideDenied();

        return false;
    }
}


template <class W>
_Use_decl_annotations_
inline bool wxAppBar<W>::UnregisterAutoHide(wxAppBarState state)
{
    wxASSERT(wxAppBarIsDocked(state));

    // Unregister application bar as auto-hide.
    APPBARDATA abd = { sizeof(abd), m_hWnd, 0, static_cast<UINT>(state), {}, (LPARAM)false };
    wxCHECK(::SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd), false);
    m_flags &= ~wxABF_AUTOHIDDEN;

    // Cancel the timer.
    if (m_timerID) {
        ::KillTimer(m_hWnd, m_timerID);
        m_timerID = 0;
    }

    return true;
}


template <class W>
_Use_decl_annotations_
inline bool wxAppBar<W>::GetDockedRect(wxAppBarState state, LPRECT rect) const
{
    wxASSERT(wxAppBarIsDocked(state));
    wxASSERT(rect);

    // Set dimensions to full screen.
    APPBARDATA abd = { sizeof(abd), m_hWnd, 0, static_cast<UINT>(state), { 0, 0, ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN) } };
    wxCHECK(::SHAppBarMessage(ABM_QUERYPOS, &abd), false);

    // Correct our dimensions accordingly.
    switch (state) {
        case wxAppBarState::LEFT:
            rect->left   = abd.rc.left;
            rect->top    = abd.rc.top;
            rect->right  = abd.rc.left + m_sizeDocked.cx;
            rect->bottom = abd.rc.bottom;
            break;

        case wxAppBarState::TOP:
            rect->left   = abd.rc.left;
            rect->top    = abd.rc.top;
            rect->right  = abd.rc.right;
            rect->bottom = abd.rc.top + m_sizeDocked.cy;
            break;

        case wxAppBarState::RIGHT:
            rect->left   = abd.rc.right - m_sizeDocked.cx;
            rect->top    = abd.rc.top;
            rect->right  = abd.rc.right;
            rect->bottom = abd.rc.bottom;
            break;

        case wxAppBarState::BOTTOM:
            rect->left   = abd.rc.left;
            rect->top    = abd.rc.bottom - m_sizeDocked.cy;
            rect->right  = abd.rc.right;
            rect->bottom = abd.rc.bottom;
            break;

        default:
            // Unknown state.
            wxFAIL_MSG(wxT("unsupported application bar state"));
            return false;
    }

    return true;
}


template <class W>
_Use_decl_annotations_
inline bool wxAppBar<W>::GetAutoHideRect(wxAppBarState state, bool bAutoHidden, LPRECT rect) const
{
    wxASSERT(wxAppBarIsDocked(state));
    wxASSERT(rect);

    // Keep a part of the application bar visible at all times
    const int iBorder = ::GetSystemMetrics(wxAppBarIsDockedVert(state) ? SM_CXBORDER : SM_CYBORDER) * 2;
    const RECT rcScreen = {
        0,
        0,
        ::GetSystemMetrics(SM_CXSCREEN),
        ::GetSystemMetrics(SM_CYSCREEN)
    };

    // Correct our dimensions accordingly.
    switch (state) {
        case wxAppBarState::LEFT:
            rect->top    = rcScreen.top;
            rect->bottom = rcScreen.bottom;
            rect->right  = rcScreen.left + (bAutoHidden ? iBorder : m_sizeDocked.cx);
            rect->left   = rect->right - m_sizeDocked.cx;
            break;

        case wxAppBarState::TOP:
            rect->left   = rcScreen.left;
            rect->right  = rcScreen.right;
            rect->bottom = rcScreen.top + (bAutoHidden ? iBorder : m_sizeDocked.cy);
            rect->top    = rect->bottom - m_sizeDocked.cy;
            break;

        case wxAppBarState::RIGHT:
            rect->left   = rcScreen.right - (bAutoHidden ? iBorder : m_sizeDocked.cx);
            rect->top    = rcScreen.top;
            rect->right  = rect->left + m_sizeDocked.cx;
            rect->bottom = rcScreen.bottom;
            break;

        case wxAppBarState::BOTTOM:
            rect->left   = rcScreen.left;
            rect->top    = rcScreen.bottom - (bAutoHidden ? iBorder : m_sizeDocked.cy);
            rect->right  = rcScreen.right;
            rect->bottom = rect->top + m_sizeDocked.cy;
            break;

        default:
            // Unknown state.
            wxFAIL_MSG(wxT("unsupported application bar state"));
            return false;
    }

    return true;
}

/// \endcond
