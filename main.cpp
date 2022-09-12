#include <iostream>

//#if defined(_WIN32)
//#define PLATFORM_NAME "windows" // Windows
//#elif defined(_WIN64)
//#define PLATFORM_NAME "windows" // Windows
//#elif defined(__CYGWIN__) && !defined(_WIN32)
//#define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
//#elif defined(__linux__)
//#define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
//#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
//    #include <TargetConditionals.h>
//    #if TARGET_IPHONE_SIMULATOR == 1
//        #define PLATFORM_NAME "ios" // Apple iOS
//    #elif TARGET_OS_IPHONE == 1
//        #define PLATFORM_NAME "ios" // Apple iOS
//    #elif TARGET_OS_MAC == 1
//        #define PLATFORM_NAME "osx" // Apple OSX
//    #endif
//#else
//    #define PLATFORM_NAME NULL
//#endif
//const std::string platform = PLATFORM_NAME;

#include "client.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Client client;
    std::cout << client.getResponse("google.com");

//    if (platform == "linux") {
//        system("xdg-open https://ru.wikipedia.org/w/index.php?curid=11099");
//
//    }
//    else if (platform == "windows") {
//        system("start https://ru.wikipedia.org/w/index.php?curid=11099");
//    }
//    else if ()

    return 0;
}
