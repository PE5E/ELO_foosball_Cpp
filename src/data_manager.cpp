#include "data_manager.hpp"

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

    // load_players();
}

DataManager::~DataManager()
{
    save_players();
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
            std::cerr << "Error opening file: " << players_filename << std::endl;
            return false;
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
        int player_false = 0;
        while(std::getline(_players_file, line)) {
            std::cerr << "Line: " << line << std::endl;

            // skip entries starting with: # 
            if(line.at(0) == '#') {
                continue;
            }

            if(add_player(line))
            {
                player_count++;
            }
            else 
            {
                player_false++;
            }
        }
        std::cout << "Loading players succesfully: " << player_count << " and failed: " << player_false << std::endl;
        for(int index = 0; index != _players->size(); index++)
        {
            const Player &player = (*_players)[index];
            std::cout << player.name << ", ";
        }
        std::cout << std::endl;

    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error in load_players() " << ex.what() << std::endl;
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
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error in save_players() " << ex.what() << std::endl;
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
                if(!set_games_file(_games_filename))
                {
                    return false;
                }
            } 
        }

    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error in save_game() " << ex.what() << std::endl;
        return false;
    }
    return true;
}

bool DataManager::add_player(const std::string &text)
{
    try {
        std::vector<std::string> values;
        std::stringstream ss (text);
        std::string item;

        while (getline (ss, item, ',')) {
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