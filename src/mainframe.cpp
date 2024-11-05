#include "mainframe.hpp"

#include <wx/filedlg.h>
#include <wx/grid.h>
#include <wx/window.h>
#include <wx/radiobox.h>

#include "new_game_dialog.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>


MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Foosball ELO Rating")
{
    _last_game_2v2 = false;
    _main_width = 800;
    _main_height = 400;

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

    wxWindow::SetSize(wxDefaultCoord, wxDefaultCoord, _main_width, _main_height, wxSIZE_AUTO);
}

MainFrame::~MainFrame()
{
    delete score_grid;
}

void MainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("Foosball ELO Rating program by Jaap", "About ", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainFrame::on_new_game(wxCommandEvent& event) {
    NewGameDialog *game_diag = new NewGameDialog(wxT("Enter Game Details"), _last_game_2v2);

    if(game_diag->ShowModal() == wxID_OK) {
        bool teams_2v2 = game_diag->getTeams2v2();

        _last_game_2v2 = teams_2v2;
    }
    else {
        // std::cout << "No resolution was set. Not loading the picture." << std::endl;
    }
    delete game_diag;
}

void MainFrame::add_score_to_list(const std::string &name, const std::string score)
{
    score_grid->Add(new wxStaticText(this, wxID_ANY, name, wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
    score_grid->Add(new wxStaticText(this, wxID_ANY, score, wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
}