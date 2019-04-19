#pragma once

#include <core/sgeDefs.h>

namespace sge
{

    /**
     * Class Ref
     */
    class SGE_CORE_API Ref
    {
    public:
        
        /**
         * Retains the ownership.
         *
         * This increases the Ref's reference count.
         *
         * @see release, autorelease
         */
        void retain();

        /**
         * Releases the ownership immediately.
         *
         * This decrements the Ref's reference count.
         *
         * If the reference count reaches 0 after the decrement, this Ref is
         * destructed.
         *
         * @see retain, autorelease
         */
        void release();
        
        /**
         * Returns the Ref's current reference count.
         *
         * @returns The Ref's reference count.
         */
        unsigned int getReferenceCount() const;

    protected:
        
        /**
         * Constructor
         *
         * The Ref's reference count is 1 after construction.
         */
        Ref();

    public:

        /**
         * Destructor
         */
        virtual ~Ref();

    protected:
        /// count of references
        unsigned int _referenceCount;
    };


}

