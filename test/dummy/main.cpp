#include "MaaFramework/Instance/MaaController.h"
#include "MaaFramework/MaaDef.h"
#include <cstdio>
#include <iostream>

#include <MaaFramework/MaaAPI.h>
#include <MaaToolkit/MaaToolkitAPI.h>

int main()
{
    auto sz = MaaToolkitFindWindow("", "r4.1.22/mac_20240116_wecom_vision");
    if (sz == 0) {
        std::cout << "no window found" << std::endl;
        return 0;
    }
    auto id = MaaToolkitGetWindow(0);
    // auto id = MaaToolkitGetForegroundWindow();
    // MaaHwnd id = 0x3b49;
    // std::cout << "foreground: 0x" << std::hex << id << std::endl;

    auto ctrl = MaaMacControllerCreate(
        id,
        MaaMacControllerType_Touch_Event | MaaMacControllerType_Key_Event
            | MaaMacControllerType_Screencap_CG,
        0,
        0);

    std::cout << ctrl << std::endl;

    auto actS = MaaControllerPostScreencap(ctrl);
    MaaControllerWait(ctrl, actS);
    MaaImageBufferHandle h = MaaCreateImageBuffer();
    MaaControllerGetImage(ctrl, h);
    auto imgSize = MaaGetImageEncodedSize(h);
    auto imgData = MaaGetImageEncoded(h);
    FILE* file = fopen("1.png", "wb");
    fwrite(imgData, imgSize, 1, file);
    fclose(file);

    // auto act = MaaControllerPostClick(ctrl, 67, 26);
    // MaaControllerWait(ctrl, act);
    auto act = MaaControllerPostPressKey(ctrl, 0);
    MaaControllerWait(ctrl, act);

    // MaaControllerDestroy(ctrl);
}
