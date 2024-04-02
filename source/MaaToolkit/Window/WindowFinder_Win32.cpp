#ifdef _WIN32

#include "WindowFinder.h"

#include "Utils/Codec.h"
#include "Utils/Logger.h"
#include "Utils/Platform.h"

MAA_TOOLKIT_NS_BEGIN

MaaHwnd WindowFinder::get_cursor_window() const
{
    POINT pt {};
    if (!GetCursorPos(&pt)) {
        return nullptr;
    }

    HWND hwnd = WindowFromPoint(pt);
    if (hwnd == NULL) {
        return nullptr;
    }

    return reinterpret_cast<MaaHwnd>(hwnd);
}

MaaHwnd WindowFinder::get_desktop_window() const
{
    return reinterpret_cast<MaaHwnd>(GetDesktopWindow());
}

MaaHwnd WindowFinder::get_foreground_window() const
{
    return reinterpret_cast<MaaHwnd>(GetForegroundWindow());
}

std::vector<WindowFinder::Window> WindowFinder::list_windows() const
{
    std::vector<Window> windows;

    for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT)) {
        if (!IsWindowVisible(hwnd)) {
            continue;
        }

        std::wstring class_name(256, '\0');
        GetClassNameW(hwnd, class_name.data(), static_cast<int>(class_name.size()));

        std::wstring window_name(256, '\0');
        GetWindowTextW(hwnd, window_name.data(), static_cast<int>(window_name.size()));

        windows.emplace_back(Window { .hwnd = reinterpret_cast<MaaHwnd>(hwnd),
                                      .class_name = from_u16(class_name),
                                      .window_name = from_u16(window_name) });
    }

#ifdef MAA_DEBUG
    LogInfo << "Window list:" << windows;
#endif

    return windows;
}

MAA_TOOLKIT_NS_END

#endif
