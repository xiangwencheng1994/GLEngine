#pragma once

#include <core/sgeRuntimeModule.h>

namespace sge
{

    /**
     * Interface AssetLoader
     */
    class AssetLoader : public IRuntimeModule
    {
    public:
        /**
         * Add a search path
         * @param path
         * @return true if add success
         */
        virtual bool addSearchPath(const char *path) = 0;
        
        /**
         * Remove a search path
         */
        virtual void removeSearchPath(const char *path) = 0;

        /**
         * Find a file in all search path
         * @return the real path for sgeFileReader, empty if not find
         */
        virtual sgeString findFile(const char *name) const = 0;
    };

    #ifdef MODULE_ASSET_EXPORTS
    #define SGE_ASSET_API SGE_EXPORT
    #else
    #define SGE_ASSET_API SGE_IMPORT
    #endif
    /**
     * Create asset loader object
     */
    SGE_ASSET_API AssetLoader* createAssetLoader();

    /**
     * Destory asset loader object
     */
    SGE_ASSET_API void destoryAssetLoader(AssetLoader* object);

}
