#if __cplusplus>=202002L && __cpp_nontype_template_args > 201911L

#include <lclib-c++/Version.hpp>

template<Version v> struct structural{};

template struct structural<Version{1,0}>;

#endif