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
#include <algorithm>

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
 * Funktio tulostaa aakkosjarjestyksessa kaikki annetut pelaajat allekkain
 *
 * Ensin funktio etsii kaikki pelaajat tietorakenteesta. Pelaaja lisataan aina
 * mappiin, koska samat nimet "päällekirjoittuu". Sen jalkeen tulostetaan
 * nimet aakkosjarjestyksessa
 * HUOM! Kaytan map rakennetta vektorin sijaan, koska huomasin taman olevan
 * lyhyempi ja parempi "sorted" algoritmi
 *
 * @param tietorakenne
  */
void all_players(map<string, map<string, string>>& tiedosto) {
    map<string, string> nimet;

    for (auto& x: tiedosto) {
        for (auto& y: (tiedosto.at(x.first))) {
            nimet.insert(make_pair(y.first, ""));
        }
    }

    for (auto& i: nimet) {
        cout << i.first << endl;;
    }
}

/**
 * @brief Funktio tulostaa aakkosjarjestyksessa kaikki annetut pelit allekkain
 * @param tietorakenne
  */
void all_games(map<string, map<string, string>>& tiedosto) {
    cout << "All games in alphabetical order:" << endl;
    for (auto& x: tiedosto) {
        cout << x.first << endl;;
    }
}
/**
 * @brief Palauttaa bool arvon onko peli olemassa
 * @param tiedosto
 * @param pelin_nimi
 * @return false=ei ole, true=on
 */
bool onko_peli_olemassa(map<string, map<string, string>>& tiedosto,
                        string pelin_nimi) {
    return (tiedosto.find(pelin_nimi) != tiedosto.end());
}

/**
 * Funktio, joka lisaa uuden pelin tietorakenteeseen,
 * jos sita ei ole ennestaan olemassa.
 *
 * Jos peli on jo olemassa, funktio tulostaa virheen
 *
 * @param tietorakenne
 * @param pelin nimi
 * @param kayttajan_syotto; true=kylla, false=ei
 */
void add_game(map<string, map<string, string>>& tiedosto, string peli,
              bool kayttajan_syotto=false) {
    // Lisataan peli, jos sita ei ole olemassa
    if (!onko_peli_olemassa(tiedosto, peli)) {
        tiedosto.insert(make_pair(peli, map<string, string>()));
        if (kayttajan_syotto == true) {
            cout << "Game was added." << endl;
        }
        return;
    }

    // Tulostetaan virhe jos on tarvetta
    if (kayttajan_syotto == true) {
        cout << "Error: Already exists." << endl;
    }
}

/**
 * Funktio, joka lisaa pelaajan tietorakenteeseen ja mahdollisesti lisaa
 * uuden pelin tietorakenteeseen, jos sita ei ole ennestaan olemassa.
 *
 * @param tietorakenne
 * @param pelin_nimi
 * @param pelaajan_nimi
 * @param pelaajan pisteet
 */
void add_player(map<string, map<string, string>>& tiedosto, string peli,
                string pelaaja, string pisteet, bool kasinsyotto=false) {
    if (kasinsyotto == true) {
        // Jos kayttaja syotti tuntemattoman pelin tulostetaan virhe
        if (!onko_peli_olemassa(tiedosto, peli)) {
            cout << "Error: Game could not be found." << endl;
            return;
        }

        // Jos pelaaja on olemassa, paivitetaan hanen pisteet
        // eli poistetaan ja sitten lisataan pelaaja uudestaan
        if (tiedosto[peli].find(pelaaja) != tiedosto[peli].end()) {
            tiedosto[peli].erase(pelaaja);
        }
        cout << "Player was added." << endl;
    }

    // Lisataan pelaaja
    tiedosto[peli].insert(make_pair(pelaaja, pisteet));
}

/**
 * Funktio lukee syotteet syotetiedostosta ja tallentaa ne tietorakenteeseen
 * Jos syotetiedosto ei avaudu tai se ei ole kirjoitettu määrittelyn mukaan
 * tulostetaan virhe.
 *
 * @param map tiedosto
 * @return bool, true=success; false=fail
 */
bool lue_tiedosto(map<string, map<string, string>>& tiedosto) {
    // Avataan tiedosto
    string input_nimi;
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
        add_game(tiedosto, syote.at(0));
        add_player(tiedosto, syote.at(0), syote.at(1), syote.at(2));
    }

    input_tiedosto.close();
    return true;
}

/**
 * Funktio lukee komennon ja lahettaa suorituspyynnon kyseiseen funktioon
 *
 * @param map tiedosto
 * @param syote; vektori jossa enintaan kolme asiaa: pelin_nimi, pelaaja, pisteet
 * @return bool; true=continue, false=QUIT
 */
bool suorita_komento(map<string, map<string, string>>& tiedosto,
                     vector<string> syote) {
    // Luodaan muuttujat
    string komento = syote.at(0);
    int param_maara = syote.size();

    // Tarkistetaan mikä komento on kyseessä
    if (komento == "QUIT") {
        return false;

    } else if (komento == "ALL_GAMES") {
        all_games(tiedosto);

    } else if (komento == "ALL_PLAYERS") {
        all_players(tiedosto);

    } else if ((komento == "GAME") and (param_maara > 1)) {
        //game(tiedosto, syote.at(1));

    } else if ((komento == "PLAYER") and (param_maara > 1)) {
        //player(tiedosto, syote.at(1));

    } else if ((komento == "ADD_GAME") and (param_maara > 1)) {
        add_game(tiedosto, syote.at(1), true);

    } else if ((komento == "ADD_PLAYER") and (param_maara > 3)) {
        add_player(tiedosto, syote.at(1), syote.at(2), syote.at(3), true);

    } else if ((komento == "REMOVE") and (param_maara > 1)) {
        //remove(tiedosto, syote.at(1));

    } else {
        cout << "Error: Invalid input." << endl;
    }
    return true;
}

int main()
{
    // Ohjelma jäsentelee tiedostosta lukemansa rivit
    // ja tallentaa tiedot peleistä ja pelaajista
    map<string, map<string, string>> tiedosto;
    if (!lue_tiedosto(tiedosto)) {
        return EXIT_FAILURE;
    }

    // Kayttaja syottaa halutun komennon ja sen
    // jalkeen ohjelma toteuttaa pyynnon
    // Tama jatkuu kunnes kayttaja syottaa kaskyn QUIT
    for( ; ; ){
        // Kayttaja syottaa komennon
        string rivi;
        cout << "games> ";
        getline(cin, rivi);

        // Jaetaan komento parametreiksi
        vector<string> syote = split(rivi, ' ');

        // Jos kayttaja syotti nolla parametria
        int param_maara = syote.size();
        if (param_maara == 0) {
            cout << "Error: Invalid input." << endl;
            continue;
        }

        // Tarkistetaan mikä komento on kyseessä
        // Jos kayttaja syotti "QUIT" lopetetaan ohjelman suorittaminen
        if (suorita_komento(tiedosto, syote) == false) {
            return EXIT_SUCCESS;

        }
    }
}
