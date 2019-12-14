//
// Created by chorm on 2019-11-08.
//

#ifndef LCLIB_IOWRAPPER_HPP
#define LCLIB_IOWRAPPER_HPP

#include <cstddef>
#include <cstdio>
#include <string>
#include <filesystem>

namespace lightningcreations::lclib::io{
    std::size_t eof(-1);
    class InputStream{
    public:
        static void* operator new(std::size_t)=delete;
        static void operator delete(void*)=delete;
        InputStream(const InputStream&)=delete;
        InputStream& operator=(const InputStream&)=default;
    protected:
        ~InputStream()=default;
    public:
        InputStream()=default;
        InputStream(InputStream&&)=default;
        InputStream& operator=(InputStream&&)=default;
        [[nodiscard]] virtual bool check_error()const noexcept=0;
        virtual void clear_error()noexcept=0;
        virtual std::size_t read(void*,std::size_t)=0;
        virtual int read()=0;
        explicit operator bool()const noexcept;
        bool operator!()const noexcept;
    };


    class NullDeviceInputStream{
    public:
        [[nodiscard]] bool check_error()const noexcept;
        void clear_error()noexcept;
        std::size_t read(void*,std::size_t);
        int read();
    };

    class ZeroDeviceInputStream{
        [[nodiscard]] bool check_error()const noexcept;
        void clear_error()noexcept;
        std::size_t read(void*,std::size_t);
        int read();
    };

    class FileInputStream{
    private:
        FILE* file;
    public:
        explicit FileInputStream(FILE* file);
        explicit FileInputStream(const char* file);
        template<typename CharTraits,typename Allocator> explicit FileInputStream(const std::basic_string<char,CharTraits,Allocator>& name)
            :FileInputStream(name.c_str()){}
        explicit FileInputStream(const std::filesystem::path&);
        FileInputStream(FileInputStream&&);
        FileInputStream& operator=(FileInputStream&&);
        ~FileInputStream();
        std::size_t read(void*,std::size_t);
        int read();
        [[nodiscard]] bool check_error()const noexcept;
        void clear_error()noexcept;
    };
    class FilterInputStream{
    private:
        InputStream* wrapped;
    public:
        FilterInputStream(InputStream&);
        std::size_t read(void*,std::size_t);
        int read();
        [[nodiscard]] bool check_error()const noexcept;
        void clear_error();
    };

    class OutputStream{
    public:
        static void* operator new(std::size_t)=delete;
        static void operator delete(void*)=delete;
        OutputStream(const OutputStream&)=delete;
        OutputStream& operator=(const OutputStream&)=default;
    protected:
        ~OutputStream()=default;
        OutputStream()=default;
    public:
        OutputStream(OutputStream&&)=default;
        OutputStream& operator=()
    };
}

#endif //LCLIB_IOWRAPPER_HPP
