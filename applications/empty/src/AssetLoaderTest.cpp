#include <asset/sgeAssetLoader.h>
#include <device/sgeDeviceModule.h>
#include <core/sgeThread.h>



int main()
{
    sge::AssetLoader* assetLoader = newAssetLoader();
    sge::DeviceModule* device = newDeviceModule();
    if (0 != assetLoader->initialize())
        return 1;
    if (0 != device->initialize())
        return 2;
    
    while (true)
    {
        assetLoader->tick();
        device->tick();
    }
    
    device->finalize();
    assetLoader->finalize();
    deleteAssetLoader(assetLoader);
    deleteDeviceModule(device);
    return 0;
}
