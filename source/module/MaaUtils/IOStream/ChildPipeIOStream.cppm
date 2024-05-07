module;

#include <memory>
#include <meojson/json.hpp>

#include "Conf/Conf.h"
#include "MaaFramework/MaaPort.h"
#include "Utils/IOStream/BoostIO.hpp"
#include "Utils/Logger.h"
#include "Utils/Time.hpp"

export module MaaUtils_ChildPipeIOStream;
import MaaUtils_IOStream;
import MaaUtils_Logger;

MAA_NS_BEGIN

export class MAA_UTILS_API ChildPipeIOStream : public IOStream
{
public:
    ChildPipeIOStream(const std::filesystem::path& exec, const std::vector<std::string>& args);

#ifdef _WIN32
    ChildPipeIOStream(const std::filesystem::path& exec, const std::vector<std::wstring>& wargs);
#endif

    // NonCopyButMovable
    // https://stackoverflow.com/questions/29289956/c11-virtual-destructors-and-auto-generation-of-move-special-functions
    ChildPipeIOStream(const ChildPipeIOStream&) = delete;
    ChildPipeIOStream(ChildPipeIOStream&&) = default;
    ChildPipeIOStream& operator=(const ChildPipeIOStream&) = delete;
    ChildPipeIOStream& operator=(ChildPipeIOStream&&) = default;

    virtual ~ChildPipeIOStream() override;

public:
    virtual bool write(std::string_view data) override;

    virtual bool release() override;
    virtual bool is_open() const override;

protected:
    virtual std::string read_once(size_t max_count) override;

private:
    using os_string = std::filesystem::path::string_type;

    ChildPipeIOStream(const std::filesystem::path& exec, const std::vector<os_string>& args, bool);

private:
    std::filesystem::path exec_;
    std::vector<os_string> args_;

    boost::process::ipstream pin_;
    boost::process::opstream pout_;
    boost::process::child child_;

    std::unique_ptr<char[]> buffer_ = nullptr;
};

MAA_NS_END

MAA_NS_BEGIN

#ifdef _WIN32
std::vector<std::wstring> conv_args(const std::vector<std::string>& args)
{
    std::vector<std::wstring> wargs;
    for (const auto& arg : args) {
        wargs.emplace_back(to_u16(arg));
    }
    return wargs;
}
#else
std::vector<std::string> conv_args(const std::vector<std::string>& args)
{
    return args;
}
#endif

ChildPipeIOStream::ChildPipeIOStream(
    const std::filesystem::path& exec,
    const std::vector<std::string>& args)
    : ChildPipeIOStream(exec, conv_args(args), false)
{
}

#ifdef _WIN32
ChildPipeIOStream::ChildPipeIOStream(
    const std::filesystem::path& exec,
    const std::vector<std::wstring>& wargs)
    : ChildPipeIOStream(exec, wargs, false)
{
}
#endif

ChildPipeIOStream::ChildPipeIOStream(
    const std::filesystem::path& exec,
    const std::vector<os_string>& args,
    bool)
    : exec_(exec)
    , args_(args)
    , child_(
          exec_,
          args_,
          boost::process::std_out > pin_,
          boost::process::std_err > boost::process::null,
          boost::process::std_in < pout_
#ifdef _WIN32
          ,
          boost::process::windows::create_no_window
#endif
      )
{
    LogTrace << VAR(exec_) << VAR(args_) << VAR(child_.id());
}

ChildPipeIOStream::~ChildPipeIOStream()
{
    release();
}

bool ChildPipeIOStream::write(std::string_view data)
{
    if (!pout_.good()) {
        LogError << "pout is not good" << VAR(exec_) << VAR(args_) << VAR(child_.id());
        return false;
    }

    pout_ << data << std::endl;
    return true;
}

bool ChildPipeIOStream::release()
{
    auto start_time = std::chrono::steady_clock::now();
    using namespace std::chrono_literals;
    while (child_.running() && duration_since(start_time) < 100ms) {
        std::this_thread::yield();
    }

    if (child_.running()) {
        child_.terminate();
    }
    else {
        child_.wait();
    }

    int code = child_.exit_code();

    if (code != 0) {
        LogWarn << "child exit with" << code << VAR(exec_) << VAR(args_) << VAR(child_.id());
        return false;
    }

    return true;
}

bool ChildPipeIOStream::is_open() const
{
    return !pin_.eof();
}

std::string ChildPipeIOStream::read_once(size_t max_count)
{
    constexpr size_t kBufferSize = 128 * 1024;

    if (!buffer_) {
        buffer_ = std::make_unique<char[]>(kBufferSize);
    }

    size_t count = std::min(kBufferSize, max_count);
    auto read = pin_.read(buffer_.get(), count).gcount();
    return std::string(buffer_.get(), read);
}

MAA_NS_END
