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
    ofstream output_tiedosto(output_nimi);

    if ( not input_tiedosto ) {
        cout << "Error! The file " << input_nimi << " cannot be opened." << endl;
    } else {
        input_tiedosto.seekg(0, input_tiedosto.end);
        long size = input_tiedosto.tellg();
        input_tiedosto.seekg (0);

        char* buffer = new char[size];

        input_tiedosto.read(buffer, size);
        output_tiedosto.write(buffer, size);

        input_tiedosto.close();
    }
}
