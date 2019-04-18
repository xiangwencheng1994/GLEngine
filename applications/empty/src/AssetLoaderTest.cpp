#include <asset/sgeAssetLoader.h>
#include <iostream>

int main()
{
    sge::AssetLoader* assetLoader = sge::createAssetLoader();
    if (0 != assetLoader->initialize())
        return 1;
    if (assetLoader->moduleType() != sge::ModuleType::kModuleTypeAsset)
        return 2;
    assetLoader->tick();
    sgeString f = assetLoader->findFile("fonts/DroidSans.ttf");
    if (f.empty())
        return 3;
    printf("File: %s\n", f.c_str());
    assetLoader->finalize();
    sge::destoryAssetLoader(assetLoader);
    return 0;
}