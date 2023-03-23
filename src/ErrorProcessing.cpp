#include "ErrorProcessing.h"


bool checkFileOpen( char * argv )
{
    std::ifstream testFileStream( argv );
    if (!testFileStream.is_open())
    {
        std::cerr << "Не удалось открыть файл " << argv << " для чтения" << std::endl;
        std::cerr << "Правильный порядок аргументов: First(FilePath) Second(FilePath) Third(FilePath) Количество(минут)" << std::endl;
        return 1;
    }
    testFileStream.close();

    return 0;
}

bool checkCommandLineArguments( int argc )
{
    if (argc != 5)
    {
        std::cerr << "Неверное количество аргументов командной строки" << std::endl;
        std::cerr << "Правильный порядок аргументов: First(FilePath) Second(FilePath) Third(FilePath) Количество(минут)" << std::endl;
        return 1;
    }
    return 0;
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

int checkErrorWithNumberOfFileLines( int numberOfFileLines )
{
    if ( numberOfFileLines )
    {
        std::cerr << "Битый файл/неверное количество элементов в строке" << std::endl;
        return 1;
    }
    return 0;
}

int checkErrorsWithFilesLines( Parser & parseResult, std::vector<std::string> & rightArgvOrderVector )
{
    int errorWithNumberOfBasicsFileLines = parseResult.parseBasicsFile( rightArgvOrderVector, parseResult );
    if ( checkErrorWithNumberOfFileLines( errorWithNumberOfBasicsFileLines ) ) 
    {
        return 1;
    }

    int errorWithNumberOfRatingsFileLines = parseResult.parseRatingsFile( rightArgvOrderVector, parseResult );
    if ( checkErrorWithNumberOfFileLines( errorWithNumberOfRatingsFileLines ) )
    {
        return 1;
    }
    
    int errorWithNumberOfAkasFileLines = parseResult.parseAkasFile( rightArgvOrderVector, parseResult );
    if ( checkErrorWithNumberOfFileLines( errorWithNumberOfAkasFileLines ) )
    {
        return 1;
    }

    return 0;
}
