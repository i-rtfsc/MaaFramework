// cv must before cocoa
#include "Utils/NoWarningCV.hpp"

#include "CGScreencap.h"

#include "Utils/Logger.h"
#include <CoreGraphics/CoreGraphics.h>
#include <Foundation/Foundation.h>

MAA_CTRL_UNIT_NS_BEGIN

std::optional<cv::Mat> CGScreencap::screencap()
{
    if (!windowId_) {
        LogError << "windowId_ is 0";
        return std::nullopt;
    }

    CGRect bounds;

    CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionAll, kCGNullWindowID);

    NSArray* windows = CFBridgingRelease(windowList);
    for (NSDictionary* window in windows) {
        NSNumber* windowIDNumber = window[(id)kCGWindowNumber];
        if (windowIDNumber && [windowIDNumber unsignedIntValue] == windowId_) {
            CGRectMakeWithDictionaryRepresentation(
                (CFDictionaryRef)window[(id)kCGWindowBounds],
                &bounds);
            break;
        }
    }

    CFRelease(windowList);

    CGFloat scale = 1.0;
    CGPoint center = CGPointMake(CGRectGetMidX(bounds), CGRectGetMidY(bounds));
    for (NSScreen* screen in [NSScreen screens]) {
        if (NSPointInRect(center, screen.frame)) {
            scale = screen.backingScaleFactor;
        }
    }

    auto image = CGWindowListCreateImage(
        bounds,
        kCGWindowListOptionOnScreenBelowWindow | kCGWindowListOptionIncludingWindow,
        windowId_,
        kCGWindowImageShouldBeOpaque);

    if (!image) {
        LogError << "CGWindowListCreateImage failed";
        return std::nullopt;
    }

    size_t width = round(CGImageGetWidth(image) / scale);
    size_t height = round(CGImageGetHeight(image) / scale);

    if (width != bounds.size.width || height != bounds.size.height) {
        LogWarn << "bounds mismatch! image:" << VAR(width) << VAR(height)
                << "bounds:" << VAR(bounds.size.width) << VAR(bounds.size.height);
        width = bounds.size.width;
        height = bounds.size.height;
    }

    auto colorSpace = CGImageGetColorSpace(image);

    if (!colorSpace) {
        LogError << "CGImageGetColorSpace failed";
        CGImageRelease(image);
        return std::nullopt;
    }

    cv::Mat mat(height, width, CV_8UC4);

    CGContextRef contextRef = CGBitmapContextCreate(
        mat.data,
        width,
        height,
        8,
        mat.step[0],
        colorSpace,
        static_cast<uint32_t>(kCGImageAlphaNoneSkipLast)
            | static_cast<uint32_t>(kCGBitmapByteOrderDefault));
    if (!contextRef) {
        LogError << "CGBitmapContextCreate failed";
        CGImageRelease(image);
        return std::nullopt;
    }

    CGContextDrawImage(contextRef, CGRectMake(0, 0, width, height), image);
    CGContextRelease(contextRef);
    CGImageRelease(image);

    cv::Mat matBGR;
    cv::cvtColor(mat, matBGR, cv::COLOR_RGBA2BGR);

    return matBGR;
}

MAA_CTRL_UNIT_NS_END
