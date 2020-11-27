
#include <lclib-c++/DynamicArray.hpp>

#include <type_traits>
#include <memory>
namespace{
    // Note: unnamed namespace
    // Could not have been forward declared.
    struct NewType{};
}
using dynamic_array = lclib::array::DynamicArray<NewType>;

static_assert(std::is_same_v<dynamic_array::pointer,typename std::allocator_traits<dynamic_array::allocator_type>::pointer>,"DynamicArray<T,Alloc> shall have a member type `pointer` which is equivalent to typename std::allocator_traits<Alloc>::pointer");



