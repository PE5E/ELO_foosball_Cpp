#include "mainframe.hpp"

#include <wx/filedlg.h>
#include <wx/grid.h>
#include <wx/window.h>
#include <wx/radiobox.h>

#include "data.hpp"

#include "new_game_dialog.hpp"
#include "new_player_dialog.hpp"
#include "player_dialog.hpp"
#include "score_dialog.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

using std::cout;
using std::cerr;
using std::endl;

// so we can use stricmp independent of OS
#ifndef _WIN32
#define stricmp strcasecmp
#define strnicmp strncasecmp
#endif


MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Foosball ELO Rating"),
    _data_manager(nullptr),
    _elo_calculator()
{
    try{
        _data_manager = std::make_unique<DataManager>();
        _data_manager->load_players();
        _players = _data_manager->players();

        // check for highest id for player and game
        for (int index = 0; index != _players->size(); index++)
        {
            const Player &player = (*_players)[index];
            // check if player can be displayed
            if(player.enabled == false)
            {
                continue;
            }
            if(player.id > _highest_player_id)
            {
                _highest_player_id = player.id;
            }
        }
        cout << "Loaded highest player id: " << _highest_player_id << endl;

        Game game;
        if(_data_manager->load_last_game(game))
        {
            _highest_game_id = game.id;
            cout << "Loaded highest game id: " << _highest_game_id << endl;
        }

        // menu
        wxMenu *menuFile = new wxMenu;
        menuFile->Append(wxID_EXIT);
        wxMenu *menuPlayers = new wxMenu;
        menuPlayers->Append(ID_add_player, "&Add Player", "New player");
        menuPlayers->Append(ID_players, "&Edit Players", "Players stuff");
        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);

        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "&File");
        menuBar->Append(menuPlayers, "&Players");
        menuBar->Append(menuHelp, "&Help");
        SetMenuBar(menuBar);

        Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
        Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
        Bind(wxEVT_MENU, &MainFrame::on_add_player_menu, this, ID_add_player);
        Bind(wxEVT_MENU, &MainFrame::on_player_menu, this, ID_players);
        

        // main screen
        SetBackgroundColour(wxColour(25, 25, 25));
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        sizer->AddSpacer(10);

        // the table of players
        // header
        wxBoxSizer *header_sizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText *header_pos = new wxStaticText(this, -1, "Position" , wxPoint(0, 0), wxSize(80, 30), wxST_NO_AUTORESIZE);
        header_pos->SetForegroundColour(wxColour(255, 255, 255));
        wxStaticText *header_name = new wxStaticText(this, -1, "Name" , wxPoint(0, 0), wxSize(300, 30), wxST_NO_AUTORESIZE);
        header_name->SetForegroundColour(wxColour(255, 255, 255));
        wxStaticText *header_score = new wxStaticText(this, -1, "Rating", wxPoint(0, 0), wxSize(80, 30), wxST_NO_AUTORESIZE);
        header_score->SetForegroundColour(wxColour(255, 255, 255));
        header_sizer->AddSpacer(25);
        header_sizer->Add(header_pos);
        header_sizer->AddSpacer(10);
        header_sizer->Add(header_name);
        header_sizer->AddSpacer(10);
        header_sizer->Add(header_score);
        sizer->Add(header_sizer, 0, wxLEFT | wxRIGHT | wxEXPAND, 70);

        // player list
        _player_panel = new wxPanel(this, -1, wxPoint(0, 0), wxSize(500, 340), wxALL);
        _player_panel->SetBackgroundColour(wxColour(40, 130, 40));

        wxBoxSizer *player_sizer = new wxBoxSizer(wxHORIZONTAL);
        _player_list = new ScrollablePlayerInfo(_player_panel, wxID_ANY, _players);
        player_sizer->Add(_player_list, 1, wxEXPAND);
        _player_panel->SetSizer(player_sizer);
        
        sizer->Add(_player_panel, 0, wxLEFT | wxRIGHT | wxGROW, 70, NULL);

        sizer->AddSpacer(20);
        auto button_sizer = new wxBoxSizer(wxHORIZONTAL);
        button_sizer->AddSpacer(180);
        button_sizer->Add(new wxButton(this, ID_new_game, "New Game"), 0, wxEXPAND | wxRIGHT | wxLEFT, 50);
        button_sizer->AddSpacer(180);
        button_sizer->Add(new wxButton(this, ID_scroll_up, "up", wxPoint(0, 0), wxSize(50, 30)), 0, wxEXPAND | wxRIGHT, 10);
        button_sizer->Add(new wxButton(this, ID_scroll_down, "down", wxPoint(0, 0), wxSize(50, 30)), 0, wxEXPAND | wxRIGHT, 30);

        sizer->Add(button_sizer, 0, wxEXPAND | wxRIGHT | wxLEFT, 50);
        sizer->AddSpacer(10);
        
        sizer->SetSizeHints(this);
        SetSizer(sizer);

        Bind(wxEVT_BUTTON, &MainFrame::on_new_game, this, ID_new_game);
        Bind(wxEVT_BUTTON, &MainFrame::on_scroll_up, this, ID_scroll_up);
        Bind(wxEVT_BUTTON, &MainFrame::on_scroll_down, this, ID_scroll_down);
        
        
        wxWindow::SetSize(wxDefaultCoord, wxDefaultCoord, _main_width, _main_height, wxSIZE_FORCE);
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Error in MainFrame(): " << ex.what() << std::endl;
    }
}

MainFrame::~MainFrame()
{}

bool MainFrame::add_player_to_list(const std::string &name)
{
    if(name == "") 
    {
        return false;
    }

    // check if name already exists
    for(auto player : (*_players))
    {
        if(stricmp(player.name.c_str(), name.c_str()) == 0 && player.enabled == true)
        {
            return false;
        }
    }

    _highest_player_id++;

    Player player;
    player.id = _highest_player_id;
    player.name = name;
    player.rating = _starting_rate;
    player.enabled = true;

    _players->push_back(player);

    return true;
}

Player& MainFrame::get_player(uint player_id)
{
    for(Player &player : (*_players))
    {
        if(player.id == player_id) return player;
    }

    // we should not end up here, but if so, return something...
    return (*_players).at(0);
}

void MainFrame::OnAbout(wxCommandEvent& event) 
{
    wxMessageBox("Foosball ELO Rating program by Jaap", "About ", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit(wxCommandEvent& event) 
{
    Close(true);
}

void MainFrame::on_new_game(wxCommandEvent& event) 
{


    // create and show dialog
    NewGameDialog *game_diag = new NewGameDialog(wxT("Enter Game Details"), _last_game_2v2, _players, _last_players);

    if(game_diag->ShowModal() == wxID_OK) {

        bool teams_2v2 = game_diag->get_teams_2v2();

        uint player1_id = game_diag->get_player1();
        uint player2_id = game_diag->get_player2();
        uint player3_id = game_diag->get_player3();
        uint player4_id = game_diag->get_player4();

        uint score_team_a = game_diag->get_score_a();
        uint score_team_b = game_diag->get_score_b();
        
        cout << "Game results:" << endl;
        cout << "Game type: " << (teams_2v2 ? "2 vs 2" : "1 vs 1") << endl;
        cout << "Selected players:" << endl;
        cout << "1. id: " << player1_id  << endl;
        cout << "2. id: " << player2_id  << endl;
        cout << "3. id: " << player3_id  << endl;
        cout << "4. id: " << player4_id  << endl;
        cout << "Score Team A: " << score_team_a << endl;
        cout << "Score Team B: " << score_team_b << endl;

        // save last game details
        _last_game_2v2 = teams_2v2;
        _last_players[0] = player1_id;
        _last_players[1] = player2_id;
        _last_players[2] = player3_id;
        _last_players[3] = player4_id;


        // check players
        if(player1_id == 0 || player2_id == 0) // there need to be players
        {
            wxMessageDialog *msg = new wxMessageDialog(NULL, "Please select all players", wxT("Error"), wxOK | wxICON_ERROR);
            msg->ShowModal();
            msg->Destroy();
            delete game_diag;
            return;
        }

        if(player1_id == player2_id) // players can not be the same
        {
            wxMessageDialog *msg = new wxMessageDialog(NULL, "Please select different players", wxT("Error"), wxOK | wxICON_ERROR);
            msg->ShowModal();
            msg->Destroy();
            delete game_diag;
            return;
        }

        if(teams_2v2) 
        {
            if(player3_id == 0 || player4_id == 0) // there need to be players
            {
                wxMessageDialog *msg = new wxMessageDialog(NULL, "Please select all players", wxT("Error"), wxOK | wxICON_ERROR);
                msg->ShowModal();
                msg->Destroy();
                delete game_diag;
                return;
            }

            if(player1_id == player3_id || player1_id == player4_id || player2_id == player3_id || player2_id == player4_id || player3_id == player4_id) // players can not be the same
            {
                wxMessageDialog *msg = new wxMessageDialog(NULL, "Please select different players", wxT("Error"), wxOK | wxICON_ERROR);
                msg->ShowModal();
                msg->Destroy();
                delete game_diag;
                return;
            }
        }

        // check results
        if(score_team_a == 0 && score_team_b == 0)
        {
            wxMessageDialog *msg = new wxMessageDialog(NULL, "Please select the scores", wxT("Error"), wxOK | wxICON_ERROR);
            msg->ShowModal();
            msg->Destroy();
            delete game_diag;
            return;
        }

        if(score_team_a == score_team_b)
        {
            wxMessageDialog *msg = new wxMessageDialog(NULL, "Please select different scores per team", wxT("Error"), wxOK | wxICON_ERROR);
            msg->ShowModal();
            msg->Destroy();
            delete game_diag;
            return;
        }

        if(score_team_a > _max_score || score_team_b > _max_score)
        {
            std::string txt = "Please select a score lower than ";
            txt += std::to_string(_max_score);

            wxMessageDialog *msg = new wxMessageDialog(NULL, txt, wxT("Error"), wxOK | wxICON_ERROR);
            msg->ShowModal();
            msg->Destroy();
            delete game_diag;
            return;
        }

        if(_only_max_score_game) // if true, only a score from one team that is equal to max score is accepted
        {
            if(score_team_a != _max_score && score_team_b != _max_score)
            {
                std::string txt = "Please select one score equal to ";
                txt += std::to_string(_max_score);

                wxMessageDialog *msg = new wxMessageDialog(NULL, txt, wxT("Error"), wxOK | wxICON_ERROR);
                msg->ShowModal();
                msg->Destroy();
                delete game_diag;
                return;
            }
        }

        // there should be valid results here

        // calculate ELO ratings
        std::vector<EloPlayer> elo_scores;

        EloPlayer elo_1;
        elo_1.id = player1_id;
        elo_1.name = get_player(player1_id).name;
        elo_1.games_played = get_player(player1_id).games_played;
        elo_1.old_elo = get_player(player1_id).rating;
        elo_1.score = score_team_a;
        elo_scores.push_back(elo_1);

        EloPlayer elo_2;
        elo_2.id = player2_id;
        elo_2.name = get_player(player2_id).name;
        elo_2.games_played = get_player(player2_id).games_played;
        elo_2.old_elo = get_player(player2_id).rating;
        elo_2.score = score_team_b;
        elo_scores.push_back(elo_2);

        if(teams_2v2)
        {
            EloPlayer elo_3;
            elo_3.id = player3_id;
            elo_3.name = get_player(player3_id).name;
            elo_3.games_played = get_player(player3_id).games_played;
            elo_3.old_elo = get_player(player3_id).rating;
            elo_3.score = score_team_a;
            elo_scores.push_back(elo_3);

            EloPlayer elo_4;
            elo_4.id = player4_id;
            elo_4.name = get_player(player4_id).name;
            elo_4.games_played = get_player(player4_id).games_played;
            elo_4.old_elo = get_player(player4_id).rating;
            elo_4.score = score_team_b;
            elo_scores.push_back(elo_4);
        }

        _elo_calculator.set_and_calculate(elo_scores);

        cout << "ELO calculation results:" << endl;
        for(EloPlayer elo_player : elo_scores)
        {
            cout << "Player name: " << elo_player.name << " old ELO: " << elo_player.old_elo << " new ELO: " << elo_player.new_elo << " ELO diff: " << elo_player.elo_diff << endl;
            get_player(elo_player.id).rating = elo_player.new_elo;
            get_player(elo_player.id).games_played++;
        }

        // save the results for the players
        _data_manager->save_players();

        // save game data
        _highest_game_id++;
        Game game;
        game.id = _highest_game_id;
        game.player_id_1 = player1_id;
        game.player_id_2 = player2_id;
        if(teams_2v2)
        {
            game.player_id_3 = player3_id;
            game.player_id_4 = player4_id;
        }
        game.score_team_a = score_team_a;
        game.score_team_b = score_team_b;
        game.teams_2v2 = teams_2v2;
        game.date_time = _data_manager->date_time();

        _data_manager->save_game(game);

        // show the results

        ScoreDialog *score_diag = new ScoreDialog(wxT("Game Results"), _last_game_2v2, elo_scores, std::to_string(score_team_a), std::to_string(score_team_b), (score_team_a > score_team_b));
        update_player_list();
    }

    delete game_diag;
}

void MainFrame::on_add_player_menu(wxCommandEvent& event)
{
    NewPlayerDialog *new_player_diag = new NewPlayerDialog(wxT("New Player"));
    if(new_player_diag->ShowModal() != wxID_OK)
    {
        new_player_diag->Destroy();
        return;
    }

    std::string name(new_player_diag->get_player_name().mb_str());
    
    if(name == "")
    {
        // no name entered
        std::string text = "Please enter a name";
        wxMessageDialog *msg = new wxMessageDialog(NULL, text, wxT("Error"), wxOK | wxICON_ERROR);
        msg->ShowModal();
        msg->Destroy();
    }
    else {
        if(add_player_to_list(name))
        {
            std::string text = "Successfully added player: ";
            text += name;
            wxMessageDialog *msg = new wxMessageDialog(NULL, text, wxT("Player Added"), wxOK | wxICON_INFORMATION);
            msg->ShowModal();
            msg->Destroy();
            _data_manager->save_players();
        }
        else 
        {
            // players name already exists
            std::string text = "This name already exists: ";
            text += name;
            text += ". Please enter something else";
            wxMessageDialog *msg = new wxMessageDialog(NULL, text, wxT("Error"), wxOK | wxICON_ERROR);
            msg->ShowModal();
            msg->Destroy();
        }
    }

    new_player_diag->Destroy();
}

void MainFrame::on_player_menu(wxCommandEvent& event)
{
    PlayerDialog *player_diag = new PlayerDialog(wxT("Players"), _players);
}

void MainFrame::on_scroll_up(wxCommandEvent& event)
{
    _player_list->Scroll(0, 0);
}

void MainFrame::on_scroll_down(wxCommandEvent& event)
{
    _player_list->Scroll(0, 100);
}

void MainFrame::update_player_list()
{
    _player_list->Destroy();
    _player_panel->SetSizer(nullptr);

    wxBoxSizer *player_sizer = new wxBoxSizer(wxHORIZONTAL);
    _player_list = new ScrollablePlayerInfo(_player_panel, wxID_ANY, _players);
    player_sizer->Add(_player_list, 1, wxEXPAND);
    _player_panel->SetSizer(player_sizer);
    _player_panel->Layout();
}
