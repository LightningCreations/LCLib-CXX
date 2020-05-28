//
// Created by chorm on 2020-05-28.
//

#ifndef LCLIB_DYNAMIC_HPP
#define LCLIB_DYNAMIC_HPP

#include <lclib-c++/Config.hpp>
#include <filesystem>
#include <stdexcept>

namespace lightningcreations::lclib::dynamic{
    struct DynamicLibrary{
    private:
        void* handle;
        void* find_sym(const char* name);
    public:
        DynamicLibrary(const std::filesystem::path&);
        ~DynamicLibrary();
        DynamicLibrary(DynamicLibrary&&)noexcept;
        DynamicLibrary& operator=(DynamicLibrary)noexcept;
        DynamicLibrary(const DynamicLibrary&)=delete;
        DynamicLibrary& operator=(const DynamicLibrary&)=delete;
        template<typename T,typename CharTraits,typename Allocator> T& get(const std::basic_string<char,CharTraits,Allocator>& name){
            if(void* sym = find_sym(name.c_str());sym)
                return *(T*)sym;
            else
                throw std::runtime_error{"Dynamic Library does not contain the named symbol (or the symbol is mapped to the null address)"};
        }
    };
}

#endif //LCLIB_DYNAMIC_HPP
