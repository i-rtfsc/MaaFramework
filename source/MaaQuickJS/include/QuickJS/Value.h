#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

#include "Conf/Conf.h"

#include "Define.h"

MAA_QUICKJS_NS_BEGIN

class Value
{
    friend class Runtime;
    friend class Context;

private:
    Value(JSValue value, JSContext* context = nullptr, bool own = true);

public:
    Value(const Value&) = delete;
    Value(Value&&);
    ~Value();
    Value& operator=(const Value&) = delete;
    Value& operator=(Value&&);

    int32_t tag() const; // Tag

    int32_t get_int() const;
    bool get_bool() const;
    double get_float64() const;
    // get_ptr

    // make_value
    // make_ptr

    static Value nan();
    bool is_nan() const;

    static Value null();
    static Value undefined();
    static Value false_();
    static Value true_();
    static Value exception();
    static Value uninitialized();

    bool is_equal(const Value& value) const;
    bool is_strict_equal(const Value& value) const;
    bool is_same_value(const Value& value) const;
    bool is_same_value_zero(const Value& value) const;

private:
    std::unique_ptr<JSValue> value_ = nullptr;
    JSContext* context_ = nullptr;
    bool own_ = true;
};

MAA_QUICKJS_NS_END
