#include "mainframe.hpp"

#include <wx/filedlg.h>
#include <wx/grid.h>
#include <wx/window.h>
#include <wx/radiobox.h>

#include "new_game_dialog.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Foosball ELO Rating")
{
    // players
    player player1{1, "Jaap", 1000.0, 5};
    player player2{2, "CC", 999.0, 5};
    player player3{3, "Richie", 998.0, 5};
    player player4{4, "Rick", 997.0, 5};
    _players.push_back(player1);
    _players.push_back(player2);
    _players.push_back(player3);
    _players.push_back(player4);


    // menu
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    wxMenu *menuPlayers = new wxMenu;
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


    // main screen
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddSpacer(20);
    wxStaticText *ranking = new wxStaticText(this, wxID_ANY, "Ranking", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT);
    ranking->SetFont( wxFont( 14, wxDEFAULT, wxNORMAL, wxBOLD, FALSE, "", wxFONTENCODING_SYSTEM ) );
    sizer->Add(ranking, 0, wxEXPAND | wxRIGHT | wxLEFT, 50);
    sizer->AddSpacer(20);

    // the table of players
    score_grid = new wxFlexGridSizer(2, 10, 3);
    sizer->Add(score_grid, 2, wxEXPAND | wxRIGHT | wxLEFT, 50);

    wxStaticText *name = new wxStaticText(this, wxID_ANY, "Name", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT);
    name->SetMinSize(wxSize(400, 25));
    name->SetSize(400, 25);

    wxStaticText *score = new wxStaticText(this, wxID_ANY, "Score", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT);
    score->SetMinSize(wxSize(50, 25));
    score->SetSize(50, 25);

    score_grid->Add(name, 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
    score_grid->Add(score, 0, wxEXPAND | wxRIGHT | wxLEFT, 0);

    
    add_score_to_list("Jaap", "1000");
    add_score_to_list("Richie", "999");

    sizer->AddSpacer(20);
    sizer->Add(new wxButton(this, ID_new_game, "New Game"), 0, wxEXPAND | wxRIGHT | wxLEFT, 250);
    sizer->AddSpacer(10);
    
    sizer->SetSizeHints(this);
    SetSizer(sizer);

    Bind(wxEVT_BUTTON, &MainFrame::on_new_game, this, ID_new_game);
    
    // icon
    wxIcon mainicon;
    if(mainicon.LoadFile(_icon_file)) {
        this->SetIcon(mainicon);
    }

    wxWindow::SetSize(wxDefaultCoord, wxDefaultCoord, _main_width, _main_height, wxSIZE_FORCE);
}

MainFrame::~MainFrame()
{}

void MainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("Foosball ELO Rating program by Jaap", "About ", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainFrame::on_new_game(wxCommandEvent& event) {
    int player_count = _players.size() + 1; // add 1 for first entry

    std::vector<uint> player_ids;
    std::vector<wxString> player_names;
    
    player_ids.push_back(0);
    player_names.push_back("-");

    for(int index = 0; index != _players.size(); index++)
    {
        player_ids.push_back(_players.at(index).id);
        player_names.push_back(_players.at(index).name);
    }

    // create and show dialog
    NewGameDialog *game_diag = new NewGameDialog(wxT("Enter Game Details"), _last_game_2v2, player_count, player_names, player_ids, _last_players);

    if(game_diag->ShowModal() == wxID_OK) {
        bool teams_2v2 = game_diag->get_teams_2v2();

        std::pair<uint, const std::string> player1 = game_diag->get_player1();
        std::pair<uint, const std::string> player2 = game_diag->get_player2();
        std::pair<uint, const std::string> player3 = game_diag->get_player3();
        std::pair<uint, const std::string> player4 = game_diag->get_player4();

        uint player1_id = player1.first;
        uint player2_id = player2.first;
        uint player3_id = player3.first;
        uint player4_id = player4.first;
        
        cout << "Game results:" << endl;
        cout << "Game type: " << (teams_2v2 ? "2 vs 2" : "1 vs 1") << endl;
        cout << "Selected players:" << endl;
        cout << "1. id: " << player1_id << ", name: " << player1.second << endl;
        cout << "2. id: " << player2_id << ", name: " << player2.second << endl;
        cout << "3. id: " << player3_id << ", name: " << player3.second << endl;
        cout << "4. id: " << player4_id << ", name: " << player4.second << endl;
        cout << "Score Team A: " << game_diag->get_score_a() << endl;
        cout << "Score Team B: " << game_diag->get_score_b() << endl;

        // check players
        if(player1_id == 0 || player2_id == 0) 
        {
            wxMessageDialog *msg = new wxMessageDialog(NULL, "Please select all players", wxT("Error"), wxOK | wxICON_ERROR);
            msg->ShowModal();
            return;
        }

        if(teams_2v2) 
        {
            if(player3_id == 0 || player4_id == 0) 
            {
                wxMessageDialog *msg = new wxMessageDialog(NULL, "Please select all players", wxT("Error"), wxOK | wxICON_ERROR);
                msg->ShowModal();
                return;
            }
        }
        else 
        {

            if(player1_id == player2_id) 
            {
                wxMessageDialog *msg = new wxMessageDialog(NULL, "Please select different players", wxT("Error"), wxOK | wxICON_ERROR);
                msg->ShowModal();
                return;
            }
        }

        // check results

        
        _last_game_2v2 = teams_2v2;
        _last_players[0] = player1_id;
        _last_players[1] = player2_id;
        _last_players[2] = player3_id;
        _last_players[3] = player4_id;
    }

    delete game_diag;
}

void MainFrame::add_score_to_list(const std::string &name, const std::string score)
{
    score_grid->Add(new wxStaticText(this, wxID_ANY, name, wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
    score_grid->Add(new wxStaticText(this, wxID_ANY, score, wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
}