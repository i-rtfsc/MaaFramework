module;

#include <filesystem>
#include <string>
#include <string_view>

module MaaUtils_LoggerUtils;

constexpr separator separator::none("");
constexpr separator separator::space(" ");
constexpr separator separator::tab("\t");
constexpr separator separator::newline("\n");
constexpr separator separator::comma(",");

std::string LogStream::stdout_string()
{
    std::string color;

    switch (lv_) {
    case level::fatal:
    case level::error:
        color = "\033[31m";
        break;
    case level::warn:
        color = "\033[33m";
        break;
    case level::info:
        color = "\033[32m";
        break;
    case level::debug:
    case level::trace:
        break;
    }

    return color + utf8_to_crt(buffer_.str()) + "\033[0m";
}

std::string_view LogStream::level_str()
{
    switch (lv_) {
    case level::fatal:
        return "FTL";
    case level::error:
        return "ERR";
    case level::warn:
        return "WRN";
    case level::info:
        return "INF";
    case level::debug:
        return "DBG";
    case level::trace:
        return "TRC";
    }
    return "NoLV";
}

std::string StringConverter::operator()(const std::filesystem::path& path) const
{
    return path_to_utf8_string(path);
}

std::string StringConverter::operator()(const std::wstring& wstr) const
{
    return from_u16(wstr);
}

std::string StringConverter::operator()(const cv::Mat& image) const
{
    if (dumps_dir_.empty()) {
        return "Not logging";
    }
    if (image.empty()) {
        return "Empty image";
    }

    std::string filename = std::format("{}-{}.png", format_now_for_filename(), make_uuid());
    auto filepath = dumps_dir_ / path(filename);
    bool ret = MAA_NS::imwrite(filepath, image);
    if (!ret) {
        return "Failed to write image";
    }
    return this->operator()(filepath);
}
