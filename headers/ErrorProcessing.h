#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include "Parser.h"



bool checkFileOpen ( char * argv );

bool checkCommandLneArguments( int argc );

int checkFileNamesPositions( char * argv );

int rightArgvOrder( char * argv[], std::vector<std::string> & rightArgvOrderVector );

void copyDataFromMapToVectors( Parser parseResult, std::vector<std::vector<std::string>>& parsedDataVectors );


bool сomparisonComporator( const std::vector<std::string>& firstVectorValue,
                           const std::vector<std::string>& secondVectorValue );

void sortParsedDataVectors( std::vector<std::vector<std::string>>& parsedDataVectors );

void printParsedDataVectors( std::vector<std::vector<std::string>> parsedDataVectors );

int checkErrorWithNumberOfFileLines( int numberOfFileLines );
