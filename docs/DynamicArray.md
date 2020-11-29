# Dynamic Fixed Sized Arrays 

## Header `<lclib-c++/DynamicArray.hpp>` Synopsis

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
}
```

## Class template DynamicArray

### Class Synopsis

```c++
template<typename T,typename Alloc=std::allocator<T>> struct DynamicArray{
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
    DynamicArray(const DynamicArray& arr,const Alloc& alloc);
    DynamicArray(DynamicArray&& arr)noexcept;
    DynamicArray(DynamicArray&& arr,const Alloc& alloc);
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

### Type Definition

The type `lclib::array::DynamicArray` is a dynamic, fixed size, and contiguous, array. 

DynamicArray satisfies *Container*, *AllocatorAwareContainer*, and *ContiguousContainer*. 

If `T` satisfies *EqualityComparable*, then `DynamicArray<T>` satisfies *EqualityComparable*. 
If `T` statisfies *LessThanComparable*, then `DynamicArray<T>` satisfies *LessThanComparable*. 

`T` shall satisfy *Eraseable*, and shall be *CopyInsertible* and *MoveInsertible* using `Alloc`.

`Alloc` shall be *Copy Constructible*, *Move Constructible*, and *Destructible* and shall satisfy the requirements of *Allocator*.
It shall be *Copy Assignable* if `std::allocator_traits<Alloc>::propagate_on_container_copy_assignment` inherits from `std::true_type`, *Move Assignable* if `std::allocator_traits<Alloc>::prooagate_on_container_move_assignment` inherits from `std::true_type`, and *Swappable* if `std::allocator_traits<Alloc>::propagate_on_container_swap` inherits from `std::true_type`.

`std::allocator_traits<Alloc>::value_type` shall be the same type as `T`. 



### Typedefs

```c++
    using element_type = T; (1)
    using reference = T&; (2)
    using const_reference = const T&; (3)
    using pointer = /*see below*/; (4)
    using const_pointer = /*see below*/; (5)
    using iterator = /*unspecified*/; (6)
    using const_iterator = /*unspecified*/; (7)
    using reverse_iterator = /*unspecified*/; (8)
    using const_reverse_iterator = /*unspecified*/; (9)
    using difference_type = /*see below*/; (10)
    using size_type = std::make_unsigned_t<difference_type>; (11)
    using allocator_type = Alloc; (12)
```

1. The element_type of this collection, exactly `T`. 
2. The type of references to elements of the collection, exactly `T&`.
3. The type of constant references to elements of the collection, exactly `const T&`.
4. The type of pointers into the collection. Defined as `typename std::allocator_traits<Alloc>::pointer`
5. The type of constant pointers into the collection. Defined as `typename std::allocator_traits<Alloc>::const_pointer`.
6. An unspecified type which satisfies *LegacyContiguousIterator* and is mutable.
7. An unspecified type which satisfies *LegacyContiguousIterator* and is not mutable.
8. An unspecified type which satifies *LegacyRandomAccessIterator*, is mutable, and iterates over the collection in reverse.
9. An unspecified type which satifies *LegacyRandomAccessIterator*, is not mutable, and iterates over the collection in reverse.
10. An implementation-defined signed integer type which is the difference between two pointers in the array. 
11. The unsigned counterpart of `difference_type`.
12. The Allocator for this collection, exactly `Alloc`.


### Constructors, Destructors, Assignment Operations

```c++
    DynamicArray(const Alloc& alloc=Alloc())noexcept; (1)
    DynamicArray(const DynamicArray& arr); (2)
    DynamicArray(const DynamicArray& arr,const Alloc& alloc); (3)
    DynamicArray(DynamicArray&& rhs)noexcept; (4)
    DynamicArray(DynamicArray&& arr,const Alloc& alloc); (5)
    template<std::size_t N> DynamicArray(const T(&arr)[N],const Alloc& alloc=Alloc()); (6)
    template<std::size_t N> DynamicArray(const std::array<T,N>& arr,const Alloc& alloc=Alloc()); (7)
    DynamicArray(std::initializer_list<T> list,const Alloc& alloc=Alloc()); (8)
    DynamicArray(size_type size,const Alloc& alloc=Alloc()); (9)
    template<typename Container> DynamicArray(Container&& c,const Alloc& alloc=Alloc()); (10)
    template<typename ForwardIter> DynamicArray(ForwardIter begin,FowardIter end,,const Alloc& alloc=Alloc()); (11)
    ~DynamicArray(); (12)

    DynamicArray& operator=(const DynamicArray&); (13)
    DynamicArray& operator=(DynamicArray&&) noexcept(/*see below*/); (14)
```

1. Constructs an empty array with a particular allocator. 
    Post: 
    * `this->begin()==this->end()`,
    * `this->size()==0`
    * `this->get_allocator()==alloc`
2. Copy constructs a new DynamicArray from an existing one. The allocator used is the one returned from `std::allocator_traits<Alloc>::select_on_container_copy_construction()` called on the `arr.get_allocator()`. 
    Post:
    * `(*this)==arr` Given `T` is *EqualityComparable*, and copy construction from `const T&` is *equality-preserving*. 
3. Constructs a new DynamicArray from an existing one, with a specified allocator
    Post:
    * `(*this)==arr` Given `T` is *EqualityComparable*, and copy construction from `const T&` is *equality-preserving*. 
    * `this->get_allocator()==alloc`
4. Move constructs a new Dynamic Array from an existing one. `rhs` is left in a valid, but unspecified state.
5. Constructs a new Dynamic Array from an existing one, using the specified allocator. `rhs` is left in a valid, but unspecified state.
    Post:
    * `this->get_allocator()==alloc`
6. Constructs a new Dynamic Array from a static array. 
    Post:
    * `this->get_allocator()==alloc`
    * `this->size()==N`
    * `std::equal(begin(*this),end(*this),begin(arr),end(arr))` Given `T` is *EqualityComparable*, and copy construction from `const T&` is *equality-preserving*. 
7. Constructs a new Dynamic Array from a static array. 
    Post:
    * `this->get_allocator()==alloc`
    * `this->size()==N`
    * `std::equal(begin(*this),end(*this),begin(arr),end(arr))` Given `T` is *EqualityComparable*, and copy construction from `const T&` is *equality-preserving*.
8. Constructs a new Dynamic Array from an initializer list
    Post:
    * `this->get_allocator()==alloc`
    * `this->size()==il.size()`
    * `std::equal(begin(*this),end(*this),begin(il),end(il))` Given `T` is *EqualityComparable*, and copy construction from `const T&` is *equality-preserving*.
9. Constructs an array of `size` default-constructed elements. If `Alloc` is the primary template of `std::allocator`, it is unspecified whether each element is value-initialized or default-initialized. Otherwise, each element is constructed by `std::allocator_traits<Alloc>::construct(ALLOC,ptr)`, where `ALLOC` is the constructed allocator of `this`, and `ptr` points to the element to be constructed.
   Post:
   * `this->get_allocator()=alloc`
   * `this->size()==size`
10. Constructs a DynamicArray from the elements of a Collection. Only participates in overload resoltion if a call to the function `size`, on `std::forward<Container>(c)`, where the function `size` is looked up in the namespace `std`, and by ADL name resolution, and `T` is constructible from `R`, where `R` is the type obtained by dereferencing an iterator into `c`. 
    Pre:
    * The behaviour is undefined if iterators into `c` do not satisfy *InputIterator*, or `size(c)` elements cannot be reached from `begin(c)`, where both `begin` and `size` are looked up in the namespace `std` and by ADL name resolution. 
    Post:
    * `this->get_allocator()==alloc`
    * `this->size()=size(c)` where `size` is looked up as above. 
    * If `std::decay_t<R>` is exactly `T`, and `R` is not an rvalue reference type, then `std::equal(begin(*this),end(*this),begin(c),end(c))`, given `T` is *EqualityComparable*, and copy-construction from `T` is *equality-preserving*., where begin and end calls for `c` are looked up in the same as `begin` is above. 
11. Constructs a DynamicArray from elements of the range referenced by `begin` and `end`. Only participates in overload resoltion if `ForwardIterator` satisfies *LegacyForwardIterator*, and `T` is constructible from `std::iterator_traits<ForwardIterator>::reference`. 
    Pre:
    * The behaviour is undefined if `[begin,end)` is not a valid range.
    * The behaviour is undefined if `ForwardIterator` does not meet the semantic requirements of *LegacyForwardIterator*. 
    Post:
    * `this->get_allocator()==alloc`
    * `this->size()==std::distance(begin,end)`
    * If `std::decay_t<std::iterator_traits<ForwardIterator>::reference>` is exactly `T`, then `std::equal(this->begin(),this->end(),begin,end)`, given `T` is *EqualityComparable*, and copy-construction from `T` is *equality-preserving*.
12. Destroys each element of the collection and deallocates the backing array using `this->get_allocator()`.
13. Destroys each element of the collection and deallocates the backing array using `this->get_allocator()`, then constructs a new array as though by the constructor call `DynamicArray(rhs,ALLOC)`, where ALLOC is as follows:
    * If `std::allocator_traits<Alloc>::propagate_on_container_copy_assignment` inherits from `std::true_type`, `ALLOC` is `rhs.get_allocator()`.
    * Otherwise, `ALLOC` is `this->get_allocator()`.
    Pre:
    * Construction of elements of rhs shall not have been interrupted by an exception
    Post:
    * Same as the `DynamicArray(rhs,ALLOC)` as specified above.
14. Destroys each element of the collection and deallocates the backing array using `this->get_allocator`, then constructs a new array as though by the constructor call determined below:
    * If `std::allocator_traits<Alloc>::propagate_on_container_move_assignment` inherits from `std::true_type`, `DynamicArray(std::move(rhs))` (that is, no new allocation takes place)
    * Otherwise, `DynamicArray(std::move(rhs),this->get_allocator())`.
In all cases, `rhs` is left in a valid, but unspecified state.
    Pre:
    * Construction of the elements of rhs shall not have been interrupted by an exception, if `std::allocator_traits<Alloc>::propagate_on_container_move_assignment` does not inherit from `std::true_type`
    Post:
    * Same as the constructor call noted above. 

#### Exceptions

1. `noexcept(true)`
2. 3. If the allocation of the underlying array throws, the resulting `DynamicArray` is the same as a default constructed `DynamicArray`. Otherwise, if the construction of any elements throws, all preceeding elements will have be constructed, and the construction of remaining elements is interrupted by the exception. The resulting array may not be used to construct a new array or assign to an existing, if the construction of the array would allocate, and the behaviour of calls to `data()`, `begin()`, `end()` and any other such method is undefined. Destroying such an array is valid, as well as assigning to the result. 
4. `noexcept(true)`.
5. 6. 7. 8. 9. 10. 11. Same as 2 and 3
12. `noexcept(true)`. If any called destructor throws, `std::terminate` is called. It is unspecified whether stack unwinding occurs in this case. 
14. If `std::allocator<Alloc>::propagate_on_container_move_assignment` inherits from `std::true_type`, then the assignment is `noexcept(true)`. In this case, if destroying the elements of the array throws, `std::terminate` is called. It is unspecified whether stack unwinding occurs. Otherwise, has the same exception guarantee as 5. 

### Complexity Guarantees

O(n), where `n` is the size of the constructed collection.

Move construction is O(1).


### swap

```c++
void swap(DynamicArray& rhs) noexcept(/*see below*/); (1)
template<typename T,typename Alloc> void swap(DynamicArray<T,Alloc>& a1,DynamicArray<T,Alloc>& a2) noexcept(/*see below*/); (2) // non-member
```

1. Swaps the arrays, without reallocating either backing array.
    Pre:
    * If `std::allocator_traits<Alloc>::propagate_on_container_swap` does not inherit from `std::true_type`, the behaviour is undefined if `this->get_allocator()==rhs.get_allocator()` is false.
2. Same as `a1.swap(a2)`.

#### Exceptions

`noexcept(true)` if and only if `std::allocator_traits<Alloc>::propagate_on_container_swap` does not inherit from `std::true_type`, or `std::is_nothrow_swappable_v<Alloc>` is true.

If swapping the allocator throws, both arrays are unmodified. 

#### Lookup rules 

Like all non-member functions declared by this library named `swap`, the behaviour is undefined if (2) is called, unless the function name was resolved by argument-dependant lookup. 

## Iterators

```c++
iterator begin()noexcept; (1)
const_iterator begin()const noexcept; (1)
const_iterator cbegin()const noexcept; (2)
iterator end()noexcept; (3)
const_iterator end()const noexcept; (3)
const_iterator cend()const noexcept; (4)
reverse_iterator rbegin()noexcept; (5)
const_reverse_iterator rbegin()const noexcept; (5)
const_reverse_iterator crbegin()const noexcept; (6)
reverse_iterator rend()noexcept; (7)
const_reverse_iterator rend()const noexcept; (7)
const_reverse_iterator crend()const noexcept; (8)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::iterator begin(DynamicArray<T,Alloc>& a) noexcept; (9)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator begin(const DynamicArray<T,Alloc>& a) noexcept; (9)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator cbegin(const DynamicArray<T,Alloc>& a) noexcept; (10)

template<typename T,typename Alloc> DynamicArray<T,Alloc>::iterator end(DynamicArray<T,Alloc>& a) noexcept; (11)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator end(const DynamicArray<T,Alloc>& a) noexcept; (11)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_iterator cend(const DynamicArray<T,Alloc>& a) noexcept; (12)

template<typename T,typename Alloc> DynamicArray<T,Alloc>::reverse_iterator rbegin(DynamicArray<T,Alloc>& a) noexcept; (13)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator rbegin(const DynamicArray<T,Alloc>& a) noexcept; (13)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator crbegin(const DynamicArray<T,Alloc>& a) noexcept; (14)

template<typename T,typename Alloc> DynamicArray<T,Alloc>::reverse_iterator rend(DynamicArray<T,Alloc>& a) noexcept; (15)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator rend(const DynamicArray<T,Alloc>& a) noexcept; (15)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_reverse_iterator crend(const DynamicArray<T,Alloc>& a) noexcept; (16)
```

1. Returns an iterator to the beginning of this collection
2. Same as `this->begin()`, but always returns a `const_iterator`, even for non-const recievers
3. Returns an iterator past-the-end of this collection
4. Same as `this->end()`, but always returns a `const_iterator`, even for non-const recievers.
5. Returns a reverse_iterator to the end element of this collection, that iterates in reverse
6. Same as `this->rbegin()`, but always returns a `const_iterator`, even for non-const recievers.
7. Returns a reverse_iterator before-the-beginning of this collection.
8. Same as `this->rend()`, but always returns a `const_iterator`, even for non-const recievers.
9. Same as `a.begin()`
10. Same as `a.cbegin()`
11. Same as `a.end()`
12. Same as `a.cend()`
13. Same as `a.rbegin()`
14. Same as `a.crbegin()`
15. Same as `a.rend()`
16. Same as `a.crend()`

#### Name resolution

Like all non-member functions with these names defined by this library, the behaviour is undefined if any of the non-member functions defined by this section are called, unless the name of that function was resolved by argument-dependant lookup.

### data

```c++
pointer data()noexcept; (1)
const_pointer data()const noexcept; (2)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::pointer data(DynamicArray<T,Alloc>& a) noexcept; (3)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::const_pointer data(const DynamicArray<T,Alloc>& a) noexcept; (3)
```

1. Returns a pointer to the first element of the allocated array. If the array was default constructed, or allocation for any of the potentially-throwing constructors threw an exception, the result is unspecified and cannot be dereferenced. This function is valid to call on moved-from arrays, the result is unspecified. 
    Pre:
    * this shall not have had the construction of elements interrupted by an exception
    Post:
    * `this->data()+i` is defined for `0<=i<=this->size()`
    * `this->data()+i` can be dereferenced for `0<=i<this->size()`
    * `this->data()+i==&*(this->begin()+i)` for `0<=i<this->size()`. 
2. Same as 1, but returns a constant pointer instead. The behaviour is undefined if the result is used to modify elements of the array, except for `mutable` subobjects of any such elements. 
3. Equivalent to `a.data()`.


#### Name resolution

Like all non-member functions name `data` defined by this library, the behaviour is undefined if 3 is called, unless it was resolved by argument-dependant lookup.

### size

```c++
size_type size()const noexcept; (1)
template<typename T,typename Alloc> DynamicArray<T,Alloc>::size_type size(const DynamicArray<T,Alloc>& a)noexcept; (2)
```

1. Returns the number of elements in the array.
2. Equivalent to `a.size()`

#### Name resolution

Like all non-member functions named `size`, the behaviour is undefined if 2 is called, except if it's name was resolved by argument-dependant lookup.

### Array Indexing

```c++
reference operator[](size_type s)noexcept; (1)
const_reference operator[](size_type s)const noexcept; (1)
```

1. Indexs the DynamicArray, and returns a reference to the element `s`.
    Pre:
    * The behaviour is undefined if `s<this->size()` is false, or construction of the elements of this array was interrupted by an exception thrown by the construction of any element up to or including element `s`. 
    Post:
    * `&a[s]==this->data()+s` is true for `s<this->size()`, if the construction of the elements of the array was not interrupted by an exception.

### get_allocator

```c++
const allocator_type& get_allocator()const;
```

Returns a reference to the allocator used by this collection. 

### Comparison operators

```c++
template<typename T,typename Alloc1,typename Alloc2> /*see below*/ operator<=>(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(/*see below*/); (1)
template<typename T,typename Alloc1,typename Alloc2> bool operator==(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(/*see below*/); (2)
template<typename T,typename Alloc1,typename Alloc2> bool operator!=(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(/*see below*/); (3)
template<typename T,typename Alloc1,typename Alloc2> bool operator<(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(/*see below*/); (4)
template<typename T,typename Alloc1,typename Alloc2> bool operator>(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(/*see below*/); (5)
template<typename T,typename Alloc1,typename Alloc2> bool operator<=(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(/*see below*/); (6)
template<typename T,typename Alloc1,typename Alloc2> bool operator>=(const DynamicArray<T,Alloc1>& a1,const DynamicArray<T,Alloc2>& a2) noexcept(/*see below*/); (7)
```

1. Performs a lexicographical 3-way comparison of the elements of a1 and a2. It is unspecified if this operator is defined, except that it shall be defined if including `<lclib-c++/Config.hpp>` defines the macro `LCLIB_CXX_HAS_20_SPACESHIP`. Does not participate in overload resolution if the expression `t1 <=> t2` is not well-formed, where `t1` and `t2` are const lvalues of type `T`. Otherwise, the result type may be either `std::three_way_compare_result<T>`, or the common comparison category between that type and `std::weak_ordering` (which type the result is, is unspecified). `noexcept(true)` if `t1 <=> t2` is known not to throw any exceptions. 
   Pre:
   * The selected function or builtin comparison operator for `t1 <=> t2` shall be consistent with the relational operators selected for 2 through 7, if the expression is well-formed. No diagnostic is required.
2. Checks two arrays for equality, by checking if each element in a1 and a2 in order are equal. Does not participate in overload resoltion unless the expression `t1 == t2` is well-formed, where `t1` and `t2` are const lvalues of type `T`.  `noexcept(true)` if `t1==t2` is known not to throw any exceptions. 
3. Equivalent to `!(a1==a2)`. Does not participate in overload resolution unless `t1 == t2` is well-formed, where `t1` and `t2` are const lvalues of type `T`. 
4. Performs a lexicographical comparison of the elements of a1 and a2. Does not participate in overload resolution unless the expression `t1 < t2` is well-formed, where `t1` and `t2` are const lvalues of type `T`. `noexcept(true)` if `t1 < t2` is known not to throw any exceptions. 
5. Equivalent to `a2<a1`. Does not participate in overload resolution unless the expression `t1 < t2` is well-formed, where `t1` and `t2` are const lvalues of type `T`.
6. Equivalent to `a1<a2||a1==a2` Does not participate in overload resolution unless both the expression `t1<t2` and the expression `t1==t2` is well-formed, where `t1` and `t2` are const lvalues of type `T`.
7. Equivalent to `a2<a1||a1==a2` Does not participate in overload resolution unless both the expression `t1<t2` and the expression `t1==t2` is well-formed, where `t1` and `t2` are const lvalues of type `T`.

Note:
    * If any of the mentioned expressions would directly invoke a builtin comparison operator involving pointers, all of these comparison operators order those values according to the strict total order imposed by `std::less<T>` and `std::compare_three_way`. 
    * The program is ill-formed if any of these functions are instantiated, and the result of any invoked comparison operator is not implicitly convertible to the result type of the function. 

Pre:
   * The behaviour is undefined if construction of the elements of either a1 or a2 was interrupted.
   * (4-7 only) If the the template instantiation `std::less<T>` selects a user-defined partial or full specialization for `T`, it shall be default constructible, and the expression `std::less<T>{}(t1,t2)` shall be well-formed if `t1<t2` is, where `t1` and `t2` are expressions of type `T`, and those expressions should be consistent (that is, `std::less<T>` shall be true if the comparison is true, and both expressions shall have the same *observable-behavior*). No diagnostic is required
   * (2, 3, 6, and 7 only) If the template instantiation `std::equal_to<T>` selects a user-defined partial or full specialization, it shall be default construcitble, and the expression `std::equal_to<>{}(t1,t2)` shall be well-formed if `t1==t2` and those expressions shall be consistent. No diagnostic is required.
   * (4-7 only) The expression `t1<t2`, if well-formed, shall be false if `t2<t1` is true. No diagnostic is required. 
   * (2, 3, 6, and 7 only) The behaviour is undefined if `T` does not model *EqualityComparable*. 
Post:
   * If `operator<=>` is defined, and the expression `a1 <=> a2` selects (1), then it shall be consistent with all other comparison functions, that is:
      * If the expression `a1==a2` selects (2), `(a1 <=> a2) == 0` shall be true iff `a1==a2` is true.
      * If the expression `a1!=a2` selects (3), `(a1 <=> a2) != 0` shall be true iff `a1!=a2` is true.
      * If the expression `a1<a2` selects (4), `(a1 <=> a2) < 0` shall be true iff `a1<a2` is true.
      * If the expression `a1>a2` selects (5), `(a1 <=> a2) > 0` shall be true iff `a1>a2` is true.
      * If the expression `a1<=a2` selects (6), `(a1 <=> a2) <= 0` shall be true iff `a1<=a2` is true.
      * If the expression `a1>=a2` selects (7), `(a1 <=> a2) >= 0` shall be true iff `a1>=a2` is true.
    * The comparisons defined here shall form a total order of arrays, unless the equivalent

#### Exceptions

All functions defined above are `noexcept(true)` if all of the mentioned expressions for each function are known not to throw exceptions. Otherwise, if the comparison of any element throws an exception, that exception is rethrown by this function. 

### Deduction Guides

```c++
template<typename T,std::size_t N> DynamicArray(const T(&)[N])->DynamicArray<T,std::allocator<T>>;
template<typename T,std::size_t N,typename Alloc> DynamicArray(const T(&)[N],const Alloc&)->DynamicArray<T,Alloc>;
template<typename T,std::size_t N> DynamicArray(const std::array<T,N>&)->DynamicArray<T,std::allocator<T>>;
template<typename T,std::size_t N,typename Alloc> DynamicArray(const std::array<T,N>&,const Alloc&)->DynamicArray<T,Alloc>;
template<typename T> DynamicArray(std::initializer_list<T>) -> DynamicArray<T,std::allocator<T>>;
template<typename T,typename Alloc> DynamicArray(std::initializer_list<T>,const Alloc&)->DynamicArray<T,Alloc>;
```