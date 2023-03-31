#include <iostream>
#include "Parser.h"


int Parser::parseBasicsFile( std::vector<std::string> argv, Parser & parseResult )
{
    std::ifstream basicsFileStream( argv[0] );
    if ( !basicsFileStream.is_open() ) {
        std::cerr << "Не удалось открыть файл " << argv[2] << " для чтения" << std::endl;
        return 1;
    }

    std::getline( basicsFileStream, parseResult.parsedLine_ );

    int numberFromUser = std::stoi( argv[3] );
    while ( std::getline( basicsFileStream, parseResult.parsedLine_ ) )
    {
        std::stringstream parsedStringStream( parseResult.parsedLine_ );
        parseResult.parsedLineWord_.clear();
        parseResult.parsedLineVector_.clear();

        while ( std::getline( parsedStringStream, parseResult.parsedLineWord_, '\t' ) )
        {
            parseResult.parsedLineVector_.push_back( parseResult.parsedLineWord_ );
        }

        if ( parseResult.parsedLineVector_.size() !=  9 ) {
            return 2;
        }

        if ( parseResult.parsedLineVector_[7] != "\\N" && parseResult.parsedLineVector_[1] == "movie" &&
                parseResult.parsedLineVector_[4] == "0" )
        {
            int parsedNumberOfMovieRating = std::stoi( parseResult.parsedLineVector_[7] );
            if ( parsedNumberOfMovieRating <= numberFromUser )
            {
                parseResult.parsedDataMap_[parseResult.parsedLineVector_[0]].push_back( parseResult.
                parsedLineVector_[7] );
            }
        }
    }
    return 0;
}

int Parser::parseRatingsFile( std::vector<std::string> argv, Parser & parseResult )
{
    std::ifstream ratingsFileStream( argv[1] );
    if ( !ratingsFileStream.is_open() ) {
        std::cerr << "Не удалось открыть файл " << argv[2] << " для чтения" << std::endl;
        return 1;
    }

    std::getline( ratingsFileStream, parseResult.parsedLine_ );

    while ( std::getline( ratingsFileStream, parseResult.parsedLine_ ) ) {
        std::stringstream parsedStringStream( parseResult.parsedLine_ );
        parseResult.parsedLineWord_.clear();
        parseResult.parsedLineVector_.clear();

        while ( std::getline( parsedStringStream, parseResult.parsedLineWord_, '\t' ) )
        {
            parseResult.parsedLineVector_.push_back( parseResult.parsedLineWord_ );
        }

        if ( parseResult.parsedLineVector_.size() !=  3 ) {
            return 2;
        }

        int parsedFilmRating = std::stoi( parseResult.parsedLineVector_[2] );
        if ( parsedFilmRating >= 1000 && parseResult.parsedDataMap_.count( parseResult.
        parsedLineVector_[0] ) != 0 )
        {
            parseResult.parsedDataMap_[parseResult.parsedLineVector_[0]].push_back( parseResult.
            parsedLineVector_[1] );
        }
        else
        {
            parseResult.parsedDataMap_.erase( parseResult.parsedLineVector_[0] );
        }
    }
    return 0;
}

int Parser::parseAkasFile ( std::vector<std::string> argv, Parser & parseResult )
{
    std::ifstream akasFileStream( argv[2] );
    if ( !akasFileStream.is_open() ) {
        std::cerr << "Не удалось открыть файл " << argv[2] << " для чтения" << std::endl;
        return 1;
    }

    std::getline( akasFileStream, parseResult.parsedLine_ );

    while ( std::getline( akasFileStream, parseResult.parsedLine_ ) )
    {
        std::stringstream parsedStringStream( parseResult.parsedLine_ );
        parseResult.parsedLineWord_.clear();
        parseResult.parsedLineVector_.clear();

        while ( std::getline( parsedStringStream, parseResult.parsedLineWord_, '\t' ) )
        {
            parseResult.parsedLineVector_.push_back( parseResult.parsedLineWord_ );
        }

        if ( parseResult.parsedLineVector_.size() !=  8 ) {
            return 2;
        }

        if ( parseResult.parsedDataMap_[parseResult.parsedLineVector_[0]].size() == 2 &&
                parseResult.parsedDataMap_.count(parseResult.parsedLineVector_[0]) != 0 )
        {
            parseResult.parsedDataMap_[parseResult.parsedLineVector_[0]].push_back( parseResult.
            parsedLineVector_[2] );
        }
        if ( parseResult.parsedDataMap_[parseResult.parsedLineVector_[0]].size() == 3 &&
                parseResult.parsedLineVector_[3] == "RU" )
        {
            parseResult.parsedDataMap_[parseResult.parsedLineVector_[0]].pop_back();
            parseResult.parsedDataMap_[parseResult.parsedLineVector_[0]].push_back( parseResult.
            parsedLineVector_[2] );
        }
        if ( parseResult.parsedDataMap_[parseResult.parsedLineVector_[0]].size() != 3 )
        {
            parseResult.parsedDataMap_.erase( parseResult.parsedLineVector_[0] );
        }

    }
    return 0;
}

std::unordered_map<std::string, std::vector<std::string>> Parser::GetMap() const 
{
    return parsedDataMap_;
}
