#include <iostream>
#include <vector>
#include <random>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}


// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const std::vector<std::vector<int>>& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

std::vector<std::vector<int>> input(std::vector<std::vector<int>> gameboard)
{
    // Muuttujien luonti
    int seed_arvo = 0;
    std::vector< int > numbers;
    int count = (BOARD_SIDE * BOARD_SIDE);

    // Kysytaan merkkijono, kunnes se vastaa haluttuja arvoja.
    while(true) {
        std::cout << "Select start (R for random, I for input): ";
        std::string sana = "";
        getline(std::cin, sana);

        // Jos halutaan satunnaiset luvut
        if (sana == "r" or sana == "R") {
            // Kysytaan siemenluku
            std::cout << "Enter seed value: ";
            std::cin >> seed_arvo;

            // Luodaan luvut ja tallenetaan vektoriin
            default_random_engine gen(seed_arvo);
            uniform_int_distribution<int> distr(1, 5);
            for(int i = 0; i < count; ++i) {
                unsigned int luku = distr(gen);
                numbers.push_back(luku);
            }
            break;

        // Jos halutaan ei-satunnaiset luvut
        } else if (sana == "i" or sana == "I") {
            // Kysytaan luvut
            int new_integer = 0;
            std::cout << "Enter the integers: ";

            // Lisataan luvut vektoriin
            for(int i = 0; i < count; ++i) {
                std::cout << "";
                std::cin >> new_integer;
                numbers.push_back(new_integer);
            }

            break;
        }
    }

    // Muodosteaan vektori vektoriin
    int a = 0;
    for(unsigned int y = 0; y < BOARD_SIDE; ++y ) {
        std::vector<int> rivi;
        for(unsigned int x = 0; x < BOARD_SIDE; ++x ) {
            rivi.push_back(numbers.at(a));
            a += 1;
        }
        gameboard.push_back( rivi );
    }

    return gameboard;
}

int main()
{
    std::vector<std::vector<int>> board;
    board = input(board);
    print(board);
}
