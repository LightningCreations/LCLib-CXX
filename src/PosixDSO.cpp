//
// Created by chorm on 2020-05-28.
//

#include <lclib-c++/Dynamic.hpp>

#include <dlfcn.h>

using namespace std::string_literals;

namespace lclib::dynamic{
    void* DynamicLibrary::find_sym(const char* name){
        return dlsym(this->handle,name);
    }
    DynamicLibrary::DynamicLibrary(const std::filesystem::path& p):handle{dlopen(p.c_str(),0)}{
        if(!handle)
            throw std::runtime_error("Loading Error: "s + dlerror());
    }
    DynamicLibrary::~DynamicLibrary(){
        if(handle)
            dlclose(handle);
    }
    DynamicLibrary::DynamicLibrary(DynamicLibrary&& rhs)noexcept:handle{std::exchange(rhs.handle,nullptr)}{}
    DynamicLibrary& DynamicLibrary::operator=(DynamicLibrary rhs)noexcept{
        std::swap(this->handle,rhs.handle);
        return *this;
    }
}
