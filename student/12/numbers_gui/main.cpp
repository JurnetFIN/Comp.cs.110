/* COMP.CS.110 Projekti 4: 2048
 * Ohjelman kirjoittaja: Juliusz Kotelba
 * Opiskelijanumero: 150586775
 * Kayttajatunnus: nmjuko
 * E-Mail: juliusz.kotelba@tuni.fi
 *
 * Pelin tarkoituksena on yhdistää laattoja, joissa on sama luku. Keskenään
 * eriarvoisia laattoja ei voi yhdistää. Peli päättyy, mikäli jokainen ruudusta
 * täyttyy tai pelaaja on saanut yhdistettyä laattoja siten, että yksi laatta on
 * arvoltaan sen verran mikä on pelaajan tavoite.
 *
 * Pelissä käytössä olevat komennot:
 * Start - pelin aloitus
 * Pause - pelin pysäyttäminen
 * Continue - pelin jatkaminen
 * Exit - pelistä poistuminen
 */

#include <mainwindow.hh>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;

    window.resize(800, 600);
    window.show();

    return app.exec();
}
