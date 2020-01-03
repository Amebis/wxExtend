/*
    Copyright 2015-2020 Amebis
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

#include <wx/dynlib.h>
#include <wx/private/tlwgeom.h>

#ifndef USER_DEFAULT_SCREEN_DPI
#define USER_DEFAULT_SCREEN_DPI 96
#endif

/// \addtogroup wxExtend
/// @{

///
/// `wxPersistentDialog` kind for persistent storage
///
#define wxPERSIST_TLW_MONITOR_X "xmon"
#define wxPERSIST_TLW_MONITOR_Y "ymon"
#define wxPERSIST_TLW_MONITOR_W "wmon"
#define wxPERSIST_TLW_MONITOR_H "hmon"
#define wxPERSIST_TLW_DPI_HORZ  "xdpi"
#define wxPERSIST_TLW_DPI_VERT  "ydpi"


class wxTLWGeometryEx : public wxTLWGeometryBase
{
public:
    wxTLWGeometryEx()
    {
        wxZeroMemory(m_placement);
        m_placement.length = sizeof(m_placement);

        wxZeroMemory(m_mntinfo);
        m_mntinfo.cbSize = sizeof(m_mntinfo);

        m_dpiHorz = USER_DEFAULT_SCREEN_DPI;
        m_dpiVert = USER_DEFAULT_SCREEN_DPI;
    }

    virtual bool Save(const Serializer& ser) const wxOVERRIDE
    {
        // For compatibility with the existing saved positions/sizes, use the
        // same keys as the generic version (which was previously used under
        // MSW too).

        // Normal position and size.
        const RECT& rc = m_placement.rcNormalPosition;
        if (!ser.SaveField(wxPERSIST_TLW_X, rc.left) ||
            !ser.SaveField(wxPERSIST_TLW_Y, rc.top) ||
            !ser.SaveField(wxPERSIST_TLW_W, rc.right - rc.left) ||
            !ser.SaveField(wxPERSIST_TLW_H, rc.bottom - rc.top))
            return false;

        // Maximized/minimized state.
        UINT show = m_placement.showCmd;
        if (!ser.SaveField(wxPERSIST_TLW_MAXIMIZED, show == SW_SHOWMAXIMIZED))
            return false;

        if (!ser.SaveField(wxPERSIST_TLW_ICONIZED, show == SW_SHOWMINIMIZED))
            return false;

        // Maximized window position.
        const POINT pt = m_placement.ptMaxPosition;
        if (!ser.SaveField(wxPERSIST_TLW_MAX_X, pt.x) ||
            !ser.SaveField(wxPERSIST_TLW_MAX_Y, pt.y))
            return false;

        // We don't currently save the minimized window position, it doesn't
        // seem useful for anything and is probably just a left over from
        // Windows 3.1 days, when icons were positioned on the desktop instead
        // of being located in the taskbar.

        // Monitor position and size.
        const RECT& rcMon = m_mntinfo.rcWork;
        if (!ser.SaveField(wxPERSIST_TLW_MONITOR_X, rcMon.left) ||
            !ser.SaveField(wxPERSIST_TLW_MONITOR_Y, rcMon.top) ||
            !ser.SaveField(wxPERSIST_TLW_MONITOR_W, rcMon.right - rcMon.left) ||
            !ser.SaveField(wxPERSIST_TLW_MONITOR_H, rcMon.bottom - rcMon.top))
            return false;

        // DPI.
        if (!ser.SaveField(wxPERSIST_TLW_DPI_HORZ, m_dpiHorz) ||
            !ser.SaveField(wxPERSIST_TLW_DPI_VERT, m_dpiVert))
            return false;

        return true;
    }

    virtual bool Restore(Serializer& ser) wxOVERRIDE
    {
        // Normal position and size.
        wxRect r;
        if (!ser.RestoreField(wxPERSIST_TLW_X, &r.x) ||
            !ser.RestoreField(wxPERSIST_TLW_Y, &r.y) ||
            !ser.RestoreField(wxPERSIST_TLW_W, &r.width) ||
            !ser.RestoreField(wxPERSIST_TLW_H, &r.height))
            return false;
        wxCopyRectToRECT(r, m_placement.rcNormalPosition);

        // Maximized/minimized state.
        //
        // Note the special case of SW_MINIMIZE: while GetWindowPlacement()
        // returns SW_SHOWMINIMIZED when the window is iconized, we restore it
        // as SW_MINIMIZE as this is what the code in wxTLW checks to determine
        // whether the window is supposed to be iconized or not.
        //
        // Just to confuse matters further, note that SW_MAXIMIZE is exactly
        // the same thing as SW_SHOWMAXIMIZED.
        int tmp;
        UINT& show = m_placement.showCmd;
        if (ser.RestoreField(wxPERSIST_TLW_MAXIMIZED, &tmp) && tmp)
            show = SW_MAXIMIZE;
        else if (ser.RestoreField(wxPERSIST_TLW_ICONIZED, &tmp) && tmp)
            show = SW_MINIMIZE;
        else
            show = SW_SHOWNORMAL;

        // Maximized window position.
        if (ser.RestoreField(wxPERSIST_TLW_MAX_X, &r.x) &&
            ser.RestoreField(wxPERSIST_TLW_MAX_Y, &r.y))
        {
            m_placement.ptMaxPosition.x = r.x;
            m_placement.ptMaxPosition.y = r.y;
        } else {
            m_placement.ptMaxPosition.x = -1;
            m_placement.ptMaxPosition.y = -1;
        }

        m_placement.ptMinPosition.x = -1;
        m_placement.ptMinPosition.y = -1;

        // Monitor position and size.
        wxRect rmon;
        if (!ser.RestoreField(wxPERSIST_TLW_MONITOR_X, &rmon.x) ||
            !ser.RestoreField(wxPERSIST_TLW_MONITOR_Y, &rmon.y) ||
            !ser.RestoreField(wxPERSIST_TLW_MONITOR_W, &rmon.width) ||
            !ser.RestoreField(wxPERSIST_TLW_MONITOR_H, &rmon.height))
            return false;
        wxCopyRectToRECT(rmon, m_mntinfo.rcWork);

        // DPI.
        if (!ser.RestoreField(wxPERSIST_TLW_DPI_HORZ, &r.x) ||
            !ser.RestoreField(wxPERSIST_TLW_DPI_VERT, &r.y))
            return false;
        m_dpiHorz = r.x;
        m_dpiVert = r.y;

        return true;
    }

    virtual bool GetFrom(const wxTopLevelWindow* tlw) wxOVERRIDE
    {
        WXHWND hWnd = GetHwndOf(tlw);
        if (!::GetWindowPlacement(hWnd, &m_placement))
        {
            wxLogLastError(wxS("GetWindowPlacement"));
            return false;
        }

        HMONITOR hMonitor = ::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
        wxASSERT_MSG(hMonitor, wxT("error locating monitor"));
        _Analysis_assume_(hMonitor);
        if (!::GetMonitorInfo(hMonitor, &m_mntinfo))
        {
            wxLogLastError(wxS("GetMonitorInfo"));
            return false;
        }

        GetDPI(hWnd, &m_dpiHorz, &m_dpiVert) || GetDPI(hMonitor, &m_dpiHorz, &m_dpiVert);

        return true;
    }

    virtual bool ApplyTo(wxTopLevelWindow* tlw) wxOVERRIDE
    {
        // There is a subtlety here: if the window is currently hidden,
        // restoring its geometry shouldn't show it, so we must use SW_HIDE as
        // show command, but showing it later should restore it to the correct
        // state, so we need to remember it in wxTLW itself. And even if it's
        // currently shown, we still need to update its show command, so that
        // it matches the real window state after SetWindowPlacement() call.
        tlw->MSWSetShowCommand(m_placement.showCmd);
        if (!tlw->IsShown())
        {
            m_placement.showCmd = SW_HIDE;
        }

        // Get monitor to restore window to.
        HMONITOR hMonitor = ::MonitorFromRect(&m_mntinfo.rcWork, MONITOR_DEFAULTTONEAREST);
        wxASSERT_MSG(hMonitor, wxT("error locating monitor"));
        _Analysis_assume_(hMonitor);
        MONITORINFO mntinfo;
        mntinfo.cbSize = sizeof(mntinfo);
        if (!::GetMonitorInfo(hMonitor, &mntinfo))
        {
            wxLogLastError(wxS("GetMonitorInfo"));
            return false;
        }

        UINT dpiHorz, dpiVert;
        GetDPI(hMonitor, &dpiHorz, &dpiVert);

        SIZE
            sizeWorkPrev = {
                m_mntinfo.rcWork.right - m_mntinfo.rcWork.left,
                m_mntinfo.rcWork.bottom - m_mntinfo.rcWork.top
            },
            sizeWork = {
                mntinfo.rcWork.right - mntinfo.rcWork.left,
                mntinfo.rcWork.bottom - mntinfo.rcWork.top
            };

        //
        // Project the coordinates:
        // - Position relative to monitor working area center.
        // - Scale according to DPI.
        //

        if (m_placement.ptMaxPosition.x != -1 && m_placement.ptMaxPosition.y != -1) {
            m_placement.ptMaxPosition.x = wxMulDivInt32(m_placement.ptMaxPosition.x - m_mntinfo.rcWork.left, sizeWork.cx, sizeWorkPrev.cx) + mntinfo.rcWork.left;
            m_placement.ptMaxPosition.y = wxMulDivInt32(m_placement.ptMaxPosition.y - m_mntinfo.rcWork.top, sizeWork.cy, sizeWorkPrev.cy) + mntinfo.rcWork.top;
        }

        SIZE sizeWndPrev, sizeWnd;
        HWND hWnd = GetHwndOf(tlw);

        if (tlw->GetWindowStyle() & wxRESIZE_BORDER) {
            sizeWndPrev.cx = m_placement.rcNormalPosition.right - m_placement.rcNormalPosition.left;
            sizeWndPrev.cy = m_placement.rcNormalPosition.bottom - m_placement.rcNormalPosition.top;
            sizeWnd.cx = wxMulDivInt32(sizeWndPrev.cx, dpiHorz, m_dpiHorz);
            sizeWnd.cy = wxMulDivInt32(sizeWndPrev.cy, dpiVert, m_dpiVert);
        } else {
            // The window is not resizable. Do not change its size.
            WINDOWPLACEMENT placement = { sizeof(placement) };
            if (!::GetWindowPlacement(hWnd, &placement))
            {
                wxLogLastError(wxS("GetWindowPlacement"));
                return false;
            }
            SIZE size = {
                placement.rcNormalPosition.right - placement.rcNormalPosition.left,
                placement.rcNormalPosition.bottom - placement.rcNormalPosition.top
            };

            UINT dpiWndHorz, dpiWndVert;
            GetDPI(hWnd, &dpiWndHorz, &dpiWndVert) || GetDPI(::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &dpiWndHorz, &dpiWndVert);

            sizeWndPrev.cx = wxMulDivInt32(size.cx, m_dpiHorz, dpiWndHorz);
            sizeWndPrev.cy = wxMulDivInt32(size.cy, m_dpiVert, dpiWndVert);
            sizeWnd.cx = wxMulDivInt32(size.cx, dpiHorz, dpiWndHorz);
            sizeWnd.cy = wxMulDivInt32(size.cy, dpiVert, dpiWndVert);
        }

        m_placement.rcNormalPosition.left = wxMulDivInt32(m_placement.rcNormalPosition.left + sizeWndPrev.cx / 2 - m_mntinfo.rcWork.left, sizeWork.cx, sizeWorkPrev.cx) + mntinfo.rcWork.left - sizeWnd.cx / 2;
        m_placement.rcNormalPosition.top = wxMulDivInt32(m_placement.rcNormalPosition.top + sizeWndPrev.cy / 2 - m_mntinfo.rcWork.top, sizeWork.cy, sizeWorkPrev.cy) + mntinfo.rcWork.top - sizeWnd.cy / 2;
        m_placement.rcNormalPosition.right = m_placement.rcNormalPosition.left + sizeWnd.cx;
        m_placement.rcNormalPosition.bottom = m_placement.rcNormalPosition.top + sizeWnd.cy;

        if (!::SetWindowPlacement(hWnd, &m_placement))
        {
            wxLogLastError(wxS("SetWindowPlacement"));
            return false;
        }

        return true;
    }

private:
    static bool GetDPI(_In_ HWND hWnd, _Out_ UINT *dpiHorz, _Out_ UINT *dpiVert)
    {
        wxASSERT(dpiHorz);
        wxASSERT(dpiVert);

#if wxUSE_DYNLIB_CLASS
        typedef UINT(WINAPI *GetDpiForWindow_t)(HWND);
        static bool s_checkedGetDpiForWindow = false;
        static GetDpiForWindow_t s_pfnGetDpiForWindow = NULL;
        if (!s_checkedGetDpiForWindow && s_dllUser32.IsLoaded()) {
            s_pfnGetDpiForWindow = (GetDpiForWindow_t)s_dllUser32.RawGetSymbol(wxT("GetDpiForWindow"));
            s_checkedGetDpiForWindow = true;
        }

        if (s_pfnGetDpiForWindow) {
            *dpiHorz = *dpiVert = s_pfnGetDpiForWindow(hWnd);
            return true;
        }
#endif

        *dpiHorz = *dpiVert = USER_DEFAULT_SCREEN_DPI;
        return false;
    }

    static bool GetDPI(_In_ HMONITOR hMonitor, _Out_ UINT *dpiHorz, _Out_ UINT *dpiVert)
    {
        wxASSERT(dpiHorz);
        wxASSERT(dpiVert);

#if wxUSE_DYNLIB_CLASS
        enum MONITOR_DPI_TYPE {
            MDT_EFFECTIVE_DPI = 0,
            MDT_ANGULAR_DPI = 1,
            MDT_RAW_DPI = 2,
            MDT_DEFAULT = MDT_EFFECTIVE_DPI
        };
        typedef HRESULT(WINAPI *GetDpiForMonitor_t)(HMONITOR, MONITOR_DPI_TYPE, UINT *, UINT *);
        static GetDpiForMonitor_t s_pfnGetDpiForMonitor = NULL;
        if (!s_pfnGetDpiForMonitor) {
            if (s_dllShCore.IsLoaded())
                s_pfnGetDpiForMonitor = (GetDpiForMonitor_t)s_dllShCore.GetSymbol(wxT("GetDpiForMonitor"));
        }

        if (s_pfnGetDpiForMonitor) {
            s_pfnGetDpiForMonitor(hMonitor, MDT_DEFAULT, dpiHorz, dpiVert);
            return true;
        }
#endif

        *dpiHorz = *dpiVert = USER_DEFAULT_SCREEN_DPI;
        return false;
    }

private:
    WINDOWPLACEMENT m_placement;
    MONITORINFO m_mntinfo;
    UINT m_dpiHorz;
    UINT m_dpiVert;

#if wxUSE_DYNLIB_CLASS
    static wxDynamicLibrary s_dllUser32;
    static wxDynamicLibrary s_dllShCore;
#endif
};
