#ifndef LCLIB_CXX_TIME_HPP_2019_10_29__16_08
#define LCLIB_CXX_TIME_HPP_2019_10_29__16_08

#include <chrono>
#include <cstdint>

#include <lclib-c++/TypeTraits.hpp>


namespace lightningcreations::lclib::time{
    using instant_clock = std::chrono::system_clock;
    using seconds_t = std::int64_t;
    using nanos_t = unsigned;
    using chrono_val_t = std::int64_t;

    using seconds_duration = std::chrono::duration<seconds_t,std::ratio<1>>;
    using nanos_duration = std::chrono::duration<chrono_val_t,std::nano>;

    struct Duration{
    private:
        seconds_t seconds;
        nanos_t nanos;
    public:

        Duration()=default;
        ~Duration()=default;
        constexpr explicit Duration(seconds_t s,nanos_t nanos=0):seconds{s},nanos{nanos}{

        }
        constexpr Duration(const seconds_duration& dur):seconds{dur.count()},nanos{}{}

    };


}

namespace std{
    template<> struct numeric_limits<lightningcreations::lclib::time::Duration>{
        constexpr static bool is_specialized{true};
        constexpr static bool is_signed{true};
        constexpr static bool is_integer{false};

    };
}

#endif