#include "UniquePtr.h"
#include <cassert>
#include <utility>
#include <iostream>

int main() {
    UniquePtr<int> ptr(new int(5));
    UniquePtr<int> ptr2(new int(10));
    UniquePtr<int> empty;
    assert(*ptr == 5);
    assert(bool(ptr));
    assert(!empty);
    assert(ptr.get() == &*ptr);
    assert(!(ptr == ptr2));

    // Move constructor and assignment.
    UniquePtr<int> ptr3(std::move(ptr));
    assert(*ptr3 == 5 && !ptr);
    ptr2 = std::move(ptr3);
    assert(*ptr2 == 5);

    // Converting constructor.
    UniquePtr<const int> converted(std::move(ptr2));
    assert(*converted == 5);

    int* released = ptr3.release();
    assert(*released == 10 && !ptr3);
    delete released;

    ptr.reset(new int(20));
    assert(*ptr == 20);
    ptr.swap(empty);
    assert(!ptr && *empty == 20);
    empty.reset();
    assert(!empty);

    std::cout << "All assertions passed" << std::endl;

    return 0;
}
