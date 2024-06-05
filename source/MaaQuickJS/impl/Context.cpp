#include "QuickJS/Context.h"
#include "QuickJS/Runtime.h"
#include "QuickJS/Value.h"

#include "quickjs.h"
#include <cstdint>
#include <optional>

MAA_QUICKJS_NS_BEGIN

Context::Context(JSContext* context, bool own)
    : context_(context)
    , own_(own)
{
}

Context::Context(const Runtime& runtime)
{
    context_ = JS_NewContext(runtime.runtime_);
}

Context::Context(Context&& ctx)
{
    context_ = ctx.context_;
    own_ = ctx.own_;
    ctx.context_ = nullptr;
    ctx.own_ = false;
}

Context::~Context()
{
    if (context_ && own_) {
        JS_FreeContext(context_);
    }
}

Context& Context::operator=(Context&& ctx)
{
    if (&ctx == this) {
        return *this;
    }
    if (context_ && own_) {
        JS_FreeContext(context_);
        context_ = nullptr;
        own_ = false;
    }
    context_ = ctx.context_;
    own_ = ctx.own_;
    ctx.context_ = nullptr;
    ctx.own_ = false;
    return *this;
}

Context Context::dup() const
{
    return JS_DupContext(context_);
}

void* Context::get_opaque() const
{
    return JS_GetContextOpaque(context_);
}

void Context::set_opaque(void* opaque) const
{
    JS_SetContextOpaque(context_, opaque);
}

Runtime Context::get_runtime() const
{
    return Runtime(JS_GetRuntime(context_), false);
}

void Context::set_class_proto(JSClassID class_id, Value obj) const
{
    JS_SetClassProto(context_, class_id, *obj.value_);
}

Value Context::get_class_proto(JSClassID class_id) const
{
    return JS_GetClassProto(context_, class_id);
}

bool Context::is_equal(const Value& op1, const Value& op2) const
{
    return JS_IsEqual(context_, *op1.value_, *op2.value_);
}

bool Context::is_strict_equal(const Value& op1, const Value& op2) const
{
    return JS_IsStrictEqual(context_, *op1.value_, *op2.value_);
}

bool Context::is_same_value(const Value& op1, const Value& op2) const
{
    return JS_IsSameValue(context_, *op1.value_, *op2.value_);
}

bool Context::is_same_value_zero(const Value& op1, const Value& op2) const
{
    return JS_IsSameValueZero(context_, *op1.value_, *op2.value_);
}

Value Context::bool_(bool value) const
{
    return JS_NewBool(context_, value);
}

Value Context::int32(int32_t value) const
{
    return JS_NewInt32(context_, value);
}

Value Context::float64(double value) const
{
    return JS_NewFloat64(context_, value);
}

Value Context::catch_offset(int32_t value) const
{
    return JS_NewCatchOffset(context_, value);
}

Value Context::int64(int64_t value) const
{
    return JS_NewInt64(context_, value);
}

Value Context::uint32(uint32_t value) const
{
    return JS_NewUint32(context_, value);
}

Value Context::number(double value) const
{
    return JS_NewNumber(context_, value);
}

Value Context::big_int64(int64_t value) const
{
    return JS_NewBigInt64(context_, value);
}

Value Context::big_uint64(uint64_t value) const
{
    return JS_NewBigUint64(context_, value);
}

Value Context::throw_(const Value& obj) const
{
    return JS_Throw(context_, *obj.value_);
}

Value Context::get_exception() const
{
    return JS_GetException(context_);
}

bool Context::is_error(const Value& value) const
{
    return JS_IsError(context_, *value.value_);
}

void Context::reset_uncatchable_error() const
{
    return JS_ResetUncatchableError(context_);
}

Value Context::new_error() const
{
    return JS_NewError(context_);
}

void Context::free(const Value& value) const
{
    JS_FreeValue(context_, *value.value_);
}

Value Context::dup(const Value& value) const
{
    return JS_DupValue(context_, *value.value_);
}

bool Context::to_bool(const Value& value) const
{
    return JS_ToBool(context_, *value.value_);
}

std::optional<int32_t> Context::to_int32(const Value& value) const
{
    int32_t result;
    if (JS_ToInt32(context_, &result, *value.value_) < 0) {
        return std::nullopt;
    }
    return result;
}

std::optional<uint32_t> Context::to_uint32(const Value& value) const
{
    uint32_t result;
    if (JS_ToUint32(context_, &result, *value.value_) < 0) {
        return std::nullopt;
    }
    return result;
}

std::optional<int64_t> Context::to_int64(const Value& value) const
{
    int64_t result;
    if (JS_ToInt64(context_, &result, *value.value_) < 0) {
        return std::nullopt;
    }
    return result;
}

std::optional<uint64_t> Context::to_index(const Value& value) const
{
    uint64_t result;
    if (JS_ToIndex(context_, &result, *value.value_) < 0) {
        return std::nullopt;
    }
    return result;
}

std::optional<double> Context::to_float64(const Value& value) const
{
    double result;
    if (JS_ToFloat64(context_, &result, *value.value_) < 0) {
        return std::nullopt;
    }
    return result;
}

std::optional<int64_t> Context::to_big_int64(const Value& value) const
{
    int64_t result;
    if (JS_ToBigInt64(context_, &result, *value.value_) < 0) {
        return std::nullopt;
    }
    return result;
}

std::optional<uint64_t> Context::to_big_uint64(const Value& value) const
{
    uint64_t result;
    if (JS_ToBigUint64(context_, &result, *value.value_) < 0) {
        return std::nullopt;
    }
    return result;
}

std::optional<int64_t> Context::to_int64_ext(const Value& value) const
{
    int64_t result;
    if (JS_ToInt64Ext(context_, &result, *value.value_) < 0) {
        return std::nullopt;
    }
    return result;
}

Value Context::string(std::string_view str) const
{
    return JS_NewStringLen(context_, str.data(), str.size());
}

Value Context::eval(std::string_view code, std::string src) const
{
    return JS_Eval(context_, code.data(), code.size(), src.c_str(), 0);
}

MAA_QUICKJS_NS_END
