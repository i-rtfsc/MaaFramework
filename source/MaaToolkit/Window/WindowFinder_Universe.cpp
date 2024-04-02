#include "WindowFinder.h"

#include "Utils/Codec.h"
#include "Utils/Logger.h"
#include "Utils/Platform.h"

MAA_TOOLKIT_NS_BEGIN

std::ostream& operator<<(std::ostream& os, const WindowFinder::Window& w)
{
    os << VAR_VOIDP_RAW(w.hwnd) << VAR_RAW(w.class_name) << VAR_RAW(w.window_name);
    return os;
}

size_t WindowFinder::find_window(std::string_view class_name, std::string_view window_name)
{
    auto windows = list_windows();

    windows_.clear();
    for (const auto& w : windows) {
        bool same_class = class_name.empty() || w.class_name == class_name;
        bool same_window = window_name.empty() || w.window_name == window_name;
        if (same_class && same_window) {
            windows_.emplace_back(w.hwnd);
        }
    }
    return windows_.size();
}

size_t WindowFinder::search_window(std::string_view class_name, std::string_view window_name)
{
    auto windows = list_windows();

    windows_.clear();
    for (const auto& w : windows) {
        bool same_class = class_name.empty() || w.class_name.find(class_name) != std::string::npos;
        bool same_window =
            window_name.empty() || w.window_name.find(window_name) != std::string::npos;
        if (same_class && same_window) {
            windows_.emplace_back(w.hwnd);
        }
    }
    return windows_.size();
}

MAA_TOOLKIT_NS_END
