#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int luku = 0;
    int potenssi = 0;

    cout << "Enter a number: ";
    cin >> luku;

    potenssi = pow(luku, 3);

    if (potenssi < 0) {
        cout << "Error! The cube of " << luku << " is not " << potenssi << "." << endl;
    }
    else if (cbrt(potenssi) == luku){
        cout << "Error! The cube of " << luku << " is not " << potenssi << "." << endl;
    }
    else {
        cout << "The cube of " << luku << " is " << potenssi << "." << endl;
    }
}
