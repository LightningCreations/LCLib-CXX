//
// Created by chorm on 2020-09-20.
//

#ifndef LCLIB_NO_MEMBER_TYPE_HPP
#define LCLIB_NO_MEMBER_TYPE_HPP

#include <type_traits>

namespace _detail{
    template<typename T> auto no_member_type_helper(typename T::type*) -> std::false_type;
    template<typename T> auto no_member_type_helper(...) -> std::true_type;

    template<typename T> auto no_member_value_helper(decltype(T::value)*) -> std::false_type;
    template<typename T> auto no_member_value_helper(...) -> std::false_type;
}

template<typename T> struct no_member_type : decltype(_detail::no_member_type_helper<T>(nullptr)){};

template<typename T> struct no_member_value : decltype(_detail::no_member_value_helper<T>(nullptr)){};

#endif //LCLIB_NO_MEMBER_TYPE_HPP
