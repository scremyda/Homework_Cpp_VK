#include "/home/scremyda/work/c++/homework/first_hw_main/Homework_Cpp_VK/headers/ErrorProcessing.h"


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

    std::vector<std::string> rightArgvOrderVector;
    if ( rightArgvOrder( argv, rightArgvOrderVector ) ) 
    {
        return 1;
    }

    Parser parseResult;

    int errorWithNumberOfBasicsFileLines = parseResult.parseBasicsFile( rightArgvOrderVector, parseResult );
    if ( checkErrorWithNumberOfFileLines( errorWithNumberOfBasicsFileLines ) ) 
    {
        return 1;
    }

    int errorWithNumberOfRatingsFileLines = parseResult.parseRatingsFile( rightArgvOrderVector, parseResult );
    if ( checkErrorWithNumberOfFileLines( errorWithNumberOfRatingsFileLines ) ) 
    {
        return 1;
    }
    
    int errorWithNumberOfAkasFileLines = parseResult.parseAkasFile( rightArgvOrderVector, parseResult );
    if ( checkErrorWithNumberOfFileLines( errorWithNumberOfAkasFileLines ) ) 
    {
        return 1;
    }

    std::vector<std::vector<std::string>> parsedDataVectors;
    copyDataFromMapToVectors( parseResult, parsedDataVectors );

    sortParsedDataVectors( parsedDataVectors );

    printParsedDataVectors( parsedDataVectors );

    return 0;
}