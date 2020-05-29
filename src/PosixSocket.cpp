//
// Created by chorm on 2020-05-27.
//

#include <lclib-c++/Sockets.hpp>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <system_error>

namespace lclib::socket{
    namespace{
        struct TcpInputStream final:InputStream{
        private:
            int sock;
        public:
            explicit TcpInputStream(int sock):sock{sock}{}
            [[nodiscard]] bool check_error()const noexcept override{
                return false;
            }
            void clear_error()noexcept override{}
            std::size_t read(void* v,std::size_t sz) override{
                if(auto x{::read(sock,v,sz)};x<0)
                    throw std::system_error(std::make_error_code(static_cast<std::errc>(errno)));
                else
                    return x;

            }
            int read() override{
                uint8_t t;
                if(read(&t,1)==0)
                    return -1;
                else
                    return t;
            }
        };
        struct TcpOutputStream final:OutputStream{
        private:
            int sock;
        public:
            explicit TcpOutputStream(int sock):sock{sock}{}
            std::size_t write(const void* v,std::size_t sz) override{
                if(auto x{::write(sock,v,sz)};x<0)
                    throw std::system_error(std::make_error_code(static_cast<std::errc>(errno)));
                else
                    return x;
            }
            virtual void write(std::uint8_t b) override{
                write(&b,1);
            }
            [[nodiscard]] bool check_error()const noexcept override{
                return false;
            }
            void clear_error()noexcept override{

            }
        };
    }
    namespace _detail{
        struct TcpImpl{
            int sock;
            TcpInputStream in;
            TcpOutputStream out;
            struct addrinfo* addr;
            TcpImpl(int sock):addr{nullptr},sock{sock},in{sock},out{sock}{}
            TcpImpl():TcpImpl{::socket(AF_INET,SOCK_STREAM,0)}{
                if(sock<0)
                    throw std::system_error(std::make_error_code(static_cast<std::errc>(errno)));
            }
            TcpImpl(TcpImpl&& out):sock{std::exchange(out.sock,0)},addr{std::exchange(out.addr,nullptr)},
                in{std::move(out.in)},out{std::move(out.out)}{}
            ~TcpImpl(){
                if(sock)
                    ::close(sock);
                if(addr)
                    ::freeaddrinfo(addr);
            }
            void listen(const std::string& name,uint16_t port){
                if(getaddrinfo(name.c_str(),nullptr,nullptr,&addr)<0)
                    throw std::system_error(std::make_error_code(static_cast<std::errc>(errno)));
                reinterpret_cast<sockaddr_in*>(addr->ai_addr)->sin_port = port;
                ::bind(sock,addr->ai_addr,addr->ai_addrlen);
                ::listen(sock,256);
            }

            void connect(const std::string& name,uint16_t port){
                if(getaddrinfo(name.c_str(),nullptr,nullptr,&addr)<0)
                    throw std::system_error(std::make_error_code(static_cast<std::errc>(errno)));
                reinterpret_cast<sockaddr_in*>(addr->ai_addr)->sin_port = port;
                ::connect(sock,addr->ai_addr,addr->ai_addrlen);
            }
            TcpImpl accept(){
                auto _sock{::accept(this->sock,nullptr,nullptr)};
                if(_sock<0)
                    throw std::system_error(std::make_error_code(static_cast<std::errc>(errno)));
                return TcpImpl{_sock};
            }
        };
    }
    TcpSocket::TcpSocket(std::unique_ptr<_detail::TcpImpl> ptr):sock{std::move(ptr)}{}
    TcpSocket::TcpSocket(const std::string& addr,uint16_t port):sock{std::make_unique<_detail::TcpImpl>()}{
        sock->connect(addr,port);
    }
    TcpSocket::~TcpSocket()=default;
    InputStream& TcpSocket::getInputStream(){
        return sock->in;
    }
    OutputStream& TcpSocket::getOutputStream(){
        return sock->out;
    }
    void TcpSocket::close(){
        sock.reset();
    }

    TcpServer::TcpServer():sock{std::make_unique<_detail::TcpImpl>()}{}
    TcpServer::~TcpServer()=default;
    void TcpServer::listen(const std::string& addr,uint16_t port){
        sock->listen(addr,port);
    }
    void TcpServer::listen(uint16_t port){
        sock->listen("0.0.0.0",port);
    }
    TcpSocket TcpServer::accept(){
        return TcpSocket(std::make_unique<_detail::TcpImpl>(sock->accept()));
    }
    void TcpServer::close(){
        sock.reset();
    }
}
