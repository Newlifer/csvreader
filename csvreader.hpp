/**
 *  csvreader.hpp
 *
 *  The MIT License
 *
 *  Copyright (c) 2015 Alex Newlifer, alex.newlifer at gmail.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 */

#pragma once

#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <istream>

/*!
 * Simple and generic CSV reader class.
 *
 * @tparam T, Char type.
 */
template< typename T >
class CSVReader {
    typedef T char_type;
    typedef typename std::list< std::list< std::basic_string< char_type > > >::iterator iterator;
    typedef typename std::list< std::list< std::basic_string< char_type > > >::const_iterator const_iterator;
public:
    CSVReader()
        : delimiter_( ',' )
        , row_delimiter_( '\n' )
    {}

    /*!
     * Constructor.
     *
     * @param[in] strm, Input stream.
     * @param[in] delimiter, Columns delimiter letter.
     * @param[in] row_delimiter, Rows endings.
     */
    CSVReader( std::basic_istream< char_type >* strm, char_type delimiter, char_type row_delimiter )
        : delimiter_( delimiter )
        , row_delimiter_( row_delimiter )
    {
        stream_ = strm;
    }

    void parse()
    {
        while( stream_->good() ) {
            std::basic_string< char_type > s;
            std::getline( *stream_, s, row_delimiter_ );
            data_.push_front( read_row( s, delimiter_ ) );
        }
    }

    iterator begin()
    {
        return data_.begin();
    }

    const_iterator begin() const
    {
        return data_.begin();
    }

    iterator end()
    {
        return data_.end();
    }

    const_iterator end() const
    {
        return data_.end();
    }

    std::size_t size() const
    {
        return data_.size();
    }


private:

    auto read_row( std::basic_istream< char_type >& in, char_type delimiter ) -> std::list< std::basic_string< char_type > >
    {
        std::basic_stringstream< char_type > ss;
        bool inquotes = false;
        std::list< std::basic_string< char_type > > row;
        while( in.good() ) {
            char_type c = in.get();
            if( !inquotes && c == '"' ) {
                inquotes = true;
            }
            else
            if( inquotes && c == '"' ) { // quotes
                if( in.peek() == '"' ) {
                    ss << ( char_type )in.get();
                }
                else {
                    inquotes = false;
                }
            }
            else
            if( !inquotes && c == delimiter ) {
                row.push_back( ss.str() );
                //ss.str( std::basic_string< char_type >( "" ) );
                static const std::basic_string< char_type > a;
                ss.str( a );
            }
            else
            if( !inquotes && ( c == '\r' ) ) {
                if( in.peek() == '\n' ) {
                      in.get();
                }
                row.push_back( ss.str() );
                return row;
            }
            else {
                ss << c;
            }
        }
    }

    auto read_row( std::basic_string< char_type > &line, char_type delimiter ) -> std::list< std::basic_string< char_type > >
    {
        std::basic_stringstream< char_type > ss( line );
        return read_row( ss, delimiter );
    }


private:
    char_type delimiter_;
    char_type row_delimiter_;
    std::list< std::list< std::basic_string< char_type > > > data_;
    std::basic_istream< char_type >* stream_;

private:
    CSVReader( const CSVReader& ) = delete;
    CSVReader& operator= ( const CSVReader& ) = delete;
};

