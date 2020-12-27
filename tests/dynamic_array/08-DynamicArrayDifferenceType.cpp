
#include <lclib-c++/DynamicArray.hpp>

#include <type_traits>
#include <iterator>
namespace{
    // Note: unnamed namespace
    // Could not have been forward declared.
    struct NewType{};
}
using dynamic_array = lclib::array::DynamicArray<NewType>;

static_assert(
    std::is_same_v<
        dynamic_array::difference_type,std::iterator_traits<dynamic_array::iterator>::difference_type
    >,
    "DynamicArray<T> shall have a member type `const_pointer`, which is equivalent to std::allocator_traits<dynamic_array::allocator_type>::const_pointer"
);


