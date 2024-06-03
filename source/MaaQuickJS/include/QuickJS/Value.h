#pragma once

#include "Conf/Conf.h"
#include <memory>
#include <string>
#include <string_view>

typedef struct JSContext JSContext;
typedef struct JSValue JSValue;

MAA_QUICKJS_NS_BEGIN

class Context;

class Value
{
    friend class Context;

private:
    Value(JSValue value, JSContext* context);

public:
    Value(const Value&) = delete;
    Value(Value&&);
    ~Value();
    Value& operator=(const Value&) = delete;
    Value& operator=(Value&&);

private:
    JSContext* context_ = nullptr;
    std::unique_ptr<JSValue> value_ = nullptr;
};

MAA_QUICKJS_NS_END
