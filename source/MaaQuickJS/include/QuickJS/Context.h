#pragma once

#include <optional>
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

    bool is_equal(const Value& op1, const Value& op2) const;
    bool is_strict_equal(const Value& op1, const Value& op2) const;
    bool is_same_value(const Value& op1, const Value& op2) const;
    bool is_same_value_zero(const Value& op1, const Value& op2) const;

    Value bool_(bool value) const;
    Value int32(int32_t value) const;
    Value float64(double value) const;
    Value catch_offset(int32_t value) const;
    Value int64(int64_t value) const;
    Value uint32(uint32_t value) const;
    Value number(double value) const;
    Value big_int64(int64_t value) const;
    Value big_uint64(uint64_t value) const;

    Value throw_(const Value& obj) const;
    Value get_exception() const;
    bool is_error(const Value& value) const;
    void reset_uncatchable_error() const;
    Value new_error() const;
    // throw xxx error

    void free(const Value& value) const;
    Value dup(const Value& value) const;

    bool to_bool(const Value& value) const;
    std::optional<int32_t> to_int32(const Value& value) const;
    std::optional<uint32_t> to_uint32(const Value& value) const;
    std::optional<int64_t> to_int64(const Value& value) const;
    std::optional<uint64_t> to_index(const Value& value) const;
    std::optional<double> to_float64(const Value& value) const;
    std::optional<int64_t> to_big_int64(const Value& value) const;
    std::optional<uint64_t> to_big_uint64(const Value& value) const;
    std::optional<int64_t> to_int64_ext(const Value& value) const;

    Value string(std::string_view str) const;
    // atom string

    Value eval(std::string_view code, std::string src) const;

private:
    JSContext* context_ = nullptr;
    bool own_ = true;
};

MAA_QUICKJS_NS_END
