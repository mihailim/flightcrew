/************************************************************************
**
**  Copyright (C) 2010  Strahinja Markovic
**
**  This file is part of FlightCrew.
**
**  FlightCrew is free software: you can redistribute it and/or modify
**  it under the terms of the GNU Lesser General Public License as published
**  by the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  FlightCrew is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public License
**  along with FlightCrew.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <iostream>
#include <flightcrew.h>
namespace fc = FlightCrew;

// We set the MSVC warning level down to 3
// for code that we have no control over
#if defined(_MSC_VER)
#   pragma warning( push, 3 )
#endif

#include <boost/foreach.hpp> 
// We're most definitely not going to use
// it as BOOST_FOREACH.
#define foreach BOOST_FOREACH

#include <boost/program_options.hpp>
namespace po = boost::program_options;

// ... and then we reset the warning level
// back to normal (warning level 4)
#if defined(_MSC_VER)
#   pragma warning( pop )
#endif


void ValidateFiles( const std::vector< std::string > &files_to_validate )
{
    foreach( const std::string &file, files_to_validate )
    {
        std::cout << "\n";
        std::vector< fc::Result > results = fc::ValidateEpub( file );

        foreach( const fc::Result &result, results )
        {
            std::cout << result.GetFilepath();

            if ( result.GetErrorLine() > 0 )
                
                std::cout << "(" << result.GetErrorLine() << ")";

            std::cout << ": ";

            if ( result.GetResultType() == fc::ResultType_ERROR )

                std::cout << "error ";

            else 

                std::cout << "warning ";

            std::cout << result.GetResultId() << ": ";
            std::cout << result.GetMessage();                       

            std::cout << "\n";
        }

        std::cout << "\n";
    }
}


int main( int argc, char *argv[] )
{
    try 
    {
        po::options_description options( "Allowed options" );
        options.add_options()
            ( "help", "produce help message" )
            ( "input-file", po::value< std::vector< std::string > >(), "input file" );

        po::positional_options_description positionals;
        // -1 for count means unlimited
        positionals.add( "input-file", -1 );

        po::variables_map var_map;       
        store( po::command_line_parser( argc, argv ).
               options( options ).positional( positionals ).run(), var_map );
        po::notify( var_map );    

        if ( var_map.count( "help" ) )
        {
            std::cout << options << "\n";
            return 1;
        }

        if ( var_map.count( "input-file" ) ) 
        {
            std::vector< std::string > files_to_validate =
                var_map[ "input-file" ].as< std::vector< std::string > >();

            ValidateFiles( files_to_validate );
        } 
        
        else
        {
            std::cout << "No input file specified. Use --help for usage information.\n";
        }
    }

    catch( std::exception& exception )
    {
        std::cerr << "Error during run: " << exception.what() << "\n";
        return 1;
    }

    catch(...) 
    {
        std::cerr << "Unknown exception!\n";
    }

    return 0;
}