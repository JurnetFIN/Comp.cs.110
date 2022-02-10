#include <cstdlib>
#include <iostream>
#include <vector>

int is_geometric_series(std::vector<int>& ints)
{
    int jako = (ints.at(1) / ints.at(0));
    int aiempi_luku = ints.at(0);
    for (int i : ints) {
        if (ints.at(0) == i) {
            continue;
        } else if (jako == i / aiempi_luku) {
            aiempi_luku = i;
        } else {
            return false;
        }
    }
    return true;
}

int is_arithmetic_series(std::vector<int>& ints)
{
    int erotus = (ints.at(1)-ints.at(0));
    int aiempi_luku = ints.at(0);
    for (int i : ints) {
        if (ints.at(0) == i) {
            continue;
        } else if (erotus == i - aiempi_luku) {
            aiempi_luku = i;
        } else {
            return false;
        }
    }
    return true;
}

int is_ordered_non_strict_ascending(std::vector<int>& ints)
{
    int aiempi_luku = ints.at(0) -1;
    for (int i : ints) {
         if (aiempi_luku < i) {
             aiempi_luku = i;
         } else {
             return false;
         }
    }
    return true;
}

int same_values(std::vector<int>& ints)
{
    int eka_luku = ints.at(0);
    for( int i : ints) {
        if (eka_luku == i) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cout << "";
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
