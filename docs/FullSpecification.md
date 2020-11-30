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
6. The term "Implementation" refers to an implementation of the C++ Standard in Use, as well as a collection of headers, binary artifacts, and optionally accompanying documentation, which provides the constructs defined by this specification.
7. This specification, refers to this document, either as a Draft for the LCS Project, or as a publication. 
8. The term "shall" refers to an absolute requirement of this specification on either the implementation or on a program. 
9. The term "shall not" is the inverse of "shall" and refers to an absolute prohibition of this specification on either the implementation or on a program. 
10. A well-formed program, is a program that is well-formed program under the C++ Standard in Use and does not violate any requirements or prohibitions of this specification. 
11. An ill-formed program is a program that is not a well-formed program.

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
5. Certain constructs of this specification, or of the C++ Standard in Use, are described as *unspecified*. These are non-deterministic aspects of the abstract machine.
6. _Note 3 - This specification typically constrains such_ unspecified _behaviour. Any behaviour which is described as _ unspecified _by the C++ Standard in Use may be further constrained by this specification - End Note_
7. Certain other constructs of this specification, or of the C++ Standard in Use, are described as *undefined*.
8. _Note 4 - This specification imposes no limitations on any such behaviour - End Note_
9. During evaluation of a correct program, an implementation shall ensure that the *observable behaviour* of the program, matches the *observable behaviour* of one possible result of the current parameterized abstract machine. 
10. During evaluation of a well-formed program that has undefined behaviour, or of an ill-formed program, no limitations are imposed on the result of that evaluation.
11. _Note 5 - The above includes the observable behaviour of programs before the first occurance of an undefined operation - End Note_
12. The observable behaviour of a program shall include the following:
    * Any operation that is described as having observable behaviour by the C++ Standard in Use
    * Any operation that is explicited denoted by this specification as having observable behaviour

13. _Note 6 - The requirements of this section do not prevent an implementation from enforcing stricter requirements on the evaluation of programs. - End Note_

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
8. A program shall not use the name of any non-member function defined by this specification, except iby directly calling that name. 
9. _Note 5 - Uses prohibited by the above clause include conversion to a function pointer, passing as callable to another function, or calling the name enclosed in parenthesis. - End Note_
10. A program shall not define any identifiers within the reserved namespace `lclib`, or any namespace contained within. 
11. A program shall not directly name any identifier within the reserved namespace, or any namespace contained within, that starts with a single underscore. 
12. A program shall not `#define` or `#undef` any name declared by any header of this specification, a name declared by any standard library header, or an identifier which is a reserved identifier, the name of a keyword, a contextual keyword, or the name of a standard attribute macro. Notwithstanding the previous statement, a program may define the attribute names `likely` and `unlikely` as function-like macros. 
