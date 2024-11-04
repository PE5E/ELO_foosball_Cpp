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

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddSpacer(20);
    wxStaticText *ranking = new wxStaticText(this, wxID_ANY, "Ranking", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT);
    ranking->SetFont( wxFont( 14, wxDEFAULT, wxNORMAL, wxBOLD, FALSE, "", wxFONTENCODING_SYSTEM ) );
    sizer->Add(ranking, 0, wxEXPAND | wxRIGHT | wxLEFT, 50);
    sizer->AddSpacer(20);

    // the table of players
    score_grid = new wxFlexGridSizer(2, 10, 3);
    sizer->Add(score_grid, 2, wxEXPAND | wxRIGHT | wxLEFT, 50);

    wxStaticText * name = new wxStaticText(this, wxID_ANY, "Name", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT);
    name->SetMinSize(wxSize(400, 25));
    name->SetSize(400, 25);

    wxStaticText * score = new wxStaticText(this, wxID_ANY, "Score", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT);
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

    wxWindow::SetSize(wxDefaultCoord, wxDefaultCoord, 800, 400, wxSIZE_AUTO);
}

MainFrame::~MainFrame(){}

void MainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("Foosball ELO Rating program by Jaap", "About ", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainFrame::on_new_game(wxCommandEvent& event) {
    NewGameDialog *game_diag = new NewGameDialog(wxT("Enter Game Details"), _last_game_2v2);
    game_diag->setBytes(1024);

    if(game_diag->ShowModal() == wxID_OK) {
        bool teams_2v2 = game_diag->getTeams2v2();

        // int resH = std::stoi(game_diag->getResolutionH().ToStdString());
        // int resV = std::stoi(game_diag->getResolutionV().ToStdString());
        //sstd::cout << "Set image resolution to width: " << resV << " and height: " << resH << std::endl;

        // Image_type type = static_cast<Image_type>(game_diag->getBitDepth() + 1);
        // Image_channels channels = static_cast<Image_channels>(game_diag->getChannels());
        // int loaded_bytes = _image->open_file(file, type, resH, resV, channels);
        _last_game_2v2 = teams_2v2;
    }
    else {
        // std::cout << "No resolution was set. Not loading the picture." << std::endl;
    }
    delete game_diag;
}

void MainFrame::OnFileLoad(wxCommandEvent& event) {
    try {
        wxFileDialog *file_dialog = new wxFileDialog(this, "Open picture file", "", "", "", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        // file_dialog->SetExtraControlCreator(&file_load_dialog);
        file_dialog->ShowModal();
        std::string file(file_dialog->GetPath());

        // option data
        // file_option_data const * const file_options{ static_cast<file_option_data const*>(file_dialog->GetClientObject())};
        // if (file_options == nullptr) {
        //     std::cerr << "file_options == nullptr" << std::endl;
        //     return;
        // }
        // _input_type_int = file_options->input_type_int;
        // _input_type_string = file_options->input_type_string;
        
        // std::cerr << "File location selected: " << file << " with option: " << _input_type_int << " " 
        //     << _input_type_string << std::endl;

        int file_size = std::filesystem::file_size(file);

        if(file_size < 1) {
            std::cout << "The selected file does not contain valid data." << std::endl;
            return;
        }

        if(file.size() > 4 && file.at(file.size() - 4) == '.') {
            std::string extension = file.substr(file.size() - 3);
            if(extension == "jpg" || extension == "bmp" || extension == "png")
            {
                // _image->open_file(file, Image_type::compressed);
            }
        }
        else {
            /*ResolutionDialog *res_diag = new ResolutionDialog(wxT("Set Resolution"));
            res_diag->setBytes(file_size);

            if(res_diag->ShowModal() == wxID_OK) {
                int resH = std::stoi(res_diag->getResolutionH().ToStdString());
                int resV = std::stoi(res_diag->getResolutionV().ToStdString());
                std::cout << "Set image resolution to width: " << resV << " and height: " << resH << std::endl;

                // Image_type type = static_cast<Image_type>(res_diag->getBitDepth() + 1);
                // Image_channels channels = static_cast<Image_channels>(res_diag->getChannels());
                // int loaded_bytes = _image->open_file(file, type, resH, resV, channels);
            }
            else {
                std::cout << "No resolution was set. Not loading the picture." << std::endl;
            }
            delete res_diag;
            */
        }
    }
    catch(std::exception ex) {
        std::cerr << "Error in file loading: " << ex.what() << std::endl;
    }
}

void MainFrame::add_score_to_list(const std::string &name, const std::string score)
{
    score_grid->Add(new wxStaticText(this, wxID_ANY, name, wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
    score_grid->Add(new wxStaticText(this, wxID_ANY, score, wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
}