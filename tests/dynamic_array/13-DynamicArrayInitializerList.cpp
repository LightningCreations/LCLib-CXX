#include <lclib-c++/DynamicArray.hpp>

#include <exception>
#include <initializer_list>
#include <cstddef>

int main(){
    auto init_list = {1,2,3,4,5,6,7,9,19};
    lclib::array::DynamicArray<int> init_list_test{1,2,3,4,5,6,7,9,19};
    if(init_list_test.size()!=9)
        throw std::logic_error{"Expected list of size 9"};
    for(std::size_t i = 0;i<9;i++)
        if(init_list.begin()[i]!=init_list_test[i])
            throw std::logic_error("element in initializer list does not match element in array");
}