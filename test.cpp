#include "csvreader.hpp"
#include <fstream>

auto main () -> int
{
    {
        std::ifstream t ( "E:\\alco2.csv", std::ios::binary );
        //std::string str ( ( std::istreambuf_iterator< char > ( t ) ), std::istreambuf_iterator< char > () );
        auto a = new CSVReaderStringList< char > ( &t, ',', '\r' );
        a->parse ();
        std::cout << a->size () << std::endl;
    }
    /*
        {
            std::ifstream t ( "E:\\alco2.csv", std::ios::binary );
            //std::string str ( ( std::istreambuf_iterator< char > ( t ) ), std::istreambuf_iterator< char > () );
            //t.close ();
            auto a = new CSVReader< char > ( &t, ',', '\r' );
            a->parse ();
            std::cout << a->size () << std::endl;
        }
        */
    return 0;
}
