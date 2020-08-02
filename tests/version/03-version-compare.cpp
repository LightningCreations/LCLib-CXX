//
// Created by chorm on 2020-08-02.
//

#include <lclib-c++/Version.hpp>
using namespace lclib::version;

constexpr Version v1{};
constexpr Version v2{1,0};
constexpr Version v3{1,1};
constexpr Version v4{2,0};

static_assert(v1 == v2, "Value constructed version, and Version{1,0} shall be equivalent");
static_assert(v2 < v3, "A version a is less than another version b with the same major component if the minor component of a is less than the minor component of b");
static_assert(v2 < v4, "A version a is less than another version b, if the major version of a is less than the major version of b");

#ifdef LCLIB_CXX_HAS_20_SPACESHIP
static_assert((v1 <=> v2) == 0,"When three-way-comparison is available, the three-way comparison operator of Version shall be consistent with all other comparisions");
static_assert((v2 <=> v3) < 0,"When three-way-comparison is available, the three-way comparison operator of Version shall be consistent with all other comparisions");
#endif