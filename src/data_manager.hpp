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
        std::shared_ptr<std::vector<Game>> games();

        void set_player_file(const std::string &player_file);
        void load_players();
        void save_players();
        
        void set_games_file(const std::string &games_file);
        void load_games();
        void save_games();

    private:
        std::shared_ptr<std::vector<Player>> _players; // info from all players
        std::shared_ptr<std::vector<Game>> _games; // info from all games

        std::string _players_filename = "elo_players.csv";
        std::string _games_filename = "elo_games.csv";

        std::unique_ptr<std::fstream> _players_file;
        std::unique_ptr<std::fstream> _games_file;
};




#endif // DATA_MANAGER_HPP