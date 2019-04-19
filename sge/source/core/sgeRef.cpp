#include <core/sgeRef.h>

namespace sge
{

    inline Ref::Ref()
        : _referenceCount(1) // when the Ref is created, the reference count of it is 1
    {
    }

    inline Ref::~Ref()
    {
    }

    inline void Ref::retain()
    {
        ASSERT(_referenceCount > 0 && "reference count should be greater than 0");
        ++_referenceCount;
    }

    inline void Ref::release()
    {
        ASSERT(_referenceCount > 0 && "reference count should be greater than 0");
        --_referenceCount;

        if (_referenceCount == 0)
        {
            delete this;
        }
    }

    inline unsigned int Ref::getReferenceCount() const
    {
        return _referenceCount;
    }

}

