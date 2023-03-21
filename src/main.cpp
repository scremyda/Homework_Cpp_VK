#include "ErrorProcessing.h"
#include "ParsedInformationProcessing.h"


int main ( int argc , char * argv[] )
{
    if( checkCommandLineArguments( argc ) )
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

    if ( checkErrorsWithFilesLines( parseResult, rightArgvOrderVector ) )
    {
        return 1;
    }

    std::vector<std::vector<std::string>> parsedDataVectors;
    copyDataFromMapToVectors( parseResult, parsedDataVectors );

    sortParsedDataVectors( parsedDataVectors );

    printParsedDataVectors( parsedDataVectors );

    return 0;
}
