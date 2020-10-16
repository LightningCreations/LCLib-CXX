# General Library Rules

## Normative Sections

All sections of this specification are to be considered normative unless they start
 with a declaration "_Note - This section is not normative - End Note_". 

Aside from the above declaration, any sequence of text which is highlighted in italics
 (when viewed in plain-text form, between underscore characters `_`)
  and starts with the word "Note" is not normative. 
  All Notes will end with the words "End Note". 
  
_Note - Notes are used to suggest implementations, provide information about future direction,
 or give further clarification to a normative section - End Note_

## Terms And definitions

### C++ Standard

ISO 14882: Programming Languages - C++, in any published revision, or committee draft revision. 

### C++

The Program Language Defined by the "C++ Standard",
 as well as the accompanying standard library. 

### C++17

The revision of the C++ Standard published in 2017,
 and all defect reports which amend that revision that have been published.
 
### C++20

The revision of the C++ Standard which was approved in Febuary of 2020,
 is scheduled to be published in the year 2020. 
 As well as any future defect reports intended to amend that revision which have been published. 

### C++ Standard in Use

Either C++17 or C++20, depending on the implementation of the C++ Standard,
 and possibly depending on specified compile-time flags. 

### Program

A Program in the context of this specification is a C++ Program as defined by the C++ Standard
 which makes use of construsts defined by this specification, which are not included in the C++ Standard.

### Implementation 

A collection of headers, library binary objects, and optionally accompanying documentation
  which define the constructs provided by this specification. 

### Shall and Shall not

An absolute requirement or prohibition imposed by this specification on either the 
 implementation or on the program. 

### Unspecified Behaviour

Behaviour which this specification provides a choice, and does not define the method
 which implementations make that choice.
 
### Implementation-Defined Behaviour

Unspecified Behaviour, for which implementations shall document how the choice is made.
 
### Undefined Behaviour

Behaviour for which no requirements are assigned by this specification. 

The use of phrase `The behaviour of ... is undefined`, the phrase `The behaviour is undefined`,
 or a lack of definition of behaviour may also be used to indicate Undefined Behaviour. 
 There is no distinction between any of these uses, all describe Behaviour which is Undefined.
 
_Note - Valid responses to undefined behaviour include (but are not limited to) to assign meaning to it,
 discard the behaviour, ignore the behaviour (potentially causing further issues with well-defined constructs),
 cause or report an error. - End Note_

### Strictly-conforming Program

A well-formed Program which is considered Strictly-conforming by the C++ standard in use, 
 except that it includes headers defined by this specification,
 and makes use of no constructs which this specification considers Unspecified, Implementation-defined,
  or Undefined, and violates no minimum implementation limits imposed by this specification. 
  
### Correct Program

A well-formed Program which is considered correct by the C++ Standard in use,
 and which makes no use of constructs which this specification considers Undefined,
 and which violates no limit validly imposed by the implementation. 
 
 _Note - A runtime construct which is not evaluated is not considered to be made use of - End Note_
### Ill-formed

A program which makes use of either an erroneous C++ construct or construct defined by this specification, for which the implementation shall cause a diagnostic. 
 
### Ill-formed, no diagnostic required

A program which makes use of either an erroneous C++ construct or construct defined by this specification,
 for which a diagnostic is not required by either this specification or the C++ Standard. 

The behaviour of executing a translated program which is ill-formed, no diagnostic required, is undefined.

 _Note - Use of this term within this specification is reserved for type constraint restrictions - End Note_

### Well-formed

A program which is neither Ill-formed, nor Ill-formed, no diagnostic required.

### Observable Behaviour

Either behaviour which is considered by the C++ Standard to be observable,
 or which this specification defines as observable. 

### Conforming Implementation

An implementation which does not alter the observable behaviour of any program which is strictly-conforming,
 which causes diagnostics to be issued for ill-formed programs, 
 and which does not cause any Correct Program to become ill-formed. 


## Reserved Identifiers

Any identifier which starts with a single underscore within the `lclib` namespace or any contained namespace,
 and any identifiers within it are reserved for the implementation. 
The behaviour of a program which names an identifier of such a form is undefined.

_Note - This is intended to allow the implementation to define constructs,
 needed to provide the specified constructs - End Note_

## lclib Namespace

All constructs defined by this specification are made available in the `lclib` namespace,
 or any subnamespace are protected by this specification. 
The behavior of a program that defines names within such namespaces is undefined.

## Transitive Dependencies

The behaviour of a program which names a symbol defined by this
 specification is undefined, unless the symbol is defined in a header included by the program,
 or the symbol exists in a header, which any header included by the program is permitted to 
 make symbols available from, or that symbol is an overloaded operator, or function,
  referenced by argument-dependent lookup. 
  
 
_Note - This allows for implementations to include other headers from this api,
 even where those headers are not permitted or required to be included, 
 to allow implementations to satisfy requirements in this api - End Note_

Including any header defined by this api may make available any symbols defined
 in any standard library header. 

If the synopsis of a header has the line `#include <header>` then the symbols defined by `<header>`
 shall be made available to programs which include the api header. 

## Functions

The behaviour is undefined if any function defined by this api appears in any
 context other than a direct function call (of the form `function(args...)`),
 macro-suppressed function call (of the form `(function)(args...)`,
 or implicit call through an overloaded operator, user-defined-literal, or `new`, `delete`, `new[]`, or `delete[]` expression. 

_Note - In particular, taking the address of a function or member-function, 
 or decaying a function to a pointer-to-function has undefined behaviour - End Note_


Additionally, the behaviour is undefined if a non-member function declared by this specification,
 with any of the following names, is called, except if the call is resolved through Argument-dependent lookup:
* swap
* begin
* end
* cbegin
* cend
* rbegin
* rend
* crbegin
* crend
* get, if the function is declared as a function template.

_Note - This allows these functions to be declared in a method which is only findable through ADL - End Note_


## Operators

The behaviour of a program that explicitly calls
 any overloaded operator function defined by this specification is undefined, unless:
* The operator function is an overload of `operator->()`, OR
* The operator function is an overload of `operator new`, `operator delete`, `operator new[]`, or `operator delete[]`,  

For the purposes of this rule an explicit call is a call to the operator function,
 that explicitly uses function call syntax, such as `v.operator+(b)`. 
 For the function call operator `v(args...)` is not an explicit call,
  though `v.operator()(args...)` is (and is thus, undefined ). 
  
_Note - This is provided to allow implementations considerable flexibility in how operators,
 are defined.  In particular, in C++ 20, implementations may leave comparison operators 
 undefined and provide `x < y` using the C++ 20 rewritten candidates if `x <=> y` is valid.
- End Note_

## Templates


### Template Specialization Policy

A Program may Specialize templates provided by lclib-c++, on user-provided types,
 unless the particular template says otherwise, provided the type satisfies the requirements of that template. 

If the specialization is a partial specialization, at least one type that is specialized must either be a user-provided type,
 or a partial specialization on a template which is not defined by either the C++ Standard Library or lclib-c++. 
 
A type T is a user-provided type if: 
* It is a class or enumeration type or instantiation of a class template,
 that is declared by neither the C++ Standard Library or lclib-c++
* It is an instantiation of a class template for which at least one type template parameter is a user-provided type, transitively.
* It is a pointer or reference to a user-provided type
* It is an array, including an array of an unknown bound, of a user-provided type.
* It is a instantiation of a template defined by either the C++ Standard Library or lclib-c++, 
 where the specialization used was not defined by either the C++ Standard Library or lclib-c++.

This specialization policy also applies to specializations of standard library templates
 (specifically, C++ Standard Templates cannot be specialized with types solely provided by lclib-c++).
 
The behavior of a program that violates these requirements is undefined. 

### Incomplete Types

Notwithstanding templates defined in the `<lclib-c++/TypeTraits.hpp>` header,
 by default, templates may not be instantiated with incomplete types. The behavior of instantiating a template with one or more incomplete types is undefined, except as otherwise provided. 
  
Templates defined in the TypeTraits Header have special rules. 
Most templates require that all instantiating parameters are either complete, an array of an unknown bound, or (possibly cv-qualfied) void. See documentation of that header for details. 
 
The behavior of violating these rules is undefined.  


