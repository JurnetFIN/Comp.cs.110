#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    string input_nimi = "";
    cout << "Input file: ";
    getline(cin, input_nimi);

    ifstream input_tiedosto(input_nimi);

    if ( not input_tiedosto ) {
        cout << "Error! The file " << input_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, vector<int>> sanat;
    map<string, vector<int>>::iterator iter;
    int rivi_nro = 0;
    string rivi;
    vector<int> rivit_nro;
    while (getline(input_tiedosto, rivi)) /*(true)*/ {
        string sana;
        int i = 0;
        rivi_nro += 1;
        string tyhja = " ";
        rivi.push_back(' ');
        int rivin_pituus = rivi.size();

        // Tulkitaan rivi
        while (i != (rivin_pituus)) {
            // Jos tutkittava kohde ei ole tyhja
            if (isspace(rivi.at(i)) == false)  {
                sana.push_back(rivi.at(i));

            // Jos se on tyhja se tarkoittaa sanan loppua
            } else {
                iter = sanat.find(sana);
                if (iter == sanat.end()) {
                    vector<int> lista;
                    lista.push_back(rivi_nro);
                    sanat.insert(pair<string, vector<int>>(sana, lista));

                } else {
                    rivit_nro = iter->second;
                    rivit_nro.push_back(rivi_nro);
                    sanat.at(sana) = rivit_nro;
                }
                sana.clear();
            }
            i += 1;
        }
    }
    iter = sanat.begin();
    while (iter != sanat.end()) {
        vector<int> rivien_nro = iter->second;
        int rivien_maara = rivien_nro.size();
        int i = 0;

        cout << iter->first << " ";
        cout << rivien_maara << ": ";
        while (i < rivien_maara) {
            if (i == 0) {
               cout << rivien_nro.at(i);
            } else {
                cout << ", " << rivien_nro.at(i);
            }
            i += 1;
        }
        cout << endl;
        ++iter;
    }
    input_tiedosto.close();
}
