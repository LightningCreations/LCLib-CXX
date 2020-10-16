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
#include <cstring>



#include <lclib-c++/Config.hpp>

#ifdef LCLIB_CXX_HAS_SPAN
# include <span>
#endif


namespace lclib::io{
    inline const std::size_t eof(-1);
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
            std::enable_if_t<lclib::type_traits::is_byte_v<Byte>&&!std::is_const_v<Byte>>>
            std::size_t read_bytes(Byte(&arr)[N]){
                return read(arr,N);
            }
        template<typename Byte,std::size_t N,typename=
            std::enable_if_t<lclib::type_traits::is_byte_v<Byte>&&!std::is_const_v<Byte>>>
            std::size_t read_bytes(std::array<Byte,N>& arr){
                return read(arr.data(),N);
            }
#ifdef LCLIB_CXX_HAS_SPAN
        template<typename Byte,std::ptrdiff_t N,typename=std::enable_if_t<lclib::type_traits::is_byte_v<Byte>&&!std::is_const_v<Byte>>>
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
        std::size_t read(void*,std::size_t) override;
        int read() override;
        [[nodiscard]] bool check_error()const noexcept override;
        void clear_error()noexcept override;
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
        template<typename Byte,std::size_t N,typename=std::enable_if_t<lclib::type_traits::is_byte_v<Byte>>>
            std::size_t write_bytes(const Byte(&arr)[N]){
                return write(arr,N);
            }
        template<typename Byte,std::size_t N,typename=std::enable_if_t<lclib::type_traits::is_byte_v<Byte>>>
            std::size_t write_bytes(const std::array<Byte,N>& arr){
                return write(arr.data(),N);
            }
#ifdef LCLIB_CXX_HAS_SPAN
        template<typename Byte,std::ptrdiff_t extent,typename=std::enable_if_t<lclib::type_traits::is_byte_v<Byte>>>
            std::size_t write_bytes(std::span<const Byte,extent> span){
                return write(span.data(),span.size());
            } 
#endif
    };
    struct open_append_t{
        constexpr explicit open_append_t()=default;
    };
    constexpr inline open_append_t open_append{};
    class FileOutputStream final:public OutputStream{
    private:
        FILE* file;
    public:
        explicit FileOutputStream(FILE* file);
        explicit FileOutputStream(const char* name);
        explicit FileOutputStream(const char* name,open_append_t);
        template<typename CharTraits,typename Allocator>
            explicit FileOutputStream(const std::basic_string<char,CharTraits,Allocator>& str):FileOutputStream{str.c_str()}{}
        template<typename CharTraits,typename Allocator>
            explicit FileOutputStream(const std::basic_string<char,CharTraits,Allocator>& str,open_append_t): FileOutputStream{str.c_str(),open_append}{}
        FileOutputStream(FileOutputStream&&)noexcept;
        FileOutputStream& operator=(FileOutputStream&&)noexcept;
        ~FileOutputStream();
        std::size_t write(const void*,std::size_t) override;
        void write(std::uint8_t) override;
        [[nodiscard]] bool check_error()const noexcept override;
        void clear_error()noexcept override;
        void flush() override;
    };
    class FilterOutputStream:public OutputStream{
    private:
        OutputStream* wrapped;
    protected:
        ~FilterOutputStream()=default;
    public:
        explicit FilterOutputStream(OutputStream&);
        std::size_t write(const void*,std::size_t) override;
        void write(std::uint8_t)override;
        [[nodiscard]] bool check_error()const noexcept override;
        void clear_error()noexcept override;
        void flush() override;
    };
    
    enum class endianness{
        big = LCLIB_CXX_ORDER_BIG,
        little = LCLIB_CXX_ORDER_LITTLE,
        native = LCLIB_CXX_BYTE_ORDER
    };

    constexpr bool operator==(endianness e1,endianness e2){
        return static_cast<int>(e1)==static_cast<int>(e2);
    }

    template<std::size_t N> static void swap_bytes(std::byte(&bytes)[N]){
        for(std::size_t i = 0;i<N/2;i++)
            std::swap(bytes[i],bytes[N-i-1]);
    }

    class DataInputStream final:public FilterInputStream{
    private:
        endianness byteorder;

    public:
        explicit DataInputStream(InputStream&,endianness=endianness::big);
        [[nodiscard]] endianness getEndianness()const;
        void setEndianness(endianness);
        void readFully(void*,std::size_t);
        uint8_t readSingle();
        using FilterInputStream::read;
        template<typename T,
                std::void_t<decltype(std::declval<DataInputStream&>() >> std::declval<T&>()),std::enable_if_t<std::is_default_constructible_v<T>>>* =nullptr>
            T read(){
                T val;
                *this >> val;
                return std::move(val);
            };

        template<typename T,std::enable_if_t<std::is_integral_v<T>||std::is_enum_v<T>||(std::is_floating_point_v<T>&&std::numeric_limits<T>::is_iec559)>* =nullptr>
            DataInputStream& operator>>(T& t){
                if constexpr(std::is_same_v<T,bool>){
                    auto v{this->readSingle()};
                    if(v>1)
                        throw IOException{"Invalid bool value"};
                    t = bool(v);
                }else if constexpr(sizeof(T)==1/* && !std::is_same_v<T,bool> */){
                    reinterpret_cast<uint8_t&>(t) = this->readSingle();
                }else{
                    std::byte storage[sizeof(T)];
                    this->readFully(&storage,sizeof(T));
                    if(this->byteorder!=endianness::native)
                        swap_bytes(storage);
                    memcpy(&t,&storage,sizeof(T));
                }
                return *this;
            }

        template<typename T,std::size_t N,decltype(std::declval<DataInputStream&>() >> std::declval<T&>())* =nullptr>
            DataInputStream& operator>>(T(&arr)[N]){
               if constexpr(sizeof(T)==1&&std::is_trivially_copyable_v<T>){
                   this->readFully(&arr,N);
               }else{
                   for(T& t:arr)
                       (*this) >> arr;
               }
               return *this;
           }

        template<typename CharTraits,typename Allocator>
            DataInputStream& operator>>(std::basic_string<char,CharTraits,Allocator>& str){
                auto size{this->read<uint16_t>()};
                str.resize(size);
                this->readFully(str.data(),size);
                return *this;
            }
    };

    template<typename DInput,typename T,std::void_t<
    std::enable_if_t<std::is_same_v<T,DataInputStream>>,
    decltype(std::declval<DataInputStream&>() >> std::declval<T&>())>* =nullptr>
        DataInputStream&& operator>>(DInput&& stream,T& val){
            return static_cast<DataInputStream&&>(stream >> val);
        }

    class DataOutputStream final: public FilterOutputStream{
    private:
        endianness byteorder;
    public:
        DataOutputStream(OutputStream& out,endianness byteorder=endianness::big);
        endianness getEndianness()const noexcept;
        void setEndianness(endianness endian)noexcept;
        template<typename T,std::enable_if_t<std::is_integral_v<T>||std::is_enum_v<T>||(std::is_floating_point_v<T>&&std::numeric_limits<T>::is_iec559)>* =nullptr>
            DataOutputStream& operator<<(const T& val){
                std::byte storage[sizeof(T)];
                std::memcpy(&storage,&val,sizeof(T));
                if(this->byteorder!=endianness::native)
                    swap_bytes(storage);
                this->write_bytes(storage);
                return *this;
            }
        template<typename CharTraits,typename Allocator>
            DataOutputStream& operator<<(const std::basic_string<char,CharTraits,Allocator>& str){
                auto len{str.size()};
                if(len>std::numeric_limits<uint16_t>::max())
                    len = std::numeric_limits<uint16_t>::max();
                ((*this) << (uint16_t)len);
                this->write(str.data(),len);
                return *this;
            }

        template<typename T,std::size_t N,decltype(std::declval<DataOutputStream&>()<<std::declval<const T&>())* =nullptr>
            DataOutputStream& operator<<(const T(&arr)[N]){
                if constexpr(std::is_trivially_copyable_v<T>&&sizeof(T)==1)
                    this->write(&arr,N);
                else{
                    for(const T& t:arr)
                        (*this) << t;
                }
            }
    };
    template<typename DOutput,typename T,
        std::void_t<std::enable_if_t<std::is_same_v<DOutput,DataOutputStream>>,
        decltype(std::declval<DataOutputStream&>() << std::declval<const T&>())>* =nullptr>
        DataOutputStream&& operator<<(DOutput&& out,const T& t){
            return static_cast<DataOutputStream&&>(out << t);
        }
    
}

#endif //LCLIB_IOWRAPPER_HPP
