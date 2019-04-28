#pragma once

#include <core/sgeRuntimeModule.h>

namespace sge
{

    /**
     * Interface AssetLoader
     */
    class SGE_API AssetLoader : public IRuntimeModule
    {
    public:
        ModuleType moduleType() const override final { return ModuleType::kModuleTypeAsset; }

        /**
         * Add a search path
         * @param path
         * @return true if add success
         */
        virtual bool addSearchPath(const char *path);
        
        /**
         * Remove a search path
         */
        virtual void removeSearchPath(const char *path);

        /**
         * Find a file in all search path
         * @return the real path for sgeFileReader, empty if not find
         */
        virtual sgeString findFile(const char *name) const;

    protected:
        friend class AssetLoaderPrivate;
        AssetLoaderPrivate* d;
    };

}

