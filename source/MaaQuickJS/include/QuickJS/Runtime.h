#pragma once

#include "Conf/Conf.h"

typedef struct JSRuntime JSRuntime;

MAA_QUICKJS_NS_BEGIN

class Context;
class Value;

class Runtime
{
    friend class Context;

public:
    Runtime();
    Runtime(const Runtime&) = delete;
    Runtime(Runtime&&);
    ~Runtime();
    Runtime& operator=(const Runtime&) = delete;
    Runtime& operator=(Runtime&&);

    Context new_context() const;
    void* opaque() const;
    void set_opaque(void*) const;

private:
    JSRuntime* runtime_ = nullptr;
};

MAA_QUICKJS_NS_END
