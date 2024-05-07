module;

#include <chrono>
#include <string>
#include <string_view>

#include "Conf/Conf.h"
#include "MaaFramework/MaaPort.h"
#include "Utils/IOStream/BoostIO.hpp"
#include "Utils/Time.hpp"

export module MaaUtils_IOStream;

MAA_NS_BEGIN

export class MAA_UTILS_API IOStream
{
public:
    using duration_t = std::chrono::milliseconds;

    virtual ~IOStream() = default;

public:
    virtual bool write(std::string_view data) = 0;

    virtual std::string read(duration_t timeout = duration_t::max());
    virtual std::string read_some(size_t count, duration_t timeout = duration_t::max());
    virtual std::string
        read_until(std::string_view delimiter, duration_t timeout = duration_t::max());

    virtual bool release() = 0;
    virtual bool is_open() const = 0;

protected:
    virtual std::string read_once(size_t max_count) = 0;
};

MAA_NS_END

MAA_NS_BEGIN

std::string IOStream::read(duration_t timeout)
{
    return read_some(std::numeric_limits<size_t>::max(), timeout);
}

std::string IOStream::read_some(size_t count, duration_t timeout)
{
    auto start_time = std::chrono::steady_clock::now();
    std::string result;

    while (is_open() && result.size() < count && duration_since(start_time) < timeout) {
        auto data = read_once(count - result.size());
        result.append(std::move(data));
    }

    return result;
}

std::string IOStream::read_until(std::string_view delimiter, duration_t timeout)
{
    auto start_time = std::chrono::steady_clock::now();
    std::string result;

    while (is_open() && !result.ends_with(delimiter) && duration_since(start_time) < timeout) {
        auto data = read_once(1);
        result.append(std::move(data));
    }

    return result;
}

MAA_NS_END
