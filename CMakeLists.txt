cmake_minimum_required(VERSION 3.23)
project(WikiApp)

set(CMAKE_CXX_STANDARD 20)

set(Boost_INCLUDE_DIR /usr/local/include/boost)
set(Boost_LIBRARY_DIR /usr/local/include/boost/libs)

find_package(Boost REQUIRED COMPONENTS thread system)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(OPENSSL_INCLUDE_DIR /usr/local/ssl/include)
set(OPENSSL_CRYPTO_LIBRARY /usr/local/ssl/lib/libcrypto.so)
set(OPENSSL_SSL_LIBRARY /usr/local/ssl/lib/libssl.so)
find_package(OpenSSL REQUIRED)

add_executable(WikiApp main.cpp HttpClient.h JsonParser.h App.h)
target_include_directories(WikiApp PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(WikiApp ${Boost_LIBRARIES} OpenSSL::SSL)