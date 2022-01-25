#include <iostream>
using namespace std;

int main()
{
    int loppu = 0;
    cout << "How many numbers would you like to have? ";
    cin >> loppu;
    for (int luku = 0; luku < loppu; luku++) {
        if (((luku + 1) % 3) == 0 and ((luku+1)%7)==0) {
            cout << ("zip boing") << endl;
        } else if (((luku+1) % 7) == 0) {
            cout << ("boing") << endl;
        } else if (((luku + 1) % 3) == 0) {
            cout << ("zip") << endl;
        } else {
            cout << (luku + 1)<< endl;
        }
    }
    return 0;
}
