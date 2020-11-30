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

### §1.3.2 Constrained Operations [intro.constrained]

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
18. _Note 7 - This implies its not valid to specialize a Standard Library type on a type defined by this specification - End Note_


## §2 Configuration Macros and [config]

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

### §3.3 Binary Stream Operators [version.op]

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
