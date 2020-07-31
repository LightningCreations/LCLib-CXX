# Configuration Macros
In header `<lclib-c++/Config.hpp>`.

The header `<lclib-c++/Config.hpp>` defines several configuration macros which are used by 
 lclib-c++, and can be used to detect features available for use.

## Other headers

Including any lclib-c++ header may make available any of the symbols defined within this header,
 even if it was not explicitly included. Certain additional rules apply to any header that does so,
 in addition to the specifications described here.
 
## C++ Version Check


A program compiled on a C++ version prior to 17 (as determined by the value of the standard version macro __cplusplus, which must be at least 201703L)
 which includes this header, or any lclib-c++ header which makes any of the symbols defined
 in this header available, is ill-formed.
 Such an included header shall issue a diagnostic message which meaningfully indicates
 the error.

If such a header defines the macro LIBLC_CXX_CXX_MAYBE_BROKEN, 
 the above check does not need to be applied. 
 The implementation may test the C++ version in a different manner, 
 or (barring that) issue a non-failing diagnostic indicating that the check was bypassed 
 due to a non-compliant C++ compiler.

## Macro LIBLC_CXX_CXX_MAYBE_BROKEN

An implementation may define this macro to indicate that it detects a non-compliant C++ compiler 
 which may cause issues with checks required by this API. 
 If the macro is defined by the implementation, 
 then certain type trait checks may produce incorrect results, 
 template overload sets which do not participate in overload resolution may cause compile-time errors instead,
 and version checks may be disabled. 
 
## Macro LIBLC_CXX_HAS_SPAN

If the 
