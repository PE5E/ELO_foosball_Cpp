#include "elo_calculator.hpp"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

EloCalculator::EloCalculator(){}

EloCalculator::~EloCalculator(){}

bool EloCalculator::set_and_calculate(std::vector<EloPlayer> &players)
{
    if(players.size() < 2)
    {
        cerr << "Error in EloRating::set_and_calculate: not enough players" << endl;
        return false;
    }
    if(players.size() == 3)
    {
        cerr << "Error in EloRating::set_and_calculate: 3 players mode is not supported" << endl;
        return false;
    }
    if(players.size() > 4)
    {
        cout << "Warning in EloRating::set_and_calculate: More than 4 players. Only the first 4 will be calculated" << endl;
    }

    bool teams_2v2 = (players.size() >= 4);

    // calculate avarage win change per team
    double team_a_avg_elo = players[0].old_elo;
    double team_b_avg_elo = players[1].old_elo;
    
    if(teams_2v2)
    {
        team_a_avg_elo = (players[0].old_elo + players[2].old_elo) / 2.0;
        team_b_avg_elo = (players[1].old_elo + players[3].old_elo) / 2.0;
    }

    // calculate expectations per team
    double team_a_expectation = calculate_expectation(team_a_avg_elo, team_b_avg_elo);
    double team_b_expectation = calculate_expectation(team_b_avg_elo, team_a_avg_elo);


    // @TODO: change newbie function so that if at least 1 newbie joined the game, all players get newbie ratings system 

    // Calculate K factor based on score
    uint score_diff = (players[0].score > players[1].score) ? (players[0].score - players[1].score) : (players[1].score - players[0].score);

    double player_0_factor = _k_factor * 0.1 * score_diff;
    double player_1_factor = _k_factor * 0.1 * score_diff;
    double player_2_factor = _k_factor * 0.1 * score_diff;
    double player_3_factor = _k_factor * 0.1 * score_diff;

    // if newbie is playing, recalculate K factor for that
    bool newbie_playing = false;
    for(auto &player : players)
    {
        if(player.games_played < _newbie_thershold) newbie_playing = true;
    }

    if(newbie_playing)
    {
        player_0_factor *= _newbie_factor;
        player_1_factor *= _newbie_factor;
        if(teams_2v2)
        {
            player_2_factor *= _newbie_factor;
            player_3_factor *= _newbie_factor;
        }
    }

    // determine winner
    uint elo_factor_team_a = 0;
    uint elo_factor_team_b = 0;
    if(players[0].score > players[1].score)
    {
        elo_factor_team_a = 1;
    }
    else 
    {
        elo_factor_team_b = 1;
    }

    // calculate individual ratings
    players[0].new_elo = calculate_rating(players[0].old_elo, team_a_expectation, elo_factor_team_a, player_0_factor);
    players[1].new_elo = calculate_rating(players[1].old_elo, team_b_expectation, elo_factor_team_b, player_1_factor);
    if(teams_2v2)
    {    
        players[2].new_elo = calculate_rating(players[2].old_elo, team_a_expectation, elo_factor_team_a, player_2_factor);
        players[3].new_elo = calculate_rating(players[3].old_elo, team_b_expectation, elo_factor_team_b, player_3_factor);
    }

    // calculate the differences
    players[0].elo_diff = players[0].new_elo - players[0].old_elo;
    players[1].elo_diff = players[1].new_elo - players[1].old_elo;
    if(teams_2v2)
    {
        players[2].elo_diff = players[2].new_elo - players[2].old_elo;
        players[3].elo_diff = players[3].new_elo - players[3].old_elo;
    }
    return true;
}

double EloCalculator::calculate_expectation(double rating_1, double rating_2)
{
    return (1.0 / (1.0 + pow(10.0, ((rating_2 - rating_1) / 1000.0))));
}

double EloCalculator::calculate_rating(double old_elo, double expectation, double result, double k_factor)
{
    return (old_elo + k_factor * (result - expectation));
}