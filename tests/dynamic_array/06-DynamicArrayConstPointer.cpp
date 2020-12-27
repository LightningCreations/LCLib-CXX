
#include <lclib-c++/DynamicArray.hpp>

#include <type_traits>
#include <memory>
namespace{
    // Note: unnamed namespace
    // Could not have been forward declared.
    struct NewType{};
}
using dynamic_array = lclib::array::DynamicArray<NewType>;

static_assert(
    std::is_same_v<
        dynamic_array::const_pointer,std::allocator_traits<dynamic_array::allocator_type>::const_pointer
    >,
    "DynamicArray<T> shall have a member type `const_pointer`, which is equivalent to std::allocator_traits<dynamic_array::allocator_type>::const_pointer"
);


