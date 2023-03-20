#include "headers/ErrorProcessing.h"

int main ( int argc , char * argv[] )
{
    if( checkCommandLneArguments( argc ) )
    {
        return 1;
    }
    for ( size_t i = 0; i < 3; ++i )
    {
        if( checkFileOpen( argv[i] ) )
        {
            return 1;
        }
    }

    std::vector<std::string> RightArgvOrderVector;
    if ( rightArgvOrder( argv, RightArgvOrderVector ) ) 
    {
        return 1;
    }

    Parser ParseResult;

    int ErrorWithNumberOfBasicsFileLines = ParseResult.parseBasicsFile( RightArgvOrderVector, ParseResult );
    if ( checkErrorWithNumberOfFileLines( ErrorWithNumberOfBasicsFileLines ) ) 
    {
        return 1;
    }

    int ErrorWithNumberOfRatingsFileLines = ParseResult.parseRatingsFile( RightArgvOrderVector, ParseResult );
    if ( checkErrorWithNumberOfFileLines( ErrorWithNumberOfRatingsFileLines ) ) 
    {
        return 1;
    }
    
    int ErrorWithNumberOfAkasFileLines = ParseResult.parseAkasFile( RightArgvOrderVector, ParseResult );
    if ( checkErrorWithNumberOfFileLines( ErrorWithNumberOfAkasFileLines ) ) 
    {
        return 1;
    }

    std::vector<std::vector<std::string>> ParsedDataVectors;
    copyDataFromMapToVectors( ParseResult, ParsedDataVectors );

    sortParsedDataVectors( ParsedDataVectors );

    printParsedDataVectors( ParsedDataVectors );

    return 0;
}