//
// Created by chorm on 2020-09-20.
//

#include <lclib-c++/TypeTraits.hpp>

template<typename T> struct is_specialization_test{};

static_assert(lclib::type_traits::is_specialization_v<is_specialization_test,is_specialization_test<int>>);

