# Version
Header: `<lclib-c++/Version.hpp>`
In namespace `lclib::version`

## Synopsis

```c++
struct Version{
public:
    Version()noexcept=default;
    constexpr Version(uint16_t major,uint8_t minor);
    constexpr Version(const Version&)=default;
    constexpr Version& operator=(const Version&)=default;
    
    [[nodiscard]] constexpr uint16_t getMajorVersion()const noexcept;
    [[nodiscard]] constexpr uint8_t  getMinorVersion()const noexcept;

    
    constexpr friend bool operator <=>(const Version& v1,const Version& v2) noexcept = default; // LCLIB_CXX_HAS_20_SPACESHIP
    
    constexpr friend bool operator ==(const Version& v1,const Version& v2)noexcept;
    constexpr friend bool operator < (const Version& v1,const Version& v2)noexcept;
    constexpr friend bool operator > (const Version& v1,const Version& v2)noexcept;
    constexpr friend bool operator <=(const Version& v1,const Version& v2)noexcept;
    constexpr friend bool operator >=(const Version& v1,const Version& v2)noexcept;
    constexpr friend bool operator !=(const Version& v1,const Version& v2)noexcept;
    
};
lclib::io::DataInputStream& operator>>(lclib::io::DataInputStream& in,Version& v);
lclib::io::DataOutputStream& operator<<(lclib::io::DataOutputStream& out,const Version& v);
```

### Class Version

The Version class represents a binary version, in of the logical form `<major>.<minor>`.

The class Version shall be *Trivial*, shall be a *Literal Type*,
 and a *Standard Layout Type*. 

The class Version shall be *EqualityComparable* and *LessThanComparable*. 

### Constructors and Assignment Operators

```c++
Version()noexcept=default; // (1)
constexpr Version(uint16_t major,uint8_t minor); // (2)
constexpr Version(const Version& rhs)=default; // (3)
constexpr Version& operator=(const Version& rhs)=default; // (4)
```

1. When used to *value-initialize* an object of type `Version`, shall be equivalent to the constructor call Version{1,0}. 
 When used to *default-initialize* an object of type `Version`, the resulting version is indeterminate. _Note - Version may be value-initialized in a core constant expression - End Note_
2. Constructs a version in the from the given major and minor components. Major shall be between 1 and 256 inclusive, or an exception of a type which matches a handler of type `std::domain_error` is thrown. 
3. Copy-constructs from the version represented by rhs.
4. Copy-assigns from the version represented by rhs. 

 
Default-initializing an object of type `Version` with static or thread storage duration,
 shall be equivalent to *value-initializing* such an object. 

#### Relational Operators

```c++
constexpr friend bool operator ==(const Version& v1,const Version& v2)noexcept; // (1)
constexpr friend bool operator < (const Version& v1,const Version& v2)noexcept; // (2)
constexpr friend bool operator > (const Version& v1,const Version& v2)noexcept; // (3)
constexpr friend bool operator <=(const Version& v1,const Version& v2)noexcept; // (4)
constexpr friend bool operator >=(const Version& v1,const Version& v2)noexcept; // (5)
constexpr friend bool operator !=(const Version& v1,const Version& v2)noexcept; // (6)

constexpr friend std::strong_ordering operator <=>(const Version& v1,const Version& v2) noexcept = default; // (7)
```

1. Tests if v1 is equal to v2. Two versions v1 and v2 are equal if they have the same major components, and the same minor components.
2. Tests if v1 is less than v2. A version v1 is less than a version v2,
 if the major component of v1 is less than the major component of v2,
  or the versions have the same major components, and the minor component of v1
  is less than the minor component of v2.
3. Tests if v1 is greater than v2. A version v1 is greater than a version v2,
 if v2 is less than v1.
4. Tests if v1 is less than or equal to v2. A version v1 is greater than a version v2,
 if v1 is less than v2, or v1 is equal to v2. 
5. Tests if v1 is greater than or equal to v2. A version v1 is greater than a version v2,
    if v1 is greater than v2, or v1 is equal to v2. 
6. Tests if v1 is not equal to v2. v1!=v2 is an equivalent expression to !(v1==v2)
7. Performs three-way comparison between versions v1 and v2.
    Post:
    * If the expression `v1<=>v2` selects (7), 

It is unspecified if (7) is available, except that (7) shall be available if including `<lclib-c++/Config.hpp>`0
 defines the macro `LCLIB_CXX_HAS_20_SPACESHIP`. 
If (7) is available, than the Version class shall have *strong-structural ordering*. 


### Field Accessors

```c++
[[nodiscard]] constexpr std::uint16_t getMajorVersion()const noexcept; // (1)
[[nodiscard]] constexpr std::uint8_t getMinorVersion()const noexcept; // (2)
```

1. Gets the major component of the version, IE. the `M` in `Version{M,m}`
2. Gets the minor component of the version, IE. the `m` in `Version{M,m}`


### Stream Operators

```c++
lclib::io::DataInputStream& operator<<(lclib::io::DataInputStream& in,Version& v); // (1)
lclib::io::DataOutputStream& operator>>(lclib::io::DataOutputStream& out,const Version& v); // (2)
```

1. Reads a version from the binary stream, encoded as specified for the `version` type in [[LCS 4]](https://lightningcreations.github.io/LCS/publications/LCS4). 
2. Writes the version to the binary stream, encoded as specified for the `version` type in [[LCS 4]](https://lightningcreations.github.io/LCS/publications/LCS4).

If (1) throws an exception, v is left in a valid but unspecified state. 

