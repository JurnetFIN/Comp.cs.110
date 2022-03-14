/* COMP.CS.110 Project 2: Pelitilasto
 * Ohjelman kirjoittaja: Juliusz Kotelba
 * Opiskelijanumero: 150586775
 * Käyttäjätunnus: nmjuko
 * E-Mail: juliusz.kotelba@tuni.fi
 *
 * Ohjelma, joka käynnistyessään lukee pelitilastoihin liittyviä tietoja
 * tiedostosta, tallentaa ne sopivaan tietorakenteeseen ja antaa käyttäjälle
 * mahdollisuuden tehdä hakuja, lisäyksiä ja poistoja kyseiseen tietorakenteeseen.
 *
 * Komennot ovat seuraavanlaiset:
 * QUIT - Ohjelman suoritus paattyy
 * ALL_GAMES - Tulostaa aakkosjärjestyksessä kaikki annetut peli allekkain.
 * GAME <oeli> - Tulostaa pelin tulokset ja pelaajat allekain.
 * ALL_PLAYERS - Tulostaa aakkosjarjestyksessa kaikki pelaajat allekain.
 * PLAYER <pelaajan nimi> - Tulostaa allekkain pelit, joita pelaaja pelaa.
 * ADD_GAME <pelin nimi> - Lisaa tietorakenteeseen annetun pelin
 * ADD_PLAYER <pelin nimi> <pelaajan nimi> <pisteet> - Komento lisaa
 * tietorakenteeseen annetulle pelille annetun pelaajan. Jos pelaaja on jo
 * olemassa paivitetaan pelaajan pelitulokset.
 * REMOVE_PLAYER <pelin nimi> - Poistaa pelaajan kaikista peleista
 *
 * Ohjelmalle annetaan syötteenä tiedosto, jonka kullakin rivillä on kolme
 * tietokenttää: pelin nimi, pelaajan nimi ja pelaajan saamat pisteet. Nämä on
 * eroteltu puolipisteellä toisistaan. Esim: <peli>;<pelaaja>;<pisteet>
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
 * Funktio tulostaa pelin tulokset ja pelaajat allekkain
 *
 * @param tiedosto
 * @param pelin_nimi
 */
void game(map<string, map<string, string>>& tiedosto, string peli) {
    map<int, vector<string>> tulokset;

    // Tarkistetaan onko peli olemassa
    if (tiedosto.find(peli) == tiedosto.end()) {
        cout << "Error: Game could not be found." << endl;
        return;
    }

    // Lisataan pelaaja "tulokset" tietorakenteeseen
    for (auto& pelaajat: tiedosto[peli]) {
        int piste_arvo = stoi(pelaajat.second, nullptr);

        // Jos piste_arvoa ei ole viela ollut lisataan se
        if (tulokset.find(piste_arvo) == tulokset.end()) {
            tulokset.insert(make_pair(piste_arvo, vector<string>()));
        }

        // Lisataan pelaaja piste arvon kohdalle
        tulokset[piste_arvo].push_back(pelaajat.first);
    }

    // Alkukommentti
    cout << "Game " << peli <<
            " has these scores and players, listed in ascending order:" << endl;

    // Tulostetaan tulokset
    for (auto& pisteet: tulokset) {
        cout << pisteet.first << " : ";

        // Jos on kyseessa ensimmainen nimi rivilla, tulostetaan ilman pilkkua.
        // Sen jalkeen tulostetaan pilkun kanssa
        string prefix = "";
        for (auto& nimet: tulokset.at(pisteet.first)) {
            cout << prefix << nimet;
            prefix = ", ";
        }
        cout << endl;
    }
}

/**
 * Funktio tulostaa kaikki pelit, missa annettu pelaaja pelaa
 *
 * @param tiedosto
 * @param pelaaja
 */
void player(map<string, map<string, string>>& tiedosto, string pelaaja) {
    vector<string> pelit;

    // Tarkastellaan missa pel(e)issa pelaaja pelaa
    for (auto& peli: tiedosto) {
        if (tiedosto[peli.first].find(pelaaja) != tiedosto[peli.first].end()) {
            pelit.push_back(peli.first);
        }
    }

    // Jos pelaaja ei pelaa tulostetaan virhe
    if (pelit.size() == 0) {
        cout << "Error: Player could not be found." << endl;

        // Jos pelaaja on pelaamassa, tulostetaan pelit jossa han pelaa
    } else {
        cout << "Player " << pelaaja << " playes the following games:" << endl;
        for (unsigned i=0; i<pelit.size(); i++) {
            cout << pelit.at(i) << endl;
        }
    }
}

/**
 * Funktio poistaa pelaajan kaikista peleista
 *
 * @param tiedosto
 * @param pelaaja
 */
void remove(map<string, map<string, string>>& tiedosto, string pelaaja) {
    bool poistettu = false;

    // Poistetaan pelaaja jokaisesta pelista
    for (auto& peli: tiedosto) {
        if (tiedosto[peli.first].find(pelaaja) != tiedosto[peli.first].end()) {
            tiedosto[peli.first].erase(pelaaja);
            poistettu = true;
        }
    }
    // Jos poisto tehtiin vahintaan kerran tulostetaan suoritus teksti
    if (poistettu) {
        cout << "Player was removed from all games." << endl;

        // Jos ei ollut ainuattakaan poistoa tulostetaan virhe
    } else {
        cout << "Error: Player could not be found." << endl;
    }
}

/**
 * Funktio tulostaa aakkosjarjestyksessa kaikki annetut pelaajat allekkain
 *
 * Ensin funktio etsii kaikki pelaajat tietorakenteesta. Pelaaja lisataan aina
 * mappiin, koska samat nimet "päällekirjoittuu". Sen jalkeen tulostetaan
 * nimet aakkosjarjestyksessa
 * HUOM! Kaytan map rakennetta vektorin sijaan, koska huomasin sen olevan
 * lyhyempi ja parempi "sorted" algoritmi
 *
 * @param tietorakenne
  */
void all_players(map<string, map<string, string>>& tiedosto) {
    map<string, string> nimet;

    // Etsitaan kaikki pelaajat tietorakenteesta
    for (auto& x: tiedosto) {
        for (auto& y: (tiedosto.at(x.first))) {
            nimet.insert(make_pair(y.first, ""));
        }
    }

    // Tulostetaan kaikki nimet aakkosjarjestyksessa
    cout << "All players in alphabetical order:" << endl;
    for (auto& i: nimet) {
        cout << i.first << endl;;
    }
}

/**
 * Funktio tulostaa aakkosjarjestyksessa kaikki annetut pelit allekkain
 *
 * @param tietorakenne
  */
void all_games(map<string, map<string, string>>& tiedosto) {
    cout << "All games in alphabetical order:" << endl;
    for (auto& x: tiedosto) {
        cout << x.first << endl;;
    }
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
    if (tiedosto.find(peli) == tiedosto.end()) {
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
        if (tiedosto.find(peli) == tiedosto.end()) {
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
    string input_nimi = "";
    cout << "Give a name for input file: ";
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
            cout << "Error: Invalid format in file." << endl;
            input_tiedosto.close();
            return false;
        }

        // Tulostetaan virhe jos joku arvo on tyhja
        for (unsigned int i=0; i<syote.size(); ++i) {
            if (syote.at(i) == "") {
                cout << "Error: Invalid format in file." << endl;
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
    transform(komento.begin(), komento.end(), komento.begin(), ::toupper);
    int param_maara = syote.size();

    // Tarkistetaan mikä komento on kyseessä
    if (komento == "QUIT") {
        return false;

    } else if (komento == "ALL_GAMES") {
        all_games(tiedosto);

    } else if (komento == "ALL_PLAYERS") {
        all_players(tiedosto);

    } else if ((komento == "GAME") and (param_maara >= 2)) {
        game(tiedosto, syote.at(1));

    } else if ((komento == "PLAYER") and (param_maara >= 2)) {
        player(tiedosto, syote.at(1));

    } else if ((komento == "ADD_GAME") and (param_maara >= 2)) {
        add_game(tiedosto, syote.at(1), true);

    } else if ((komento == "ADD_PLAYER") and (param_maara >= 4)) {
        add_player(tiedosto, syote.at(1), syote.at(2), syote.at(3), true);

    } else if ((komento == "REMOVE") and (param_maara >= 2)) {
        remove(tiedosto, syote.at(1));

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
