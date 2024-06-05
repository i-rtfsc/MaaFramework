#include "QuickJS/Runtime.h"

#include "Conf/Conf.h"
#include "QuickJS/Define.h"
#include "QuickJS/Value.h"

#include "quickjs.h"

MAA_QUICKJS_NS_BEGIN

Runtime::Runtime(JSRuntime* runtime, bool own)
    : runtime_(runtime)
    , own_(own)
{
}

Runtime::Runtime()
{
    runtime_ = JS_NewRuntime();
}

Runtime::Runtime(Runtime&& rt)
{
    runtime_ = rt.runtime_;
    own_ = rt.own_;
    rt.runtime_ = nullptr;
    rt.own_ = false;
}

Runtime::~Runtime()
{
    if (runtime_ && own_) {
        JS_FreeRuntime(runtime_);
    }
}

Runtime& Runtime::operator=(Runtime&& rt)
{
    if (&rt == this) {
        return *this;
    }
    if (runtime_ && own_) {
        JS_FreeRuntime(runtime_);
        runtime_ = nullptr;
        own_ = false;
    }
    runtime_ = rt.runtime_;
    own_ = rt.own_;
    rt.runtime_ = nullptr;
    rt.own_ = false;
    return *this;
}

void Runtime::set_runtime_info(const char* info) const
{
    JS_SetRuntimeInfo(runtime_, info);
}

void Runtime::set_memory_limit(size_t limit) const
{
    JS_SetMemoryLimit(runtime_, limit);
}

void Runtime::set_dump_flags(uint64_t flags) const
{
    JS_SetDumpFlags(runtime_, flags);
}

void Runtime::set_gc_threshold(size_t gc_threshold) const
{
    JS_SetGCThreshold(runtime_, gc_threshold);
}

void Runtime::set_max_stack_size(size_t stack_size) const
{
    JS_SetMaxStackSize(runtime_, stack_size);
}

void Runtime::update_stack_top() const
{
    JS_UpdateStackTop(runtime_);
}

void* Runtime::get_opaque() const
{
    return JS_GetRuntimeOpaque(runtime_);
}

void Runtime::set_opaque(void* opaque) const
{
    JS_SetRuntimeOpaque(runtime_, opaque);
}

void Runtime::run_gc() const
{
    JS_RunGC(runtime_);
}

bool Runtime::is_live_object(const Value& value) const
{
    return JS_IsLiveObject(runtime_, *value.value_);
}

JSClassID Runtime::new_class_id() const
{
    JSClassID result;
    return JS_NewClassID(runtime_, &result);
    return result;
}

void Runtime::free(const Value& value) const
{
    JS_FreeValueRT(runtime_, *value.value_);
}

Value Runtime::dup(const Value& value) const
{
    return JS_DupValueRT(runtime_, *value.value_);
}

MAA_QUICKJS_NS_END
