#pragma once

#include <asset/sgeAssetLoader.h>

namespace sge
{

    class AssetLoaderImpl : public AssetLoader
    {
    public:
        AssetLoaderImpl();
        ~AssetLoaderImpl();
        int initialize() override;
        void finalize() override;
        void tick() override {}
    public:
        bool    addSearchPath(const char *path);
        void    removeSearchPath(const char *path);
        sgeString   findFile(const char *name) const;
    public:
        sgeVector<sgeString>    _searchPath;
    };

}