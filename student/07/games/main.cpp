/*  COMP.CS.100 Project 2: GAME STATISTICS
 * ===============================
 * EXAMPLE SOLUTION
 * ===============================
 *
 *  Acts as a game statistics with n commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

// Casual split func, if delim char is between "'s, ignores it.
vector<string> split( const string& str, char delim = ';' )
{
    vector<string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' ) {
            inside_quatation = not inside_quatation;
        } else if ( current_char == delim and not inside_quatation ) {
            result.push_back("");
        } else {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" ) {
        result.pop_back();
    }
    return result;
}

/**
 * Funktio, joka lisaa uuden pelin tietorakenteeseen,
 * jos sita ei ole ennastaan olemassa.
 *
 * Jos peli on jo olemassa funktio palauttaa paluuarvon false
 *
 * @param tietorakenne
 * @param pelin nimi
 * @return true/false
 */
bool add_game(map<string, map<string, string>>& tiedosto, string peli) {
    if (tiedosto.find(peli) == tiedosto.end()) {
        tiedosto.insert(make_pair(peli, map<string, string>()));
        return true;
    }
    return false;
}

/**
 * Funktio, joka lisaa pelaajan tietorakenteeseen ja mahdollisesti lisaa
 * uuden pelin tietorakenteeseen
 *
 * @param tietorakenne
 * @param syote; vektorissa on kolme asiaa tässä järjestyksessä:
 *               peli, pelaajan_nimi, pelaajan_pisteet
 */
void add_player(map<string, map<string, string>>& tiedosto, vector<string> syote){
    add_game(tiedosto, syote.at(0));

    tiedosto[syote.at(0)].insert(make_pair(syote.at(1), syote.at(2)));
}

/**
 * Funktio lukee syotteet syotetiedostosta ja tallentaa ne tietorakenteeseen
 * Jos syötetiedosto ei avaudu tai se ei ole kirjoitettu määrittelyn mukaan
 * tulostetaan virhe.
 *
 * @param map tiedosto
 * @return bool, true=success; false=fail
 */
bool lue_tiedosto(map<string, map<string, string>>& tiedosto) {
    // Avataan tiedosto
    string input_nimi = "";
    cout << "Input file: ";
    getline(cin, input_nimi);
    ifstream input_tiedosto(input_nimi);

    // Tulosteteen virhe jos tiedostoa ei pystytä lukemaan
    if ( not input_tiedosto ) {
        cout << "Error: File could not be read." << endl;
        return false;
    }

    // Luetaan syotetiedosta ja tallennetaan tiedot tietorakenteseen
    string rivi = "";
    while (getline(input_tiedosto, rivi)) {
        // Jaetaan rivi kolmeen arvoon; peli, nimi, pisteet
        vector<string> syote = split(rivi);

        // Tulostetaan virhe jos rivillä on jotain muuta kun kolme arvoa
        if (syote.size() != 3) {
            cout << "Invalid format in file" << endl;
            input_tiedosto.close();
            return false;
        }

        // Tulostetaan virhe jos joku arvo on tyhja
        for (unsigned int i=0; i<syote.size(); ++i) {
            if (syote.at(i) == "") {
                cout << "Invalid format in file" << endl;
                input_tiedosto.close();
                return false;
            }
        }
        // Tallennetaan syotteet tietorakenteeseen
        add_player(tiedosto, syote);
    }

    input_tiedosto.close();
    return true;
}

int main()
{
    map<string, map<string, string>> tiedosto;
    if (!lue_tiedosto(tiedosto)) {
        return EXIT_FAILURE;
    }
    cout << tiedosto["Hitori"]["Mikko"] << endl;

    return EXIT_SUCCESS;
}
