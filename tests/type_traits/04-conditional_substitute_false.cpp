//
// Created by chorm on 2020-09-20.
//

#include <lclib-c++/TypeTraits.hpp>

static_assert(!lclib::type_traits::conditional_substitute<false,lclib::type_traits::always_true,lclib::type_traits::always_false,void>
        ::type::value);

