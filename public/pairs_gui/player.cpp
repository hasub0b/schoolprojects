/*
* Ohjelman kirjoittaja
* Nimi: Aleksi Hasu
* Opiskelijanumero: 284211
* K�ytt�j�tunnus: hasu
* E-Mail: aleksi.hasu@tuni.fi
* */
#include "player.hh"
#include <iostream>


Player::Player(const std::string &name) :
    name_(name)
{

}

std::string Player::get_name() const
{
    return name_;
}

unsigned int Player::number_of_pairs() const
{
    return (number_of_cards_ / 2);
}

void Player::add_card(Card card)
{
    number_of_cards_ += 1;
    card.remove_from_game_board();
}
