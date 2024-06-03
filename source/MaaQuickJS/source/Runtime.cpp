#include "QuickJS/Runtime.h"
#include "Conf/Conf.h"
#include "QuickJS/Context.h"

#include "quickjs.h"

MAA_QUICKJS_NS_BEGIN

Runtime::Runtime()
{
    runtime_ = JS_NewRuntime();
}

Runtime::Runtime(Runtime&& rt)
{
    runtime_ = rt.runtime_;
    rt.runtime_ = nullptr;
}

Runtime::~Runtime()
{
    if (runtime_) {
        JS_FreeRuntime(runtime_);
    }
}

Runtime& Runtime::operator=(Runtime&& rt)
{
    if (&rt == this) {
        return *this;
    }
    if (runtime_) {
        JS_FreeRuntime(runtime_);
    }
    runtime_ = rt.runtime_;
    rt.runtime_ = nullptr;
    return *this;
}

Context Runtime::new_context() const
{
    return Context(*this);
}

void* Runtime::opaque() const
{
    return JS_GetRuntimeOpaque(runtime_);
}

void Runtime::set_opaque(void* opaque) const
{
    JS_SetRuntimeOpaque(runtime_, opaque);
}

MAA_QUICKJS_NS_END
