#include "sgeAssetLoaderImpl.h"
#include <core/sgeFileReader.h>

#include <stdio.h>

namespace sge
{

    AssetLoaderImpl::AssetLoaderImpl()
    {
    }

    AssetLoaderImpl::~AssetLoaderImpl()
    {
    }

    int AssetLoaderImpl::initialize()
    {
        addSearchPath("./");
        addSearchPath("./assets/");
        addSearchPath("../assets/");
#ifdef SGE_ANDROID
        #error "add asset path from jni"
        #error "add application path from jni"
#endif // SGE_ANDROID

        return 0;
    }

    void AssetLoaderImpl::finalize()
    {
    }

    bool AssetLoaderImpl::addSearchPath(const char *path)
    {
        for (sgeVector<sgeString>::iterator it = _searchPath.begin();
            it != _searchPath.end(); ++it)
        {
            if (0 == (*it).compare(path))
            {
                return true;
            }
        }

        _searchPath.push_back(path);
        return true;
    }

    void AssetLoaderImpl::removeSearchPath(const char *path)
    {
        for (sgeVector<sgeString>::iterator it = _searchPath.begin();
            it != _searchPath.end(); ++it)
        {
            if (0 == (*it).compare(path))
            {
                _searchPath.erase(it);
                break;
            }
        }
    }

    sgeString AssetLoaderImpl::findFile(const char *name) const
    {
        sgeString fullPath;
        for (auto it = _searchPath.cbegin();
            it != _searchPath.cend(); ++it, fullPath.clear())
        {
            fullPath.append(*it);
            fullPath.append(name);
            bool ret;
            FileReader reader(fullPath.c_str(), &ret);
            if (ret)
            {
                break;
            }
        }
        return fullPath;
    }

    SGE_ASSET_API AssetLoader* newAssetLoader()
    {
        return (AssetLoader*)new AssetLoaderImpl();
    }

    SGE_ASSET_API void deleteAssetLoader(AssetLoader* object)
    {
        AssetLoaderImpl* myImpl = dynamic_cast<AssetLoaderImpl*>(object);
        if (myImpl)
        {
            delete myImpl;
        }
    }

}

