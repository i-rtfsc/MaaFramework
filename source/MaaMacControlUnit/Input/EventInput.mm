#include "EventInput.h"

#include "Utils/Logger.h"
#include "Utils/Platform.h"
#include <AppKit/AppKit.h>
#include <CoreGraphics/CoreGraphics.h>
#include <cstddef>

MAA_CTRL_UNIT_NS_BEGIN

EventInput::EventInput(CGWindowID windowId)
    : windowId_(windowId)
{
    CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionAll, kCGNullWindowID);

    NSArray* windows = CFBridgingRelease(windowList);
    for (NSDictionary* window in windows) {
        NSNumber* windowIDNumber = window[(id)kCGWindowNumber];
        if (windowIDNumber && [windowIDNumber unsignedIntValue] == windowId) {
            NSNumber* ownerPID = window[(id)kCGWindowOwnerPID];
            pid_ = [ownerPID integerValue];
            break;
        }
    }

    CFRelease(windowList);
}

bool EventInput::click(int x, int y)
{
    LogInfo << VAR(x) << VAR(y);

    if (!windowId_) {
        LogError << "windowId_ is 0";
        return false;
    }

    if (!pid_) {
        LogError << "pid_ is 0";
        return false;
    }

    auto downEvent = [NSEvent mouseEventWithType:NSEventTypeLeftMouseDown
                                        location:CGPointMake(x, y)
                                   modifierFlags:0
                                       timestamp:[NSDate timeIntervalSinceReferenceDate]
                                    windowNumber:windowId_
                                         context:nil
                                     eventNumber:0
                                      clickCount:1
                                        pressure:0];
    CGEventPostToPid(pid_, [downEvent CGEvent]);

    auto upEvent = [NSEvent mouseEventWithType:NSEventTypeLeftMouseUp
                                      location:CGPointMake(x, y)
                                 modifierFlags:0
                                     timestamp:[NSDate timeIntervalSinceReferenceDate]
                                  windowNumber:windowId_
                                       context:nil
                                   eventNumber:0
                                    clickCount:1
                                      pressure:0];
    CGEventPostToPid(pid_, [upEvent CGEvent]);

    return true;
}

bool EventInput::swipe(int x1, int y1, int x2, int y2, int duration)
{
    LogInfo << VAR(x1) << VAR(y1) << VAR(x2) << VAR(y2) << VAR(duration);

    if (!windowId_) {
        LogError << "windowId_ is 0";
        return false;
    }

    if (!pid_) {
        LogError << "pid_ is 0";
        return false;
    }

    if (duration <= 0) {
        LogWarn << "duration out of range" << VAR(duration);
        duration = 500;
    }

    auto start = std::chrono::steady_clock::now();
    auto now = start;

    auto downEvent = [NSEvent mouseEventWithType:NSEventTypeLeftMouseDown
                                        location:CGPointMake(x1, y1)
                                   modifierFlags:0
                                       timestamp:[NSDate timeIntervalSinceReferenceDate]
                                    windowNumber:windowId_
                                         context:nil
                                     eventNumber:0
                                      clickCount:1
                                        pressure:0];
    CGEventPostToPid(pid_, [downEvent CGEvent]);

    constexpr double kInterval = 10; // ms
    const double steps = duration / kInterval;
    const double x_step_len = (x2 - x1) / steps;
    const double y_step_len = (y2 - y1) / steps;
    const std::chrono::milliseconds delay(static_cast<int>(kInterval));

    for (int i = 0; i < steps; ++i) {
        int tx = static_cast<int>(x1 + i * x_step_len);
        int ty = static_cast<int>(y1 + i * y_step_len);
        std::this_thread::sleep_until(now + delay);
        now = std::chrono::steady_clock::now();

        auto moveEvent = [NSEvent mouseEventWithType:NSEventTypeLeftMouseDragged
                                            location:CGPointMake(tx, ty)
                                       modifierFlags:0
                                           timestamp:[NSDate timeIntervalSinceReferenceDate]
                                        windowNumber:windowId_
                                             context:nil
                                         eventNumber:0
                                          clickCount:1
                                            pressure:0];
        CGEventPostToPid(pid_, [moveEvent CGEvent]);
    }

    std::this_thread::sleep_until(now + delay);
    now = std::chrono::steady_clock::now();

    auto moveEventEnd = [NSEvent mouseEventWithType:NSEventTypeLeftMouseDragged
                                           location:CGPointMake(x2, y2)
                                      modifierFlags:0
                                          timestamp:[NSDate timeIntervalSinceReferenceDate]
                                       windowNumber:windowId_
                                            context:nil
                                        eventNumber:0
                                         clickCount:1
                                           pressure:0];
    CGEventPostToPid(pid_, [moveEventEnd CGEvent]);

    std::this_thread::sleep_until(now + delay);
    now = std::chrono::steady_clock::now();

    auto upEvent = [NSEvent mouseEventWithType:NSEventTypeLeftMouseUp
                                      location:CGPointMake(x2, y2)
                                 modifierFlags:0
                                     timestamp:[NSDate timeIntervalSinceReferenceDate]
                                  windowNumber:windowId_
                                       context:nil
                                   eventNumber:0
                                    clickCount:1
                                      pressure:0];
    CGEventPostToPid(pid_, [upEvent CGEvent]);

    return true;
}

bool EventInput::touch_down(int contact, int x, int y, int pressure)
{
    LogInfo << VAR(contact) << VAR(x) << VAR(y) << VAR(pressure);

    std::ignore = contact;
    std::ignore = pressure;

    if (!windowId_) {
        LogError << "windowId_ is 0";
        return false;
    }

    auto downEvent = [NSEvent mouseEventWithType:NSEventTypeLeftMouseDown
                                        location:CGPointMake(x, y)
                                   modifierFlags:0
                                       timestamp:[NSDate timeIntervalSinceReferenceDate]
                                    windowNumber:windowId_
                                         context:nil
                                     eventNumber:0
                                      clickCount:1
                                        pressure:0];
    CGEventPostToPid(pid_, [downEvent CGEvent]);

    return true;
}

bool EventInput::touch_move(int contact, int x, int y, int pressure)
{
    LogInfo << VAR(contact) << VAR(x) << VAR(y) << VAR(pressure);

    std::ignore = contact;
    std::ignore = pressure;

    if (!windowId_) {
        LogError << "windowId_ is 0";
        return false;
    }

    if (!pid_) {
        LogError << "pid_ is 0";
        return false;
    }

    auto moveEvent = [NSEvent mouseEventWithType:NSEventTypeLeftMouseDragged
                                        location:CGPointMake(x, y)
                                   modifierFlags:0
                                       timestamp:[NSDate timeIntervalSinceReferenceDate]
                                    windowNumber:windowId_
                                         context:nil
                                     eventNumber:0
                                      clickCount:1
                                        pressure:0];
    CGEventPostToPid(pid_, [moveEvent CGEvent]);

    cache_point_ = CGPointMake(x, y);

    return true;
}

bool EventInput::touch_up(int contact)
{
    LogInfo << VAR(contact);

    std::ignore = contact;

    if (!windowId_) {
        LogError << "windowId_ is 0";
        return false;
    }

    if (!pid_) {
        LogError << "pid_ is 0";
        return false;
    }

    auto upEvent = [NSEvent mouseEventWithType:NSEventTypeLeftMouseUp
                                      location:cache_point_
                                 modifierFlags:0
                                     timestamp:[NSDate timeIntervalSinceReferenceDate]
                                  windowNumber:windowId_
                                       context:nil
                                   eventNumber:0
                                    clickCount:1
                                      pressure:0];
    CGEventPostToPid(pid_, [upEvent CGEvent]);

    return true;
}

bool EventInput::press_key(int key)
{
    LogInfo << VAR(key);

    if (!windowId_) {
        LogError << "windowId_ is 0";
        return false;
    }

    if (!pid_) {
        LogError << "pid_ is 0";
        return false;
    }

    auto downEvent = CGEventCreateKeyboardEvent(NULL, 0, YES);
    CGEventPostToPid(pid_, downEvent);

    auto upEvent = CGEventCreateKeyboardEvent(NULL, 0, NO);
    CGEventPostToPid(pid_, upEvent);
    // auto downEvent = [NSEvent keyEventWithType:NSEventTypeKeyDown
    //                                   location:CGPointMake(0, 0)
    //                              modifierFlags:0
    //                                  timestamp:[NSDate timeIntervalSinceReferenceDate]
    //                               windowNumber:windowId_
    //                                    context:nil
    //                                 characters:@""
    //                charactersIgnoringModifiers:@""
    //                                  isARepeat:NO
    //                                    keyCode:key];
    // CGEventPostToPid(pid_, [downEvent CGEvent]);

    // auto upEvent = [NSEvent keyEventWithType:NSEventTypeKeyUp
    //                                 location:CGPointMake(0, 0)
    //                            modifierFlags:0
    //                                timestamp:[NSDate timeIntervalSinceReferenceDate]
    //                             windowNumber:windowId_
    //                                  context:nil
    //                               characters:@""
    //              charactersIgnoringModifiers:@""
    //                                isARepeat:NO
    //                                  keyCode:key];
    // CGEventPostToPid(pid_, [upEvent CGEvent]);

    return true;
}

bool EventInput::input_text(const std::string& text)
{
    LogInfo << VAR(text);

    if (!windowId_) {
        LogError << "windowId_ is 0";
        return false;
    }

    if (!pid_) {
        LogError << "pid_ is 0";
        return false;
    }

    LogError << "input_text not supported";

    return false;
}

MAA_CTRL_UNIT_NS_END
