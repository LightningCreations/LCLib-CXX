# General Library Rules


## Reserved Identifiers

Any identifier which starts with a single underscore within the `lightningcreations::lclib` namespace,
 and any identifiers within it are reserved for the implementation. 
 
## Templates
### Template Specialization Policy

A Program may Specialize templates provided by lclib-c++, on user-provided types,
 unless the particular template says otherwise, provided the type satisfies the requirements of that template. 

If the specialization is a partial specialization, at least one type that is specialized must either be a user-provided type,
 or a partial specialization on a template which is not defined by either the C++ Standard Library or lclib-c++. 
 
A type T is a user-provided type if: 
* It is a class or enumeration type or instantiation of a class template,
 that is declared by neither the C++ Standard Library or lclib-c++
* It is an instantiation of a class template for which at least one type template parameter is a user-provided type, 
   transitively.
* It is a pointer or reference to a user-provided type
* It is an array, including an array of an unknown bound, of a user-provided type.
* It is a instantiation of a template defined by either the C++ Standard Library or lclib-c++, 
 where the specialization used was not defined by either the C++ Standard Library or lclib-c++.

This specialization policy also applies to specializations of standard library templates
 (specifically, C++ Standard Templates cannot be specialized with types solely provided by lclib-c++).
 
The behavior of a program that violates these requirements is undefined. 

### Incomplete Types

Notwithstanding templates defined in the `<lclib-c++/TypeTraits.hpp>` header,
 by default, templates may not be instantiated with incomplete types. The behavior of instantiating a template 
  with one or more incomplete types is undefined. 
  
Templates defined in the TypeTraits Header have special rules. 
Most templates require that all instantiating parameters are either complete, an array of an unknown bound,
 or (possibly cv-qualfied) void. See documentation of that header for details. 
 
The behavior of violating these rules is undefined.  to 


