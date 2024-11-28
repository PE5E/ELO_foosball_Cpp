#include "data_manager.hpp"

#include <ctime>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

DataManager::DataManager() :
    _players_file(),
    _games_file()
{
    // set the correct line ending for the OS
    #if defined (_WIN32) 
        #define LINE_END "\r\n"
    #else 
        #define LINE_END "\n"
    #endif

    _players = std::make_shared<std::vector<Player>>();

    set_player_file(_players_filename);
    set_games_file(_games_filename);
}

DataManager::~DataManager()
{
    _players_file.close();
    _games_file.close();
}

std::shared_ptr<std::vector<Player>> DataManager::players()
{
    return _players;
}

bool DataManager::set_player_file(const std::string &players_filename)
{
    try 
    {
        if(_players_file)
        {
            if(_players_file.is_open())
            {
                _players_file.close();
            }
        }

        _players_file.open(players_filename, std::ios::in | std::ios::out);
        if((_players_file.rdstate() & std::fstream::failbit) != 0)
        {
            std::cerr << "Error opening file: " << players_filename << " maybe it doesn't exist yet" << std::endl;
        }
        
        std::cout << "Using players file: " << players_filename << std::endl;
        _players_filename = players_filename;
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error setting player file: " << players_filename << ", " << ex.what() << std::endl;
        return false;
    }
    return true;
}

bool DataManager::load_players()
{
    try 
    {
        if(_players_file)
        {
            if(!_players_file.is_open())
            {
                std::cerr << "Error in load_players(). File is not open" << std::endl;
                return false;
            } 
        }
        else 
        {
            return false;
        }

        std::string line;
        int player_count = 0;
        int player_failed = 0;
        while(std::getline(_players_file, line)) {
            // std::cerr << "Line: " << line << std::endl;
            if(line.empty()) continue;

            // skip entries starting with: # 
            if(line.at(0) == '#') 
            {
                continue;
            }

            if(add_player(line))
            {
                player_count++;
            }
            else 
            {
                player_failed++;
            }
        }
        std::cout << "Loading players succesfully: " << player_count << " and failed: " << player_failed << std::endl;
        for(int index = 0; index != _players->size(); index++)
        {
            const Player &player = (*_players)[index];
            std::cout << player.name << ", ";
        }
        std::cout << std::endl;

        _players_file.clear();
        _players_file.seekg(0, std::ios::beg);
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error in load_players() " << ex.what() << std::endl;
        return false;
    }
    return true;
}

bool DataManager::save_players()
{
    try 
    {
        if(_players_file)
        {
            if(!_players_file.is_open())
            {
                std::cerr << "Error in save_players(). File is not open" << std::endl;
                return false;
            }
        }
        else {
            std::cerr << "Error in save_players(). fstream doesn't exist" << std::endl;
            return false;
        }

        // start at beginning of file
        _players_file.clear();
        _players_file.seekg(0, std::ios::beg);

        // write header
        _players_file << _players_header << LINE_END;

        // write all data
        for(int index = 0; index != _players->size(); index++)
        {   // "#id,name,rating,games_played,enabled";
            char line[100];
            const Player &player = (*_players)[index];
            sprintf(line, "%u,%s,%1.2f,%u,%c", player.id, player.name.c_str(), player.rating, player.games_played, (player.enabled ? 'y' : 'n'));
            _players_file << line << LINE_END;
        }

        _players_file.clear();
        _players_file.seekg(0, std::ios::beg);

        std::cout << "Done saving players. _players_file status: " << (_players_file.good() ? "good" : "bad") << std::endl;
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error in save_players() " << ex.what() << std::endl;
        return false;
    }
    return true;
}

bool DataManager::set_games_file(const std::string &games_filename)
{
    try {
        if(_games_file)
        {
            if(_games_file.is_open())
            {
                _games_file.close();
            }
        }

        _games_file.open(games_filename, std::ios::in | std::ios::out | std::ios::app);
        if((_games_file.rdstate() & std::fstream::failbit) != 0)
        {
            std::cerr << "Error opening file: " << games_filename << std::endl;
            return false;
        }

        std::cout << "Using games file: " << games_filename << std::endl;

        _games_filename = games_filename;
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error setting games file: " << games_filename << ", " << ex.what() << std::endl;
        return false;
    }
    return true;
}

bool DataManager::save_game(const Game &game)
{
    try 
    {
        if(_games_file)
        {
            if(!_games_file.is_open())
            {
                std::cerr << "Error in save_game(). File is not open" << std::endl;
                return false;
            }
        }
        else 
        {
            std::cerr << "Error in save_game(). fstream doesn't exist" << std::endl;
            return false;
        }

        // check if header already exists exactly like defined here, else write header first

        /*  uint id;            // sequential, starting from 1
            bool teams_2v2;     // 1v1 or 2v2
            uint player_id_1;   // sequential, starting from 1
            uint player_id_2;   // sequential, starting from 1
            uint player_id_3;   // sequential, starting from 1
            uint player_id_4;   // sequential, starting from 1
            uint score_team_a;  // 0-10
            uint score_team_b;  // 0-10
            std::string date_time
        */
    
        char line[50];
        sprintf(line, "%u,%c,%u,%u,%u,%u,%u,%u,%s", game.id, (game.teams_2v2 ? '2' : '1'), game.player_id_1, game.player_id_2, game.player_id_3,
            game.player_id_4, game.score_team_a, game.score_team_b, game.date_time.c_str());
        _games_file << line << LINE_END;
        _games_file.flush();
        std::cout << "Write to game file: " << std::endl;
        std::cout << line << std::endl;

    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error in save_game() " << ex.what() << std::endl;
        return false;
    }
    return true;
}

bool DataManager::load_last_game(Game &game)
{
    try 
    {
        if(_games_file)
        {
            if(!_games_file.is_open())
            {
                std::cerr << "Error in load_players(). File is not open" << std::endl;
                return false;
            } 
        }
        else 
        {
            std::cerr << "Error in load_last_game(). fstream doesn't exist" << std::endl;
            return false;
        }

        _games_file.clear();
        _games_file.seekg(0, std::ios::beg);

        std::string line;
        std::cout << "Loading games" << std::endl;

        int game_counter = 0;

        while(std::getline(_games_file, line)) 
        {
            // std::cout << "Line: " << line << std::endl;
            
            // entries starting with: # 
            if(line.at(0) == '#') 
            {
                // check if last header in file is equal to current header
                if (line == _games_header) 
                {
                    _games_header_equal = true;
                }
                else 
                {
                    _games_header_equal = false;
                }
                continue;
            }

            // read the values from a single line
            std::vector<std::string> values;
            std::stringstream ss (line);
            std::string item;

            while (getline (ss, item, ',')) 
            {
                values.push_back (item);
            }
            if(values.size() < 9)
            {
                std::cerr << "Error in DataManager::load_last_game: not enough values" << std::endl;
                continue;
            }

            Game tmp_game;
            tmp_game.id = std::stoi(values[0]);
            tmp_game.teams_2v2 = (values[1] == "2");
            tmp_game.player_id_1 = std::stoi(values[2]);
            tmp_game.player_id_2 = std::stoi(values[3]);
            tmp_game.player_id_3 = std::stoi(values[4]);
            tmp_game.player_id_4 = std::stoi(values[5]);
            tmp_game.score_team_a = std::stoi(values[6]);
            tmp_game.score_team_b = std::stoi(values[7]);
            tmp_game.date_time = values[8];

            game = std::move(tmp_game);
            game_counter++;
        }

        std::cout << "Read games succesfully: " << game_counter << std::endl;
        std::cout << "Last games header in file equal to current: " << (_games_header_equal ? "yes" : "no") << std::endl;
        _games_file.clear(); // reset flags
        
        // new write header
        if(!_games_header_equal)
        {
            _games_file << _games_header << LINE_END;
        }

        if(game_counter == 0)
        {
            return false;
        }

        return true;
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error in load_last_game() " << ex.what() << std::endl;
        return false;
    }
    return true;
}

std::string DataManager::date_time()
{
    time_t timestamp = time(nullptr);
    struct tm now = *localtime(&timestamp);

    char datetime[14];
    std::string year = std::to_string(now.tm_year).substr(1);
    sprintf(datetime, "%s%02u%02u-%02u%02u%02u", year.c_str(), (now.tm_mon + 1), now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
    
    return std::string(datetime);
}

bool DataManager::add_player(const std::string &text)
{
    try {
        std::vector<std::string> values;
        std::stringstream ss (text);
        std::string item;

        while (getline (ss, item, ',')) 
        {
            values.push_back (item);
        }
        if(values.size() < 5)
        {
            std::cerr << "Error in DataManager::add_player: not enough values" << std::endl;
            return false;
        }

        Player player;
        player.id = std::stoi(values[0]);
        player.name = values[1];
        player.rating = std::stof(values[2]);
        player.games_played = std::stoi(values[3]);
        player.enabled = (values[4] == "y" || values[4] == "Y");

        _players->push_back(player);
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error Datamanager::add_player() " << ex.what() << std::endl;
        return false;
    }
    return true;
}