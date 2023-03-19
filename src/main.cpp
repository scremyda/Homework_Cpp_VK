#include "/home/scremyda/work/c++/homework/first_hw/headers/ErrorProcessing.h"

int main ( int argc , char * argv[] )
{
    if( CheckCommandLneArguments( argc ) )
    {
        return 1;
    }
    for ( size_t i = 0; i < 3; ++i )
    {
        if( CheckFileOpen( argv[i] ) )
        {
            return 1;
        }
    }

    std::vector<std::string> RightArgvOrderVector;
    if ( RightArgvOrder( argv, RightArgvOrderVector ) ) 
    {
        return 1;
    }

    Parser ParseResult;

    int ErrorWithNumberOfBasicsFileLines = ParseResult.ParseBasicsFile( RightArgvOrderVector, ParseResult );
    if ( CheckErrorWithNumberOfFileLines( ErrorWithNumberOfBasicsFileLines ) ) 
    {
        return 1;
    }

    int ErrorWithNumberOfRatingsFileLines = ParseResult.ParseRatingsFile( RightArgvOrderVector, ParseResult );
    if ( CheckErrorWithNumberOfFileLines( ErrorWithNumberOfRatingsFileLines ) ) 
    {
        return 1;
    }
    
    int ErrorWithNumberOfAkasFileLines = ParseResult.ParseAkasFile( RightArgvOrderVector, ParseResult );
    if ( CheckErrorWithNumberOfFileLines( ErrorWithNumberOfAkasFileLines ) ) 
    {
        return 1;
    }

    std::vector<std::vector<std::string>> ParsedDataVectors;
    CopyDataFromMapToVectors( ParseResult, ParsedDataVectors );

    SortParsedDataVectors( ParsedDataVectors );

    PrintParsedDataVectors( ParsedDataVectors );

    return 0;
}