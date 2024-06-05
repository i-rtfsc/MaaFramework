#pragma once

#include <string>
#include <string_view>

#include "Conf/Conf.h"

#include "Define.h"

MAA_QUICKJS_NS_BEGIN

class Context
{
private:
    Context(JSContext* context, bool own = true);

public:
    Context(const Runtime& runtime);
    Context(const Context&) = delete;
    Context(Context&&);
    ~Context();
    Context& operator=(const Context&) = delete;
    Context& operator=(Context&&);

    Context dup() const;

    void* get_opaque() const;
    void set_opaque(void*) const;

    Runtime get_runtime() const;

    void set_class_proto(JSClassID class_id, Value obj) const;
    Value get_class_proto(JSClassID class_id) const;

    Value eval(std::string_view code, std::string src) const;

private:
    JSContext* context_ = nullptr;
    bool own_ = true;
};

MAA_QUICKJS_NS_END
