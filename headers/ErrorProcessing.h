#pragma once
#include <iostream>
#include <algorithm>
#include <map>
#include "Parser.h"



bool checkFileOpen ( char * argv );

bool checkCommandLneArguments( int argc );

int checkFileNamesPositions( char * argv );

int rightArgvOrder( char * argv[], std::vector<std::string> & RightArgvOrderVector );

void copyDataFromMapToVectors( Parser ParseResult, std::vector<std::vector<std::string>>& ParsedDataVectors );


bool сomparisonComporator( const std::vector<std::string>& FirstVectorValue,
                           const std::vector<std::string>& SecondVectorValue );

void sortParsedDataVectors( std::vector<std::vector<std::string>>& ParsedDataVectors );

void printParsedDataVectors( std::vector<std::vector<std::string>> ParsedDataVectors );

int checkErrorWithNumberOfFileLines( int NumberOfFileLines );
