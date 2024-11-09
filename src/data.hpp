#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Player
{
    uint id;            // sequential, starting from 1
    std::string name;   // name or nickname
    double rating;      // ELO rating
    uint games_played;  // total of games played
    bool enabled;       // set to false to disable player (looks like a delete to the outside)

    Player()
    {
        id = 0;
        name = "";
        rating = 0.0;
        games_played = 0;
        enabled = true;
    }
};

struct Game
{
    uint id;            // sequential, starting from 1
    bool teams_2v2;     // 1v1 or 2v2
    uint player_id_1;   // sequential, starting from 1
    uint player_id_2;   // sequential, starting from 1
    uint player_id_3;   // sequential, starting from 1
    uint player_id_4;   // sequential, starting from 1
    uint score_team_a;  // 0-10
    uint score_team_b;  // 0-10
    std::string date_time; // yymmdd-hhmmss local time

    Game()
    {
        id = 0;
        teams_2v2 = false;
        player_id_1 = 0;
        player_id_2 = 0;
        player_id_3 = 0;
        player_id_4 = 0;
        score_team_a = 0;
        score_team_b = 0;
        date_time = "";
    }
};
/*
Game data:
- id (sequential, starting from 1)
- 1v1 or 2v2
- player id 1, 2, 3, 4 (1&3 team A, 2&4 team B)
- score teams A & B
- datetime
*/
#endif // DATA_HPP