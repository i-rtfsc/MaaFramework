#pragma once

#include <string_view>
#include <vector>

#include "Conf/Conf.h"
#include "MaaToolkit/MaaToolkitDef.h"

class MaaWindowAPI
{
public:
    virtual ~MaaWindowAPI() = default;

    virtual size_t find_window(std::string_view class_name, std::string_view window_name) = 0;
    virtual size_t search_window(std::string_view class_name, std::string_view window_name) = 0;
    virtual std::vector<MaaHwnd> found_window() const = 0;
    virtual MaaHwnd get_cursor_window() const = 0;
    virtual MaaHwnd get_desktop_window() const = 0;
    virtual MaaHwnd get_foreground_window() const = 0;
};
