#include <algorithm>
#include <iostream>
#include "ParsedInformationProcessing.h"


void copyDataFromParsedFilesMapToVectors( const Parser & parseResult, std::vector<std::vector<std::string>> & parsedDataVectors )
{
    std::unordered_map<std::string, std::vector<std::string>> parsedDataMap = parseResult.GetMap();
    for ( const auto& item : parsedDataMap )
    {
        const auto& values = item.second;
        if ( values.size() == 3 )
        {
            std::vector<std::string> temporaryVectorForMapPair = {item.first};
            temporaryVectorForMapPair.insert( temporaryVectorForMapPair.end(), values.begin(),
                                               values.end() );
            parsedDataVectors.push_back( temporaryVectorForMapPair );
        }
    }
}

bool comparisonComparator( const std::vector<std::string> & firstVectorValue,
                           const std::vector<std::string> & secondVectorValue )
{
    return firstVectorValue[2] > secondVectorValue[2];
}

void sortParsedDataVectors( std::vector<std::vector<std::string>> & parsedDataVectors )
{
    std::sort( parsedDataVectors.begin(), parsedDataVectors.end(),
                   comparisonComparator );
}

void printParsedDataVectors( std::vector<std::vector<std::string>> parsedDataVectors )
{
    for (int i = 0; i < 10 && i < parsedDataVectors.size(); i++)
    {
            std::cout << parsedDataVectors[i][3] << std::endl;
    }
}
