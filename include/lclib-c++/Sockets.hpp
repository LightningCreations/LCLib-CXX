//
// Created by chorm on 2020-05-27.
//

#ifndef LCLIB_SOCKETS_HPP
#define LCLIB_SOCKETS_HPP

#include <memory>
#include <lclib-c++/IOWrapper.hpp>

namespace lclib::socket{
    using io::InputStream;
    using io::OutputStream;
    namespace _detail{
        struct TcpImpl;
    }
    class TcpSocket{
    private:
        std::unique_ptr<_detail::TcpImpl> sock;
        TcpSocket(std::unique_ptr<_detail::TcpImpl>);
        friend class TcpServer;
    public:
        TcpSocket(const std::string& addr,uint16_t port);
        ~TcpSocket();
        InputStream& getInputStream();
        OutputStream& getOutputStream();
        void close();
    };

    class TcpServer{
    private:
        std::unique_ptr<_detail::TcpImpl> sock;
    public:
        TcpServer();
        ~TcpServer();
        void listen(const std::string& addr,uint16_t port);
        void listen(uint16_t port);
        TcpSocket accept();
        void close();
    };
}

#endif //LCLIB_SOCKETS_HPP
