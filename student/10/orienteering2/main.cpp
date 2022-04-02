/* COMP.CS.110 Projekti 3: Suunnistus
 * Ohjelman kirjoittaja: Juliusz Kotelba
 * Opiskelijanumero: 150586775
 * Kayttajatunnus: nmjuko
 * E-Mail: juliusz.kotelba@tuni.fi
 *
 * Ohjelma, joka kaynnistyessaan lukee suunnistusreitteihin liittyvia tietoja
 * tiedosta, tallentaa ne tietorakenteeseen ja antaa kayttajalle mahdollisuuden
 * tehda hakuja tietorakenteeseen
 *
 * Tiedoston tulisi olla muodossa:
 * Ensimmainen rivi: <leveys>;<korkeus>
 * Haluttu maara rasteja: <rastin_nimi>;<x>;<y>;<korkeus>;<lyhenne>
 * Rasti luettelo paattyy sanaan ROUTES
 * Sen jalkeen haluttu maara reitteja: <reitin_nimi>;<pisteet>
 * ESIM:
 * 4;5
 * Alpha;1;2;100;A
 * Beeta;2;3;200;B
 * ROUTES
 * Alpha_to_beeta;Alpha;Beeta
 *
 * Komennot ovat seuraavanlaiset:
 * QUIT - Ohjelman suoritus paattyy
 * MAP - Komento tulostaa kartan
 * ROUTES - Komento tulostaa aakkosjarjestyksessa allekkain kaikki reitit
 * ROUTE <reitti> - Komento tulostaa annetulle reitille kuuluvat rastit
 * POINTS - Komento tulostaa syotetiedosta annetut reitit
 * LENGTH <reitti> - Komento tulostaa annetun reitin pituuden
 * RISE <rasti> - Komento tulostaa suurimman jatkuvan nousun annetulta rastilta
 */
#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include "route.hh"
#include <iostream>

using namespace std;

int main()
{
    shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    cout << "Input> ";
    string input;
    getline(cin, input);
    if( not read_input_from_file(input, routes) )
    {
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


