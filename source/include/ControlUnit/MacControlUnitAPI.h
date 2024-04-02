#pragma once

#include <memory>
#include <optional>

#include "ControlUnit/ControlUnitAPI.h"
#include "MaaFramework/MaaDef.h"

#ifdef __cplusplus
extern "C"
{
#endif

    MAA_CONTROL_UNIT_API MaaStringView MaaMacControlUnitGetVersion();

    MAA_CONTROL_UNIT_API MaaControlUnitHandle MaaMacControlUnitCreate(
        MaaMacWindowId windowId,
        MaaMacControllerType type,
        MaaControllerCallback callback,
        MaaCallbackTransparentArg callback_arg);

    MAA_CONTROL_UNIT_API void MaaMacControlUnitDestroy(MaaControlUnitHandle handle);

#ifdef __cplusplus
}
#endif
