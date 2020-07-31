//
// Created by chorm on 2020-07-30.
//

#ifndef LCLIB_TIME_HPP
#define LCLIB_TIME_HPP

#include <lclib-c++/Config.hpp>

#include <chrono>
#include <ratio>
#include <cstdint>



#if defined(__cpp_lib_chrono)&&__cpp_lib_chrono>201907L
#define LCLIB_CXX_HAS_CXX20_CLOCK
#endif

namespace lclib::time{
    using seconds_t = int64_t;
    using nanos_t = uint32_t;
    using chrono_val_t = int64_t;

    using seconds_duration = std::chrono::duration<seconds_t,std::ratio<1>>;
    using nanos_duration = std::chrono::duration<chrono_val_t,std::nano>;
    using nanos_of_second = std::chrono::duration<nanos_t,std::nano>;
    using chrono_duration = std::chrono::duration<chrono_val_t,std::micro>;


    /// A clock which produces time_points which are suitable for use with
    using instant_clock = std::chrono::system_clock;

    template<typename Duration> using instant_time = std::chrono::time_point<instant_clock,Duration>;
}

#endif //LCLIB_TIME_HPP
