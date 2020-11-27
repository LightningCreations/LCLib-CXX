
#include <lclib-c++/DynamicArray.hpp>
#include <exception>

int main(){
    lclib::array::DynamicArray<int> arr{};
    if(arr.size())
        throw std::logic_error{"A default constructed DynamicArray shall have size 0"};
    
    if(arr.begin()!=arr.end())
        throw std::logic_error{"For a default constructed DynamicArray a, a.begin() shall be equal to a.end()"};
    
}
