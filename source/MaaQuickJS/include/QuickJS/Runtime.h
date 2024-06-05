#pragma once

#include "Conf/Conf.h"

#include "Define.h"
#include <cstdint>

MAA_QUICKJS_NS_BEGIN

class Runtime
{
    friend class Context;

private:
    Runtime(JSRuntime* runtime, bool own = true);

public:
    Runtime();
    // runtime2
    Runtime(const Runtime&) = delete;
    Runtime(Runtime&&);
    ~Runtime();
    Runtime& operator=(const Runtime&) = delete;
    Runtime& operator=(Runtime&&);

    void set_runtime_info(const char* info) const;
    void set_memory_limit(size_t limit) const;
    void set_dump_flags(uint64_t flags) const;
    void set_gc_threshold(size_t gc_threshold) const;
    void set_max_stack_size(size_t stack_size) const;
    void update_stack_top() const;

    void* get_opaque() const;
    void set_opaque(void*) const;

    // mark
    void run_gc() const;

    bool is_live_object(const Value& value) const;

private:
    JSRuntime* runtime_ = nullptr;
    bool own_ = true;
};

MAA_QUICKJS_NS_END
