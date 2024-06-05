#include "QuickJS/Value.h"
#include "QuickJS/Define.h"
#include "QuickJS/Runtime.h"

#include "quickjs.h"
#include <memory>

MAA_QUICKJS_NS_BEGIN

Value::Value(JSValue value)
    : value_(new JSValue { value })
{
}

Value::Value(const Value& val)
{
    value_ = std::make_unique<JSValue>(*val.value_);
}

Value& Value::operator=(const Value& val)
{
    if (&val == this) {
        return *this;
    }
    value_ = std::make_unique<JSValue>(*val.value_);
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
    return JS_NAN;
}

bool Value::is_nan() const
{
    return JS_VALUE_IS_NAN(*value_);
}

Value Value::null()
{
    return JS_NULL;
}

Value Value::undefined()
{
    return JS_UNDEFINED;
}

Value Value::false_()
{
    return JS_FALSE;
}

Value Value::true_()
{
    return JS_TRUE;
}

Value Value::exception()
{
    return JS_EXCEPTION;
}

Value Value::uninitialized()
{
    return JS_UNINITIALIZED;
}

JSClassID Value::get_class_id() const
{
    return JS_GetClassID(*value_);
}

bool Value::is_number() const
{
    return JS_IsNumber(*value_);
}

bool Value::is_big_int() const
{
    return JS_IsBigInt(nullptr, *value_);
}

bool Value::is_bool() const
{
    return JS_IsBool(*value_);
}

bool Value::is_null() const
{
    return JS_IsNull(*value_);
}

bool Value::is_undefined() const
{
    return JS_IsUndefined(*value_);
}

bool Value::is_exception() const
{
    return JS_IsException(*value_);
}

bool Value::is_uninitialized() const
{
    return JS_IsUninitialized(*value_);
}

bool Value::is_string() const
{
    return JS_IsString(*value_);
}

bool Value::is_symbol() const
{
    return JS_IsSymbol(*value_);
}

bool Value::is_object() const
{
    return JS_IsObject(*value_);
}

MAA_QUICKJS_NS_END
