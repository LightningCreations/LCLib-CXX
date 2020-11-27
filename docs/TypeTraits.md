# LCLib-C++ Type Traits

In header `<lclib-c++/TypeTraits.hpp>`

## Synopsis

```c++
#include <type_traits>

namespace lightningcreations::lclib{
    struct empty;
    template<bool b,template<typename...> class if_true,template<typename...> class if_false,typename... Ts> 
        struct conditional_substitute;
    template<bool b,template<typename...> class if_true,template<typename...> class if_false,typename... Ts>
        using conditional_substitute_t = typename conditional_substitute<b,if_true,if_false>::type;
    
    template<auto val> struct auto_constant : std::integral_constant<decltype(val),val>;
    
    template<typename...> using always_false = std::false_type;
    template<typename...> using always_true = std::true_type;
    
    template<typename T> struct type_identity;
    template<typename T> using type_identity_t = typename type_identity<T>::type;
    
    template<typename... Ts> struct has_common_type;
    template<typename... Ts> constexpr bool has_common_type_v = has_common_type<T>::value;

    template<typename T> struct is_char<T>;
    template<typename T> constexpr bool is_char_v = is_char<T>::value;
    
    template<typename T> struct is_cstring<T>;
    template<typename T> constexpr bool is_cstring_v = is_cstring<T>::value;
    
    template<typename T,typename... Args> struct is_list_constructible;
    template<typename T,typename... Args> constexpr bool is_list_constructible_v = is_list_constructible<T>::value;

    template<template<typename...> class Template,typename T> struct is_specialization;
    template<template<typename...> class Template,typename T> constexpr bool is_specialization_v = is_specialization<T>::value;
}
```

## Includes

The standard library header `<type_traits>` is transitively included by `<lclib-c++/TypeTraits.hpp>`

## Specialization Policy

Notwithstanding the template `is_char`,
 no templates in this library may be specialized by the user. 
Additionally, users may only specialize `is_char` and `is_cstring` for specific types, 
 see the respective documentation for information about that.

The behaviour of a program which specializes any templates in this header,
 except for `is_char`, is undefined. 
 

## Instantiation Policy

Templates in this library may be instantiated with incomplete types,
 the specific limitations of instantiations of this form are template specific. 

## Class Templates

### conditional_substitute

```c++
template<bool val,template<typename...> class if_true, template<typename...> class if_false,typename... Ts>
    struct conditional_substitute{
    typedef type = /*see below*/;
};

template<bool val,template<typename...> class if_true, template<typename...> class if_false,typename... Ts>
    using conditional_substitute_t = typename conditional_substitute<val,if_true,if_false,Ts...>::type;
```

If the bool template value is true, defines a member `type` to be the instantiation of
  if_true with Ts..., otherwise defines that member `type` to be the instantiation of if_false with Ts.... 
    
If the selected instantiation would be ill-formed,
 then there is no member `type` (conditional_substitute is SFINAE friendly).

The template which is not selected is not instantiated. 

If any type in Ts... is an incomplete type,
 then both of if_true, and if_false must allow incomplete types (reguardless of which template is selected),
 or the selected template must allow incomplete types and all such incomplete types shall 
 be either (possibly cv-qualified) void, or an array of an unknown bound. 
 If neither of these constraints are satisfied, the behavior of the instantiation is undefined. 


### auto_constant

```c++
template<auto val> struct auto_constant : integral_constant<decltype(val),val>{};
```

Represents a compile-time metaconstant with a deduced type. 

Note: It is not required that auto_constant be its own distinct class type inheriting from integral_constant. 
If a distinct or unified type is required, the creation of a distinct type inheriting from `auto_constant`,
 or the use of the integral_constant::type member can achieve these requirements. 


### has_common_type

```c++
template<typename... Ts> struct has_common_type;
```

If All types in Ts... share a mutual common type, then has_common_type inherits from std::true_type,
 otherwise inherits from std::false_type. 

If including `<lclib-c++/Config.hpp>` defines LCLIB_CXX_CXX_MAYBE_BROKEN, 
 then if Ts... is more than 4 types, `has_common_type` may inherit from `std::false_type` (even if the conditions below are satisfied).
 It is unspecified if this is the case, and the minimum number of types where this becomes the case. 

A single type T shares a mutual common type (as does an empty set of types, vacuously).

Two types T and U share a mutual common type if the following conditions are satisfied:
* The instantiation of both std::common_type_t<T,U> and std::common_type_t<U,T> are well formed
* Both instantiations name the same type
* Both T and U are implicitly convertible to the named type

Three types T, U, and V share a mutual common type if the following conditions are satisfied:
* The instantiation of `std::common_type_t<T,U,V>` is well formed
* Each pair of types in T, U, and V, share a mutual common type. 
* The instantiation of `std::common_type_t<std::common_type_t<T,U>,std::common_type_t<T,V>,std::common_type_t<U,V>>` 
 is well formed, and has a mutual common type with `std::common_type_t<T,U,V>`
* All of T, U, and V are implicitly convertible to `std::common_type_t<T,U,V>`

Four types S, T, U, V share a mutual common type if the following conditions are satisfied:
* The instantiation `std::common_type_t<S,T,U,V>` is well formed.
* Each triplet of types in S, T, U, and V (S,T,U; S,T,V; S,U,V; T,U,V) share a mutual common type. 
 Let these types be A, B, C, and D.
* The instantiation of `std::common_type_t<A,B,C,D>` is well-formed and shares a mutual common type with `std::common_type_t<S,T,U,V> 
* All of `S,T,U,V` are implicitly convertible to `std::common_type_t<S,T,U,V>`

Five or More types S, T, U, V, Rest... share a mutual common type
* S, T, U, and V share a mutual common type
* All types in Rest... share a mutual common type
* All types in Rest... share a mutual common type with S
* All types in Rest... share a mutual common type with T
* All types in Rest... share a mutual common type with U
* All types in Rest... share a mutual common type with V
*`std::common_type_t<S,T,U,V,Rest...>` is well-formed, and all types in `S,T,U,V,Rest...` can be implicitly converted to that type.

If any type in `Ts...` is an incomplete type, other than (possibly cv-qualified) void,
 or an array of an unknown bound, the behaviour is undefined. 
 
### struct empty

```c++
struct empty{};
```

A complete type which has neither a member `type` nor a member `value`. 

It is unspecified if empty can be default constructed, copy constructed, 
 move constructed, copy assigned, move assigned, or destroyed,
  or if any of these operations are trivial. 

`empty` shall be an empty type, that is, `std::is_empty<lclib::type_traits::empty>`
 shall inherit from `std::true_type`. 
 
### struct type_identity

```c++
template<typename T> struct type_identity{
    typename T type;
};
template<typename T> using type_identity_t = typename type_identity<T>::type;
```

An instantiation `type_identity<T>` with some type `T`, declares a member `type` which is an alias of `T`.

`T` may be an incomplete type, including an incomplete class type. 

### type always_true

```c++
template<typename... Ts> using always_true = std::true_type;
```

An alias for `std::true_type`, regardless of the template parameters.

Any type in `Ts...` may be an incomplete type, including an incomplete class type. 

### type always_false

```c++
template<typename... Ts> using always_false = std::false_type;
```

An alias for `std::false_type`, regardless of the template parameters.

Any type in `Ts...` may be an incomplete type, including an incomplete class type. 

### struct nonesuch

```c++
struct nonesuch{
    nonesuch(const nonesuch&)=delete;
    ~nonesuch()=delete;
    void operator=(const nonesuch&)=delete;
};
```

A type which is not *Default Constructible*, *Copy Constructible*, *Move Constructible*,
 *Copy Assignable*, *Move Assignable*, or *Destructible*. 

### type is_detected

```c++
template<template<typename...> typename Op,template... Args> struct is_detected;
```

If the instantiation of `Op` with `Args...` is well formed,
 then inherits from `std::true_type`, otherwise inherits from `std::false_type`. 

If Op does not permit any type in `Args...`, the behaviour is undefined. 

Notwithstanding the above, all of `Args...` and the instantiation `Op<Args...>` (if well-formed),
  may be incomplete types.

### type detected_or

```c++
template<template<typename...> typename Op,typename... Args> using detected_or = /*see below*/;
```

If the instantiation of `Op` with `Args...` is well-formed, defined as an alias of
 the template instantiation `Op<Args...>`, otherwise
 defined as an alias of `nonesuch`.
 
 If Op does not permit any type in `Args...`, the behaviour is undefined. 
 
 Notwithstanding the above, all of `Args...` and the instantiation `Op<Args...>` (if well-formed),
   may be incomplete types.
 
### type detected_t

```c++
template<typename Default,template<typename...> typename Op,typename... Args> using detected_t = /*see below*/;
```

If the instantiation of `Op` with `Args...` is well-formed, defined as an alias of 
 the template instantiation `Op<Args...>`, otherwise defined as an alias of `Default`.
 
 If Op does not permit any type in `Args...`, the behaviour is undefined. 
 
 Notwithstanding the above, all of `Default`, `Args...`, and the instantiation `Op<Args...>` (if well-formed),
  may be incomplete types.

### struct is_char

```c++
template<typename T> struct is_char;
template<typename T> constexpr bool is_char_v = is_char<T>::value;
```

`is_char<T>` inherits from `std::true_type` if and only if `T` is a character type,
 otherwise it inherits from `std::false_type`.
The primary template inherits from `std::true_type` for a type `T` which is
 (possibly cv-qualified) `char`, `wchar_t`, `char16_t` and `char32_t`, 
 or a cv-qualified version of a type for which `is_char` is specialized to inherit from `std::true_type`. 
 If the C++ Standard in Use is C++20, and the macro `__cpp_char8_t` is defined by the C++ Implementation,
 it shall also inherit from `std::true_type` for (possibly cv-qualified) `char8_t` (if the macro is defined,
 but the C++ Standard in Use is not C++20, its unspecified if `std::is_char<char8_t>` inherits from `std::true_type`)
 
`is_char<T>` may be specialized for a user-provided type T. 
 Any type used to specialize `is_char` must be *Trivial*, 
 and `std::is_same_v<std::decay_t<T>,T>` must be true.
 Additionally, `std::char_traits<T>` must be a partial or full specialization
  of `std::char_traits` which satisfies the requirements of *CharTraits*. 
The behaviour of a program that specializes this template in violation of these rules is undefined.

If `T` is an incomplete type, it shall either be (possibly cv-qualified) void, or an array of an unknown bound. Otherwise, the behaviour is undefined.

### struct is_cstring

```c++
template<typename T> struct is_cstring;
template<typename T> constexpr bool is_cstring_v = is_cstring<T>::value;
```

`is_cstring` inherits from `std::true_type` if `T` models a C-style string,
that is, `T` is either a pointer to or array of a character type.

`is_cstring` inherits from `std::true_type` if `std::decay_t<T>` is a pointer to a type `U`,
 where `is_char<U>` inherits from `std::true_type`, otherwise `is_cstring` inherits from `std::false_type`.
 

### struct is_specialization

```c++
template<template<typename...> typename Template,typename T> struct is_specialization;
template<template<typename...> typename Template,typename T> constexpr bool is_specialization_v = is_specialization<Template,T>::value;
```

`is_specialization<Template,T>` inherits from `std::true_type`,
 if `T` is `Template<Args...>` for some sequence of arguments `Args...`,
 otherwise it inherits from `std::false_type`.
 

 