#include "MaaFramework/MaaDef.h"
#import <Cocoa/Cocoa.h>
#include <memory>

#include "ControlUnit/MacControlUnitAPI.h"

#include "Base/UnitBase.h"
#include "Input/EventInput.h"
#include "Manager/ControlUnitMgr.h"
#include "Screencap/CGScreencap.h"
#include "Utils/Logger.h"

MaaStringView MaaMacControlUnitGetVersion()
{
#pragma message("MaaMacControlUnit MAA_VERSION: " MAA_VERSION)

    return MAA_VERSION;
}

MaaControlUnitHandle MaaMacControlUnitCreate(
    MaaMacWindowId windowId,
    MaaMacControllerType type,
    MaaControllerCallback callback,
    MaaCallbackTransparentArg callback_arg)
{
    using namespace MAA_CTRL_UNIT_NS;

    LogFunc << VAR_VOIDP(windowId) << VAR_VOIDP(callback) << VAR_VOIDP(callback_arg);

    if (!windowId) {
        LogError << "windowId is 0";
        return nullptr;
    }

    std::shared_ptr<TouchInputBase> touch_unit = nullptr;
    std::shared_ptr<KeyInputBase> key_unit = nullptr;
    std::shared_ptr<ScreencapBase> screencap_unit = nullptr;

    auto touch_type = type & MaaMacControllerType_Touch_Mask;
    auto key_type = type & MaaMacControllerType_Key_Mask;
    auto screencap_type = type & MaaMacControllerType_Screencap_Mask;

    std::shared_ptr<EventInput> event_input_unit = nullptr;

    switch (touch_type) {
    case MaaMacControllerType_Touch_Event:
        LogInfo << "touch_type: Event";
        if (!event_input_unit) {
            event_input_unit = std::make_shared<EventInput>(windowId);
        }
        touch_unit = event_input_unit;
        break;

    default:
        LogWarn << "Unknown touch input type" << VAR(touch_type);
        break;
    }

    switch (key_type) {
    case MaaMacControllerType_Key_Event:
        LogInfo << "key_type: Event";
        if (!event_input_unit) {
            event_input_unit = std::make_shared<EventInput>(windowId);
        }
        key_unit = event_input_unit;
        break;

    default:
        LogWarn << "Unknown key input type" << VAR(touch_type);
        break;
    }

    switch (screencap_type) {
    case MaaMacControllerType_Screencap_CG:
        LogInfo << "screencap_type: CG";
        screencap_unit = std::make_shared<CGScreencap>(windowId);
        break;

    default:
        LogWarn << "Unknown screencap input type" << VAR(screencap_type);
        break;
    }

    auto unit_mgr = std::make_unique<ControlUnitMgr>(windowId, callback, callback_arg);

    unit_mgr->set_touch_input_obj(touch_unit);
    unit_mgr->set_key_input_obj(key_unit);
    unit_mgr->set_screencap_obj(screencap_unit);

    return unit_mgr.release();
}

void MaaMacControlUnitDestroy(MaaControlUnitHandle handle)
{
    LogFunc << VAR_VOIDP(handle);

    if (handle) {
        delete handle;
    }
}
