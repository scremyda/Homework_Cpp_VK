#include <iostream>
#include <map>
#include "ErrorProcessing.h"


bool checkCommandLineArguments( int argc )
{
    if (argc != 5)
    {
        std::cerr << "Неверное количество аргументов командной строки" << std::endl;
        std::cerr << "Правильный порядок аргументов: First(FilePath) Second(FilePath) Third(FilePath) Количество(минут)" << std::endl;
        return false;
    }
    return true;
}

int checkFileNamesPositions( char * argv )
{
    std::string basicsFileName = "title.basics.tsv";
    std::string ratingsFileName = "title.ratings.tsv";
    std::string akasFileName = "title.akas.tsv";

    std::string commandLineArgument = std::string( argv );

    if ( commandLineArgument.find( basicsFileName ) != std::string::npos )
    {
        return 1;
    }
    if ( commandLineArgument.find( ratingsFileName ) != std::string::npos )
    {
        return 2;
    }
    if ( commandLineArgument.find( akasFileName ) != std::string::npos )
    {
        return 3;
    }
    if ( commandLineArgument.find( ratingsFileName ) == std::string::npos || commandLineArgument.find( akasFileName ) == std::string::npos ||
    commandLineArgument.find( basicsFileName ) == std::string::npos )
    {
        return 5;
    }
    return 4;
}

int rightArgvOrder( char * argv[], std::vector<std::string> & rightArgvOrderVector )
{
    int firstArgvPosition = checkFileNamesPositions( argv[1] );
    int secondArgvPosition = checkFileNamesPositions( argv[2] );
    int thirdArgvPosition = checkFileNamesPositions( argv[3] );

    if ( firstArgvPosition == 5 || secondArgvPosition == 5 || thirdArgvPosition == 5 )
    {
        std::cerr << "Задано неверное имя файла(файлы должны называться: title.basics.tsv, title.ratings.tsv, title.akas.tsv) \n";
        return 1;
    }

    int fourthArgvPosition = checkFileNamesPositions( argv[4] );

    std::map< int, std::string > rightArgvOrderMap;
    rightArgvOrderMap[firstArgvPosition] = argv[1];
    rightArgvOrderMap[secondArgvPosition] = argv[2];
    rightArgvOrderMap[thirdArgvPosition] = argv[3];
    rightArgvOrderMap[fourthArgvPosition] = argv[4];

    for ( auto it = rightArgvOrderMap.begin(); it != rightArgvOrderMap.end(); ++it )
    {
        rightArgvOrderVector.push_back( it->second );
    }

    return 0;
}

int checkErrorsWithReadingFiles( int errorsWithFile )
{
    if ( errorsWithFile == 1 )
    {
        return 1;
    } else if ( errorsWithFile == 2 )
    {
        std::cerr << "Битый файл/неверное количество элементов в строке" << std::endl;
        return 1;
    }
    return 0;
}

int checkErrorsWithFiles( Parser & parseResult, std::vector<std::string> & rightArgvOrderVector )
{
    int errorsWithFileBasics = parseResult.parseBasicsFile( rightArgvOrderVector, parseResult );
    if ( checkErrorsWithReadingFiles( errorsWithFileBasics ) ) 
    {
        return 1;
    }

    int errorsWithFileRatings = parseResult.parseRatingsFile( rightArgvOrderVector, parseResult );
    if ( checkErrorsWithReadingFiles( errorsWithFileRatings ) )
    {
        return 1;
    }
    
    int errorsWithFileAkas = parseResult.parseAkasFile( rightArgvOrderVector, parseResult );
    if ( checkErrorsWithReadingFiles( errorsWithFileAkas ) )
    {
        return 1;
    }

    return 0;
}
