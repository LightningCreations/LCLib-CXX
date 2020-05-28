//
// Created by chorm on 2020-05-28.
//

#include <lclib-c++/Version.hpp>
#include <lclib-c++/IOWrapper.hpp>

namespace lightningcreations::lclib::version{
    io::DataInputStream& operator>>(io::DataInputStream& in,Version& v){
        in >> v.major >> v.minor;

        return in;
    }
    io::DataOutputStream& operator<<(io::DataOutputStream& out,const Version& v){
        out << v.major << v.minor;

        return out;
    }
}