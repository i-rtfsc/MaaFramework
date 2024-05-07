#ifndef _WIN32

module;

#include <filesystem>
#include <string_view>
#include <unistd.h>

#include "Conf/Conf.h"

module MaaUtils_Platform;

MAA_NS_BEGIN

os_string to_osstring(std::string_view utf8_str)
{
    return os_string(utf8_str);
}

std::string from_osstring(os_string_view os_str)
{
    return std::string(os_str);
}

std::string path_to_utf8_string(const std::filesystem::path& path)
{
    return path.native();
}

std::string path_to_ansi_string(const std::filesystem::path& path)
{
    return path.native();
}

std::string path_to_crt_string(const std::filesystem::path& path)
{
    return path.native();
}

MAA_NS_END

#endif
