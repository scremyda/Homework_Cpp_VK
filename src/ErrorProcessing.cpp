#include "headers/ErrorProcessing.h"


bool checkFileOpen( char * argv )
{
    std::ifstream TestFileStream( argv );
    if (!TestFileStream.is_open())
    {
        std::cout << "Не удалось открыть файл " << argv << " для чтения" << std::endl;
        std::cout << "Правильный порядок аргументов: First(FilePath) Second(FilePath) Third(FilePath) Количество(минут)" << std::endl;
        return 1;
    }
    TestFileStream.close();

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
    std::string BasicsFileName = "title.basics.tsv";
    std::string RatingsFileName = "title.ratings.tsv";
    std::string AkasFileName = "title.akas.tsv";

    std::string CommanLineArgument = std::string( argv );

    if ( CommanLineArgument.find( BasicsFileName ) != std::string::npos )
    {
        return 1;
    }
    if ( CommanLineArgument.find( RatingsFileName ) != std::string::npos )
    {
        return 2;
    }
    if ( CommanLineArgument.find( AkasFileName ) != std::string::npos )
    {
        return 3;
    }
    if ( CommanLineArgument.find( RatingsFileName ) == std::string::npos || CommanLineArgument.find( AkasFileName ) == std::string::npos ||
    CommanLineArgument.find( BasicsFileName ) == std::string::npos )
    {
        return 5;
    }
    return 4;
}

int rightArgvOrder( char * argv[], std::vector<std::string> & RightArgvOrderVector )
{
    int FirstArgvPosition = checkFileNamesPositions( argv[1] );
    int SecondArgvPosition = checkFileNamesPositions( argv[2] );
    int ThirdArgvPosition = checkFileNamesPositions( argv[3] );

    if ( FirstArgvPosition == 5 || SecondArgvPosition == 5 || ThirdArgvPosition == 5 ) 
    {
        std::cout << "Задано неверное имя файла(файлы должны называться: title.basics.tsv, title.ratings.tsv, title.akas.tsv) \n";
        return 1;
    }

    int FourthArgvPosition = checkFileNamesPositions( argv[4] );

    std::map< int, std::string > RightArgvOrderMap;
    RightArgvOrderMap[FirstArgvPosition] = argv[1];
    RightArgvOrderMap[SecondArgvPosition] = argv[2];
    RightArgvOrderMap[ThirdArgvPosition] = argv[3];
    RightArgvOrderMap[FourthArgvPosition] = argv[4];

    for ( auto it = RightArgvOrderMap.begin(); it != RightArgvOrderMap.end(); ++it ) 
    {
        RightArgvOrderVector.push_back( it->second );
    }

    return 0;
}

void copyDataFromMapToVectors( Parser ParseResult, std::vector<std::vector<std::string>>& ParsedDataVectors )
{
    std::unordered_map<std::string, std::vector<std::string>> ParsedDataMap = ParseResult.GetMap();
    for ( const auto& item : ParsedDataMap )
    {
        const auto& values = item.second;
        if ( values.size() == 3 )
        {
            std::vector<std::string> TemporaryVectorForMapPair = {item.first};
            TemporaryVectorForMapPair.insert( TemporaryVectorForMapPair.end(), values.begin(),
                                               values.end() );
            ParsedDataVectors.push_back( TemporaryVectorForMapPair );
        }
    }
}

bool сomparisonComporator( const std::vector<std::string>& FirstVectorValue,
                           const std::vector<std::string>& SecondVectorValue )
{
    return FirstVectorValue[2] > SecondVectorValue[2];
}

void sortParsedDataVectors( std::vector<std::vector<std::string>>& ParsedDataVectors )
{
    std::sort( ParsedDataVectors.begin(), ParsedDataVectors.end(),
                   сomparisonComporator );
}

void printParsedDataVectors( std::vector<std::vector<std::string>> ParsedDataVectors )
{
    for (int i = 0; i < 10 && i < ParsedDataVectors.size(); i++)
    {
            std::cout << ParsedDataVectors[i][3] << std::endl;
    }
}

int checkErrorWithNumberOfFileLines( int NumberOfFileLines )
{
    if ( NumberOfFileLines ) 
    {
        std::cout << "Битый файл/неверное количество элементов в строке" << std::endl;
        return 1;
    }
    return 0;

}