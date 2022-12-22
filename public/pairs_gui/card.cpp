/*
* Ohjelman kirjoittaja
* Nimi: Aleksi Hasu
* Opiskelijanumero: 284211
* K�ytt�j�tunnus: hasu
* E-Mail: aleksi.hasu@tuni.fi
* */
#include "card.hh"
#include <iostream>

Card::Card():
    letter_(EMPTY_CHAR), visibility_(EMPTY)
{

}

Card::Card(const char c):
    letter_(c), visibility_(HIDDEN)
{

}

void Card::set_letter(const char c)
{
    letter_ = c;
}

void Card::set_visibility(const Visibility_type visibility)
{
    visibility_ = visibility;
}

char Card::get_letter() const
{
    return letter_;
}

Visibility_type Card::get_visibility() const
{
    return visibility_;
}


void Card::remove_from_game_board()
{
    visibility_ = EMPTY;
}
