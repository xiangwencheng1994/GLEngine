#include <asset/sgeAssetLoader.h>
#include <device/sgeDeviceModule.h>
#include <core/sgeThread.h>
#include <graphics/sgeGraphicsSystem.h>
#include <graphics/sgeGpuBuffer.h>

#ifndef _DEBUG
    #pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
#endif

int main()
{
    sge::AssetLoader assetLoader;
    sge::DeviceModule device;
    sge::GraphicsSystem graphics;
    if (0 != assetLoader.initialize())
        return 1;
    if (0 != device.initialize())
        return 2;
    if (0 != graphics.initialize())
        return 3;
    
    while (true)
    {
        assetLoader.tick();
        device.tick();
        graphics.tick();
        device.swapBuffer();
    }
    
    graphics.finalize();
    device.finalize();
    assetLoader.finalize();
    return 0;
}
