#ifndef ELO_CALCULATION_HPP
#define ELO_CALCULATION_HPP

#include <string>
#include <vector>
#include <cmath>

// based on this python program:
// https://github.com/johnjsyoo/foosball-elo-calc

struct EloPlayer
{
    uint id;            // unique id
    std::string name;   // duh
    uint games_played;  // if player is newbie, other calculation is used
    uint score;         // the score of the last game
    double old_elo;     // the ELO rating before this game
    double new_elo;     // the ELO rating after this game
    double elo_diff;    // difference between before and after
    
    EloPlayer()
    {
        id = 0;
        name = "";
        games_played = 0;
        score = 0;
        old_elo = 0.0;
        new_elo = 0.0;
        elo_diff = 0.0;
    }
};

class EloRating
{
public:
    EloRating();
    ~EloRating();

    bool set_and_calculate(const std::vector<EloPlayer> players); // players can hold 2 or 4 players. First and third are a team, second and fourth are the other team
    std::vector<EloPlayer> get_results();

private:
    double calculate_expectation(double rating_1, double rating_2);
    double calculate_rating(double old_elo, double expectation, int result, double k_factor);

    std::vector<EloPlayer> _players;
    uint _newbie_thershold = 5; // number of games that needs to be played before exiting the newbie status
    uint _newbie_factor = 4;
    double _k_factor = 50;
};


#endif // ELO_CALCULATION_HPP