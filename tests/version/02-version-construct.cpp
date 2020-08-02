//
// Created by chorm on 2020-08-02.
//

#include <lclib-c++/Version.hpp>

constexpr lclib::version::Version value{1,0};
static_assert(value.getMajorVersion()==1,"Major constructed from one should have version field 1");
static_assert(value.getMinorVersion()==0,"Minor field incorrect");