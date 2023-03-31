#include "ErrorProcessing.h"
#include "ParsedInformationProcessing.h"


int main ( int argc , char * argv[] )
{
    if( !checkCommandLineArguments( argc ) )
    {
        return 1;
    }

    std::vector<std::string> rightArgvOrderVector;
    if ( rightArgvOrder( argv, rightArgvOrderVector ) )
    {
        return 1;
    }

    Parser parseResult;

    if ( checkErrorsWithFiles( parseResult, rightArgvOrderVector ) )
    {
        return 1;
    }

    std::vector<std::vector<std::string>> parsedDataVectors;
    copyDataFromParsedFilesMapToVectors( parseResult, parsedDataVectors );

    sortParsedDataVectors( parsedDataVectors );

    printParsedDataVectors( parsedDataVectors );

    return 0;
}
