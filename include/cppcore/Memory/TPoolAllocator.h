/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014-2021 Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------*/
#pragma once

#include <cppcore/CPPCoreCommon.h>

#include <string>

namespace CPPCore {

//-------------------------------------------------------------------------------------------------
///	@class		TPoolAllocator
///	@ingroup	CPPCore
///
///	@brief  This class implements a simple pool-based allocation scheme.
/// Initially you have to define its size. Each allocation will be done from this initially created
/// pool. You have to release all pooled instances after the usage.
/// This allocation scheme is fast and does no call any new-calls during the lifetime of the
/// allocator.
/// @code
/// struct foo { int payload[10]; };
/// TPoolAllocator<foo> allocator(10000);
/// foo *instance = allocator.alloc();
/// ...
/// allocator.release(instance);
/// @endcode
//-------------------------------------------------------------------------------------------------
template <class T>
class TPoolAllocator {
public:
    /// @brief  The default class constructor.
    TPoolAllocator();

    /// @brief  The class constructor with the pool size.
    /// @param  numItems    [in] The pool size.
    TPoolAllocator(size_t numItems);

    /// @brief  The class destructor.
    ~TPoolAllocator();

    /// @brief
    T *alloc();

    /// @brief  Will release all allocated items.
    void release();

    /// @brief  Will reserve the pool.
    /// @apram  size    [in] The pool size to reserve.
    void reserve(size_t size);

    /// @brief  Will clear the pool, memory will be deallocated.
    /// @note   All instances which are currently is use will get invalid. PLease use with care.
    void clear();

    /// @brief  Returns the capacity of items in the pool allocator.
    /// @return The capacity.
    size_t capacity() const;

    /// @brief  WIll return the reserved memory in bytes.
    /// @return The reserved memory in bytes.
    size_t reservedMem() const;

    /// @brief  Will return the free memory in the pool in bytes.
    /// @return The free memory in bytes.
    size_t freeMem() const;

    /// @brief  Will dump a statistic overview into the given string.
    /// @param  allocs  [inout] The string to hold the allocation statistic.
    void dumpAllocations(std::string &allocs);

    /// @brief  Will perform a resize for the pool.
    /// @param  growSize    [in] The soze to grow.
    void resize(size_t growSize);

    /// @brief  Will reset the allocator.
    void reset();
    
    /// No copying allowed
    CPPCORE_NONE_COPYING(TPoolAllocator)

private:
    struct Pool {
        size_t m_poolsize;
        T *m_pool;
        size_t m_currentIdx;
        Pool *m_next;

        Pool() :
                m_poolsize(0u),
                m_pool(nullptr),
                m_currentIdx(0u),
                m_next(nullptr) {
            // empty
        }

        Pool(size_t numItems, Pool *prev) :
                m_poolsize(numItems),
                m_pool(nullptr),
                m_currentIdx(0u),
                m_next(prev) {
            m_pool = new T[m_poolsize];
        }

        ~Pool() {
            delete[] m_pool;
            m_pool = nullptr;
        }

        CPPCORE_NONE_COPYING(Pool)
    };

    Pool *getFreePool() {
        Pool *current = m_freeList;
        if (nullptr != m_freeList) {
            m_freeList = m_freeList->m_next;
        }
        return current;
    }

    Pool *m_first;
    Pool *m_current;
    Pool *m_freeList;
    size_t m_capacity;
};

template <class T>
inline TPoolAllocator<T>::TPoolAllocator() :
        m_first(nullptr),
        m_current(nullptr),
        m_freeList(nullptr),
        m_capacity(0L) {
    // empty
}

template <class T>
inline TPoolAllocator<T>::TPoolAllocator(size_t numItems) :
        m_first(nullptr),
        m_current(nullptr),
        m_freeList(nullptr),
        m_capacity(0L) {
    m_first = new Pool(numItems, nullptr);
    m_capacity += numItems;
    m_current = m_first;
}

template <class T>
inline TPoolAllocator<T>::~TPoolAllocator() {
    clear();
}

template <class T>
inline T *TPoolAllocator<T>::alloc() {
    if (nullptr == m_current) {
        return nullptr;
    }

    if (m_current->m_currentIdx == m_current->m_poolsize) {
        resize(m_current->m_poolsize);
    }

    T *ptr = &m_current->m_pool[m_current->m_currentIdx];
    m_current->m_currentIdx++;

    return ptr;
}

template <class T>
inline void TPoolAllocator<T>::release() {
    if (nullptr == m_current) {
        return;
    }

    Pool *current = m_first;
    while (nullptr != current) {
        current->m_currentIdx = 0;
        current = current->m_next;
    }
    m_freeList = m_first->m_next;
    m_current = m_first;
}

template <class T>
inline void TPoolAllocator<T>::reserve(size_t size) {
    clear();

    m_first = new Pool(size, nullptr);
    m_current = m_first;

    m_current->m_pool = new T[size];
    m_current->m_poolsize = size;

    m_capacity = size;
}

template <class T>
inline void TPoolAllocator<T>::clear() {
    if (nullptr == m_current) {
        return;
    }

    Pool *next = m_first;
    while (nullptr != next) {
        Pool *current = next;
        next = current->m_next;
        delete current;
    }
    m_current = nullptr;
    m_freeList = nullptr;
}

template <class T>
inline size_t TPoolAllocator<T>::capacity() const {
    return m_capacity;
}

template <class T>
inline size_t TPoolAllocator<T>::reservedMem() const {
    return m_capacity * sizeof(T);
}

template <class T>
inline size_t TPoolAllocator<T>::freeMem() const {
    if (nullptr == m_current) {
        return 0L;
    }

    return (m_current->m_poolsize - m_current->m_currentIdx);
}

template <class T>
inline void TPoolAllocator<T>::dumpAllocations(std::string &allocs) {
    allocs.clear();
    allocs += "Number allocations = ";
    allocs += std::to_string(m_current->m_currentIdx);
    allocs += "\n";
}

template <class T>
inline void TPoolAllocator<T>::resize(size_t growSize) {
    if (nullptr != m_current) {
        if (growSize < m_current->m_poolsize) {
            return;
        }
    }

    if (nullptr == m_first) {
        m_first = new Pool(growSize, nullptr);
        m_current = m_first;
        m_capacity += m_current->m_poolsize;
    } else {
        Pool *pool = getFreePool();
        if (nullptr == pool) {
            pool = new Pool(growSize, nullptr);
            m_capacity += growSize;
        }
        m_current->m_next = pool;
        m_current = m_current->m_next;
    }
}

template<class T>
void TPoolAllocator<T>::reset() {
    m_current = m_first;
}

} // Namespace CPPCore
