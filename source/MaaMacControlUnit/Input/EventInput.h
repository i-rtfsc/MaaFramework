#pragma once

#import <Cocoa/Cocoa.h>
#include <CoreGraphics/CoreGraphics.h>
#include <sys/_types/_pid_t.h>

#include "ControlUnit/ControlUnitAPI.h"

#include "Base/UnitBase.h"

MAA_CTRL_UNIT_NS_BEGIN

class EventInput
    : public TouchInputBase
    , public KeyInputBase
{
public:
    EventInput(CGWindowID windowId);

    virtual ~EventInput() override = default;

public: // from TouchInputBase
    virtual bool click(int x, int y) override;
    virtual bool swipe(int x1, int y1, int x2, int y2, int duration) override;

    virtual bool touch_down(int contact, int x, int y, int pressure) override;
    virtual bool touch_move(int contact, int x, int y, int pressure) override;
    virtual bool touch_up(int contact) override;

public: // from KeyInputBase
    virtual bool press_key(int key) override;
    virtual bool input_text(const std::string& text) override;

private:
    CGWindowID windowId_ = 0;
    pid_t pid_ = 0;

    CGPoint cache_point_ = { 0, 0 };
};

MAA_CTRL_UNIT_NS_END
