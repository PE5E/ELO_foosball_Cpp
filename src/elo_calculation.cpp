#include "elo_calculation.hpp"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

EloRating::EloRating(){}

EloRating::~EloRating(){}

bool EloRating::set_and_calculate(const std::vector<EloPlayer> players)
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

    _players = players;

    bool teams_2v2 = (_players.size() >= 4);

    // calculate avarage win change per team
    double team_a_avg;
    double team_b_avg;
    
    if(teams_2v2)
    {
        team_a_avg = (_players[0].old_elo + _players[2].old_elo) / 2.0;
        team_b_avg = (_players[1].old_elo + _players[3].old_elo) / 2.0;
    }
    else 
    {
        team_a_avg = _players[0].old_elo;
        team_b_avg = _players[1].old_elo;
    }

    // calculate expectations per team
    double team_a_expectation = calculate_expectation(team_a_avg, team_b_avg);
    double team_b_expectation = calculate_expectation(team_b_avg, team_a_avg);

    // Calculate K factor based on newbie status
    double player_0_factor = _k_factor;
    double player_1_factor = _k_factor;
    double player_2_factor = _k_factor;
    double player_3_factor = _k_factor;

    if(_players[0].games_played < _newbie_thershold) player_0_factor *= _newbie_factor;
    if(_players[1].games_played < _newbie_thershold) player_1_factor *= _newbie_factor;
    if(_players[2].games_played < _newbie_thershold) player_2_factor *= _newbie_factor;
    if(_players[3].games_played < _newbie_thershold) player_3_factor *= _newbie_factor;

    // calculate individual ratings
    _players[0].new_elo = calculate_rating(_players[0].old_elo, team_a_expectation, _players[0].score, player_0_factor);
    _players[1].new_elo = calculate_rating(_players[1].old_elo, team_b_expectation, _players[1].score, player_1_factor);
    _players[2].new_elo = calculate_rating(_players[2].old_elo, team_a_expectation, _players[2].score, player_2_factor);
    _players[3].new_elo = calculate_rating(_players[3].old_elo, team_b_expectation, _players[3].score, player_3_factor);

    // calculate the differences
    _players[0].elo_diff = _players[0].new_elo - _players[0].old_elo;
    _players[1].elo_diff = _players[1].new_elo - _players[1].old_elo;
    _players[2].elo_diff = _players[2].new_elo - _players[2].old_elo;
    _players[3].elo_diff = _players[3].new_elo - _players[3].old_elo;

    return true;
}

std::vector<EloPlayer> EloRating::get_results()
{
    return _players;
}

double EloRating::calculate_expectation(double rating_1, double rating_2)
{
    return (1.0 / (1.0 + pow(10.0, ((rating_2 - rating_1) / 1000.0))));
}

double calculate_rating(double old_elo, double expectation, int result, double k_factor)
{
    return (old_elo + k_factor * ((double)result - expectation));
}