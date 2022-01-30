#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int luku = 0;
    int a = 0;
    int b = 0;
    
    cout << "Enter a positive number: ";
    cin >> luku;
    if (luku <= 0) {
        cout << "Only positive numbers accepted" << endl;
        return 0;
    }
    if (luku > 0) {
        a = sqrt(luku);
        while("True") {
            b = luku / a;
            if (b*a==luku) {
                cout << luku << " = " << a << " * " << b << endl;
                break;
            }
            a -= 1;
        }
    }
}
