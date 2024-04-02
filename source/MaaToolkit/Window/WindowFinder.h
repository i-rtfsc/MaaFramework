#pragma once

#include "WindowAPI.h"

#include "Utils/Platform.h"
#include "Utils/SingletonHolder.hpp"

MAA_TOOLKIT_NS_BEGIN

class WindowFinder
    : public MaaWindowAPI
    , public SingletonHolder<WindowFinder>
{
public:
    struct Window
    {
        MaaHwnd hwnd;
        std::string class_name;
        std::string window_name;
    };

public:
    virtual ~WindowFinder() = default;

    virtual size_t find_window(std::string_view class_name, std::string_view window_name) override;
    virtual size_t
        search_window(std::string_view class_name, std::string_view window_name) override;

    virtual std::vector<MaaHwnd> found_window() const override { return windows_; }

    virtual MaaHwnd get_cursor_window() const override;
    virtual MaaHwnd get_desktop_window() const override;
    virtual MaaHwnd get_foreground_window() const override;

private:
    std::vector<Window> list_windows() const;

private:
    std::vector<MaaHwnd> windows_;
};

std::ostream& operator<<(std::ostream& os, const WindowFinder::Window& window);

MAA_TOOLKIT_NS_END
