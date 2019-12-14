# Polymorphic Wrapper
In header `<lclib-c++/Polymorphic.hpp>`



## Header Synopsis

```c++
namespace lightningcreations::lclib::polymorphic{
    template<typename T> struct PolymorphicWrapper;
    template<typename T> PolymorphicWrapper(const T&)->PolymorphicWrapper<T>;
    template<typename T> PolymorphicWrapper(T&&)->PolymorphicWrapper<T>;
    template<typename T,typename... Args> explicit PolymorphicWrapper(std::in_place_type_t<T>,Args&&...);
}
namespace std{
    template<typename T,typename U> struct common_type<PolymorphicWrapper<T>,PolymorphicWrapper<U>>;
}
```

## Class Template PolymorphicWrapper

```c++
template<typename T> struct PolymorphicWrapper final{
public:
    using type = T;
    template<typename U> derivied_type = /*see below*/;
    using can_move_object = /*unknown*/;
    constexpr PolymorphicWrapper();
    constexpr PolymorphicWrapper(PolymorphicWrapper&&);
    template<typename U> /*conditionally-constexpr*/ /*conditionally-explicit*/ PolymorphicWrapper(PolymorphicWrapper<U>&&) noexcept(/*see below*/);
    template<typename U> PolymorphicWrapper(const U&) noexcept(/*see below*/);
    template<typename U> PolymorphicWrapper(U&&) noexcept(/*see below*/);
    template<typename U,typename... Args> PolymorphicWrapper(std::in_place_type_t<U>,Args&&...) noexcept(/*see below*/);
    operator T&()&;
    operator const T&()const;
    operator T&&()&&;
    T& operator*()&;
    const T&operator*()const;
    T&&operator *()&&;
    template<typename U> /*conditionally-explicit*/ operator U&()&;
    template<typename U> /*conditionally-explicit*/ operator const U&()const;
    template<typename U> /*conditionally-explicit*/ operator U&&()&&;
    T* operator->()noexcept;
    const T* operator->()const noexcept;
    template<typename U> U& checked_cast()&;
    template<typename U> U&& checked_cast()&&;
    template<typename U> const U& checked_cast()const&;
    template<typename U> bool instanceof()const noexcept;
};
```

Represents a Type-erased, move-only wrapper for holding a value of a polymorphic type,
 or any type derived from that polymorphic type. 

At any given time, a PolymorphicWrapper either contains a value of a dynamic type derived from T,
 or contains no value. 
The value is type-erased to a value of type T, and can be accessed normally as a value of type T. 
It can be upcast to any base class of T, and be downcast to any class derived from T. 
All Downcasts are checked, as though by a reference dynamic cast. 
The value is allocated in an unspecified manner. 
In particular, it may be allocated in the object representation. 
Move constructors, including casting move constructors, are permitted (though not required),
 to call the move constructor of the owned object (even if it is non-trivial),
  provided the constructor is non-throwing. (This is to permit small-value optimization for PolymorphicWrapper)
If, for a particular specialization, the implementation can call the move constructor of the owned object,
 it defines the member type `can_move_object` as `std::true_type`. Otherwise it defines it as `std::false_type`.
 This does not guarantee that such a move constructor will be called (only that it can).
 Note that defining the type as `std::true_type` is a looser guarantee.
 In particular, an implementation that generally can call the move constructor is permitted to define
  `can_move_object` as `std::true_type`, even if the particular specialization does will not.

If a Move constructor of PolymorphicWrapper calls the move constructor of the derived object,
 it is unspecified when the destructor of the owned object is called (It may be immediately after moving, before moving a 2nd time,
  or before destroying the object).

If T is not a polymorphic class type with a public, virtual destructor, the program is ill-formed. 
A program may not define partial or full specializations for PolymorphicWrapper.

If `T` is an *over-aligned type*, whether or not `T` is supported is implementation-defined. 

### Member Types

```c++
using type = T; //(1)
template<typename U> using derived_type = /*see below*/; //(2)
using can_move_object = /*see below*/;
```
1. The base type for this PolymorphicWrapper, identically T
2. If `std::is_base_of_v<T,U>` is true, then defined as identically U. Otherwise, does not name a type (RAII friendly). 
Note that `derived_type<T>` is the same as T.
3. If this specialization of PolymorphicWrapper may call a move constructor of its owned object when being moved from
 (including when cast-moving), then aliases a type that inherits from `std::true_type`, otherwise aliases a type that inherits from `std::false_type`.



### Constructors/Destructors

```c++
constexpr PolymorphicWrapper()noexcept; //(1)
constexpr PolymorphicWrapper(PolymorphicWrapper&& rhs)noexcept; //(2)
template<typename U> /*conditionally constexpr*/ /*conditionally-explicit*/ PolymorphicWrapper(PolymorphicWrapper<U>&& rhs) noexcept(/*see below*/); //(3)
template<typename U> PolymorphicWrapper(U&& u) noexcept(/*see below*/); // (4)
template<typename U> PolymorphicWrapper(const U& u) noexcept(/*see below*/); //(5)
template<typename U,typename... Args> explicit PolymorphicWrapper(std::in_place_type_t<U>,Args&&... args) noexcept(/*see below*/); //(6)
~PolymorphicWrapper(); //(7)
```
1. Constructs a Polymorphic Wrapper that owns no value. 
2. Move-constructs from rhs, taking ownership of the value owned by rhs, and leaving rhs in a default-constructed state.
 Neither this, nor (3) may directly call any global allocation function (including through an allocator),
  but may call a non-throwing move constructor of the owned object, even if that move constructor is non-trivial.
3. Move-constructs from rhs as above performing a upcast from U to T, or a checked downcast from U to T.
 If U is a base class of T, the downcast is checked. If the dynamic type of the owned object of rhs is not derived from T,
  an instance of std::bad_cast or an unspecified type inheriting from std::bad_cast is thrown.
  If an exception is thrown, rhs retains ownership of the owned object.
 Does not participate in overload resolution if U is exactly T, or neither U is not a base class of T nor T a base class of U.
 This method is explicit (and neither constexpr nor noexcept) if U is a base class of T. Otherwise it is not explicit, 
 and is both constexpr and noexcept.
 Like 2, this constructor is permitted to call any non-throwing move constructor of the owned object,
  even if that move constructor is non-trivial, but may not directly call any global allocation function (including through an allocator).
  If rhs is not moved (IE. the upcast failed), the move constructor of the owned object is not called.
  If rhs owns no object (IE. is default-constructed), no exception is thrown (both rhs and the constructed object are left in a default-constructed state).
4. Move constructs the owned object of type U from `u`. If U is not move constructible, or T is not a base class of U,
 then this constructor is defined as deleted. Does not participate in overload resolution if U is a specialization of PolymorphicWrapper or `std::in_place_type_t`.
5. Copy constructs the owned object of type U from `u`. If U is not copy constructible, or T is not a base class of U,
 then this constructor is defined as deleted. Does not participate in overload resolution if U is a specialization of PolymorphicWrapper or `std::in_place_type_t`.
6. Constructs the owned object of type U from `std::forward<Args>(args)...` in place.
 Does not participate in overload resolution if U is not constructable from `args...` or T is not a base class of U.
7. Destroys the owned object, if it exists, and deallocates the storage allocated by the constructor. 

If any constructor allocates memory, and that memory allocation fails, the object is left in a default-constructed state.

If `U` is an over-aligned type, constructors (4),(5),(6) are conditionally supported.
If unsupported, (4) and (5) are defined as deleted, and (6) does not participate in overload resolution. 
Note that `U` being over-aligned may be supported even if instantiating with an over-aligned type is not supported,
 and vice-versa.

### Exception Guarantees

1. `noexcept(true)`
2. `noexcept(true)`
3. `noexcept(std::is_base_of_v<T,U>)`. If U is a base class of T (IE. `!std::is_base_of_v<T,U>`) and the upcast fails, rhs is left in its original state.
4. `noexcept(std::is_nothrow_move_constructible_v<U>)`. If the move constructor of U throws an exception, then any memory allocated by this constructor is deallocated.
5. `noexcept(std::is_nothrow_copy_constructible_v<U>)`. If the copy constructor of U throws an exception, then any memory allocated by this constructor is deallocated.
6. `noexcept(std::is_nothrow_constructible_v<T,Args&&...>)`. If the constructor called throws an exception, then any memory allocated by this constructor is deallocated.
7. `noexcept(true)`. 

### Conversion Operators

```c++
operator T&()&; //(1)
operator const T&()const; //(1)
operator T&&()&&; //(2)
template<typename U> /*conditionally-explicit*/ operator U&()&; //(3)
template<typename U> /*conditionally-explicit*/ operator const U&()const; //(3)
template<typename U> /*conditionally-explicit*/ operator U&&()&&; //(4)
```

1. Returns a reference to the owned object, type-erased to T. The behavior is undefined if this has no owned object, or `*this` has been moved from.
2. Same as (1), except the owned object is returned by rvalue-reference.
3. If the dynamic type of the owned object is derived from `U`, then returns a reference to the owned object, cast to `U`. 
 Otherwise, throws `std::bad_cast` or an exception of a type derived from `std::bad_cast`.
 If there is no owned object, the behavior is undefined.
4. Same as (3), except the owned object is returned by rvalue-reference.

(3),(4) do not participate in overload resolution unless `T` is a base class of `U` or `U` is a base class of `T` (`U` cannot be identically `T`). 
  Explicit if `T` is a base class of `U` (and `U` is not a base class of `T`).
  
#### Exceptions
 (1),(2): None
 
 (3),(4): If `T` is a base class of `U`, throws `std::bad_cast` if the downcast to `U` failed. Otherwise throws no exceptions.
 
### Pointer-like operations

```c++
T& operator*()&; //(1)
const T& operator*()const; //(1)
T&& operator *()&&; //(2)
T* operator->()noexcept; //(3)
const T* operator->()const noexcept; //(3)
```

1. Same as `static_cast<T&>(*this)` or `static_cast<const T&>(*this)` respectively
2. Same as `static_cast<T&&>(static_cast<PolymorphicWrapper<T>&&>(*this))`
3. Returns a pointer to the owned object, type-erased to `T`, or a null pointer if this does not own an object.

### Named Cast and instanceof

```c++
template<typename U> U& checked_cast()&; //(1)
template<typename U> const U& checked_cast()const; //(1)
template<typename U> U&& checked_cast()&&; //(2)
template<typename U> bool instanceof()const noexcept; //(3)
```

1. Same as `static_cast<U&>(*this)` or `static_cast<const U&>(*this)` respectively.
2. Same as `static_cast<U&&>(*this)`.
3. If `*this` owns an object, and the dynamic type of that object is derived from `U`, then returns true. Otherwise returns false.

(1),(2) only participate in overload resolution if `std::is_base_of_v<T,U>` is true.

(3) only participates in overload resolution if `std::is_base_of_v<T,U>` or `std::is_base_of_v<U,T>` is true.

### Deduction Guides

```c++
template<typename T> PolymorphicWrapper(const T&) -> PolymorphicWrapper<T>;
template<typename T> PolymorphicWrapper(T&&) -> PolymorphicWrapper<T>;
template<typename T,typename... Args> explicit PolymorphicWrapper(std::in_place_type_t<T>,Args&&...) -> PolymorphicWrapper<T>;
```

Provided to deduce `T` from the type of the initial value. 

## Specialization std::common_type<PolymorphicWrapper>
in namespace `std`

```c++
template<typename T,typename U> struct common_type<PolymorphicWrapper<T>,PolymorphicWrapper<U>>;
```

If `T*` and `U*` have a mutual common type `S*`, and `S` is a polymorphic class type with a public virtual destructor,
 then defines a member `type` which is `PolymorphicWrapper<S>`.
 Otherwise, there is no member `type`.
 