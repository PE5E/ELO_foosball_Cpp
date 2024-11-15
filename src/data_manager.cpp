#include "data_manager.hpp"

#include <iostream>

DataManager::DataManager() :
    _players_file(nullptr),
    _games_file(nullptr)
{
    _players = std::make_shared<std::vector<Player>>();
    _games = std::make_shared<std::vector<Game>>();

    load_players();
    load_games();
}

DataManager::~DataManager()
{
    save_players();
    save_games();
    _players_file->close();
    _games_file->close();
}

std::shared_ptr<std::vector<Player>> DataManager::players()
{
    return _players;
}

std::shared_ptr<std::vector<Game>> DataManager::games()
{
    return _games;
}

void DataManager::set_player_file(const std::string &player_file)
{
    if(_players_file->is_open())
    {
        save_players();
        _players_file->close();
    }

    _players_file = std::make_unique<std::fstream>(_players_filename, std::ios::trunc);
    std::cout << "Using players file: " << _players_filename << std::endl;

    load_players();
}

void DataManager::load_players()
{

}

void DataManager::save_players()
{

}

void DataManager::set_games_file(const std::string &games_file)
{
    if(_players_file->is_open())
    {
        save_games();
        _games_file->close();
    }

    _games_file = std::make_unique<std::fstream>(_games_filename, std::ios::trunc);
    std::cout << "Using games file: " << _games_filename << std::endl;

    load_games();
}

void DataManager::load_games()
{

}

void DataManager::save_games()
{

}