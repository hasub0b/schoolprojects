/*
* Ohjelman kirjoittaja
* Nimi: Aleksi Hasu
* Opiskelijanumero: 284211
* K�ytt�j�tunnus: hasu
* E-Mail: aleksi.hasu@tuni.fi
* */
#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "vector"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <QGraphicsView>
#include <random>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    calculate_factors();
    init_with_empties();
    init_with_cards();
    init_buttons();
    init_players();
    init_text_browser();
    init_close_button();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Handling card push button clicks
void MainWindow::handleButtonClick()
{

    // get the card clicked
    QPushButton* pressed_button = static_cast<QPushButton*>(sender());

    QPushButton* tmp = current_;
    current_ = pressed_button;
    previous_ = tmp;

    // check if the card clikced is different than previously clicked card
    if(pressed_button != previous_)
    {
        if(cards_[pressed_button].get_visibility() != EMPTY)
        {
            // show the corresponding letter and set color
            char c = cards_[pressed_button].get_letter();
            QString letter = "";
            letter += c;
            pressed_button->setText(letter);

            QPalette pal = pressed_button->palette();
            pal.setColor(QPalette::Button, QColor(Qt::green));
            pressed_button->setAutoFillBackground(true);
            pressed_button->setPalette(pal);
            pressed_button->update();

            turned_cards_ += 1;

            // if currently 2 cards turned, disable buttons and check for pair after delay
            if(turned_cards_ == 2)
            {
                centralWidget()->setDisabled(true);
                QTimer::singleShot(DELAY, this, SLOT(wait()));
            }
        }
    }
}

// delay function, check for pair and reset buttons
void MainWindow::wait()
{
    centralWidget()->setDisabled(false);

    if(check_pair()) // pair
    {
        add_pair();
    }
    else // no pair
    {
        set_player_inturn();
    }
    // reset buttons
    for(unsigned int i = 0; i < pushbuttons_.size(); ++i)
    {

        QPushButton* button = pushbuttons_.at(i);
        button->setText("");

        QPalette pal = button->palette();
        pal.setColor(QPalette::Button, QColor(Qt::blue));
        button->setAutoFillBackground(true);
        button->setPalette(pal);
        previous_ = nullptr;

        turned_cards_ = 0;
    }
}


// Fills the game board, the size of which is rows * columns, with empty cards.
// From 04/pairs
void MainWindow::init_with_empties()
{
    game_board_.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns_; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows_; ++i)
    {
        game_board_.push_back(row);
    }
}

// Finds the next free position in the game board (g_board), starting from the
// given position start and continuing from the beginning if needed.
// (Called only by the function init_with_cards.)
// From 04/pairs
unsigned int MainWindow::next_free(unsigned int start)
{
    for(unsigned int i = start; i < rows_ * columns_; ++i)
    {
        if(game_board_.at(i / columns_).at(i % columns_).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }

    for(unsigned int i = 0; i < start; ++i)
    {
        if(game_board_.at(i / columns_).at(i % columns_).get_visibility() == EMPTY)
        {
            return i;
        }
    }

    return  rows_;
}

// Initializes the given game board (g_board) with randomly generated cards,
// based on the given seed value.
// From 04/pairs
void MainWindow::init_with_cards()
{
    std::default_random_engine randomEng(SEED);
    std::uniform_int_distribution<int> distr(0, rows_ * columns_ - 1);

    distr(randomEng);

    for(unsigned int i = 0, c = 'A'; i < rows_ * columns_ - 1; i += 2, ++c)
    {
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(cell);
            game_board_.at(cell / columns_).at(cell % columns_).set_letter(c);
            game_board_.at(cell / columns_).at(cell % columns_).set_visibility(HIDDEN);
        }
    }
}


void MainWindow::init_players()
{
    for(unsigned int i = 1; i <= PLAYER_AMOUNT; ++i)
    {
        std::string name = "Player";
        std::string number = std::to_string(i);
        name += number;
        Player* new_player = new Player(name);
        players_.push_back(new_player);
    }
}

// Creates the card push buttons
void MainWindow::init_buttons()
{
    // Grid layout for card buttons
    QWidget* central = new QWidget(this);
    QGridLayout* gLayout = new QGridLayout(central);
    gLayout->setHorizontalSpacing(0);
    gLayout->horizontalSpacing();

    for(unsigned int r = 0; r < rows_; ++r)
    {
        for(unsigned int c = 0; c < columns_; ++c)
        {
            QPushButton* pushButton = new QPushButton(this);
            pushButton->setFixedWidth(DEAFULT_BUTTON_WIDTH);
            pushButton->setFixedHeight(DEFAULT_BUTTON_HEIGTH);

            QPalette pal = pushButton->palette();
            pal.setColor(QPalette::Button, QColor(Qt::blue));
            pushButton->setAutoFillBackground(true);
            pushButton->setPalette(pal);
            pushButton->update();
            pushbuttons_.push_back(pushButton);
            gLayout->addWidget(pushButton,r,c);
            Card& card = game_board_[r].at(c);
            cards_[pushButton] = card;

            connect(pushButton, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
        }
    }

    setCentralWidget(central);

}

void MainWindow::init_text_browser()
{
    text_browser_ = new QTextBrowser(this);
    text_browser_->setGeometry(TEXT_X, TEXT_Y, TEXT_W, TEXT_H);

    std::string name = players_[in_turn_]->get_name();
    QString qname = QString::fromStdString(name);
    text_browser_->setText(qname + "'s turn!");

}

void MainWindow::init_close_button()
{
    closeButton = new QPushButton(this);
    closeButton->setGeometry(CLOSE_X, CLOSE_Y, CLOSE_W, CLOSE_H);

    connect(closeButton, &QPushButton::clicked, this, &MainWindow::on_close_button);

    closeButton->setText("Close");
}


// Calculates the factors of the product such that the factor as near to each other as possible.
// From 04/pairs
void MainWindow::calculate_factors()
{
    for(unsigned int i = 1; i * i <= CARD_AMOUNT; ++i)
    {
        if(CARD_AMOUNT% i == 0)
        {
            rows_ = i;
        }
    }
    columns_ = CARD_AMOUNT / rows_;
}

// Checks if the previous and current cards have the same letter.
bool MainWindow::check_pair()
{
    if(cards_[current_].get_letter() == cards_[previous_].get_letter())
    {
        return true;
    }

    return false;
}

// Switches the turn of players
void MainWindow::set_player_inturn()
{

    if(in_turn_ == PLAYER_AMOUNT - 1)
    {
        in_turn_ = 0;
    }
    else
    {
        in_turn_ += 1;
    }

    std::string name = players_[in_turn_]->get_name();
    QString qname = QString::fromStdString(name);
    text_browser_->setText(qname + "'s turn!");
}

// Adds pair to the current player
void MainWindow::add_pair()
{
    players_.at(in_turn_)->add_card(cards_[current_]);
    players_.at(in_turn_)->add_card(cards_[previous_]);

    // Change the color of button, remove the button from all lists
    // and disable the buttons
    QPalette pal = current_->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    current_->setPalette(pal);
    previous_->setPalette(pal);

    current_->setText("");
    previous_->setText("");

    current_->setDisabled(true);
    previous_->setDisabled(true);

    pushbuttons_.erase(std::remove(pushbuttons_.begin(),pushbuttons_.end(),current_),pushbuttons_.end());
    pushbuttons_.erase(std::remove(pushbuttons_.begin(),pushbuttons_.end(),previous_),pushbuttons_.end());

    cards_.erase(current_);
    cards_.erase(previous_);

    if(not cards_left())
    {
        get_winner();
    }
}

// Check if there's any card buttons left
bool MainWindow::cards_left()
{
    if(cards_.size() > 0)
    {
        return true;
    }
    return false;
}

// At the end of the game calculate the winner
void MainWindow::get_winner()
{
    unsigned int most_pairs = 0;
    unsigned int players_with_most_pairs = 0;
    std::string winner = "";
    for(unsigned int i = 0; i < players_.size(); ++i)
    {
        if(players_.at(i)->number_of_pairs() > most_pairs)
        {
            most_pairs = players_.at(i)->number_of_pairs();
            players_with_most_pairs = 1;
            winner = players_.at(i)->get_name();
        }
        else if(players_.at(i)->number_of_pairs() == most_pairs)
        {
            players_with_most_pairs += 1;
        }
    }
    // set the final scores to the text browser
    QString qmost_pairs = QString::number(most_pairs);
    QString qplayers_with_most_pairs = QString::number(players_with_most_pairs);
    QString qwinner = QString::fromStdString(winner);

    text_browser_->clear();

    for(unsigned int i = 0; i < players_.size(); ++i)
    {
        QString qname = QString::fromStdString(players_.at(i)->get_name());
        QString qpairs = QString::number(players_.at(i)->number_of_pairs());

        text_browser_->append(qname + "'s pairs: " + qpairs);
    }

    if(players_with_most_pairs == 1)
    {
        text_browser_->append(qwinner + " has won with " + qmost_pairs + " pairs.");
    }
    else
    {
        text_browser_->append("Tie of " + qplayers_with_most_pairs + " players with " + qmost_pairs + " pairs.");
    }

}

void MainWindow::on_close_button()
{
    for(Player* player : players_)
    {
        delete player;
    }

    for(QPushButton* button : pushbuttons_)
    {
        delete button;
    }
    close();
}
