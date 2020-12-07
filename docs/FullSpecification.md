# LCS Draft - Lclib-c++

Draft Date - 2020/11/29

Drafted By Connor Horman

Copyright (C) 2020 Lightning Creations and Connor Horman

This document is released under the terms of the GNU Free Documentation License, with no front-cover texts, no back-cover texts, and no invariant sections. 

## §1 Introduction [intro]

1. This document describes a series of extensions to ISO 14882 (The C++ Standard), for version 2017, 2020, or any later version published after this document. 
2. If an implementation of the C++ Standard implements this specification, it shall make available the constructs of this specification to any C++ program that includes a header defined by this specification. 
3. Unless otherwise specified, each section of this document is normative. A clause is not normative if it is listed in italics (when viewed in plain, unformatted text, between underscore characters), starts with the word "Note", and ends with "End Note". 
4. A section of this document that starts with a note that states "This section is non-normative" is not normative. 

### §1.1 Normative References [intro.ref]

1. ISO 14882:2017: Programming Languages, C++ (ISO Joint Technical Committee 1, Standards Committee 22, Working Group 21). (C++17)
2. ISO 14882:2020: Programming Languages, C++ (ISO Joint Technical Committee 1, Standards Committee 22, Working Group 21). (C++20)
3. ISO 9899:2017: Programming Languages, C (ISO Joint Technical Committee 1, Standards Committee 22, Working Group 14) (C18)
4. Lightning Creations Specification, Publication 4 - Binary IO Format (Lightning Creations Specification Project, Connor Horman). (LCS4)


### §1.2 Terms and Definitions [intro.def]

1. The term "C++ Standard" refers to any published version of ISO 14882 by ISO Joint Technical Committe 1, Standards Committee 22, Working Group 21, or any draft version thereof.
2. The term "C++" refers to the program language defined by the C++ Standard.
3. The term "C++ Standard in Use" refers to a particular version of the C++ Standard, including a draft version, which has been published in or since the year 2017. 
4. _Note 1 - Which version of the C++ Standard is in use is implementation-defined - End Note_
5. The term "Program" refers to a Program as defined by the C++ Standard in Use, which makes use of the constructs defined by this specification, and not by the C++ Standard in Use.
6. _Note 2 - Program excludes the implementation - End Note_
7. The term "Implementation" refers to an implementation of the C++ Standard in Use, as well as a collection of headers, binary artifacts, and optionally accompanying documentation, which provides the constructs defined by this specification.
8. This specification, refers to this document, either as a Draft for the LCS Project, or as a publication. 
9. The term "shall" refers to an absolute requirement of this specification on either the implementation or on a program. 
10. The term "shall not" is the inverse of "shall" and refers to an absolute prohibition of this specification on either the implementation or on a program. 
11. A well-formed program, is a program that is well-formed program under the C++ Standard in Use and does not violate any requirements or prohibitions of this specification. 
12. An ill-formed program is a program that is not a well-formed program.

### §1.3 Compliance [intro.compliance]

1. An implementation complies with this specification if it complies with the C++ Standard in use, implements the extensions to that C++ Standard in use defined by this document in a way not inconsistent with §1.3.1, and that issues diagnostics for any ill-formed program for which a diagnostic is required. A compliant implementation may additionally issue diagnostics for ill-formed programs for which a diagnostic is not required.  
2. Unless otherwise stated, any clause that imposes a requirement on the program, or that makes a program ill-formed requires a diagnostic. If a program violates multiple clauses of this specification, where at least one such clause requires a diagnostic, a diagnostic is required to be issued.
3. _Note 1 - The above applies even if some of the clauses violated do not require a diagnostic - End Note_
4. A well-formed program is correct if, during evaluation of the program according to §1.3.1, it does not evaluate any unsupported construct that is conditionally supported, or a construct without defined behaviour, or violate a semantic requirement of this specification or of the C++ Standard in Use. Such a program shall be evaluated by the implementation subject to §1.3.1 and the section `[intro.abstract]` of the C++ Standard in Use. 
5. A program that uses a syntactic or structural *conditionally-supported* construct that is unsupported is ill-formed.
6. An implementation shall provide, and/or include, documentation which at the minimum describes all *implementation-defined* behaviour, as well as any *conditionally-supported* construct that is unsupported.

#### §1.3.1 Evaluation [intro.abstract]

1. The semantic descriptions in this document define a parameterized, non-deterministic, abstract machine, that extends the Abstract Machine defined by the C++ Standard in Use. An implementation need not implement or emulate the abstract machine, rather an implementation only need emulate the *observable behaviour* of the abstract machine, defined below. 

2. Certain constructs of this specification, or of the C++ Standard in Use, are described as *implementation-defined*. These are parameters of the Abstract machine. Implementations shall document the particular values of these parameters.
3. _Note 1 - This specification typically constrains such_ implementation-defined _behaviour. Any behaviour that is described as_ implementation-defined _by the C++ Standard in Use may be further constrained by this specification - End Note_
4. Certain constructs of this specification, or of the C++ Standard in Use, are described as *unspecified*. These are non-deterministic aspects of the abstract machine.
5. _Note 2 - This specification typically constrains such_ unspecified _behaviour. Any behaviour which is described as_  unspecified _by the C++ Standard in Use may be further constrained by this specification - End Note_
6. Certain other constructs of this specification, or of the C++ Standard in Use, are described as *undefined*.
7. _Note 3 - This specification imposes no limitations on any such behaviour - End Note_
8. During evaluation of a correct program, an implementation shall ensure that the *observable behaviour* of the program, matches the *observable behaviour* of one possible result of the current parameterized abstract machine. 
9. During evaluation of a well-formed program that has undefined behaviour, or of an ill-formed program, no limitations are imposed on the result of that evaluation.
10. _Note 4 - The above includes the observable behaviour of programs before the first occurance of an undefined operation - End Note_
11. The observable behaviour of a program shall include the following:
    * Any operation that is described as having observable behaviour by the C++ Standard in Use
    * Any operation that is explicited denoted by this specification as having observable behaviour

12. _Note 5 - The requirements of this section do not prevent an implementation from enforcing stricter requirements on the evaluation of programs. - End Note_

#### §1.3.2 Constrained Operations [intro.constrained]

1. This document defines a number of operations that are prohibited by this specification to enhance the freedom of implementations in implementing the provisions of this specification. No diagnostic is required for a violation of any clause of this section. 
2. A program shall not contain a call to any operator function defined by this specification, unless the call was an implicit call via the overloaded operator or the operator is one of the following
    * An assignment operator
    * `operator->`
    * An allocation or deallocation operator. 
    * A conversion function. 
3. _Note 1 - The above includes calls such as `a.operator+(b)` or `operator+(a,b)`, when the operator is defined, but excludes the implicit call if the function is selected for `a+b`. For the function call operator, this applies to `a.operator()(args...)`, but not `a(args...)`. This is intended to allow flexibility in how these operators are defined, and even if they are defined, for example, in the case of the standard comparison operators - End Note_
4. _Note 2 - The above does not include calls to a user-defined operator functions, even if they take arguments of types defined by this specification - End Note_
5. A program shall not contain call to a function defined by this specification with the following unqualified names, unless the name of the function was resolved by argument-dependant lookup:
   * begin
   * end
   * cbegin
   * cend
   * rbegin
   * rend
   * crbegin
   * crend
   * get, if the function is a template, that has a non-deduced non-type template parameter.
   * swap
   * data
   * size
6. _Note 3 - This allows the implementation to define the functions in a way that is only accessible via ADL name resolution, and that cannot be found in any other way - End Note_ 
7. _Note 4 - This only applies to non-member functions. Member functions with those names may be called directly - End Note_
8. A program shall not use the name of any non-member function defined by this specification, except by directly calling that name. 
9. _Note 5 - Uses prohibited by the above clause include conversion to a function pointer, passing as callable to another function, or calling the name enclosed in parenthesis. - End Note_
10. A program shall not define any identifiers within the reserved namespace `lclib`, or any namespace contained within. 
11. A program shall not directly name any identifier within the reserved namespace, or any namespace contained within, nor a function or data member of any class declared in such a namespace, that starts with a single underscore. 
12. A program shall not `#define` or `#undef` any name declared by any header of this specification, a name declared by any standard library header, or an identifier which is a reserved identifier, the name of a keyword, a contextual keyword, or the name of a standard attribute macro. Notwithstanding the previous statement, a program may define the attribute names `likely` and `unlikely` as function-like macros. 
13. Including the any header defined by this specification may make any symbols defined in any other such header, or in any header defined by the C++ Standard in use, available. 
14. Excluding templates that mention otherwise, and templates defined by the header `<lclib-c++/TypeTraits.hpp>`, a program shall not instantiate any template defined by this library with an incomplete type. 
15. A program shall not provide explicit template arguments for any deduced template argument of a function template. If all template arguments are deduced, a program shall not call the function as a template. 
16. Excluding templates that mention otherwise, and templates defined by the header `<lclib-c++/TypeTraits.hpp>`, a program may provide partial and full specializations for templates defined by this library. Each full specialization, and each instantiation of each partial specialization of such templates must satify all of the following requirements:
    - At least one type template parameter shall a *user-provided type*, which is one of the following
        * A class type or an instantiation of a class template, except a class type or class template defined by this specification or by the C++ Standard in use
        * The instantiation of a class template, where the template permits a full specialization on the template arguments provided to that instantiation to be defined by the program
        * _Note 6 - This is permitted, even the instantiation does not select a partial or full specialization defined by the program. - End Note_
        * A cv-qualified version of a *user-provided type*.
        * An lvalue or rvalue reference type to a *user-provided type*.
        * A pointer to a *user-provided type*.
        * An array, including an array of unknown bound, of a *user-provided type*.
    - All specialized template parameters shall be valid for the primary template. 
    - The provided specialization meets the requirements of the type, or, if defined, the requirements on specializations instead. 
17. A program that provides partial or full specializations for types defined by the C++ Standard in Use must have at least one type template parameter that is a *user-provided type*. 
18. _Note 7 - This implies its not valid to specialize a Standard Library template on a type defined by this specification - End Note_


### §1.4 Concurrency Operations in this library [intro.concurrency]

1. Unless otherwise indicated, functions declared in this library act as though by only accessing objects which are accessible from it's arguments, including the implicit parameter, as well as any `const` complete objects that have no `mutable` subobjects. 

2. Functions declared in this library act as though by only writing to objects accessible from it's non-const reference and pointer arguments, including the implicit parameter. 

3. Functions declared in this library may assume any object accessible through an rvalue reference argument is not accessible through any other pointer or reference parameter, including the implicit parameter. 

4. _Note 1 - If an implementation so chooses to make that assumption, the result of violating that assumption is undefined behaviour - End Note_

## §2 Configuration Macros and Version Info [config]

1. Header `<lclib-c++/Config.hpp>` Synopsis
```c++

#define LCLIB_CXX_STANDARD_CXX20

#include <version>
#define LCLIB_CXX20_SPAN
#define LCLIB_CXX_VERSION_INFO
#define LCLIB_CXX_HAS_20_SPACESHIP
#define LCLIB_CXX_CXX_MAYBE_BROKEN


#define LCLIB_CXX_ORDER_LITTLE /*unspecified*/
#define LCLIB_CXX_ORDER_BIG /*unspecified*/
#define LCLIB_CXX_BYTE_ORDER /*implementation-defined*/

#define LCLIB_CXX_UNREACHABLE() /*unspecified*/
#define LCLIB_CXX_ASSERT(expr,message) /*see below*/

#define LCLIB_CXX_VERSION 202008L
```

2. In addition to macros defined above, the implementation may define any other *unspecified* macros which start with the name `LCLIB_CXX_`. 

3. A program shall not define any macro that starts with `LCLIB_CXX_`, except that the program may define the macro `LCLIB_CXX_DEBUG`. 

### §2.1 C++ Standard in Use

1. 
```c++
#define LCLIB_CXX_STANDARD_CXX20  
#define LCLIB_CXX_CXX_MAYBE_BROKEN

#define LCLIB_CXX_VERSION_INFO
#define LCLIB_CXX_HAS_20_SPACESHIP
#define LCLIB_CXX20_SPAN
```

2. If the C++ Standard in use is C++20, then including the header `<lclib-c++/Config.hpp>` defines the macro LCLIB_CXX_STANDARD_CXX20. 

3. Including the header `<lclib-c++/Config.hpp>` may define the macro LCLIB_CXX_CXX_MAYBE_BROKEN. 

4. If the C++ Standard in use is a version of the C++ Standard published prior to 2017, a program that includes any header in this library is ill-formed. No diagnostic is required if including the header `<lclib-c++/Config.hpp>` defines the macro `LCLIB_CXX_CXX_MAYBE_BROKEN`. 

5. If the C++ Standard in use is C++20, and the header `<version>` can be included, then including `<lclib-c++/Config.hpp>` defines the macro `LCLIB_CXX_VERSION_INFO`, and makes all symbols defined by the header `<version>` available to the program.

6. If the C++ Standard in use is C++20, and the header `<compare>` can be included, then including `<lclib-c++/Config.hpp>` defines the macro `LCLIB_CXX_HAS_20_SPACESHIP`.

7. If the C++ Standard in use is C++20, and the header `<span>` can be included, then including `<lclib-c++/Config.hpp>` defines the macro `LCLIB_CXX20_SPAN`. 

### §2.2 Byte Order Info [config.order]

```c++
#define LCLIB_CXX_ORDER_LITTLE /*unspecified*/
#define LCLIB_CXX_ORDER_BIG /*unspecified*/
#define LCLIB_CXX_BYTE_ORDER /*implementation-defined*/
```

1. Including the header `<lclib-c++/Config.hpp>` shall define the macro `LCLIB_CXX_ORDER_LITTLE` to an unspecified constant expression of an integer type.

2. Including the header `<lclib-c++/Config.hpp>` shall define the macro `LCLIB_CXX_ORDER_BIG` to an unspecified constant expression of an integer type.

3. Including the header `<lclib-c++/Config.hpp>` shall define the macro `LCLIB_CXX_BYTE_ORDER` to an implementation-defined constant expression of an integer type, that compares equal to one of `LCLIB_CXX_ORDER_LITTLE` or `LCLIB_CXX_ORDER_BIG`. If it compares equal to `LCLIB_CXX_ORDER_LITTLE`, then integer types are stored in memory according to the little-endian byte order. Otherwise, integer types are stored in memory according to the big-endian byte order. 

### §2.3 Diagnostics and Reachability hints [config.diag]

```c++
#define LCLIB_CXX_UNREACHABLE() /*unspecified*/
#define LCLIB_CXX_ASSERT(expr,message) /*see below*/
```

1. Including the header `<lclib-c++/Config.hpp>` defines the function-like macro `LCLIB_CXX_UNREACHABLE()` expands to an unspecified prvalue expression of type `void`. The behaviour of a program that evaluates `LCLIB_CXX_UNREACHABLE()` is undefined.
2. Including the header `<lclib-c++/Config.hpp>` defines the function-like macro `LCLIB_CXX_ASSERT(expr,message)` which expands to a statement which has the following effects:
    * If expr, *contextually-converted* to a prvalue of type `bool`, is `true`, the macro has no effect.
    * Otherwise (expr is `false`), if the macro LCLIB_CXX_DEBUG is defined by the program or the implementation. Evaluating the macro throws an exception that matches a handler of type `std::logic_error`, with an unspecified `what()` message which includes the provided message (which must be a string literal), as well as the file name and line that expands the macro. It is unspecified whether the implementation defines the macro `LCLIB_CXX_DEBUG`, except that the implementation shall not define that macro if `NDEBUG` is defined.
    * Otherwise (expr is `false` and `LCLIB_CXX_DEBUG` is not defined), the behaviour is undefined. 
    * If the evaluation of `expr`, including the contextual conversion to `bool`, has any *observable behaviour*, the behaviour is undefined.
    * If a program includes any headers from this specification, it shall not define `LCLIB_CXX_DEBUG` after including any header, contain an intervening `#undef` of `LCLIB_CXX_DEBUG` between two headers. No diagnostic is required
    * If a program includes any headers from this specification or the C++ Standard Library, it shall not define `NDEBUG` after including any header, contain an intervening `#undef` of `NDEBUG` between two headers. No diagnostic is required.

### §2.4 Library Version

```C++
#define LCLIB_CXX_VERSION 202008L
```

1. Including the header `<lclib-c++/Config.hpp>`  defines the macro `LCLIB_CXX_VERSION` to the current version of the LCLib-C++ Specification, `202080L`.

## §3 Binary Version encoding [version]

1. Header `<lclib-c++/Version.hpp>` synopsis
```c++
namespace lclib::version{
    struct Version;
    auto operator<=>(const Version& v1,const Version& v2)noexcept;
    bool operator==(const Version& v1,const Version& v2)noexcept;
    bool operator!=(const Version& v1,const Version& v2)noexcept;
    bool operator<(const Version& v1,const Version& v2)noexcept;
    bool operator>(const Version& v1,const Version& v2)noexcept;
    bool operator<=(const Version& v1,const Version& v2)noexcept;
    bool operator>=(const Version& v1,const Version& v2)noexcept;
    lclib::io::DataOutputStream& operator<<(lclib::io::DataOutputStream& out,const Version& v);
    lclib::io::DataInputStream& operator>>(lclib::io::DataInputStream& in,Version& v);
}

namespace std{
    template<> struct hash<lclib::version::Version>{}
}

```


### §3.1 class Version [version.version]

1. Class `lclib::version::Version` synopsis
```c++
struct Version{
    Version()=default;
    constexpr Version(const Version&)=default
    constexpr Version(Version&&)=default;
    constexpr Version(std::uint16_t M,std::uint8_t m);
    constexpr Version& operator=(const Version&)=default;
    constexpr Version& operator=(Version&&)=default;

    constexpr std::uint16_t getMajor()const noexcept;
    constexpr std::uint8_t getMinor()const noexcept;

};
```

2. The class `lclib::version::Version` shall be a *Trivial*, *Standard Layout*, *structural*, *Literal Type* that is suitable for storing encoded binary versions with a major component between 1 and 256 inclusive, and a minor component between 0 and 255. 

3. The class `lclib::version::Version` satisfies *LessThanComparable* and *EqualityComparable*. The equivalence relation described by *LessThanComparable* is equivalent to comparing the versions for equality. 

#### §3.1.1 Class Constructors [version.ctor]

`Version()noexcept=default;`

1. default or value-constructs a version. This default constructor is trivial. 

2. Postconditions:
    - `Version{}==Version{}`
    - `Version{}.getMajor()==1`
    - `Version{}.getMinor()==0`

3. _Note 1 - Version may be value-initialized in a core constant expression - End Note_

4. _Note 2 - A default-initialized version has an indeterminate value - End Note_

`constexpr Version(const Version& v)noexcept=default;`

5. Copy-constructs a version. This constructor is trivial

6. Postconditions:
    - `Version{v}==v`, if `v` is an lvalue or const rvalue of type `Version`

`constexpr Version(Version&& v)noexcept=default;`

7. Move constructs a version. This constructor is trivial. 

8. Postconditions:
    - `Version{rv}==rv`, if `rv is a non-const rvalue.

`constexpr Version(std::uint16_t M,std::uint8_t m);`

9. Constructs the version `M.m`, where `M` is the major component, and `m` is the minor component. 
10. Postconditions:
    - `Version{M,m}.getMajor()==M` if `M` is an expression of type `std::uint16_t` such that `0<M<=256`, and `m` is an expression of type `std::uint8_t`. 
    - `Version{M,m}.getMinor()==m` if `M` is an expression of type `std::uint16_t` such that `0<M<=256`, and `m` is an expression of type `std::uint8_t`. 
11. Exceptions:
    - If `M` is equal to 0, or greater than 256, throws an exception that matches a handler of type `std::domain_error`. 

#### §3.1.2 Assignment operators [version.assign]

`constexpr Version& operator=(const Version& rhs)noexcept=default;`

1. Copy-assigns this version from rhs. This copy-assignment operator is trivial.

2. Postconditions:
    - After `v=cv`, `v==cv`, where `v` is an lvalue of type `Version`, and `cv` is a (potentially const) lvalue or a const rvalue of type `Version`.

`constexpr Version& operator=(Version&& rhs) noexcept=default;`

3. Move-assigns this version from rhs. This move-assignment operator is trivial.

4. Postconditions:
    - After `v=rv`, `v==rv`, where `v` is an lvalue of type `Version`, and `rv` is an rvalue of type version.


#### §3.1.3 Accessors [version.access]

`constexpr std::uint16_t getMajor()const noexcept;`

1. Returns the major version component of this verison

2. Postconditions:
    - `v.getMajor()>0`, where `v` is an expression of type `Version`.
    - `v.getMajor()<=256`, where `v` is an expression of type `Version`.

### §3.2 Comparison Operators [version.comp]

`constexpr std::strong_ordering operator<=>(const Version& v1,const Version& v2)noexcept;`

1. Compares two versions according to their major and minor components. 

2. Guaranteed to be defined only if including the header `<lclib-c++/Config.hpp>` defines the macro `LCLIB_CXX_HAS_20_SPACESHIP`. Otherwise, not defined.

3. Postconditions:
    - `(v1<=>v2)<0` if `v1.getMajor()<v2.getMajor()`.
    - `(v1<=>v2)<0` if `v1.getMinor()<v2.getMinor()` and `v1.getMajor()==v2.getMajor()`. 

`constexpr bool operator==(const Version& v1,const Version& v2)noexcept;`

4. Compares two versions for equality. 

5. Postconditions:
    - `(v1==v2)` iff `v1.getMajor()==v2.getMajor()&&v1.getMinor()==v2.getMinor()`
    - `(v1==v2)` iff `(v1<=>v2)==0`. 
    - `v==v`
    - `v1==v2` iff `v2==v1`
    - if `v1==v2` and `v2==v3` then `v1==v3`

`constexpr bool operator<(const Version& v1,const Version& v2)noexcept;`

6. Orders two versions, according to their major and minor components.

7. Postconditions:
    - `v1<v2` if `v1.getMajor()<v2.getMajor()`
    - `v1<v2` if `v1.getMinor()<v2.getMinor()` and `v1.getMajor()==v2.getMajor()`
    - `v1<v2` iff `(v1 <=> v2) < 0`
    - Exactly one of `v1<v2`, `v2<v1`, `v1==v2` is true

`constexpr bool operator<(const Version& v1,const Version& v2)noexcept;`

8. Orders two versions, according to their major and minor components.

9. Postconditions:
    - `v1>v2` iff `v2<v1`
    - `v1>v2` iff `(v1<=>v2) > 0`

`constexpr bool operator<=(const Version& v1,const Version& v2)noexcept;`

10. Orders two versions, accordng to their major and minor components.

11. Postconditions:
    - `v1<=v2` if `v1<v2`
    - `v1<=v2` if `v1==v2`
    - `v1<=v2` iff `(v1<=>v2)<=0`
    - `v1<=v2` and `v2<=v1` iff `v1==v2`

`constexpr bool operator>=(const Version& v1,const Version& v2)noexcept;`

12. Orders two versions, according to their major and minor components.

13. Postconditions:
    - `v1>=v2` if `v1>v2`
    - `v1>=v2` if `v1==v2`
    - `v1>=v2` iff `(v2<=>v2)>=0`
    - `v1>=v2` and `v2>=v1` iff `v1==v2`

### §3.3 Binary Stream Operators [version.stream]

`lclib::io::DataOutputStream& operator<<(lclib::io::DataOutputStream& out,const Version& v);`

1. Writes the binary data of `v` to out, according to the LCS4 type `version` (LCS4 §3.5.3).

2. Returns: 
    - out

3. Forward Reference `[io]`. 

4. Exceptions:
     - Throws any exception resulting from the write. 


`lclib::io::DataInputStream& operator>>(lclib::io::DataInputStream& in,Version& v);`

5. Reads the binary data of `v` from `in`, according to the LCS4 type `version` (LCS4 §3.5.3).

6. Returns:
    - in

7. Exceptions:
    - Throws any exceptions resulting from the read. If an exception is thrown, v is left in a valid, but unspecified, state. 

### §3.4 `std::hash<Version>` [version.hash]

1. The class template, `std::hash` shall be specialized by the implementation, for the class `lclib::version::Version`. This specialization shall be enabled and satisfy *Hash*. 

`std::size_t operator()(Version v)noexcept`
2. Computes an unspecified hash for the version. 

3. Postconditions:
    - `std::hash<Version>{}(v1)==std::hash<Version>{}(v2)` if v1 and v2 are expressions of type `Version`, and `v1==v2`. 
    - `std::hash<Version>{}(v1)!=std::hash<Version>{}(v2)` if v1 and v2 are expressions of type `Version`, and `v1!=v2`
    - _Note 1 - The above implies that the specialization is a perfect hash function - End Note_




## §4 Dynamic Arrays [array]

1. Header `<lclib-c++/DynamicArray.hpp>` Synopsis
```c++
namespace lclib::array{
    template<typename T,typename Alloc=std::allocator<T>> struct DynamicArray;

    template<typename T,typename Alloc1,typename Alloc2> auto operator<=>(const DynamicArray<T,Alloc1>&,const DynamicArray<T,Alloc>&) noexcept(/*see below*/);
    template<typename T,typename Alloc1,typename Alloc2> bool operator==(const DynamicArray<T,Alloc1>&,const DynamicArray<T,Alloc>&) noexcept(/*see below*/);
    template<typename T,typename Alloc1,typename Alloc2> bool operator<(const DynamicArray<T,Alloc1>&,const DynamicArray<T,Alloc>&) noexcept(/*see below*/);
    template<typename T,typename Alloc1,typename Alloc2> bool operator>(const DynamicArray<T,Alloc1>&,const DynamicArray<T,Alloc>&) noexcept(/*see below*/);
    template<typename T,typename Alloc1,typename Alloc2> bool operator<=(const DynamicArray<T,Alloc1>&,const DynamicArray<T,Alloc>&) noexcept(/*see below*/);
    template<typename T,typename Alloc1,typename Alloc2> bool operator>=(const DynamicArray<T,Alloc1>&,const DynamicArray<T,Alloc>&) noexcept(/*see below*/);

    template<typename T,typename Alloc> DynamicArray<T,Alloc>::iterator begin(DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator begin(const DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator cbegin(const DynamicArray<T,Alloc>&) noexcept;

    template<typename T,typename Alloc> DynamicArray<T,Alloc>::iterator end(DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator end(const DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator cend(const DynamicArray<T,Alloc>&) noexcept;

    template<typename T,typename Alloc> DynamicArray<T,Alloc>::reverse_iterator rbegin(DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator rbegin(const DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator crbegin(const DynamicArray<T,Alloc>&) noexcept;

    template<typename T,typename Alloc> DynamicArray<T,Alloc>::reverse_iterator rend(DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator rend(const DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator crend(const DynamicArray<T,Alloc>&) noexcept;

    template<typename T,typename Alloc> void swap(DynamicArray<T,Alloc>&,DynamicArray<T,Alloc>&) noexcept;

    template<typename T,typename Alloc> DynamicArray<T,Alloc>::pointer data(DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_pointer data(const DynamicArray<T,Alloc>&) noexcept;
    template<typename T,typename Alloc> DynamicArray<T,Alloc>::size_type size(const DynamicArray<T,Alloc>&);

    template<typename T,std::size_t N> DynamicArray(const T(&)[N])->DynamicArray<T>;
    template<typename T,std::size_t N,typename Alloc> DynamicArray(const T(&)[N],const Alloc&)->DynamicArray<T,Alloc>;
    template<typename T,std::size_t N> DynamicArray(const std::array<T,N>&)->DynamicArray<T>;
    template<typename T,std::size_t N,typename Alloc> DynamicArray(const std::array<T,N>&,const Alloc&)->DynamicArray<T,Alloc>;
    template<typename T> DynamicArray(std::initializer_list<T>) -> DynamicArray<T>;
    template<typename T,typename Alloc> DynamicArray(std::initializer_list<T>,const Alloc&)->DynamicArray<T,Alloc>;
    template<typename T,typename Alloc1,typename Alloc2> DynamicArray(const DynamicArray<T,Alloc2>&,const Alloc1&) -> DynamicArray<T,Alloc1>;
    template<typename T,typename Alloc1,typename Alloc2> DynamicArray(DynamicArray<T,Alloc2>&&,const Alloc1&) -> DynamicArray<T,Alloc1>;
}
```

### §4.1 class DynamicArray [array.array]

1. Class template `DynamicArray` Synopsis
```c++
template<typename T,typename Alloc=std::allocator<T>> DynamicArray{
    using element_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = /*see below*/;
    using const_pointer = /*see below*/;
    using iterator = /*unspecified*/;
    using const_iterator = /*unspecified*/;
    using reverse_iterator = /*unspecified*/;
    using const_reverse_iterator = /*unspecified*/;
    using difference_type = /*see below*/;
    using size_type = std::make_unsigned_t<difference_type>;
    using allocator_type = Alloc;

    DynamicArray(const Alloc& alloc=Alloc());
    DynamicArray(const DynamicArray& arr);
    template<typename U,typename Alloc2> DynamicArray(const DynamicArray<U,Alloc2>& arr,const Alloc& alloc);
    DynamicArray(DynamicArray&& arr)noexcept;
    template<typename U,typename Alloc2> DynamicArray(DynamicArray<U,Alloc2>&& arr,const Alloc& alloc);
    template<std::size_t N> DynamicArray(const T(&)[N],const Alloc& alloc=Alloc());
    template<std::size_t N> DynamicArray(const std::array<T,N>&,const Alloc& alloc=Alloc());
    DynamicArray(std::initializer_list<T>,const Alloc& alloc=Alloc());
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray&);
    DynamicArray& operator=(DynamicArray&&) noexcept(/*see below*/);

    void swap(DynamicArray&) noexcept(/*see below*/);

    iterator begin()noexcept;
    const_iterator begin()const noexcept;
    const_iterator cbegin()const noexcept;
    iterator end()noexcept;
    const_iterator end()const noexcept;
    const_iterator cend()const noexcept;
    reverse_iterator rbegin()noexcept;
    const_reverse_iterator rbegin()const noexcept;
    const_reverse_iterator crbegin()const noexcept;
    reverse_iterator rend()noexcept;
    const_reverse_iterator rend()const noexcept;
    const_reverse_iterator crend()const noexcept;
    
    pointer data()noexcept;
    const_pointer data()const noexcept;
    size_type size()const noexcept;

    reference operator[](difference_type)noexcept;
    const_reference operator[](difference_type)const noexcept;
    const Alloc& get_allocator()const noexcept;
};
```

2. The class DynamicArray is a dynamic, fixed-sized, heap-allocated array of some type `T`. 

3. Unless `T` is an array of unknown bound, `T` shall be *Eraseable*, *CopyInsertible* with `Alloc`, *MoveInsertible* with `Alloc`. `T` shall be an object type.

4. `Alloc` shall satisfies *Allocator*. `std::allocator_traits<Alloc>::value_type` shall be exactly `T`. `Alloc` shall satsify *MoveConstructible*, and *Destructible*. Move construction with `Alloc` shall not throw exceptions, no diagnostic is required. 

5. If `std::allocator_traits<Alloc>::propagate_on_container_copy_assignment` inherits from `std::true_type`, `Alloc` shall satisfy *CopyAssignable*. If `std::allocator_traits<Alloc>::propagate_on_container_move_assignment` inherits from `std::true_type`, `Alloc` shall satisfy *MoveAssignable*, and move assignment with `Alloc` shall not throw exceptions, no diagnostic is required. If `std::allocator_traits<Alloc>::propagate_on_container_swap` inherits from `std::true_type`, `Alloc` shall satisfy *Swappable*, and the call to `swap(a1,a2)`, where a1, a2 are lvalues of type `Alloc` and `swap` is looked up in the namespace std, and by argument-dependant lookup, shall not throw exceptions, no diagnostic is required. 

6. `std::allocator_traits<Alloc>::pointer` shall be *CopyConstructible*, *MoveConstructible*, *CopyAssignable*, *MoveAssignable*, *Destructible*, and *Swappable*. No operation mentioned in those named requirements shall throw exceptions, no diagnostic is required. 

7. If `T` satisfies *LessThanComparable*, then `DynamicArray<T,Alloc>` satisfies *LessThanComparable*.

8. If `T` satisfies *EqualityComparable*, then `DynamicArray<T,Alloc>` satisfies *EqualityComparable*. 

9. `DynamicArray<T,Alloc>` satisfies *Container*, *AllocatorAwareContainer*, and *ContiguousContainer*. 

10. `T` shall not be an incomplete type, other than an array of an unknown bound. No diagnostic is required

#### §4.1.1 Dynamic Array Member Types [array.types]

`using value_type = T;`

1. The value type of the array, exactly `T`.

`using reference = T&;`

2. The reference type of the array, which is an lvalue reference type to `T`.

`using const_reference = const T&;`

3. The constant reference type of the array, which an lvalue reference type to `const T`.

`using pointer = typename std::allocator_traits<Alloc>::pointer;`

4. The pointer type. This shall be the pointer type of the `Alloc`. 

`using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;`

5. The constant pointer type. This shall be the `const_pointer` type of `Alloc`.

`using iterator = /*see below*/;`

6. An unspecified type that satisfies *Cpp17RandomAccessIterator* and *Cpp17ContiguousIterator*, which may be used as a mutable iterator into an object of type `DynamicArray<T>`.

`using const_iterator = /*see below*/;`

7. An unspecified type that satisfies *Cpp17RandomAccessIterator* and *Cpp17ContiguousIterator*, which may be used as an immutable iterator into an object of type `DynamicArray<T>`. `iterator` shall be implicitly convertible to `const_iterator`. 

`using reverse_iterator = /*see below*/;`

8. An unspecified type that satisfies *Cpp17RandomAccessIterator*, which may be used as a mutable iterator that iterates in reverse over the elements of an object of type `DynamicArray<T>`. 

`using const_iterator = /*see below*/;`

9. An unspecified type that satisfies *Cpp17RandomAccessIterator*, which may be used as an immutable iterator that iterates in reverse over the elements of an object of type `DynamicArray<T>`. 

`using difference_type = std::pointer_traits<pointer>::difference_type;`

10. The difference type between elements of this collection, which is exactly the difference type of pointers to it's elements. 


`using size_type = std::make_unsigned_t<difference_type>;`

11. The unsigned version of `difference_type`, and the size type of this collection.
e pointer type docs from
`using allocator_type = Alloc;`

12. The allocator type of this collection, exactly `Alloc`.

#### §4.1.2 DynamicArray Constructors [array.ctor]

`DynamicArray(const Alloc& alloc=Alloc())`
1. Constructs an empty array. It is unspecified whether any allocation occurs

2. Postconditions:
    - `this->get_allocator()==alloc`
    - `this->size()==0`
    - `DynamicArray{alloc1}==DynamicArray{alloc2}` if `alloc1` and `alloc2` are both objects of type `Alloc`, which both meet the requirements of *Allocator*, and `T` meets the requirements of *EqualityComparable*. 

`DynamicArray(const DynamicArray& arr)`
3. Constructs a new Array with the same size as `arr`, by copying the elements of `arr`.

4. Preconditions:
    - The behaviour is undefined if `arr` is *partially-constructed*

5. Postconditions:
    - `this->get_allocator()==std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`
    - `this->size()==arr.size()`
    - `DynamicArray(arr)==arr` if `T` meets the requirements of *EqualityComparable*, and the copy constructor of `T` is *equality-preserving*. 

6. Exceptions:
    - If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed. 

`template<typename U,typename Alloc2> DynamicArray(const DynamicArray<U,Alloc2>& arr, const Alloc& alloc)`

7. Copy constructs from arr using `alloc` to allocate the underlying array.

8. Requires:
    - `std::is_constructible_v<T,const U&>` shall be true. 

9. Preconditions:
    - The behaviour is undefined if `arr` is *partially-constructed*

10. Postconditions:
    - `this->get_allocator()==alloc`
    - `this->size()==arr.size()`
    - `DynamicArray{arr,alloc1}==DynamicArray{arr,alloc2}` if `alloc1` and `alloc2` are both expressions of type `Alloc`, and `arr` is an lvalue of type (possible `const`) `DynamicArray<U,Alloc2>`, if `T` meets the requirements of *EqualityComparable* and construction of `T` from a lvalue of type `const U` is an *equality-preserving* operation. 
11. Exceptions:
    - If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed. 

`DynamicArray(DynamicArray&& arr)noexcept;`

12. Move constructs a DynamicArray from `arr`. `arr` is left in valid, but unspecified, state. 

13. Preconditions:
    - Move construction of `Alloc` shall not throw exceptions.

`template<typename U,typename Alloc2> DynamicArray(DynamicArray<U,Alloc2>&& arr,const Alloc& alloc)`

14. Move constructs a DynamicArray from` arr` using `alloc`. `arr` is left in a valid, but unspecified, state. 

15. Requires:
    - `T` shall be constructible from `U&&`. 

16. Preconditions:
    - The behaviour is undefined if `arr` is *partially-constructed*

17. Postconditions:
    - `this->get_allocator()==alloc`

`explicit DynamicArray(size_type len,const Alloc& alloc=Alloc())`

17. Default constructs an array of `len` elements of type `T`. If `Alloc` is `std::allocator`, it is unspecified whether each element is *value-initialized* or *default-initialized*. 

18. Postconditions:
    - `this->get_allocator()==alloc`.

19. Exceptions:
    - If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed. 

`template<std::size_t N> DynamicArray(const T(&arr)[N],const Alloc& alloc=Alloc())`
`template<std::size_t N> DynamicArray(const std::array<T,N>& arr,const Alloc& alloc=Alloc())`

20. Constructs a Dynamic Array from a statically-sized array. 

21. Postconditions:
    - `this->get_allocator()==alloc`
    - `this->size()==N`
    - `std::equal(begin(*this),end(*this),begin(arr),end(arr))`, where `begin` and `end` are both looked up in the associated namespaces, as well as the namespace std, if `T` is *EqualityComparable*, and copy-construction of `T` is *equality-preserving*

22. Exceptions:
    - If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed. 


`DynamicArray(std::initializer_list<T> il,const Alloc& alloc=Alloc());`

23. Constructs a new DynamicArray from the elements of `il` (this allows list-initialization)

24. Postconditions:
    - `this->get_allocator()==alloc`
    - `this->size()==il.size()`
    - `std::equal(begin(*this),end(*this),begin(il),end(il))`, where `begin` and `end` are both looked up in the associated namespaces, as well as the namespace std, if `T` is *EqualityComparable*, and copy-construction of `T` is *equality-preserving*

25. Exceptions:
    - If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed. 

`template<typename Container> explicit DynamicArray(const Container& c,const Alloc& alloc=Alloc())`

26. Constructs a new array from the elements of the container `c`.

27. Requires:
    - `Container` shall satisfy *Container*, and have *Cpp17ForwardIterator*s. The expression `size(c)` shall be well-formed, where `size` is looked up in the associated namespaces and in the namespace `std`. 
    - `T` shall be constructible from the result of the expression `*begin(c)`, where `begin` is looked up in the associated namespaces, and in the namespace `std`.
    - `Container` shall not be an array type, `std::array<T,N>`, `std::initializer_list<T>`, or a specialization of `DynmaicArray`. 

28. Preconditions:
    - `begin(c)` shall be incrementable for `size(c)` elements, and the range `[begin(c),std::advance(begin(c),size(c)))` shall be dereferenceable. 
    - The iterator type of `Container` shall model `*Cpp17ForwardIterator*. 

29. Postconditions:
    - `this->get_allocator()==alloc`
    - `this->size()==size(c)` where `size` is looked up in the associated namespaces, as well as the namespace std. 
    - `std::equal(begin(*this),end(*this),begin(c),end(c))`, where `begin` and `end` are both looked up in the associated namespaces, as well as the namespace std, if `T` is *EqualityComparable*, and copy-construction of `T` is *equality-preserving*

30. Exceptions:
    - If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed.  

`template<typename ForwardIter> DynamicArray(ForwardIter begin,ForwardIter end,const Alloc& alloc=Alloc())`

31. Constructs a new `DynamicArray` with the elements in the range `[begin,end)`. 

32. Requires:
    - `ForwardIter` shall satisfy the requirements of *Cpp17ForwardIterator*.
    - `T` shall be constructible from `ForwardIter::reference`. 

33. Preconditions:
    - The range `[begin,end)` shall be valid. 

34. Postconditions:
    - `this->get_allocator()==alloc`
    - `this->size()==std::distance(begin,end)`
    - `std::equal(begin(*this),end(*this),begin,end)`, where `begin` and `end` are both looked up in the associated namespaces, as well as the namespace std, if `T` is *EqualityComparable*, and copy-construction of `T` is *equality-preserving*

35. Exceptions:
    - If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed. 

`template<typename ForwardIter> DynamicArray(ForwardIter begin,size_type length,const Alloc& alloc=Alloc())`

36. Constructs a new `DynamicArray` from the elements of the range `[begin,begin+length)`.

37. Requires:
    - `ForwardIter` shall satisfy the requirements of *Cpp17ForwardIterator*.
    - `T` shall be constructible from `ForwardIter::reference`. 

38. Preconditions:
    - The range `[begin,end)` shall be valid. 

39. Postconditions:
    - `this->get_allocator()==alloc`
    - `this->size()==std::distance(begin,end)`
    - `std::equal(begin(*this),end(*this),begin,end)`, where `begin` and `end` are both looked up in the associated namespaces, as well as the namespace std, if `T` is *EqualityComparable*, and copy-construction of `T` is *equality-preserving*

40. Exceptions:
    - If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed. 

#### §4.1.3 Destructor [array.dtor]

`~DynamicArray()noexcept;`

1. Destroys the elements of the array, and then deallocates the backing array. If the array is *partially-constructed* only the elements which were fully constructed are destroyed.

2. Exceptions:
    - If the destructor of any element throws an exception, `std::terminate` is called. It is unspecified if stack unwinding occurs. 

#### §4.1.4 Assignment [array.assign]

`DynamicArray& operator=(const DynamicArray& arr)`

1. Copy-assigns `*this` from `arr`. Each element in `*this` is copy-constructed or copy-assigned (which occurs is unspecified). 

2. Preconditions:
    - The behaviour is undefined if `arr` is *partially-constructed*.

3. Postconditions:
    - Let `ALLOC` be `this->get_allocator()` before this call if `std::allocator_traits<Alloc>::propagate_on_container_copy_assignment::value` is `false`, or `arr.get_allocator()` otherwise. After copy-assignment from `arr`, `this->get_allocator()==ALLOC`.
    -  After copy-assignment from `arr`,`(*this)==arr`is true if `T` satsifies *EqualityComparable* and copy-construction of `T` is equality-preserving, and that copy-assigning any element is equivalent, as observed by equality comparison, to invoking the destructor, followed by constructing a new element into the same storage.
    - After copy-assignment from `arr`, `this->size()==arr.size()`. 

4. Exceptions:
    - If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed. 
    - If an exception occurs while assigning any element, other assignment elements remain assigned, and subsequent elements remain in there original state.

`DynamicArray& operator=(DynamicArray&& rhs) noexcept(/*see below*/)`

5. Move assigns `*this` from `rhs`. `rhs` is left in a valid, but unspecified, state. 

6. Preconditions:
    - If `std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value` is false, the behaviour is undefined if rhs is *partially-constructed*.

7. Postconditions:
    - Let `RHS_ALLOC` be `rhs.get_allocator()` before the move assignment, and let `ALLOC` be `this->get_allocator()` before the move assignment if `std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value` is false, and `RHS_ALLOC` otherwise. `this->get_allocator()==ALLOC` is true.

8. Exceptions:
    - `noexcept(true)` if `std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value` is true. 
    - Otherwise, If an exception occurs while allocating the underlying array, the resulting object is equivalent to an array default-constructed with `std::allocator_traits<Alloc>::select_on_container_copy_construction(arr.get_allocator())`. The exception is rethrown by this constructor.
    - If an exception occurs while constructing any element, the resulting array is *partially-constructed*. Each element which was constructed before the element under construction will remain fully constructed. 
    - If an exception occurs while assigning any element, other assignment elements remain assigned, and subsequent elements remain in there original state.

#### §4.1.5  DynamicArray swap [array.swap]

`void swap(DynamicArray<T>& rhs) noexcept(/*see below*/);`

1. Swaps this with rhs. Does not perform any allocation.

2. Preconditions:
    - If `std::allocator_traits<Alloc>::propagate_on_container_swap` is false, the behaviour is undefined if `this->get_allocator()==rhs.get_allocator()` is false.
3. Exceptions:
    - If `std::allocator_traits<Alloc>::propagate_on_container_swap` is false, then the function is `noexcept(true)`.
    - Otherwise, if the expression `swap(ALLOC,rhs.ALLOC)`, where `ALLOC` is an *exposition-only* field of type `Alloc`, accessible to the body of this function and `swap` is looked up in the associated namespaces and in the namespace `std`, is not *potentially-throwing* the function is `noexcept(true)`.
    - Otherwise, if that expression throws an exception, both `*this` and `rhs` are left in their original states. If an exception is thrown, but the expression modifies either `ALLOC` or `rhs.ALLOC`, the behaviour is undefined. 

`template<typename T,typename Alloc> void swap(DynamicArray<T,Alloc>& a1,DynamicArray<T,Alloc>& a2) noexcept(/*see below*/);`

4. Non-member specialization of the `swap` customization point. The expression `swap(a1,a2)`, where `a1` and `a2` are lvalues of type `DynamicArray<T,Alloc>`, is equivalent to `a1.swap(a2)`. 

5. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

6. Exceptions:
    - Same as `a1.swap(a2)`.

#### §4.1.6 DynamicArray iterators [array.iter]

`iterator begin()noexcept`

`const_iterator begin()const noexcept`
1. Returns an iterator to the beginning of the collection. 

2. Preconditions:
    - The behaviour is undefined if `*this` is *partially-constructed*.

3. Postconditions:
    - `t.begin()==t.begin()`, where `t` is an expression of type `DynamicArray`.
    - `t.begin()` is dereferenceable and incrementable if `t.size()!=0`, where `t` is an expression of type `DynamicArray`.
    - `const_cast<const DynamicArray<T,Alloc>&>(t).begin()==t.begin()`, where `t` is an expression of type `DynamicArray`.

`iterator end()noexcept`

`const_iterator end()const noexcept`

4. Returns an iterator past-the-end of the collection

5. Preconditions:
    - The behaviour is undefined if `*this` is *partially-constructed*.

6. Postconditions:
    - `t.end()==t.end()`, where `t` is an expression of type `DynamicArray`.
    - `[t.begin(),t.end())` is a valid range, where `t` is an expression of type `DynamicArray`.
    - `std::distance(t.begin(),t.end())==t.size()`, where `t` is an expression of type `DynamicArray`.
    - `const_cast<const DynamicArray<T,Alloc>&>(t).end()==t.end()`, where `t` is an expression of type `DynamicArray`.

`const_iterator cbegin()const noexcept`

7. Equivalent to `this->begin()`, but selects the const overload even if called on a non-const lvalue.

`const_iterator cend()const noexcept`

8. Equivalent to `this->end()`, but selects the const overload even if called on a non-const lvalue.

`reverse_iterator rbegin()noexcept`

`const_reverse_iterator rbegin()const noexcept`

9. Returns an iterator to end of the collection, that iterates in reverse.

10. Preconditions:
    - The behaviour is undefined if `*this` is *partially-constructed*. 

11. Postconditions:
    - `t.rbegin()==t.rbegin()`, where `t` is an expression of type `DynamicArray`.
    - `t.rbegin()` is dereferenceable and incrementable if `t.size()!=0`, where `t` is an expression of type `DynamicArray`.
    - `const_cast<const DynamicArray<T,Alloc>&>(t).rbegin()==t.rbegin()`, where `t` is an expression of type `DynamicArray`.

`reverse_iterator rend()noexcept`

`const_reverse_iterator rend()const noexcept`

12. Returns an iterator past-the-beginning of this collection, that iterates in reverse.


13. Preconditions:
    - The behaviour is undefined if `*this` is *partially-constructed*.

14. Postconditions:
    - `t.rend()==t.rend()`, where `t` is an expression of type `DynamicArray`.
    - `[t.rbegin(),t.rend())` is a valid range, where `t` is an expression of type `DynamicArray`.
    - `std::distance(t.rbegin(),t.rend())==t.size()`, where `t` is an expression of type `DynamicArray`.
    - `const_cast<const DynamicArray<T,Alloc>&>(t).rend()==t.rend()`, where `t` is an expression of type `DynamicArray`.

`const_reverse_iterator crbegin()const noexcept`

15. Same as `this->rbegin()`, but selects the const overload even if called on a non-const lvalue.

`const_reverse_iterator crend()const noexcept`

15. Same as `this->rend()`, but selects the const overload even if called on a non-const lvalue.

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::iterator begin(DynamicArray<T,Alloc>& arr)noexcept`

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator begin(const DynamicArray<T,Alloc>& arr)noexcept`

16. Non-member specialization of the `begin` customization point. The expression `begin(arr)` is an equivalent expression to `arr.begin()`, if `arr` is an expression of type `DynamicArray<T,Alloc>`. 

17. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

18. Requires:
    - `T` shall not be an array of an unknown bound.

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::iterator end(DynamicArray<T,Alloc>& arr)noexcept`

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator end(const DynamicArray<T,Alloc>& arr)noexcept`

19. A specialization of the `end` customization point. The expression `end(arr)` is an equivalent expression to `arr.end()`, if `arr` is an expression of type `DynamicArray<T,Alloc>`. 

20. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

21. Requires:
    - `T` shall not be an array of an unknown bound.

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator cbegin(DynamicArray<T,Alloc>& arr)noexcept`

22. A specialization of the `cbegin` customization point. The expression `cbegin(arr)` is an equivalent expression to `arr.cbegin()`, if `arr` is an expression of type `DynamicArray<T,Alloc>`. 

23. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

24. Requires:
    - `T` shall not be an array of an unknown bound.

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator cend(DynamicArray<T,Alloc>& arr)noexcept`

25. A specialization of the `cend` customization point. The expression `cend(arr)` is an equivalent expression to `arr.cend()`, if `arr` is an expression of type `DynamicArray<T,Alloc>`. 

26. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

27. Requires:
    - `T` shall not be an array of an unknown bound.

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::reverse_iterator rbegin(DynamicArray<T,Alloc>& arr)noexcept`

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator rbegin(const DynamicArray<T,Alloc>& arr)noexcept`

25. A specialization of the `rbegin` customization point. The expression `rbegin(arr)` is an equivalent expression to `arr.rbegin()`, if `arr` is an expression of type `DynamicArray<T,Alloc>`. 

26. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

27. Requires:
    - `T` shall not be an array of an unknown bound.

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::reverse_iterator rend(DynamicArray<T,Alloc>& arr)noexcept`

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator rend(const DynamicArray<T,Alloc>& arr)noexcept`

28. A specialization of the `rend` customization point. The expression `rn(arr)` is an equivalent expression to `arr.rbegin()`, if `arr` is an expression of type `DynamicArray<T,Alloc>`. 

29. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

30. Requires:
    - `T` shall not be an array of an unknown bound.

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator crbegin(DynamicArray<T,Alloc>& arr)noexcept`

31. A specialization of the `rcbegin` customization point. The expression `crbegin(arr)` is an equivalent expression to `arr.crbegin()`, if `arr` is an expression of type `DynamicArray<T,Alloc>`. 

32. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

33. Requires:
    - `T` shall not be an array of an unknown bound.

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator crend(DynamicArray<T,Alloc>& arr)noexcept`

34. A specialization of the `crend` customization point. The expression `crend(arr)` is an equivalent expression to `arr.crend()`, if `arr` is an expression of type `DynamicArray<T,Alloc>`. 

35. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

36. Requires:
    - `T` shall not be an array of an unknown bound.

#### §4.1.7 DynamicArray data [array.data]

`pointer data()noexcept`

`const_pointer data()const noexcept`

1.  Returns a pointer to the first element of the array

2. Postconditions:
    - `&*(this->data()+i)==&*(this->begin()+i)` for `0<=i<this->size()`, if `*this` is not *partially-constructed*.

3. The behaviour is undefined if a pointer returned by the const overload is used to mutate any element of the array, except any `mutable` subobjects of `T`.  

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::pointer data(DynamicArray<T,Alloc>& arr) noexcept`

`template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_pointer data(const DynamicArray<T,Alloc>& arr) noexcept`

4. Non-member Specialization of the `data` customization point. The expression `data(arr)` is an equivalent expression to `arr.data()` if `arr` is an expression of type `DynamicArray<T,Alloc>`.

5. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

#### §4.1.8 DynamicArray size [array.size]

`size_type size()const noexcept`

1. Returns the size of the array. 

`template<typename T,typename Alloc> DynamicArray<T,Alloc> size(const DynamicArray<T,Alloc>& arr);`

2. Non-member specialization of the `size` customization point. 

3. If overload resolution selects an instantiation of this function template, except for a call with an unqualified-id, where the parameter has the type `DynamicArray<T,Alloc>`, the program is ill-formed. No diagnostic is required

#### §4.1.9 DynamicArray Indexing [array.index]

`reference operator[](difference_type i)noexcept`

`const_reference operator[](different_type i)noexcept`

1. Indexes the array.

2. Preconditions:
    - `0<=i<this->size()`
    - If `*this` is *partially-constructed*, then `i` shall be less than the index of first element that was not fully constructed
    - _Note 1 - this is the element which construction threw an exception - End Note_

3. Postconditions:
    - `&arr[i]==arr.data()+i`, if `arr` is an expression of type `DynamicArray<T,Alloc>`

4. The behaviour is undefined if a reference returned by the const overload is used to modify any element of the array, except any `mutable` subobjects of `T`. 

#### §4.1.8 DynamicArray allocator [array.alloc]

`const Alloc& get_allocator()const noexcept;`

1. Returns a reference to the allocator type for this collection.

### §4.2 DynamicArray Comparison Operators [array.compare]

`template<typename T,typename Alloc1,typename Alloc2> /*see below*/ operator<=>(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(/*see below*/);`

1. Performs a lexicographical three-way comparison of the elements of `a1` and `a2`. 

2. Requires:
    - The expression `t1<=>t2` shall be well-formed, where `t1`, `t2` are expressions of type `T`. 
    - `T` shall not be an array of an unknown bound. 

3. Mandates:
    - The expression `t1<=>t2` shall have type `std::strong_ordering`, `std::weak_ordering`, or `std::partial_ordering`. 

4. Preconditions:
    - Given `t1`, `t2` are expressions of type `T`,
        - `(t1<=>t2)==0` shall be equivalent to `t1==t2`.
        - `(t1<=>t2)!=0` shall be equivalent to `t1!=t2`.
        - `(t1<=>t2)<0` shall be equivalent to `t1<t2`
        - `(t1<=>t2)>0` shall be equivalent to `t1>t2`
        - `(t1<=>t2)<=0` shall be equivalent to `t1<=t2`
        - `(t1<=>t2)>=0` shall be equivalent to `t1>=t2`
    - _Note 1 - That is, the three-way comparison operator selected for the comparison must be consistent with the other relational operators - End Note_
    - During overload resolution against user-defined operator functions, the above operations only considers operator functions found in the associated namespaces of `T`, and any builtin operator candiates.

5. Postconditions:
    - If the expression `arr1<=>arr2` selects this overload, then all of the following pairs of expressions shall be equivalent, where each comparsion operation that has `arr1` and `arr2` as direct operands selects an operator function defined by this section. 
        - `(arr1<=>arr2) == 0` and `arr1==arr2`
        - `(arr1<=>arr2) != 0` and `arr1!=arr2`
        - `(arr1<=>arr2) < 0` and `arr1<arr2`
        - `(arr1<=>arr2) > 0` and `arr1>arr2`
        - `(arr1<=>arr2) <= 0` and `arr1<=arr2`
        - `(arr1<=>arr2) >= 0` and `arr1>=arr2`

6. Returns:
    - `std::compare_three_way_result<T>::type`, if that type is `std::partial_ordering` or `std::weak_ordering`, or
    - Either `std::strong_ordering` or `std::weak_ordering` (which type is used is *implementation-defined*) otherwise (that is, if `std::compare_three_way_result<T>::type` is `std::strong_ordering`)

7. Exceptions:
    - `noexcept(true)` if the expression `t1<=>t2` used above is not *potentially-throwing*
    - Otherwise, throws any exceptions thrown by the comparison between two elements of the array. 


`template<typename T,typename Alloc1,typename Alloc2> bool operator==(const DynamicArray<T,Alloc1>& arr1,const DynamicArray<T,Alloc2>& arr2) noexcept(/*see below*/)`

1. Compares the elements of `arr1` and `arr2` for equality. An equivalent expression to `std::equal(begin(arr1),end(arr1),begin(arr2),end(arr2))`

2. Requires:
    - Given `t1`, `t2` are expressions of type `T`, `t1==t2` shall be well-formed in a context that only considers the associated namespaces of `T`. 
    - `T` shall not be an array of an unknown bound



