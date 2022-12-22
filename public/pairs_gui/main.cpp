/* Memory pairs game
 *
 * PLayers take turns trying to find pairs
 * If pair is found, current player will continue, otherwise turn changes.
 * Game will end when all pairs are found
 * Winner is the player who found most pairs.
 *
 * Ohjelman kirjoittaja
 * Nimi: Aleksi Hasu
 * Opiskelijanumero: 284211
 * K�ytt�j�tunnus: hasu
 * E-Mail: aleksi.hasu@tuni.fi
 *
 * */
#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
