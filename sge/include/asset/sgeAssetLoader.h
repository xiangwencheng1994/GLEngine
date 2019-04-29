#pragma once

#include <core/sgeRuntimeModule.h>
#include <core/sgeBufferReader.h>

namespace sge
{

    /**
     * Class AssetLoader
     */
    class SGE_API AssetLoader : public IRuntimeModule
    {
    public:
        /**
         * Constructor
         */
        AssetLoader();

        /**
         * Destructor
         */
        ~AssetLoader();

        /**
         * Get type enum
         */
        ModuleType moduleType() const override final { return ModuleType::kModuleTypeAsset; }

        /**
         * Add a search path
         * @param path
         * @return true if add success
         */
        bool addSearchPath(const char *path);
        
        /**
         * Remove a search path
         */
        void removeSearchPath(const char *path);

        /**
         * Find a file in all search path
         */
        SharedPtr<StreamReader> findFile(const char *name) const;

    public:
        int     initialize() override;
        void    finalize() override;
        void    tick() override {}

    protected:
        friend class AssetLoaderPrivate;
        AssetLoaderPrivate* d;
    };

}

