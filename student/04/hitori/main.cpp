/* Hitori
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Hitori-pelin. Pelissä on peliruudukko kooltaan
 * 5 x 5. Kukin ruutu sisältää jonkin numeroista 1-5. Vaaka- ja
 * pystyriveillä voi aluksi olla useita samoja numeroita, mutta
 * tarkoituksena on poistaa numeroita niin, että kullakin vaaka- ja
 * pystyrivillä on kutakin numeroa vain yksi tai ei yhtään. Kuitenkaan
 * vierekkäisten ruutujen numeroita ei saa poistaa, eikä mikään jäljelle
 * jäävä numero (ruutu) saa jäädä irralleen muista, eli sen ympäriltä
 * (yläpuolelta, alapuolelta, vasemmalta, oikealta) ei saa poistaa
 * kaikkia numeroita.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla luvuilla 1-5 vai käyttäjän valitsemilla 25 luvulla.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 25 lukua.
 *   Joka kierroksella käyttäjältä kysytään poistettavan numeron
 * koordinaatteja eli kahta lukua. Peli päättyy pelaajan voittoon,
 * jos peliruudukon kaikilla vaaka- ja pystyriveillä esiintyy kukin
 * numero 1-5 korkeintaan kerran. Peli päättyy pelaajan häviöön,
 * jos hän poistaa jo poistetun numeron viereisen numeron tai jos
 * jokin numero jää irralleen muista.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, ja niiden osoittaman ruudun pitää sisältää
 * numero, eli jo poistettua numeroa ei voi poistaa toiseen kertaan.
 *   Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Ohjelman kirjoittaja
 * Nimi: Juliusz Kotelba
 * Opiskelijanumero: 150586775
 * Käyttäjätunnus: nmjuko
 * E-Mail: juliusz.kotelba@tuni.fi
 *
 * */

#include <iostream>
#include <vector>
#include <random>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';


bool game_won(vector<vector<int>> pelikentta)
{
    int num_check;
    int tarkistus = 1;

    for(unsigned int x = 0; x < BOARD_SIDE; ++x) {
        for(unsigned int y = 0; y < BOARD_SIDE; ++y) {
            int num = pelikentta.at(x).at(y);

            if (num != 0) {
                for (unsigned int c = 0; c < BOARD_SIDE; ++c) {
                    if (c != x) {
                        num_check = pelikentta.at(c).at(y);
                        if (num == num_check) {
                            tarkistus = 0;
                        }
                    }

                    if (c != y) {
                        num_check = pelikentta.at(x).at(c);
                        if (num == num_check) {
                            tarkistus = 0;
                        }
                    }
                }
            }
        }
    }

    if (tarkistus == 1) {
        return true;
    }

    return false;
}


bool game_lost(vector<vector<int>> pelikentta)
{
    for(unsigned int x = 0; x < BOARD_SIDE; ++x) {
        for (unsigned int y = 0; y < BOARD_SIDE; ++y) {
            int tarkistus = 1;

            if (x > 0) {
                if (pelikentta.at(x-1).at(y) != 0) {
                    tarkistus *= 0; }}

            if (y > 0) {
                if (pelikentta.at(x).at(y-1) != 0) {
                    tarkistus *= 0; }}

            if (y < (BOARD_SIDE-1)) {
                if (pelikentta.at(x).at(y+1) != 0) {
                    tarkistus *= 0; }}

            if (x < (BOARD_SIDE-1)) {
                if (pelikentta.at(x+1).at(y) != 0) {
                    tarkistus *= 0; }}

            if (tarkistus == 1) {
                return true;
            }
        }
    }

    return false;
}

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Kayttaja syottaa ruudun kordinaatit, jonka han haluaa poistaa
vector<unsigned int> remove_input(vector<vector<int>> pelikentta) {
    // Luodaan muuuttujat
    vector<unsigned int> inputs;
    string uusi_numero = "";
    int num = 0;

    // Kysyllaan niin kauan kunnes tulee hyvaksyttava arvo
    while(true) {
        cout << "Enter removable element (x, y): ";

        // Tallennetaan syotteet
        for(int i = 0; i < 2; ++i) {
            cout << "";
            cin >> uusi_numero;

            // jos meilla on tarve sulkea peli valittomasti
            if (uusi_numero == "q") {
                inputs.push_back(0);
                inputs.push_back(0);
                return inputs;

            // jos syote on luku lisataan se vektoriin
            } else {
                num = stoi_with_check(uusi_numero);
                if (num != 0) {
                    inputs.push_back(num);
                } // else, syote ei ole luku
            }
        }

        // Tarkastellaan syotteita
        // jos vektori on tyhja se tarkoittaa, etta syotteet eivat olleet lukuja
        if (inputs.size() != 0) {
            if ((inputs.at(0) > BOARD_SIDE) or (inputs.at(1) > BOARD_SIDE)) {
                cout << "Out of board" << endl;
                inputs.clear();

            } else if ((pelikentta.at((inputs.at(1))-1).at((inputs.at(0))-1)) == 0) {
                cout << "Already removed" << endl;
                inputs.clear();

            } else {
                break;
            }

        // tulostetaan virhe
        } else {
            cout << "Out of board" << endl;
        }
    }
    return inputs;
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
//
// Prints the game board with row and column numbers.
void print(const std::vector<std::vector<int>>& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j)
        {
            if(gameboard.at(i).at(j) == 0) {
                cout << EMPTY << " ";

            } else {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
        }
    cout << "=================" << endl;
}

// Luo kentan kayttajan syotteiden pohjalta
vector<vector<int>> input(vector<vector<int>> pelikentta)
{
    // Muuttujien luonti
    int seed_arvo = 0;
    vector< int > numerot;
    int count = (BOARD_SIDE * BOARD_SIDE);

    // Kysytaan merkkijono, kunnes se vastaa haluttuja arvoja.
    while(true) {
        cout << "Select start (R for random, I for input): ";
        string sana = "";
        getline(cin, sana);

        // Jos halutaan satunnaiset luvut
        if (sana == "r" or sana == "R") {
            // Kysytaan siemenluku
            cout << "Enter seed value: ";
            cin >> seed_arvo;

            // Luodaan luvut ja tallenetaan vektoriin
            default_random_engine gen(seed_arvo);
            uniform_int_distribution<int> distr(1, 5);
            for(int i = 0; i < count; ++i) {
                unsigned int luku = distr(gen);
                numerot.push_back(luku);
            }
            break;

        // Jos halutaan ei-satunnaiset luvut
        } else if (sana == "i" or sana == "I") {
            // Kysytaan luvut
            int uusi_numero = 0;
            cout << "Enter the integers: ";

            // Lisataan luvut vektoriin
            for(int i = 0; i < count; ++i) {
                cout << "";
                cin >> uusi_numero;
                numerot.push_back(uusi_numero);
            }

            break;
        }
    }

    // Muodosteaan vektori vektoriin
    int a= 0;
    for(unsigned int y = 0; y < BOARD_SIDE; ++y ) {
        vector<int> rivi;
        for(unsigned int x = 0; x < BOARD_SIDE; ++x ) {
            rivi.push_back(numerot.at(a));
            a += 1;
        }
        pelikentta.push_back( rivi );
    }

    return pelikentta;
}

int main()
{
    vector<vector<int>> board;
    vector<unsigned int> kordinaatit;

    board = input(board);
    print(board);

    while(true) {
        kordinaatit = remove_input(board);

        // jos kayttaja syotti q(uit)
        if (kordinaatit.at(0) == 0 and kordinaatit.at(1) == 0) {
            cout << "Quitting" << endl;
            break;

        // Muulloin tarkastellaan pelitilannetta
        } else {
            // Poistetaan luku
            board.at((kordinaatit.at(1)-1)).at((kordinaatit.at(0)-1)) = 0;
            print(board);

            if (game_lost(board) == true) {
                cout << "You lost" << endl;
                break;

            } else if (game_won(board) == true) {
                cout << "You won" << endl;
                break;
            }
        }
    }
}
