#import <Cocoa/Cocoa.h>

#include "WindowFinder.h"

#include "Utils/Codec.h"
#include "Utils/Logger.h"
#include "Utils/Platform.h"

MAA_TOOLKIT_NS_BEGIN

MaaHwnd WindowFinder::get_cursor_window() const
{
    return 0;
}

MaaHwnd WindowFinder::get_desktop_window() const
{
    return 0;
}

MaaHwnd WindowFinder::get_foreground_window() const
{
    auto res = list_windows();
    if (res.size()) {
        return res[0].hwnd;
    }
    else {
        return 0;
    }
}

std::vector<WindowFinder::Window> WindowFinder::list_windows() const
{
    std::vector<Window> windows;

    CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionAll, kCGNullWindowID);

    NSArray* windowsInfo = CFBridgingRelease(windowList);
    for (NSDictionary* window in windowsInfo) {
        if (!window[(id)kCGWindowLayer] || [window[(id)kCGWindowLayer] integerValue] != 0) {
            continue;
        }

        id hwnd = window[(id)kCGWindowNumber];
        if (!hwnd) {
            continue;
        }

        windows.push_back({});
        Window& info = windows.back();

        info.hwnd = static_cast<CGWindowID>([hwnd unsignedIntValue]);

        NSString* window_name = window[(id)kCGWindowName];
        info.window_name = window_name ? [window_name UTF8String] : "";

        NSString* app_name = window[(id)kCGWindowOwnerName];
        info.class_name = app_name ? [app_name UTF8String] : "";
    }

    CFRelease(windowList);

#ifdef MAA_DEBUG
    LogInfo << "Window list:" << windows;
#endif

    return windows;
}

MAA_TOOLKIT_NS_END
