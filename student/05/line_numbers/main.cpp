#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string input_nimi = "";
    cout << "Input file: ";
    getline(cin, input_nimi);

    string output_nimi = "";
    cout << "Output file: ";
    getline(cin, output_nimi);

    ifstream input_tiedosto(input_nimi);

    if ( not input_tiedosto ) {
        cout << "Error! The file " << input_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    ofstream output_tiedosto(output_nimi);

    string rivi;
    int i = 0;
    while (getline(input_tiedosto, rivi)) {
        i += 1;
        output_tiedosto << i << " " << rivi << endl;
    }

    input_tiedosto.close();
    output_tiedosto.close();
}
