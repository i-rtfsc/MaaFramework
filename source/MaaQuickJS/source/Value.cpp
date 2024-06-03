#include "QuickJS/Value.h"
#include "QuickJS/Runtime.h"

#include "quickjs.h"

MAA_QUICKJS_NS_BEGIN

Value::Value(JSValue value, JSContext* context)
    : context_(context)
    , value_(new JSValue { value })
{
}

Value::Value(Value&& val)
{
    context_ = val.context_;
    val.context_ = nullptr;
    value_.swap(val.value_);
}

Value::~Value()
{
    if (context_ && value_) {
        JS_FreeValue(context_, *value_);
    }
}

Value& Value::operator=(Value&& val)
{
    if (&val == this) {
        return *this;
    }
    if (context_ && value_) {
        JS_FreeValue(context_, *value_);
        value_.reset();
    }
    context_ = val.context_;
    val.context_ = nullptr;
    value_.swap(val.value_);
    return *this;
}

MAA_QUICKJS_NS_END
