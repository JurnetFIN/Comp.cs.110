/* Suunnistus
 *
 *
 */
#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include "route.hh"
#include <iostream>

using namespace std;

int main()
{
    shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    cout << "Input> ";
    string input;
    getline(cin, input);
    if( not read_input_from_file(input, routes) )
    {
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


