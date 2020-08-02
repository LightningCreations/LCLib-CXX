//
// Created by chorm on 2020-07-30.
//

#ifndef LCLIB_TIME_HPP
#define LCLIB_TIME_HPP

#include <lclib-c++/Config.hpp>
#include <lclib-c++/TypeTraits.hpp>

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


    /// A clock which produces time_points which are suitable for use with Instant
    using instant_clock = std::chrono::system_clock;

    template<typename duration> using instant_time = std::chrono::time_point<instant_clock,duration>;



#ifdef LCLIB_CXX_HAS_CXX20_CLOCK
    namespace _detail{
        template<typename Clock,decltype(std::clock_cast<instant_clock>(std::declval<Clock::time_point>()))* =nullptr>
            auto detect_instant_clock_expr(const Clock&) -> std::true_type;
            auto detect_instant_clock_expr(...) -> std::false_type;

        template<typename Clock> using detect_instant_clock = decltype(detect_instant_clock_expr(std::declval<Clock>()));
    }
    template<typename Clock> struct is_instant_clock : _detail::detect_instant_clock<Clock>{};
#else
    template<typename Clock> struct is_instant_clock : std::false_type{};
    template<> struct is_instant_clock<instant_clock> : std::true_type{};
#endif

    template<typename Clock> constexpr inline bool is_instant_clock_v = is_instant_clock<Clock>::value;

    template<typename Duration,typename Clock,
        std::enable_if_t<lclib::type_traits::is_specialization_v<std::chrono::duration,Duration>>* =nullptr,
        std::enable_if_t<is_instant_clock_v<Clock>>* =nullptr> instant_time<Duration> as_instant_time(const std::chrono::time_point<Clock,Duration>& tp){
#ifdef LCLIB_CXX_HAS_CXX20_CLOCK
            return std::chrono::clock_cast<instant_clock>(tp);
#else
            return tp;
#endif
        }


}

#endif //LCLIB_TIME_HPP
