#pragma once

#include "Conf/Conf.h"
#include <string>
#include <string_view>

typedef struct JSContext JSContext;

MAA_QUICKJS_NS_BEGIN

class Runtime;
class Value;

class Context
{
public:
    Context(const Runtime& runtime);
    Context(const Context&) = delete;
    Context(Context&&);
    ~Context();
    Context& operator=(const Context&) = delete;
    Context& operator=(Context&&);

    Value eval(std::string_view code, std::string src) const;

private:
    JSContext* context_ = nullptr;
};

MAA_QUICKJS_NS_END
