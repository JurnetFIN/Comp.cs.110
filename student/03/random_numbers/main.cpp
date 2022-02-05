#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    string kirjain = "";
    while (kirjain != "q") {
        cout << "" << endl;
        int luku = (rand() % upper);
        if(lower < luku) {
            cout << "Your drawn random number is " << luku << endl;
            cout << "Press q to quit or any other key to continue: ";
            cin >> kirjain;
        }
    }
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
