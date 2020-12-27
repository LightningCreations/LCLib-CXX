#include <lclib-c++/DynamicArray.hpp>

#include <type_traits>
#include <iterator>

namespace{
    struct NewType{};
}

using dynamic_array = lclib::array::DynamicArray<NewType>;


static_assert(std::is_base_of_v<std::random_access_iterator_tag,typename std::iterator_traits<dynamic_array::const_iterator>::iterator_category>,"dynamic_array shall have a member type const_iterator, which satisfies LegacyRandomAccessIterator");
