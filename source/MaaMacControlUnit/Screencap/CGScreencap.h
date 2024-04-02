#pragma once

#import <Cocoa/Cocoa.h>

#include "Base/UnitBase.h"

MAA_CTRL_UNIT_NS_BEGIN

class CGScreencap : public ScreencapBase
{
public:
    explicit CGScreencap(CGWindowID windowId)
        : windowId_(windowId)
    {
    }

    virtual ~CGScreencap() override = default;

public: // from ScreencapBase
    virtual std::optional<cv::Mat> screencap() override;

private:
    CGWindowID windowId_ = 0;
};

MAA_CTRL_UNIT_NS_END
