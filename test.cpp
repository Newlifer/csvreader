#include "csvreader.hpp"
#include <fstream>

auto main() -> int
{
    std::ifstream t( "E:\\alco2.csv" );
    std::string str( ( std::istreambuf_iterator< char >( t ) ), std::istreambuf_iterator< char >() );
    auto a = new CSVReaderA< char >( &t, ',', '\r' );
    a->parse ();
    std::cout << a->size();
    return 0;
}
