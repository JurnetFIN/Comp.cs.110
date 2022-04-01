#include "parser.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string ERROR_IN_FORMAT = "Error: Incorrect line in input file";

bool read_size(ifstream &file, shared_ptr<OrienteeringMap> routes);
bool read_points(ifstream &file, shared_ptr<OrienteeringMap> routes);
bool read_routes(ifstream &file, shared_ptr<OrienteeringMap> routes);
void split_line(vector<string>& res, string& line);
bool is_number(string& str);

void split_line(vector<string>& result, string& line)
{
    result.push_back("");
    for ( char c : line )
    {
        if ( c == ';' )
        {
            result.push_back("");
        }
        else
        {
            result.back() += c;
        }
    }
}

bool is_number(string& str)
{
    return any_of(str.begin(), str.end(), ::isdigit);
}

bool read_size(ifstream& file, shared_ptr<OrienteeringMap> routes)
{
    string line;
    getline(file, line);
    vector<string> temp;
    split_line(temp, line);
    if( temp.size() == 2 and is_number(temp.at(0)) and is_number(temp.at(1)) )
    {
        routes->set_map_size(stoi(temp.at(0)), stoi(temp.at(1)));

        return true;
    }
    else
    {
        std::cout << ERROR_IN_FORMAT << std::endl;
        return false;
    }
}

bool read_points(ifstream& file, shared_ptr<OrienteeringMap> routes)
{
    vector<string> temps;
    string line;
    while( getline( file, line) )
    {
        if ( line == "ROUTES" )
        {
            return true;
        }
        temps.clear();
        split_line(temps, line);
        if( temps.size() != 5
             or not is_number(temps.at(1))
             or not is_number(temps.at(2))
             or not is_number(temps.at(3))
             or temps.at(4).size() != 1 )
        {
            cout << ERROR_IN_FORMAT << std::endl;
            return false;
        }
        else
        {
            routes->add_point(temps.at(0),
                              stoi(temps.at(1)),
                              stoi(temps.at(2)),
                              stoi(temps.at(3)),
                              temps.at(4).at(0));
        }
    }
    return true;
}

bool read_routes(ifstream& file, shared_ptr<OrienteeringMap> routes)
{
    vector<string> temp;
    string line, route;
    while( getline(file, line) )
    {
        temp.clear();
        split_line(temp, line);
        if( temp.size() > 2 )
        {
            route = temp.at(0);
            for( uint i = 2 ; i < temp.size(); ++i )
            {
                if( not routes->connect_route(temp.at(i - 1),
                                              temp.at(i),
                                              route) )
                {
                    return false;
                }
            }
        }
        else
        {
            std::cout << ERROR_IN_FORMAT << std::endl;
            return false;
        }
    }
    return true;
}

bool read_input_from_file(string file,
                          shared_ptr<OrienteeringMap> routes)
{
    ifstream input(file);
    if( not input )
    {
        cout << "Error: Can't read file" << endl;
        return false;
    }
    return (read_size(input, routes) and
            read_points(input, routes) and
            read_routes(input, routes));
}
