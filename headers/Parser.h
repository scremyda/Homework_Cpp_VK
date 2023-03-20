#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>

class Parser {
public:
    int parseBasicsFile( std::vector<std::string> argv, Parser & ParseResult );

    int parseRatingsFile( std::vector<std::string> argv, Parser & ParseResult );

    int parseAkasFile( std::vector<std::string> argv, Parser & ParseResult );

    std::unordered_map<std::string, std::vector<std::string>> GetMap() const;

private:
    std::unordered_map<std::string, std::vector<std::string>> ParsedDataMap_;
    std::string ParsedLine_;
    std::vector<std::string> ParsedLineVector_;
    std::string ParsedLineWord_;
};

