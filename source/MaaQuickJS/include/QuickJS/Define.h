#pragma once

#include <cstdint>
#include <span>

#include "Conf/Conf.h"

#ifndef QUICKJS_H

typedef struct JSRuntime JSRuntime;
typedef struct JSContext JSContext;
typedef struct JSValue JSValue;
typedef uint32_t JSClassID;
typedef uint32_t JSAtom;

#endif

MAA_QUICKJS_NS_BEGIN

enum class Tag : int32_t
{
    BigInt = -9,
    Symbol = -8,
    String = -7,
    // Module = -3,
    // FunctionBytecode = -2,
    Object = -1,

    Int = 0,
    Bool = 1,
    Null = 2,
    Undefined = 3,
    Uninitialized = 4,
    CatchOffset = 5,
    Exception = 6,
    Float64 = 7
};

enum class Prop : int32_t
{
    Configurable = 1 << 0,
    Writable = 1 << 1,
    Enumerable = 1 << 2,
    CWE = Configurable | Writable | Enumerable,

    // Length = 1 << 3,
    TMask = 3 << 4,

    Normal = 0 << 4,
    GetSet = 1 << 4,
    // VarRef = 2 << 4,
    // AutoInit = 3 << 4,

    HasShift = 8,
    HasConfigurable = 1 << 8,
    HasWritable = 1 << 9,
    HasEnumerable = 1 << 10,
    HasGet = 1 << 11,
    HasSet = 1 << 12,
    HasValue = 1 << 13,

    Throw = 1 << 14,
    ThrowStrict = 1 << 15,

    // NoAdd = 1 << 16,
    // NoExotic = 1 << 17,
    // DefineProperty = 1 << 18,
    // ReflectDefineProperty = 1 << 19,
};

enum class Eval : int32_t
{
    TypeGlobal = 0 << 0,
    TypeModule = 1 << 0,
    // TypeDirect = 2 << 0,
    // TypeIndirect = 3 << 0,
    // TypeMask = 3 << 0,

    FlagStrict = 1 << 3,
    // FlagUnused = 1 << 4,
    FlagCompileOnly = 1 << 5,
    BacktraceBarrier = 1 << 6
};

class Runtime;
class Context;
class Value;

// using CFunction = Value(Context ctx, Value this_val, std::span<Value> args);

MAA_QUICKJS_NS_END
