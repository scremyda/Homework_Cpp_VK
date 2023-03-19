#pragma once

#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>

class Parser {
public:
    int ParseBasicsFile( std::vector<std::string> argv, Parser & ParseResult );

    int ParseRatingsFile( std::vector<std::string> argv, Parser & ParseResult );

    int ParseAkasFile ( std::vector<std::string> argv, Parser & ParseResult );

    std::unordered_map<std::string, std::vector<std::string>> GetMap() const;

private:
    std::unordered_map<std::string, std::vector<std::string>> ParsedDataMap_;
    std::string ParsedLine_;
    std::vector<std::string> ParsedLineVector_;
    std::string ParsedLineWord_;
};

