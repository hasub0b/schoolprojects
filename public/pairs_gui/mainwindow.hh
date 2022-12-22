 /* COMP.CS.110 K2021
 * Class Card
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 *
 * Program's main window
 *
 * Ohjelman kirjoittaja
 * Nimi: Aleksi Hasu
 * Opiskelijanumero: 284211
 * K�ytt�j�tunnus: hasu
 * E-Mail: aleksi.hasu@tuni.fi
 *
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <QTimer>
#include <vector>
#include "card.hh"
#include "player.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using Game_row_type = std::vector<Card>;
using Game_board_type = std::vector<std::vector<Card>>;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClick();
    void wait();
    void on_close_button();

private:

    Ui::MainWindow *ui;

    // Changeable constants
    const int DELAY = 1000;
    const int SEED = 1337;
    const unsigned int CARD_AMOUNT = 12; // Must be even number for the game to end
    const unsigned int PLAYER_AMOUNT = 2;

    // card push button size
    const int DEAFULT_BUTTON_WIDTH = 60;
    const int DEFAULT_BUTTON_HEIGTH = 60;

    // Text Browser geometry
    const int TEXT_X = 20;
    const int TEXT_Y = 20;
    const int TEXT_W = 700;
    const int TEXT_H = 80;

    // Close button goemoetry
    const int CLOSE_X = 360;
    const int CLOSE_Y = 530;
    const int CLOSE_W = 80;
    const int CLOSE_H = 30;

    // rows and columns for the cards grid
    unsigned int rows_;
    unsigned int columns_;

    // pointers to the current and previously clicked cards
    QPushButton* previous_ = nullptr;
    QPushButton* current_ = nullptr;

    // currently visible cards
    unsigned int turned_cards_ = 0;

    // used to determine the players turn
    unsigned int in_turn_ = 0;

    // pointers to widgets
    QTextBrowser* text_browser_;
    QPushButton* closeButton;

    // containers
    std::vector<QPushButton*> pushbuttons_;
    std::map<QPushButton*, Card> cards_;
    std::vector<Player*> players_;

    Game_board_type game_board_;

    void init_buttons();
    void init_with_empties();
    unsigned int next_free(unsigned int cell);
    void init_with_cards();
    void init_players();
    void init_text_browser();
    void init_close_button();
    void calculate_factors();
    bool check_pair();
    void set_player_inturn();
    void add_pair();
    bool cards_left();
    void get_winner();


};
#endif // MAINWINDOW_HH
