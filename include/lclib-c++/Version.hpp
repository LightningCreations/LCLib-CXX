//
// Created by chorm on 2020-05-28.
//

#ifndef LCLIB_VERSION_HPP
#define LCLIB_VERSION_HPP

#include <lclib-c++/Config.hpp>
#include <cstdint>
#include <tuple>

#ifdef LCLIB_CXX_HAS_20_SPACESHIP
#include <compare>
#endif

namespace lclib::io{
    struct DataInputStream;
    struct DataOutputStream;
}

namespace lclib::version{
    struct Version{
    public:
        uint8_t major;
        uint8_t minor;
        Version()noexcept=default;
        constexpr Version(uint16_t major,uint8_t minor) noexcept:
            major{static_cast<uint8_t>(major-1)},minor{minor}{}
        constexpr Version(const Version&)noexcept=default;
        constexpr Version& operator=(const Version&)noexcept=default;
        [[nodiscard]] constexpr uint16_t getMajorVersion()const{
            return static_cast<uint16_t>(major)+1;
        }
        [[nodiscard]] constexpr uint8_t getMinorVersion()const{
            return minor;
        }
#ifdef LCLIB_CXX_HAS_20_SPACESHIP
        constexpr auto operator<=>(const Version&)const noexcept =default;
        constexpr bool operator==(const Version&)const noexcept = default;
#else
        constexpr bool operator<(const Version& v)const noexcept{
            return std::tie(this->major,this->minor)<std::tie(v.major,v.minor);
        }
        constexpr bool operator==(const Version& v)const noexcept{
            return std::tie(this->major,this->minor)==std::tie(v.major,v.minor);
        }
        constexpr bool operator!=(const Version& v)const noexcept{
            return std::tie(this->major,this->minor)!=std::tie(v.major,v.minor);
        }
        constexpr bool operator>(const Version& v)const noexcept{
            return std::tie(this->major,this->minor)>std::tie(v.major,v.minor);
        }
        constexpr bool operator<=(const Version& v)const noexcept{
            return std::tie(this->major,this->minor)<=std::tie(v.major,v.minor);
        }
        constexpr bool operator>=(const Version& v)const noexcept{
            return std::tie(this->major,this->minor)>=std::tie(v.major,v.minor);
        }
#endif
// Commented out because the implementation managed to segfault clang
        friend io::DataInputStream& operator>>(io::DataInputStream&,Version&);
        friend io::DataOutputStream& operator<<(io::DataOutputStream&,const Version&);
    };
}

#endif //LCLIB_VERSION_HPP
