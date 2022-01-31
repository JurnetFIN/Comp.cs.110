#include <iostream>

using namespace std;

int laskeminen(int pallot, int arvat) {
    int jakava = 1;
    int jakaja = 1;
    int tulos = 1;

    if (pallot == arvat) {
        return 1;
    }

    for (int i = pallot-arvat+1; i <= pallot; ++i) {
            jakava *= i;
    }
    for (int i = 1; i <= arvat; ++i) {
        jakaja *= i;
    }
    tulos = jakava / jakaja;
    return tulos;
}

int positiiviinen(int luku1, int luku2) {
    if (luku1 <= 0 or luku2 <= 0) {
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    }
    else if (luku1 < luku2){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;
    }
    else {
        return 1;
    }
}

int main() {
    int palloja = 0;
    int arvat = 0;
    int numero = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> palloja;
    cout << "Enter the number of drawn balls: ";
    cin >> arvat;

    numero = positiiviinen(palloja, arvat);
    if (numero == 1) {
        numero = laskeminen(palloja, arvat);
        cout << "The probability of guessing all "<< arvat << " balls correctly is 1/" << numero << endl;
    }
    return 0;
}
