module;

#include "Conf/Conf.h"
#include "MaaFramework/MaaPort.h"

export module MaaUtils_NonCopyable;

MAA_NS_BEGIN

export class MAA_UTILS_API NonCopyButMovable
{
public:
    NonCopyButMovable(const NonCopyButMovable&) = delete;
    NonCopyButMovable(NonCopyButMovable&&) = default;

    NonCopyButMovable& operator=(const NonCopyButMovable&) = delete;
    NonCopyButMovable& operator=(NonCopyButMovable&&) = default;

protected:
    NonCopyButMovable() = default;
};

export class MAA_UTILS_API NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = delete;

    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable& operator=(NonCopyable&&) = delete;

protected:
    NonCopyable() = default;
};

MAA_NS_END
