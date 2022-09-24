#ifndef WIKIAPP_HTTPCLIENT_H
#define WIKIAPP_HTTPCLIENT_H

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <iomanip>
#include <boost/beast/ssl/ssl_stream.hpp>

namespace asio = boost::asio;
namespace http = boost::beast::http;


class HttpClient {
public:

    // boost asio hhtp get request function that get full url and return response in json in std::string
    std::string getRequestHttp(const std::string& url) {
        boost::beast::error_code ec;

        boost::asio::io_context ioc;
        boost::asio::ip::tcp::resolver resolver(ioc);
        boost::beast::tcp_stream stream(ioc);

        std::string host = url.substr(0, url.find('/'));
        std::string target = url.substr(url.find('/'));

        auto const results = resolver.resolve(host, "http", ec);

        stream.connect(results);

        http::request<http::string_body> req{ http::verb::get, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(stream, req);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);

        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        switch(res.base().result_int()) {
            case 301:
                this->getRequestHttps(
                        res.base()["Location"].to_string().substr(res.base()["Location"].to_string().find("r")));
                break;
            case 200:
                break;
            default:
                std::cout << "Unexpected HTTP status " << res.result_int() << "\n";
                stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
                return "";
        }


        stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

        if (ec && ec != boost::beast::errc::not_connected) {
            std::cerr << ec << '\n';
            throw boost::beast::system_error{ ec };
        }

        return boost::beast::buffers_to_string(res.body().data());
    }


    // boost asio https get request gunction that get url and return response body in json
    std::string getRequestHttps(const std::string& url) {
        boost::beast::error_code ec;

        boost::asio::io_context ioc;
        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
        boost::asio::ip::tcp::resolver resolver(ioc);
        boost::beast::ssl_stream<boost::beast::tcp_stream> stream(ioc, ctx);

        std::string host = url.substr(0, url.find('/'));
        std::string target = url.substr(url.find('/'));

        auto const results = resolver.resolve(host, "https", ec);

        stream.next_layer().connect(results);

        stream.handshake(boost::asio::ssl::stream_base::client, ec);

        http::request<http::string_body> req{ http::verb::get, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        http::write(stream, req);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);

        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);


        switch(res.base().result_int()) {
            case 301:
                this->getRequestHttps(
                        res.base()["Location"].to_string().substr(res.base()["Location"].to_string().find("r")));
                break;
            case 200:
                break;
            default:
                std::cout << "Unexpected HTTP status " << res.result_int() << "\n";
                stream.shutdown();
                return "";
        }

        stream.shutdown();

        if (ec && ec != boost::beast::errc::not_connected) {
            std::cerr << ec << '\n';
            throw boost::beast::system_error{ ec };
        }

        return boost::beast::buffers_to_string(res.body().data());
    }

    // url encoder converts characters into a format that can be transmitted over the Internet
    std::string urlEncode(const std::string &value) {
        std::ostringstream escaped;
        escaped.fill('0');
        escaped << std::hex;

        for (char c : value) {
            // Keep alphanumeric and other accepted characters intact
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                escaped << c;
                continue;
            }

            // Any other characters are percent-encoded
            escaped << std::uppercase;
            escaped << '%' << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c));
            escaped << std::nouppercase;
        }

        return escaped.str();
    }
};
#endif //WIKIAPP_HTTPCLIENT_H
