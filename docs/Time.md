# Time Library

In header `<lclib-c++/Time.hpp>`

Provides types to serialize `std::chrono` types to LCLib Binary IO Compatible forms. 

## Deprecation of Uses

Note: Prior versions of LCLib-C++ provided these as a standard interface similar to the `java.time` classes Duration and Instant. 
However, review of the usefulness as a primary timekeeping library has shown that the utilities of `std::chrono` are usually sufficient, and sometimes optimal.
 LCLib-C++ deprecates the use of this library for serializing `std::chrono`. 


## Library Synopsis

```cpp

#define LCLIB_CXX20_CLOCK /*unspecified*/

namespace lightningcreations::lclib::time{
    typedef /*unspecified*/ seconds_t;
    typedef /*unspecified*/ nanos_t;
    typedef /*unspecified*/ chrono_val_t;
    typedef std::chrono::duration<seconds_t> seconds_duration;
    typedef std::chrono::duration<chrono_val_t,/*unspecified*/> chrono_duration;
    
    typedef /*see below*/ instant_clock;     
    typedef std::chrono::time_point<instant_clock,chrono_duration> instant_time;
    typedef std::chrono::time_point<instant_clock,seconds_t> instant_seconds;    

    enum class ChronoUnit{
        HOURS,
        MINUTES,
        SECONDS,
        //optional
        MILISECONDS,
        MICROSECONDS,
        NANOSECONDS,
        /*unspecified*/
    };
    class Duration;
    class Instant;
}
namespace std{
    template<> struct numeric_limits<Duration>;
}
```

### LCLIB_CXX20_CLOCK

Optional.
If defined, the implementation supports the enhanced features of the C++20 Chrono Utilities

### seconds_t

`seconds_t` is defined as an unspecified type which satisfies *IntegerType*,
 and can exactly represent all values in the range `[-31556889864421200,31556889864421199]`.
 
 Note: The type is permitted to exactly represent values outside this range.
 
### nanos_t

`nanos_t` is defined as an unspecified type which satisfies *UnsignedIntegerType*,
 and can exactly represent all values in the range `[0,1000000000)`

### chrono_val_t

`chrono_val_t` is defined as an unspecified type which satisfies *IntegerType*,
 and be able to exactly represent all values that `int64_t` can represent. 
 
### seconds_duration

`seconds_duration` is a specialization of `std::chrono::duration` which can validly represent all valid Durations to exactly seconds precision

### chrono_duration

`chrono_duration` is a specialization of `std::chrono::duration` which can exactly represent all valid Durations to 
 at least seconds precision. 

The period of `chrono_duration` may be any ratio, that is at most the unit value (`1`).

### instant_clock

If `LCLIB_CXX20_CLOCK` is not defined by the implementation,
 defined to be exactly `std::chrono::system_clock`. 
 If the epoch of this clock is not defined by the C++ implementation to be the unix epoch,
 the behavior of any *clock sensative* methods is undefined.
 
If `LCLIB_CXX20_CLOCK` is defined by the implementation,
 defined to be an unspecified type which satisfies the requirements of *Clock*
 for which the epoch of the clock is the unix epoch.
The clock shall satisfy the following requirements, given a is a value of type `std::chrono::time_point<instant_clock,Duration>`,
 and b is a value of type `std::chrono::time_point<std::chrono::system_clock,Duration>`
 and c is a value of type `std::chrono::time-point<std::chrono::utc_clock,Duration>` 
 for some Duration that is a specialization of std::chrono::duration:
* The expression `std::chrono::clock_time_conversion<std::chrono::system_clock>{}(a)` shall be well formed
* The expression `std::chrono::clock_time_conversion<instant_clock>{}(b)` shall be well formed
* The expression `std::chrono::clock_time_conversion<std::chrono::utc_clock>{}(a)` shall be ill-formed
* The expression `std::chrono::clock_time_conversion<instant_clock>{}(c)` shall be ill-formed

(These requirements imply that `clock_cast` is valid to and from instant_clock for all clock types that have a conversion from `std::chrono::system_clock`
 or `std::chrono::utc_clock`, including those that have both).

It is unspecified whether or not `instant_clock::now()` can throw exceptions.
 If it cannot, than `instant_clock` satisfies the requirements of *TrivialClock*.


In either requirement,
 both `chrono_duration` and `seconds_duration` shall be constructable from `instant_clock::duration`. 



### instant_time and instant_seconds

`instant_time` is defined to alias `std::chrono::time_point<instant_clock,chrono_duration>`

`instant_seconds` is defined to alias `std::chrono::time_point<instant_clock,seconds_duration>`
 
 
### ChronoUnit

ChronoUnit defines a set of constant values which are units of time. 

The HOURS, MINUTES, and SECONDS units are required to be defined,
 and represent the time in hours, minutes, and seconds respectively.
 
Additionally, the units MILISECONDS, MICROSECONDS, and NANOSECONDS may be defined,
 and are required if `chrono_duration` is at least as precise as the time unit. 
If any of these units are defined, then each of these units must be able to convert
 the seconds component of any valid Instant to the unit, and exactly represent the result 
 as a value of type `chrono_val_t`.

The implementation may define additional units, 
 which have an implementation-defined relationship with the seconds unit.
 It is unspecified whether the unit is able convert the seconds component of any valid instant
 to the unit, and if the result can be exactly represented as a value of type `chrono_val_t`. 
 
