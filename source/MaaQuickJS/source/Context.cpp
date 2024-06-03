#include "QuickJS/Context.h"
#include "QuickJS/Runtime.h"
#include "QuickJS/Value.h"

#include "quickjs.h"

MAA_QUICKJS_NS_BEGIN

Context::Context(const Runtime& runtime)
{
    context_ = JS_NewContext(runtime.runtime_);
}

Context::Context(Context&& rt)
{
    context_ = rt.context_;
    rt.context_ = nullptr;
}

Context::~Context()
{
    if (context_) {
        JS_FreeContext(context_);
    }
}

Context& Context::operator=(Context&& rt)
{
    if (&rt == this) {
        return *this;
    }
    if (context_) {
        JS_FreeContext(context_);
    }
    context_ = rt.context_;
    rt.context_ = nullptr;
    return *this;
}

Value Context::eval(std::string_view code, std::string src) const
{
    JSValue value = JS_Eval(context_, code.data(), code.size(), src.c_str(), 0);
    return Value(value, context_);
}

MAA_QUICKJS_NS_END
