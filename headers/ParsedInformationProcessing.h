#pragma once

#include "Parser.h"


void copyDataFromParsedFilesMapToVectors( const Parser & parseResult, std::vector<std::vector<std::string>> & parsedDataVectors );

bool comparisonComparator( const std::vector<std::string>& firstVectorValue,
                           const std::vector<std::string>& secondVectorValue );

void sortParsedDataVectors( std::vector<std::vector<std::string>> & parsedDataVectors );

void printParsedDataVectors( std::vector<std::vector<std::string>> parsedDataVectors );