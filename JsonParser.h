#ifndef WIKIAPP_JSONPARSER_H
#define WIKIAPP_JSONPARSER_H

#include <vector>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class JsonParser {
private:
    std::string json_;
    std::vector<std::pair<std::string, std::string>> data_;

    void parseTitlesAndPageIdsFromJson();
public:
    JsonParser() = delete;
    explicit JsonParser(const std::string &json) : json_(json) {
        parseTitlesAndPageIdsFromJson();
    }
    std::vector<std::string> getTitles();
    std::vector<std::string> getPageIds();
    std::vector<std::pair<std::string, std::string>> getTitlesAndPageIds();
};


void JsonParser::parseTitlesAndPageIdsFromJson() {
    std::stringstream jsonEncoded(json_);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);

    if (root.empty())
        return;

    for (boost::property_tree::ptree::value_type &search : root.get_child("query").get_child("search")) {
        auto title = search.second.get<std::string>("title");
        auto pageId = search.second.get<std::string>("pageid");
        data_.emplace_back(title, pageId);
    }

}

std::vector<std::string> JsonParser::getTitles() {
    std::vector<std::string> titles;
    for (std::pair<std::string, std::string> &pair: data_) {
        titles.push_back(pair.first);
    }
    return titles;
}

std::vector<std::string> JsonParser::getPageIds() {
    std::vector<std::string> pageIds;
    for (std::pair<std::string, std::string> &pair: data_) {
        pageIds.push_back(pair.second);
    }
    return pageIds;
}

std::vector<std::pair<std::string, std::string>> JsonParser::getTitlesAndPageIds() {
    return data_;
}

#endif //WIKIAPP_JSONPARSER_H
