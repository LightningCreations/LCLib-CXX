# Time Library

In header `<lclib-c++/Time.hpp>`

Provides types to serialize `std::chrono` types to LCLib Binary IO Compatible forms. 

## Deprecation of Uses

Note: Prior versions of LCLib-C++ provided these as a standard interface similar to the `java.time` classes Duration and Instant. 
However, review of the usefulness as a primary timekeeping library has shown that the utilities of `std::chrono` 
 are usually sufficient, and sometimes optimal.
 LCLib-C++ deprecates the use of this library except when necessary for serialization. 


## Library Synopsis

```cpp
namespace lightningcreations::lclib::time{
    typedef /*unspecified*/ seconds_t;
    typedef /*unspecified*/ nanos_t;
    typedef /*unspecified*/ chrono_val_t;
    typedef std::duration<seconds_t> seconds_duration;
    typedef /*unspecified*/ chrono_duration;
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

### seconds_t

`seconds_t` is defined as an unspecified type which satisfies *IntegerType*,
 and can exactly represent all values in the range `[`

