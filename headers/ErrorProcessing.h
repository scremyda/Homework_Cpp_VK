#pragma once
#include <iostream>
#include <algorithm>
#include <map>
#include "Parser.h"



bool CheckFileOpen ( char * argv );

bool CheckCommandLneArguments( int argc );

int CheckFileNamesPositions( char * argv );

int RightArgvOrder( char * argv[], std::vector<std::string> & RightArgvOrderVector );

void CopyDataFromMapToVectors( Parser ParseResult, std::vector<std::vector<std::string>>& ParsedDataVectors );


bool ComparisonComporator( const std::vector<std::string>& FirstVectorValue,
                           const std::vector<std::string>& SecondVectorValue );

void SortParsedDataVectors( std::vector<std::vector<std::string>>& ParsedDataVectors );

void PrintParsedDataVectors( std::vector<std::vector<std::string>> ParsedDataVectors );

int CheckErrorWithNumberOfFileLines( int NumberOfFileLines );
