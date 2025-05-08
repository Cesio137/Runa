#pragma once

#include <EASTL/allocator_malloc.h>
#include <stdlib.h>
#include <malloc.h>

void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* name, int flags, unsigned debugFlags, const char* file, int line);
/*
void operator delete[](void* p, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p, size_t alignment, size_t alignmentOffset, const char* name, int flags, unsigned debugFlags, const char* file, int line);
*/

/*
namespace eastl {
    void allocator::set_name(const char* pName);
    void* allocator::allocate(size_t n, int flags);
    void* allocator::allocate(size_t n, size_t alignment, size_t offset, int flags);
    void allocator::deallocate(void* p, size_t);
}
*/
