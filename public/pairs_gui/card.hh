/* Class: Card
 * -----------
 * Represents a single card in pairs (memory) game.
 *
 * COMP.CS.110 K2021
 * Class Card
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Kuvaa yhtä korttia muistipelissä.
 * 04/pair
 *
 * Ohjelman kirjoittaja
 * Nimi: Aleksi Hasu
 * Opiskelijanumero: 284211
 * K�ytt�j�tunnus: hasu
 * E-Mail: aleksi.hasu@tuni.fi
 *
 * */

#ifndef CARD_HH
#define CARD_HH

enum Visibility_type {OPEN, HIDDEN, EMPTY};
const char HIDDEN_CHAR = '#';
const char EMPTY_CHAR = '.';

class Card
{
public:

    // Default constructor: creates an empty card.
    Card();


    // Constructor: creates a hidden card with the given character.
    Card(const char c);


    // Obvious setter and getter methods.
    void set_letter(const char c);
    void set_visibility(const Visibility_type visibility);
    char get_letter() const;
    Visibility_type get_visibility() const;


    // Removes a card from the game board: changes the visibility to empty.
    void remove_from_game_board();

private:
    char letter_;
    Visibility_type visibility_;
};

#endif // CARD_HH
