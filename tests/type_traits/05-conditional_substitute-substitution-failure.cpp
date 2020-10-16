//
// Created by chorm on 2020-09-20.
//

#include <lclib-c++/TypeTraits.hpp>
#include "no_member_type.hpp"

template<typename T,typename U> struct to_sfinae_fail{};

static_assert(no_member_type<lclib::type_traits::conditional_substitute<true,to_sfinae_fail,lclib::type_traits::always_false,void>>::value);
