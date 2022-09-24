#ifndef WIKIAPP_APP_H
#define WIKIAPP_APP_H

#include <vector>
#include <string>
#include "HttpClient.h"
#include "JsonParser.h"

class App {
private:
    enum class EXIT_STATUS {
        CONTINUE,
        CONTINUE_WITH_ASKING,
        EXIT
    };

    std::string jsonResponse_;
    std::string searchQuery_;
    std::string urlWithoutSearchQuery_ = "ru.wikipedia.org/w/api.php?action=query&format=json&list=search&utf8=&srsearch=";
    std::vector<std::pair<std::string, std::string>> titlesAndPageIds_;
    EXIT_STATUS exitStatus_ = EXIT_STATUS::CONTINUE_WITH_ASKING;
    int selectedArticle_{};

    void askForSearchQuery();
    void processingRequest();
    void selectDesiredArticle();
    void openSelectedArticle();
    void askWouldLikeToDoAnotherRequest();

public:
    App() = default;
    void Run() {
        while (exitStatus_ != EXIT_STATUS::EXIT) {
            askForSearchQuery();
            processingRequest();
            if (exitStatus_ != EXIT_STATUS::CONTINUE) {
                selectDesiredArticle();
                openSelectedArticle();
                askWouldLikeToDoAnotherRequest();
            }
        }
    }

};

void App::askForSearchQuery() {
    std::cout << "Enter a search query:" << std::endl;
    std::cin >> searchQuery_;
}

void App::processingRequest() {
    HttpClient client;

    std::string encodedSearchQuery = client.urlEncode("\"" + searchQuery_ + "\"");
    jsonResponse_ = client.getRequestHttps(urlWithoutSearchQuery_ + encodedSearchQuery);

    JsonParser jsonParser(jsonResponse_);
    // parse titles and pageIds from jsonResponse_
    titlesAndPageIds_ = jsonParser.getTitlesAndPageIds();

    exitStatus_ = EXIT_STATUS::CONTINUE_WITH_ASKING;

    // if search query is invalid, after parsing titlesAndPageIds will be empty
    if (titlesAndPageIds_.empty()) {
        std::cout << "Enter a valid search query" << std::endl;
        exitStatus_ = EXIT_STATUS::CONTINUE;
    }
}

void App::selectDesiredArticle() {
    int i = 1;
    for (const std::pair<std::string, std::string>& title : titlesAndPageIds_) {
        std::cout << i << ") " << title.first << std::endl;
        i++;
    }
    std::cout << "\nSelect article number: ";
    std::cin >> selectedArticle_;
}

void App::openSelectedArticle() {
    std::string pageId = titlesAndPageIds_[selectedArticle_ - 1].second;
    std::string command("xdg-open https://ru.wikipedia.org/w/index.php?curid=" + pageId);
    system(command.c_str());
}

void App::askWouldLikeToDoAnotherRequest() {
    std::cout << "Would you like to make a request?   (yes/no)" << std::endl;
    std::string answer;
    std::cin >> answer;
    while (answer != "yes" && answer != "no") {
        std::cout << "Enter a valid answer" << std::endl;
        std::cin >> answer;
    }
    if (answer == "yes") {
        exitStatus_ = EXIT_STATUS::CONTINUE_WITH_ASKING;
    }
    else {
        exitStatus_ = EXIT_STATUS::EXIT;
    }

}


#endif //WIKIAPP_APP_H
