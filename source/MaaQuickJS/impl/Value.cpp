#include "QuickJS/Value.h"
#include "QuickJS/Runtime.h"

#include "quickjs.h"

MAA_QUICKJS_NS_BEGIN

Value::Value(JSValue value, JSContext* context, bool own)
    : value_(new JSValue { value })
    , context_(context)
    , own_(own)
{
}

Value::Value(Value&& val)
{
    value_.swap(val.value_);
    context_ = val.context_;
    own_ = val.own_;
    val.context_ = nullptr;
    val.own_ = false;
}

Value::~Value()
{
    if (context_ && value_ && own_) {
        JS_FreeValue(context_, *value_);
    }
}

Value& Value::operator=(Value&& val)
{
    if (&val == this) {
        return *this;
    }
    if (context_ && value_ && own_) {
        JS_FreeValue(context_, *value_);
        value_.reset();
        context_ = nullptr;
        own_ = false;
    }
    value_.swap(val.value_);
    context_ = val.context_;
    own_ = val.own_;
    val.context_ = nullptr;
    val.own_ = false;
    return *this;
}

int32_t Value::tag() const
{
    return JS_VALUE_GET_TAG(*value_);
}

int32_t Value::get_int() const
{
    return JS_VALUE_GET_INT(*value_);
}

bool Value::get_bool() const
{
    return JS_VALUE_GET_BOOL(*value_);
}

double Value::get_float64() const
{
    return JS_VALUE_GET_FLOAT64(*value_);
}

Value Value::nan()
{
    return Value(JS_NAN);
}

bool Value::is_nan() const
{
    return JS_VALUE_IS_NAN(*value_);
}

Value Value::null()
{
    return Value(JS_NULL);
}

Value Value::undefined()
{
    return Value(JS_UNDEFINED);
}

Value Value::false_()
{
    return Value(JS_FALSE);
}

Value Value::true_()
{
    return Value(JS_TRUE);
}

Value Value::exception()
{
    return Value(JS_EXCEPTION);
}

Value Value::uninitialized()
{
    return Value(JS_UNINITIALIZED);
}

bool Value::is_equal(const Value& value) const
{
    return JS_IsEqual(context_, *value_, *value.value_);
}

bool Value::is_strict_equal(const Value& value) const
{
    return JS_IsStrictEqual(context_, *value_, *value.value_);
}

bool Value::is_same_value(const Value& value) const
{
    return JS_IsSameValue(context_, *value_, *value.value_);
}

bool Value::is_same_value_zero(const Value& value) const
{
    return JS_IsSameValueZero(context_, *value_, *value.value_);
}

MAA_QUICKJS_NS_END
