
#include <lclib-c++/DynamicArray.hpp>

#include <type_traits>
#include <iterator>
namespace{
    // Note: unnamed namespace
    // Could not have been forward declared.
    struct NewType{};
}
using dynamic_array = lclib::array::DynamicArray<NewType>;

static_assert(std::is_same_v<dynamic_array::value_type,NewType>,"DynamicArray<T> shall have a member type `element_type` which is exactly T");



