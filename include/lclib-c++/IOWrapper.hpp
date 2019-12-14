//
// Created by chorm on 2019-11-08.
//

#ifndef LCLIB_IOWRAPPER_HPP
#define LCLIB_IOWRAPPER_HPP

#include <cstddef>
#include <cstdio>
#include <string>
#include <filesystem>
#include <stdexcept>
#include <type_traits>
#include <lclib-c++/TypeTraits.hpp>
#include <array>

#if __cplusplus>201703L
# ifdef __has_include
#  if __has_include(<span>)
#    include <span>
#    define LCLIB_CXX_HAS_SPAN
#  endif
# endif
#endif

namespace lightningcreations::lclib::io{
    std::size_t eof(-1);
    class IOException:public std::runtime_error{
    public:
        using runtime_error::runtime_error;
    };
    class EOFException:public IOException{
    public:
        using IOException::IOException;
    };
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
        template<typename Byte,std::size_t N,typename=
            std::enable_if_t<lightningcreations::lclib::type_traits::is_byte_v<Byte>&&!std::is_const_v<Byte>>>
            std::size_t read_bytes(Byte(&arr)[N]){
                return read(arr,N);
            }
        template<typename Byte,std::size_t N,typename=
            std::enable_if_t<lightningcreations::lclib::type_traits::is_byte_v<Byte>&&!std::is_const_v<Byte>>>
            std::size_t read_bytes(std::array<Byte,N>& arr){
                return read(arr.data(),N);
            }
#ifdef LCLIB_CXX_HAS_SPAN
        template<typename Byte,std::ptrdiff_t N,typename=std::enable_if_t<lightningcreations::lclib::type_traits::is_byte_v<Byte>&&!std::is_const_v<Byte>>>
        std::size_t read_bytes(std::span<Byte,N> span){
            return read(span.data(),span.size());
        }
#endif
    };


    class NullDeviceInputStream:public InputStream{
    public:
        [[nodiscard]] bool check_error()const noexcept;
        void clear_error()noexcept;
        std::size_t read(void*,std::size_t);
        int read();
    };

    class ZeroDeviceInputStream:public InputStream{
        [[nodiscard]] bool check_error()const noexcept;
        void clear_error()noexcept;
        std::size_t read(void*,std::size_t);
        int read();
    };

    class FileInputStream:public InputStream{
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
    class FilterInputStream:public InputStream{
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
        OutputStream& operator=(OutputStream&&)=default;
        virtual std::size_t write(const void*,std::size_t)=0;
        virtual void write(std::uint8_t)=0;
        [[nodiscard]] virtual bool check_error()const noexcept =0;
        virtual void clear_error()noexcept=0;
        operator bool()const noexcept;
        bool operator!()const noexcept;
        virtual void flush();
        template<typename Byte,std::size_t N,typename=std::enable_if_t<lightningcreations::lclib::type_traits::is_byte_v<Byte>>>
            std::size_t write_bytes(const Byte(&arr)[N]){
                return write(arr,N);
            }
        template<typename Byte,std::size_t N,typename=std::enable_if_t<lightningcreations::lclib::type_traits::is_byte_v<Byte>>>
            std::size_t write_bytes(const std::array<Byte,N>& arr){
                return write(arr.data(),N);
            }
#ifdef LCLIB_CXX_HAS_SPAN
        template<typename Byte,std::ptrdiff_t extent,typename=std::enable_if_t<lightningcreations::lclib::type_traits::is_byte_v<Byte>>>
            std::size_t write_bytes(std::span<const Byte,extent> span){
                return write(span.data(),span.size());
            } 
#endif
    };
    struct open_append_t{
        constexpr explicit open_append_t()=default;
    };
    constexpr inline open_append_t open_append{};
    class FileOutputStream:public OutputStream{
    private:
        FILE* file;
    public:
        FileOutputStream(FILE* file);
        explicit FileOutputStream(const char* name):
        explicit FileOutputStream(const char* name,open_append_t);
        template<typename CharTraits,typename Allocator>
            explicit FileOutputStream(const std::basic_string<char,CharTraits,Allocator>& str):FileOutputStream{str.c_str()}{}
        template<typename CharTraits,typename Allocator>
            explicit FileOutputStream(const std::basic_string<char,CharTraits,Allocator>& str,open_append_t): FileOutputStream{str.c_str(),open_append}{}
        FileOutputStream(FileOutputStream&&);
        FileOutputStream& operator=(FileOutputStream&&);
        ~FileOutputStream();
        std::size_t write(const void*,std::size_t);
        void write(std::uint8_t);
        [[nodiscard]] bool check_error()const noexcept;
        void clear_error()noexcept;
        void flush();
    };
    class FilterOutputStream:public OutputStream{
    private:
        OutputStream* wrapped;
    public:
        FilterOutputStream(OutputStream&);
        std::size_t write(const void*,std::size_t);
        void write(std::uint8_t);
        [[nodiscard] bool check_error()const noexcept;
        void clear_error()noexcept;
        void flush();
    };
    
    enum class endianness{
        big = 1,
        little = 2
    };
    class DataInputStream:public FilterInputStream{
    private:
        endianness byteorder;
    public:
        explicit DataInputStream(InputStream&,endianness=endianness::big);
        void setEndianness(endianness);
        void readFully(void*,std::size_t);
        uint8_t readSingle();
        uint8_t read_u8();
        int8_t read_i8();
        int16_t read_i16();
        uint16_t read_u16();
        int32_t read_i32();
        uint32_t read_u32();
        int64_t read_i64();
        
    };
}

#endif //LCLIB_IOWRAPPER_HPP
