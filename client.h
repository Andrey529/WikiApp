#ifndef WIKIAPP_CLIENT_H
#define WIKIAPP_CLIENT_H

#include <boost/beast.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <string>
#include <vector>
#include <iostream>

#include <boost/asio/ssl.hpp>
#include <boost/beast/ssl/ssl_stream.hpp>

namespace asio = boost::asio;

class Client {
public:

//    void getResponse(const std::string &url) {
//        boost::beast::error_code ec;
//
//        asio::io_context context;
//
//        asio::ip::tcp::endpoint endpoint(asio::ip::make_address(url, ec), 80);
//
//        asio::ip::tcp::socket socket(context);
//        socket.connect(endpoint, ec);
//
//        if (!ec) {
//            std::cout << "Connected " << ec.message() << std::endl;
//        }
//        else {
//            std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
//        }
//
//        if (socket.is_open()) {
//            std::string sRequest =
//                    "GET example.com\r\n";
//
//            socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);
//
//            using namespace std::chrono_literals;
//            std::this_thread::sleep_for(400ms);
//
//            size_t bytes = socket.available();
//            std::cout << "Bytes available: " << bytes << std::endl;
//
//            if (bytes > 0) {
//                std::vector<char> vBuffer(bytes);
//                socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);
//
//                for (auto c : vBuffer) {
//                    std::cout << c;
//                }
//            }
//        }
//    }

    // boost asio http get request function
//    std::string getResponse(const std::string& host, const std::string& target) {
//        boost::asio::io_context ioc;
//        boost::asio::ip::tcp::resolver resolver(ioc);
//        boost::beast::tcp_stream stream(ioc);
//
//        auto const results = resolver.resolve(host, "http");
//
//        stream.connect(results);
//
//        namespace http = boost::beast::http;
//
//        http::request<http::string_body> req{ http::verb::get, target, 11 };
//        req.set(http::field::host, host);
//        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
//
//        http::write(stream, req);
//
//        boost::beast::flat_buffer buffer;
//        http::response<http::dynamic_body> res;
//        http::read(stream, buffer, res);
//
//        boost::beast::error_code ec;
//        stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
//
//        if (ec && ec != boost::beast::errc::not_connected)
//            throw boost::beast::system_error{ ec };
//
//        return boost::beast::buffers_to_string(res.body().data());
//    }

    // boost asio hhtp get request function that get full url and return response in json in std::string
    std::string getResponse(const std::string& url) {
        boost::beast::error_code ec;

        boost::asio::io_context ioc;
        boost::asio::ip::tcp::resolver resolver(ioc);
        boost::beast::tcp_stream stream(ioc);
//        boost::beast::ssl_stream<boost::beast::tcp_stream> stream(ioc, boost::asio::ssl::context::sslv23_client);

        std::string host = url.substr(0, url.find('/'));
        std::string target = url.substr(url.find('/'));

        std::cout << "host: " << host << "\ntarget: " << target << '\n';

        auto const results = resolver.resolve(host, "http", ec);

        stream.connect(results);

        namespace http = boost::beast::http;

        http::request<http::string_body> req{ http::verb::get, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(stream, req);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);

        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        std::cout << "data size: " << buffer.data().size() << '\n';


        switch(res.base().result_int()) {
            case 301:
                std::cout << "Status code: " << res.result_int() << "\nRedirecting.....\n";
                this->getResponse(res.base()["Location"].to_string().substr(res.base()["Location"].to_string().find("r")));
                break;
            case 200:
                std::cout << "Status code: " << res.result_int() << '\n' << res << "\n";
                break;
            default:
                std::cout << "Unexpected HTTP status " << res.result_int() << "\n";
                break;
        }


        stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

        if (ec && ec != boost::beast::errc::not_connected) {
            std::cerr << ec << '\n';
            throw boost::beast::system_error{ ec };
        }
        std::cout << "Status code: " << res.result_int() << std::endl;

        return boost::beast::buffers_to_string(res.body().data());
    }



    // boost asio https get request gunction that get url and return response body in json
    std::string getResponseHttps(const std::string& url) {
        boost::beast::error_code ec;

        boost::asio::io_context ioc;
        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
        boost::asio::ip::tcp::resolver resolver(ioc);
//        boost::asio::ssl::stream<asio::ip::tcp::socket> sock(ioc, ctx);
        boost::beast::ssl_stream<boost::beast::tcp_stream> stream(ioc, ctx);

        std::string host = url.substr(0, url.find('/'));
        std::string target = url.substr(url.find('/'));

        std::cout << "host: " << host << "\ntarget: " << target << '\n';

        auto const results = resolver.resolve(host, "https", ec);

        stream.next_layer().connect(results);

        stream.handshake(boost::asio::ssl::stream_base::client, ec);

        namespace http = boost::beast::http;

        http::request<http::string_body> req{ http::verb::get, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(stream, req);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);

        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        std::cout << "data size: " << buffer.data().size() << '\n';


        switch(res.base().result_int()) {
            case 301:
                std::cout << "Status code: " << res.result_int() << "\nRedirecting.....\n";
                this->getResponse(res.base()["Location"].to_string().substr(res.base()["Location"].to_string().find("r")));
                break;
            case 200:
                std::cout << "Status code: " << res.result_int() << '\n' << res << "\n";
                break;
            default:
                std::cout << "Unexpected HTTP status " << res.result_int() << "\n";
                break;
        }


        stream.shutdown(); //socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

        if (ec && ec != boost::beast::errc::not_connected) {
            std::cerr << ec << '\n';
            throw boost::beast::system_error{ ec };
        }
        std::cout << "Status code: " << res.result_int() << std::endl;

        return boost::beast::buffers_to_string(res.body().data());
    }
};
#endif //WIKIAPP_CLIENT_H
