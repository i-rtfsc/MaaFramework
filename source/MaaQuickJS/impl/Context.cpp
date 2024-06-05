#include "QuickJS/Context.h"
#include "QuickJS/Runtime.h"
#include "QuickJS/Value.h"

#include "quickjs.h"

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
    return Value(JS_GetClassProto(context_, class_id), context_, false);
}

Value Context::eval(std::string_view code, std::string src) const
{
    JSValue value = JS_Eval(context_, code.data(), code.size(), src.c_str(), 0);
    return Value(value, context_);
}

MAA_QUICKJS_NS_END
