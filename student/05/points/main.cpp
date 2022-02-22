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

    map<string, int> piste_taulukko;
    map<string, int>::iterator iter;
    string rivi;
    while (getline(input_tiedosto, rivi)) /*(true)*/ {
        string nimi;
        int pisteet = 0;
        int i = 0;
        int found = (rivi.find(":")+1);
        int rivin_pituus = rivi.size();
        int pisteet_nyt;
        // Tulkitaan rivi
        while (i != rivin_pituus) {
            // Otetaan tarkistettava arvo
            char tarkistettava = rivi.at(i);
            i += 1;
            // Jos se on pienempi kuin : niin se on nimi
            if (i < found) {
                nimi.push_back(tarkistettava);
            // Jos se on yhtasuuri kuin : niin se on :
            } else if (i == found) {
                continue;
            // Jos se on isomoi kuin : niin se on piste arvo
            } else if (i > found) {
                pisteet *= 10;
                pisteet += (tarkistettava - '0');
            }
        }

        iter = piste_taulukko.find(nimi);
        if (iter == piste_taulukko.end()) {
            piste_taulukko.insert(pair<string, int>(nimi, pisteet));
        } else {
            pisteet_nyt = iter->second;
            pisteet += pisteet_nyt;
            piste_taulukko.at(nimi) = pisteet;
        }
    }
    cout << "Final scores:" << endl;
    iter = piste_taulukko.begin();
    while (iter != piste_taulukko.end()) {
        cout << iter->first << ": " << iter->second << endl;
        ++iter;
    }
//    input_tiedosto.close();
}
