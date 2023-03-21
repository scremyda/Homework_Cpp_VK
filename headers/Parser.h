#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>


class Parser {
 public:
    int parseBasicsFile( std::vector<std::string> argv, Parser & parseResult );

    int parseRatingsFile( std::vector<std::string> argv, Parser & parseResult );

    int parseAkasFile( std::vector<std::string> argv, Parser & parseResult );

    std::unordered_map<std::string, std::vector<std::string>> GetMap() const;

 private:
    std::unordered_map<std::string, std::vector<std::string>> parsedDataMap_;
    std::string parsedLine_;
    std::vector<std::string> parsedLineVector_;
    std::string parsedLineWord_;
};

