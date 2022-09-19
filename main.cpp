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

//    if (platform == "linux") {
//        system("xdg-open https://ru.wikipedia.org/w/index.php?curid=11099");
//
//    }
//    else if (platform == "windows") {
//        system("start https://ru.wikipedia.org/w/index.php?curid=11099");
//    }
//    else if ()

#include <iomanip>
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
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}


#include "client.h"
#include "JsonParser.h"

int main() {

    std::string searchQuery(urlEncode("\"Лэти\""));
    std::string leti("ru.wikipedia.org/w/api.php?action=query&format=json&list=search&utf8=&srsearch=");
    leti += searchQuery;
    Client client;

    std::string response = client.getResponseHttps(leti);

    std::cout << "Titles and PageIds:" << std::endl;
    JsonParser jsonParser(response);
    std::vector<std::pair<std::string, std::string>> data = jsonParser.getTitlesAndPageIds();
    for (std::pair<std::string, std::string> &pair : data) {
        std::cout << "Title: " << pair.first << ", pageId: " << pair.second << std::endl;
    }

    return 0;
}