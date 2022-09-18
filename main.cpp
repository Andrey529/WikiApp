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

#include "client.h"
#include "JsonParser.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string leti("ru.wikipedia.org/w/api.php?action=query&format=json&list=search&srsearch=%22%D0%9B%D1%8D%D1%82%D0%B8%22&utf8=");
    Client client;

    std::string response = client.getResponse("example.com/");
    std::cout << response << std::endl;


    std::string res("{\"batchcomplete\":\"\",\"continue\":{\"sroffset\":10,\"continue\":\"-||\"},\"query\":{\"searchinfo\":{\"totalhits\":492},\"search\":[{\"ns\":0,\"title\":\"Санкт-Петербургский государственный электротехнический университет\",\"pageid\":11099,\"size\":56610,\"wordcount\":2101,\"snippet\":\"Санкт-Петербургский государственный электротехнический университет «<span class=\\\"searchmatch\\\">ЛЭТИ</span>» имени В. И. Ульянова (Ленина) — российское техническое высшее учебное заведение\",\"timestamp\":\"2022-09-15T17:22:38Z\"},{\"ns\":0,\"title\":\"Буревестник (баскетбольный клуб, Ленинград)\",\"pageid\":2235164,\"size\":5406,\"wordcount\":204,\"snippet\":\"мужская студенческая команда Ленинграда выступала в высшей лиге под названием <span class=\\\"searchmatch\\\">ЛЭТИ</span> (1951-52 гг.), «Наука» (1953-54 гг.) и, наконец, снова «Буревестник» (1955-61\",\"timestamp\":\"2022-04-17T23:30:41Z\"},{\"ns\":0,\"title\":\"Кафедра микро- и наноэлектроники Санкт-Петербургского государственного электротехнического университета\",\"pageid\":4619191,\"size\":33211,\"wordcount\":2143,\"snippet\":\"наноэлектроники СПбГЭТУ «<span class=\\\"searchmatch\\\">ЛЭТИ</span>» — кафедра факультета электроники Санкт-Петербургского государственного электротехнического университета «<span class=\\\"searchmatch\\\">ЛЭТИ</span>» им. В. И. Ульянова\",\"timestamp\":\"2021-06-08T04:28:01Z\"},{\"ns\":0,\"title\":\"Богородицкий, Николай Петрович\",\"pageid\":4619043,\"size\":19512,\"wordcount\":1066,\"snippet\":\"электротехнических материалов <span class=\\\"searchmatch\\\">ЛЭТИ</span> имени В. И. Ульянова (Ленина) (в настоящее время кафедра микро- и наноэлектроники). Ректор (1954—1967) <span class=\\\"searchmatch\\\">ЛЭТИ</span>. Один из основателей\",\"timestamp\":\"2022-08-08T18:25:34Z\"},{\"ns\":0,\"title\":\"Институт прикладной астрономии РАН\",\"pageid\":1122180,\"size\":12474,\"wordcount\":561,\"snippet\":\"Институт прикладной астрономии (полное официальное название — «Федеральное государственное бюджетное учреждение науки Институт прикладной астрономии Российской\",\"timestamp\":\"2022-04-03T20:02:14Z\"},{\"ns\":0,\"title\":\"Рубекин, Борис Александрович\",\"pageid\":518362,\"size\":4382,\"wordcount\":214,\"snippet\":\"города Ленинграда, закончил математический класс. В 1992-м году закончил <span class=\\\"searchmatch\\\">ЛЭТИ</span> (Ленинградский Электротехнический Институт имени Ульянова (Ленина)) по специальности\",\"timestamp\":\"2022-04-26T09:24:36Z\"},{\"ns\":0,\"title\":\"Мемориальный музей А. С. Попова (ЛЭТИ)\",\"pageid\":1664770,\"size\":8716,\"wordcount\":510,\"snippet\":\"Мемориальный музей А. С. Попова (<span class=\\\"searchmatch\\\">ЛЭТИ</span>) — музей А. С. Попова в Санкт-Петербургском государственном электротехническом университете «<span class=\\\"searchmatch\\\">ЛЭТИ</span>» имени В. И. Ульянова (Ленина)\",\"timestamp\":\"2022-07-15T00:45:40Z\"},{\"ns\":0,\"title\":\"Пасынков, Владимир Васильевич\",\"pageid\":4622402,\"size\":14530,\"wordcount\":790,\"snippet\":\"наук (1955), профессор (1959). Кандидат технических наук (1943). Работал в <span class=\\\"searchmatch\\\">ЛЭТИ</span> в качестве ассистента (1940), доцента (1945), профессора (1952—1967 и 1984—2000)\",\"timestamp\":\"2021-04-17T22:38:10Z\"},{\"ns\":0,\"title\":\"Пузанков, Дмитрий Викторович\",\"pageid\":7449364,\"size\":7759,\"wordcount\":295,\"snippet\":\"степени (2001). Родился 3 июля 1944 года в Ленинграде. 1967 год — окончил <span class=\\\"searchmatch\\\">ЛЭТИ</span> по специальности «Математические и счётно-решающие приборы и устройства»\",\"timestamp\":\"2022-07-28T15:16:56Z\"},{\"ns\":0,\"title\":\"Ахутин, Владимир Михайлович\",\"pageid\":4603806,\"size\":35158,\"wordcount\":1741,\"snippet\":\"среды в Санкт-Петербургском государственном электротехническом университете «<span class=\\\"searchmatch\\\">ЛЭТИ</span>» им. В. И. Ульянова (Ленина) (СПбГЭТУ). Более 25-ти лет являлся бессменным\",\"timestamp\":\"2022-06-04T09:34:29Z\"}]}}");

    JsonParser jsonParser(res);
    std::vector<std::pair<std::string, std::string>> data = jsonParser.getTitlesAndPageIds();
    for (std::pair<std::string, std::string> &pair : data) {
        std::cout << "Title: " << pair.first << ", pageId: " << pair.second << std::endl;
    }
    return 0;
}