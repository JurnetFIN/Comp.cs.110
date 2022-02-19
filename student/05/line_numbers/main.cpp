#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto(tiedoston_nimi);
    if ( not tiedosto ) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
    } else {
        vector<string> rivit_tiedostossa;
        string rivi;
        while (getline(tiedosto, rivi)) {
            rivit_tiedostossa.push_back(rivi);
        }
        tiedosto.close();
        cout << rivit_tiedostossa.at(1) << endl;
    }
}
