#include "ErrorProcessing.h"


bool checkFileOpen( char * argv )
{
    std::ifstream testFileStream( argv );
    if (!testFileStream.is_open())
    {
        std::cout << "Не удалось открыть файл " << argv << " для чтения" << std::endl;
        std::cout << "Правильный порядок аргументов: First(FilePath) Second(FilePath) Third(FilePath) Количество(минут)" << std::endl;
        return 1;
    }
    testFileStream.close();

    return 0;
}

bool checkCommandLneArguments( int argc )
{
    if (argc != 5)
    {
        std::cout << "Неверное количество аргументов командной строки" << std::endl;
        std::cout << "Правильный порядок аргументов: First(FilePath) Second(FilePath) Third(FilePath) Количество(минут)" << std::endl;
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
        std::cout << "Задано неверное имя файла(файлы должны называться: title.basics.tsv, title.ratings.tsv, title.akas.tsv) \n";
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

void copyDataFromMapToVectors( Parser parseResult, std::vector<std::vector<std::string>>& parsedDataVectors )
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

bool сomparisonComporator( const std::vector<std::string>& firstVectorValue,
                           const std::vector<std::string>& secondVectorValue )
{
    return firstVectorValue[2] > secondVectorValue[2];
}

void sortParsedDataVectors( std::vector<std::vector<std::string>>& parsedDataVectors )
{
    std::sort( parsedDataVectors.begin(), parsedDataVectors.end(),
                   сomparisonComporator );
}

void printParsedDataVectors( std::vector<std::vector<std::string>> parsedDataVectors )
{
    for (int i = 0; i < 10 && i < parsedDataVectors.size(); i++)
    {
            std::cout << parsedDataVectors[i][3] << std::endl;
    }
}

int checkErrorWithNumberOfFileLines( int numberOfFileLines )
{
    if ( numberOfFileLines ) 
    {
        std::cout << "Битый файл/неверное количество элементов в строке" << std::endl;
        return 1;
    }
    return 0;

}