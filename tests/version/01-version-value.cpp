//
// Created by chorm on 2020-07-30.
//

#include <lclib-c++/Version.hpp>

using namespace lclib::version;

constexpr Version value{};
static_assert(value.getMajorVersion()==1,"Value constructor for Version shall set major and minor fields to 0");
static_assert(value.getMinorVersion()==0,"Value constructor for Version shall set major and minor fields to 0");