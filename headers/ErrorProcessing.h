#pragma once

#include <iostream>
#include <map>
#include "Parser.h"


bool checkFileOpen ( char * argv );

bool checkCommandLneArguments( int argc );

int checkFileNamesPositions( char * argv );

int rightArgvOrder( char * argv[], std::vector<std::string> & rightArgvOrderVector );

int checkErrorWithNumberOfFileLines( int numberOfFileLines );

int checkErrorsWithFilesLines( Parser & parseResult, std::vector<std::string> & rightArgvOrderVector );
