module;

#include "Conf/Conf.h"

export module MaaUtils_ScopeLeave;

MAA_NS_BEGIN

export template <typename FuncT>
class ScopeLeaveHelper
{
public:
    explicit ScopeLeaveHelper(FuncT func)
        : func_(func)
    {
    }

    ~ScopeLeaveHelper() { func_(); }

private:
    FuncT func_;
};

MAA_NS_END
