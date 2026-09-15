#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <utility>

// Your implementation here
template <typename T>
class UniquePtr {
    public: 
        UniquePtr(T* p = nullptr) : ptr(p)  // ctor
        {
        }

        ~UniquePtr() {  // dtor
            if (ptr != nullptr) {
                delete ptr;
            }
        }
        
        UniquePtr(UniquePtr&& other) : ptr(other.ptr)  // Move Constructor
        {
            other.ptr = nullptr;
        }
        
        UniquePtr& operator=(UniquePtr&& other) // Move assignment
        {
            std::swap(ptr, other.ptr);
            return *this;
        }

        // Copy not allowed
        UniquePtr(const UniquePtr& other) = delete; // Copy Constructor
        UniquePtr& operator=(const UniquePtr&) = delete;  // Copy assignment

        template <typename U>
        UniquePtr(UniquePtr<U>&& other) : ptr(other.release())  // Converting constructor
        {
        }

        T& operator*() const    // Dereference operator
        {
            return *ptr;
        }

        T* operator->() const   // Arrow operator
        {
            return ptr;
        }

        T* get() const  // get(), the same as the arrow operator
        {
            return ptr;
        }

        bool operator==(const UniquePtr<T>& other) const // Comparison operator
        {
            return other.ptr == ptr;
        }

        T* release()  // Release operator
        {
            T* temp = ptr;
            ptr = nullptr;
            return temp;
        }

        void reset(T* newPtr = nullptr) // Reset operator
        {
            T* temp = ptr;
            ptr = newPtr;
            delete temp;
        }

        void swap(UniquePtr<T>& other)  // Swap operator
        {
            T* temp = other.ptr;
            other.ptr = ptr;
            ptr = temp;
        }

        operator bool() const   // Bool operator -> returns true if ptr is non-empty
        {
            return ptr != nullptr;
        }

    private:
        T* ptr;

};
#endif
