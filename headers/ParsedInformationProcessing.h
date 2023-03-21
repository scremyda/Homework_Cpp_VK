#pragma once

#include <algorithm>
#include <iostream>
#include "Parser.h"


void copyDataFromMapToVectors( Parser parseResult, std::vector<std::vector<std::string>> & parsedDataVectors );

bool сomparisonComporator( const std::vector<std::string>& firstVectorValue,
                           const std::vector<std::string>& secondVectorValue );

void sortParsedDataVectors( std::vector<std::vector<std::string>> & parsedDataVectors );

void printParsedDataVectors( std::vector<std::vector<std::string>> parsedDataVectors );