#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include "data.hpp"

#include <fstream>
#include <memory>
#include <vector>

class DataManager {
    public:
        DataManager();
        ~DataManager();
        std::shared_ptr<std::vector<Player>> players();

        bool set_player_file(const std::string &players_filename);
        bool load_players();
        bool save_players();
        
        bool set_games_file(const std::string &games_filename);
        bool save_game(const Game &game);
        // for now, games are only saved and can not be loaded

    private:
        bool add_player(const std::string &text);

        std::shared_ptr<std::vector<Player>> _players; // info from all players

        std::string _players_filename = "./elo_players.csv";
        std::string _games_filename = "./elo_games.csv";

        std::fstream _players_file;
        std::fstream _games_file;

        std::string _players_header = "#id,name,rating,games_played,enabled";
        std::string _games_header = "#id,teams_2v2,player_id_1,player_id_2,player_id_3,player_id_4,score_team_a,score_team_b,date_time";
};




#endif // DATA_MANAGER_HPP