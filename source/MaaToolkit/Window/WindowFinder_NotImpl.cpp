#if !defined(_WIN32) && !defined(__APPLE__)

#include "WindowFinder.h"

#include "Utils/Logger.h"

MAA_TOOLKIT_NS_BEGIN

MaaHwnd WindowFinder::get_cursor_window() const
{
    LogError << "Not implemented";
    return MaaHwnd {};
}

MaaHwnd WindowFinder::get_desktop_window() const
{
    LogError << "Not implemented";
    return MaaHwnd {};
}

MaaHwnd WindowFinder::get_foreground_window() const
{
    LogError << "Not implemented";
    return MaaHwnd {};
}

std::vector<WindowFinder::Window> WindowFinder::list_windows() const
{
    LogError << "Not implemented";
    return {};
}

MAA_TOOLKIT_NS_END

#endif
