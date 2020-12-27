//
// Created by chorm on 2020-05-28.
//

#include <lclib-c++/Version.hpp>
#include <lclib-c++/IOWrapper.hpp>

namespace lclib::version{

    io::DataInputStream& operator>>(io::DataInputStream& in,Version& v){
        if constexpr(sizeof(Version)==2)
            in.read(&v,sizeof(Version));
        else
            in >> v.major >> v.minor;
        return in;
    }
    io::DataOutputStream& operator<<(io::DataOutputStream& out,const Version& v){
        if constexpr(sizeof(Version)==2)
            out.write(&v,2);
        else
            out << v.major << v.minor;

        return out;
    }
}