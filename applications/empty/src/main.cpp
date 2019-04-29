#include <asset/sgeAssetLoader.h>
#include <device/sgeDeviceModule.h>
#include <core/sgeThread.h>

#ifndef _DEBUG
    #pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
#endif

int main()
{
    sge::AssetLoader assetLoader;
    sge::DeviceModule device;
    if (0 != assetLoader.initialize())
        return 1;
    if (0 != device.initialize())
        return 2;
    
    while (true)
    {
        assetLoader.tick();
        device.tick();
        device.swapBuffer();
    }
    
    device.finalize();
    assetLoader.finalize();
    return 0;
}
