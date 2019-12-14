//
// Created by chorm on 2019-11-08.
//
#include <lclib-c++/IOWrapper.hpp>
#include <cstring>
namespace lightningcreations::lclib::io{
    InputStream::operator bool() const noexcept{
        return !this->check_error();
    }
    bool InputStream::operator!()const noexcept{
        return this->check_error();
    }


    bool NullDeviceInputStream::check_error() const noexcept {
        return false;
    }
    void NullDeviceInputStream::clear_error() noexcept {}
    std::size_t NullDeviceInputStream::read(void *, std::size_t) {
        return eof;
    }
    int NullDeviceInputStream::read(){
        return -1;
    }

    bool ZeroDeviceInputStream::check_error() const noexcept {
        return false;
    }
    void ZeroDeviceInputStream::clear_error() noexcept {}

    std::size_t ZeroDeviceInputStream::read(void* out,std::size_t size){
        std::memset(out,0,size);
        return size;
    }

    int ZeroDeviceInputStream::read() {
        return 0;
    }

    FileInputStream::FileInputStream(FILE *file) : file{file} {

    }

}
