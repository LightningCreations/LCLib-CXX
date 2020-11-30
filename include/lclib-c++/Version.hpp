//
// Created by chorm on 2020-05-28.
//

#ifndef LCLIB_VERSION_HPP
#define LCLIB_VERSION_HPP

#include <lclib-c++/Config.hpp>
#include <cstdint>
#include <tuple>
#include <stdexcept>
#include <functional>

#ifdef LCLIB_CXX_HAS_20_SPACESHIP
#include <compare>
#endif

namespace lclib::io{
    class DataInputStream;
    class DataOutputStream;
}

namespace lclib::version{
    struct Version{
    public:
        uint8_t _major;
        uint8_t _minor;
    public:
        Version()noexcept=default;
        constexpr Version(uint16_t major,uint8_t minor):
            _major{static_cast<uint8_t>(major-1)},_minor{minor}{
            if(major==0||major>256)throw std::domain_error{"major must be between 1 and 256"};
        }
        constexpr Version(const Version&)noexcept=default;
        constexpr Version& operator=(const Version&)noexcept=default;
        [[nodiscard]] constexpr uint16_t getMajorVersion()const noexcept{
            return static_cast<uint16_t>(_major)+1;
        }
        [[nodiscard]] constexpr uint8_t getMinorVersion()const noexcept{
            return _minor;
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
        LCLIB_CXX_API friend io::DataInputStream& operator>>(io::DataInputStream&,Version&);
        LCLIB_CXX_API friend io::DataOutputStream& operator<<(io::DataOutputStream&,const Version&);
    };

    namespace _detail{
        const unsigned char seed{};
    }
}

namespace std{
    template<> struct hash<lclib::version::Version>{
        constexpr hash()=default;

        std::size_t operator()(lclib::version::Version v)const {
            return std::hash<const unsigned char*>{}(&lclib::version::_detail::seed)^(static_cast<std::size_t>(v._major)*257+v._minor);
        }
    }
}

#endif //LCLIB_VERSION_HPP
