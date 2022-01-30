#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int luku = 0;
    int a = 0;
    int b = 0;
    
    while("True") {
        cout << "Enter a positive number: ";
        cin >> luku;
        if (luku <= 0) {
            cout << "Only positive numbers accepted" << endl;
            break;
        }
        else {
            break;
        }
    }

    a = sqrt(luku);

    while("True") {
        b = luku / a;
        if (b*a==luku) {
            cout << luku << " = " << a << " * " << b << endl;
            break;
        }
        else {
            a -= 1;
        }
    }
    
    return 0;
}
