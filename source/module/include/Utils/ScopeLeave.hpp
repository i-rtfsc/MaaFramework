#pragma once

#include "Conf/Conf.h"

#define _Cat_(a, b) a##b
#define _Cat(a, b) _Cat_(a, b)
#define _CatVarNameWithLine(Var) _Cat(Var, __LINE__)
#define ScopeHelperVarName _CatVarNameWithLine(_scope_)

#define OnScopeLeave(func) MAA_NS::ScopeLeaveHelper ScopeHelperVarName(func)
