#include <asset/sgeAssetLoader.h>
#include <core/sgeFileReader.h>

#include <stdio.h>

namespace sge
{

    class AssetLoaderPrivate : public Vector<String>
    {
    };

    AssetLoader::AssetLoader()
        : d(new AssetLoaderPrivate())
    {
    }


    AssetLoader::~AssetLoader()
    {
        delete d;
    }

    int AssetLoader::initialize()
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

    void AssetLoader::finalize()
    {
    }

    bool AssetLoader::addSearchPath(const char *path)
    {
        for (Vector<String>::iterator it = d->begin();
            it != d->end(); ++it)
        {
            if (0 == (*it).compare(path))
            {
                return true;
            }
        }

        d->push_back(path);
        return true;
    }

    void AssetLoader::removeSearchPath(const char *path)
    {
        for (Vector<String>::iterator it = d->begin();
            it != d->end(); ++it)
        {
            if (0 == (*it).compare(path))
            {
                d->erase(it);
                break;
            }
        }
    }

    SharedPtr<StreamReader> AssetLoader::findFile(const char *name) const
    {
        FileReader* reader = new FileReader();
        String fullPath;
        for (auto it = d->cbegin();
            it != d->cend(); ++it, fullPath.clear())
        {
            fullPath.append(*it);
            fullPath.append(name);
            if (reader->open(fullPath.c_str()))
            {
                break;
            }
        }
        if (reader->isBad())
        {
            delete reader;
            reader = NULL;
        }
        return SharedPtr<StreamReader>((StreamReader*)reader);
    }

}

