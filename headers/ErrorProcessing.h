#pragma once

#include "Parser.h"


bool checkCommandLineArguments( int argc );

int checkFileNamesPositions( char * argv );

int rightArgvOrder( char * argv[], std::vector<std::string> & rightArgvOrderVector );

int checkErrorsWithReadingFiles( int errorsWithFile );

int checkErrorsWithFiles( Parser & parseResult, std::vector<std::string> & rightArgvOrderVector );
