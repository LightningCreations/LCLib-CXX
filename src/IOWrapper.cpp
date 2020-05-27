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

    FileInputStream::FileInputStream(const char* name): file{std::fopen(name,"rb")}{}

    FileInputStream::FileInputStream(const std::filesystem::path& p)
        : FileInputStream{p.u8string()}{}

    FileInputStream::~FileInputStream(){
        if(file)
            std::fclose(file);
    }

    std::size_t FileInputStream::read(void* v,std::size_t sz){
        return std::fread(v,1,sz,file);
    }
    int FileInputStream::read(){
        unsigned char val;
        if(!std::fread(&val,1,1,file))
            return -1;
        else
            return val&0xff;
    }

    [[nodiscard]] bool FileInputStream::check_error()const noexcept{
        return std::ferror(file)||std::feof(file);
    }

    void FileInputStream::clear_error() noexcept{
        std::clearerr(file);
    }

    FileInputStream::FileInputStream(FileInputStream&& rhs) : file{std::exchange(rhs.file,nullptr)}{}
    FileInputStream& FileInputStream::operator=(FileInputStream&& rhs) {
        std::swap(file,rhs.file);
        return *this;
    }

    FilterInputStream::FilterInputStream(InputStream& in):wrapped{&in}{}
    std::size_t FilterInputStream::read(void* v,std::size_t sz){
        return wrapped->read(v,sz);
    }
    int FilterInputStream::read(){
        return wrapped->read();
    }
    [[nodiscard]] bool FilterInputStream::check_error()const noexcept{
        return wrapped->check_error();
    }
    void FilterInputStream::clear_error()noexcept{
        return wrapped->clear_error();
    }
    OutputStream::operator bool()const noexcept{
        return !this->check_error();
    }
    bool OutputStream::operator!()const noexcept{
        return this->check_error();
    }
    void OutputStream::flush(){}
    
    FileOutputStream::FileOutputStream(FILE* file):file{file}{}
    FileOutputStream::FileOutputStream(const char* name):file{std::fopen(name,"wb")}{}
    FileOutputStream::FileOutputStream(const char* name,open_append_t):file{std::fopen(name,"ab")}{}
    std::size_t FileOutputStream::write(const void* v,std::size_t sz){
        return std::fwrite(v,1,sz,file);
    }
    void FileOutputStream::write(std::uint8_t u){
        std::fwrite(&u,1,1,file);
    }
    [[nodiscard]] bool FileOutputStream::check_error()const noexcept{
        return std::ferror(file)||std::feof(file);
    }
    void FileOutputStream::clear_error()noexcept{
        std::clearerr(file);
    }
    void FileOutputStream::flush(){
        std::fflush(file);
    }
    FileOutputStream::~FileOutputStream(){
        if(file)
            std::fclose(file);
    }
    FileOutputStream::FileOutputStream(FileOutputStream&& stream)noexcept:file{std::exchange(stream.file,nullptr)}{}
    FileOutputStream& FileOutputStream::operator=(FileOutputStream&& stream)noexcept{
        std::swap(file,stream.file);
        return *this;
    }
    FilterOutputStream::FilterOutputStream(OutputStream& wrapped):wrapped{&wrapped}{}
    std::size_t FilterOutputStream::write(const void* v,std::size_t sz){
        return wrapped->write(v,sz);
    }
    void FilterOutputStream::write(std::uint8_t byte){
        return wrapped->write(byte);
    }
    [[nodiscard]] bool FilterOutputStream::check_error()const noexcept{
        return wrapped->check_error();
    }
    void FilterOutputStream::clear_error()noexcept{
        wrapped->clear_error();
    }
    void FilterOutputStream::flush(){
        wrapped->flush();
    }

    DataInputStream::DataInputStream(InputStream& in,endianness e):FilterInputStream(in),byteorder{e}{}
    endianness DataInputStream::getEndianness()const{
        return this->byteorder;
    }
    void DataInputStream::setEndianness(endianness e){
        this->byteorder = e;
    }
    void DataInputStream::readFully(void* v,std::size_t sz){
        if(this->read(v,sz)!=sz)
            throw EOFException{"File reached EOF before finishing readFully"};
    }
    uint8_t DataInputStream::readSingle(){
        uint8_t byte{};
        readFully(&byte,1);
        return byte;
    }

    DataOutputStream::DataOutputStream(OutputStream& out,endianness byteorder):FilterOutputStream{out},byteorder{byteorder}{}
    endianness DataOutputStream::getEndianness()const noexcept{
        return this->byteorder;
    }
    void DataOutputStream::setEndianness(endianness endian)noexcept{
        this->byteorder = endian;
    }
}
