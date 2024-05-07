module;

#include <filesystem>
#include <optional>
#include <ostream>
#include <set>
#include <string>
#include <string_view>
#include <type_traits>

#ifdef _WIN32
#include "SafeWindows.hpp"
#else
#include <sys/types.h>
#endif

#include "Conf/Conf.h"
#include "MaaFramework/MaaPort.h"

export module MaaUtils_Platform;

MAA_NS_BEGIN

/* string and path */

export using os_string = std::filesystem::path::string_type;
export using os_string_view = std::basic_string_view<os_string::value_type>;

export MAA_UTILS_API os_string to_osstring(std::string_view utf8_str);
export MAA_UTILS_API std::string from_osstring(os_string_view os_str);

export inline std::filesystem::path path(std::string_view utf8_str)
{
    return std::filesystem::path(to_osstring(utf8_str)).make_preferred();
}

export MAA_UTILS_API std::string path_to_utf8_string(const std::filesystem::path& path);
export MAA_UTILS_API std::string path_to_ansi_string(const std::filesystem::path& path);
export MAA_UTILS_API std::string path_to_crt_string(const std::filesystem::path& path);

export namespace path_literals
{
inline std::filesystem::path operator"" _path(const char* utf8_str, size_t len)
{
    return path(std::string_view(utf8_str, len));
}
}

/* process */

#ifdef _WIN32
export using os_pid = DWORD;
#else
export using os_pid = pid_t;
#endif

export struct ProcessInfo
{
    os_pid pid = 0;
    std::string name;

    bool operator<(const ProcessInfo& rhs) const { return pid < rhs.pid; }

    bool operator==(const ProcessInfo& rhs) const { return pid == rhs.pid; }
};

export inline std::ostream& operator<<(std::ostream& os, const ProcessInfo& info)
{
    return os << info.pid << " " << info.name;
}

export MAA_UTILS_API std::set<ProcessInfo> list_processes();
export MAA_UTILS_API std::optional<std::filesystem::path> get_process_path(os_pid pid);

MAA_NS_END
