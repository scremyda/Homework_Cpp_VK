#include "headers/Parser.h"

int Parser::parseBasicsFile( std::vector<std::string> argv, Parser & ParseResult )
{
    std::ifstream BasicsFileStream( argv[0] );
    std::getline( BasicsFileStream, ParseResult.ParsedLine_ );

    int main_int = std::stoi( argv[3] );
    while ( std::getline( BasicsFileStream, ParseResult.ParsedLine_ ) )
    {
        std::stringstream ParsedStringStream( ParseResult.ParsedLine_ );
        ParseResult.ParsedLineWord_.clear();
        ParseResult.ParsedLineVector_.clear();

        while ( std::getline( ParsedStringStream, ParseResult.ParsedLineWord_, '\t' ) )
        {
            ParseResult.ParsedLineVector_.push_back( ParseResult.ParsedLineWord_ );
        }

        if ( ParseResult.ParsedLineVector_.size() !=  9 ) {
            return 1;
        }

        if ( ParseResult.ParsedLineVector_[7] != "\\N" && ParseResult.ParsedLineVector_[1] == "movie" &&
                ParseResult.ParsedLineVector_[4] == "0" )
        {
            int ParsedNumberOfMovieRating = std::stoi( ParseResult.ParsedLineVector_[7] );
            if ( ParsedNumberOfMovieRating <= main_int )
            {
                ParseResult.ParsedDataMap_[ParseResult.ParsedLineVector_[0]].push_back( ParseResult.
                ParsedLineVector_[7] );
            }
        }
    }
    BasicsFileStream.close();
    return 0;
}

int Parser::parseRatingsFile( std::vector<std::string> argv, Parser & ParseResult )
{
    std::ifstream RatingsFileStream( argv[1] );
    std::getline( RatingsFileStream, ParseResult.ParsedLine_ );

    while (std::getline( RatingsFileStream, ParseResult.ParsedLine_ ) ) {
        std::stringstream ParsedStringStream( ParseResult.ParsedLine_ );
        ParseResult.ParsedLineWord_.clear();
        ParseResult.ParsedLineVector_.clear();

        while ( std::getline( ParsedStringStream, ParseResult.ParsedLineWord_, '\t' ) )
        {
            ParseResult.ParsedLineVector_.push_back( ParseResult.ParsedLineWord_ );
        }

        if ( ParseResult.ParsedLineVector_.size() !=  3 ) {
            return 1;
        }

        int ParsedFilmRating = std::stoi( ParseResult.ParsedLineVector_[2] );
        if ( ParsedFilmRating >= 1000 && ParseResult.ParsedDataMap_.count( ParseResult.
        ParsedLineVector_[0] ) != 0 )
        {
            ParseResult.ParsedDataMap_[ParseResult.ParsedLineVector_[0]].push_back( ParseResult.
            ParsedLineVector_[1] );
        }
        else
        {
            ParseResult.ParsedDataMap_.erase( ParseResult.ParsedLineVector_[0] );
        }
    }
    RatingsFileStream.close();
    return 0;
}

int Parser::parseAkasFile ( std::vector<std::string> argv, Parser & ParseResult )
{
    std::ifstream AkasFileStream( argv[2] );
    std::getline( AkasFileStream, ParseResult.ParsedLine_ );

    while ( std::getline( AkasFileStream, ParseResult.ParsedLine_ ) )
    {
        std::stringstream ParsedStringStream( ParseResult.ParsedLine_ );
        ParseResult.ParsedLineWord_.clear();
        ParseResult.ParsedLineVector_.clear();

        while ( std::getline( ParsedStringStream, ParseResult.ParsedLineWord_, '\t' ) )
        {
            ParseResult.ParsedLineVector_.push_back( ParseResult.ParsedLineWord_ );
        }

        if ( ParseResult.ParsedLineVector_.size() !=  8 ) {
            return 1;
        }

        if ( ParseResult.ParsedDataMap_[ParseResult.ParsedLineVector_[0]].size() == 2 &&
                ParseResult.ParsedDataMap_.count(ParseResult.ParsedLineVector_[0]) != 0 )
        {
            ParseResult.ParsedDataMap_[ParseResult.ParsedLineVector_[0]].push_back( ParseResult.
            ParsedLineVector_[2] );
        }
        if ( ParseResult.ParsedDataMap_[ParseResult.ParsedLineVector_[0]].size() == 3 &&
                ParseResult.ParsedLineVector_[3] == "RU" )
        {
            ParseResult.ParsedDataMap_[ParseResult.ParsedLineVector_[0]].pop_back();
            ParseResult.ParsedDataMap_[ParseResult.ParsedLineVector_[0]].push_back( ParseResult.
            ParsedLineVector_[2] );
        }
        if ( ParseResult.ParsedDataMap_[ParseResult.ParsedLineVector_[0]].size() != 3 )
        {
            ParseResult.ParsedDataMap_.erase( ParseResult.ParsedLineVector_[0] );
        }

    }
    AkasFileStream.close();
    return 0;
}

std::unordered_map<std::string, std::vector<std::string>> Parser::GetMap() const {
    return ParsedDataMap_;
}