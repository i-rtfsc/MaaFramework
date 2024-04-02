#include "MaaToolkit/Window/MaaToolkitWindow.h"

#include <string_view>

#include "Utils/Logger.h"
#include "Window/WindowFinder.h"

static auto& window_mgr = MAA_TOOLKIT_NS::WindowFinder::get_instance();

MaaSize MaaToolkitFindWindow(MaaStringView class_name, MaaStringView window_name)
{
    LogInfo << VAR(class_name) << VAR(window_name);

    return window_mgr.find_window(class_name, window_name);
}

MaaSize MaaToolkitSearchWindow(MaaStringView class_name, MaaStringView window_name)
{
    LogInfo << VAR(class_name) << VAR(window_name);

    return window_mgr.search_window(class_name, window_name);
}

MaaHwnd MaaToolkitGetWindow(MaaSize index)
{
    return window_mgr.found_window().at(index);
}

MaaHwnd MaaToolkitGetCursorWindow()
{
    LogInfo;

    return window_mgr.get_cursor_window();
}

MaaHwnd MaaToolkitGetDesktopWindow()
{
    LogInfo;

    return window_mgr.get_desktop_window();
}

MaaHwnd MaaToolkitGetForegroundWindow()
{
    LogInfo;

    return window_mgr.get_foreground_window();
}
