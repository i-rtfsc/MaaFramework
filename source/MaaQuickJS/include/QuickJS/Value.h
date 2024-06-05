#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

#include "Conf/Conf.h"

#include "Define.h"
#include "quickjs.h"

MAA_QUICKJS_NS_BEGIN

class Value
{
    friend class Runtime;
    friend class Context;

private:
    Value(JSValue value);

public:
    Value(const Value&);
    Value(Value&&) = default;
    Value& operator=(const Value&);
    Value& operator=(Value&&) = default;

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

    JSClassID get_class_id() const;

    bool is_number() const;
    bool is_big_int() const;
    bool is_bool() const;
    bool is_null() const;
    bool is_undefined() const;
    bool is_exception() const;
    bool is_uninitialized() const;
    bool is_string() const;
    bool is_symbol() const;
    bool is_object() const;

private:
    std::unique_ptr<JSValue> value_ = nullptr;
};

MAA_QUICKJS_NS_END
