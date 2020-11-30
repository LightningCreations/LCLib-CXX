//
// Created by chorm on 2020-05-28.
//

#include <lclib-c++/Version.hpp>
#include <lclib-c++/IOWrapper.hpp>

namespace lclib::version{
    io::DataInputStream& operator>>(io::DataInputStream& in,Version& v){
        in >> v._major >> v._minor;

        return in;
    }
    io::DataOutputStream& operator<<(io::DataOutputStream& out,const Version& v){
        out << v._major << v._minor;

        return out;
    }
}