#include "core/ea/eamalloc.h"

void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
    return malloc(size);
}

void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
    #if defined(_MSC_VER)
        return _aligned_malloc(size, alignment);
    #else
        void* p = nullptr;
        posix_memalign(&p, alignment, size);
        return p;
    #endif
}

/*
void operator delete[](void* p, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
    free(p);
}

void operator delete[](void* p, size_t alignment, size_t alignmentOffset, const char* name, int flags, unsigned debugFlags, const char* file, int line) {
    #if defined(_MSC_VER)
        _aligned_free(p);
    #else
        free(p);
    #endif
}
*/

/*
namespace eastl {
    void allocator::set_name(const char* pName) {

    }

    void* allocator::allocate(size_t n, int flags) {
        return malloc(n);
    }

    void* allocator::allocate(size_t n, size_t alignment, size_t offset, int flags) {
        #if defined(_MSC_VER)
            return _aligned_malloc(n, alignment);
        #else
            void* p = nullptr;
            posix_memalign(&p, alignment, n);
            return p;
        #endif
    }

    void allocator::deallocate(void* p, size_t) {
        free(p);
    }
}
*/