#include "mainframe.hpp"

#include <wx/filedlg.h>
#include <wx/grid.h>
#include <wx/window.h>
#include <wx/radiobox.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>


MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Foosball ELO Rating")
{
  
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
    sizer->Add(new wxStaticText(this, wxID_ANY, "Player Ranking", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 50);
    sizer->AddSpacer(20);

    // the table of players
    wxFlexGridSizer *grid_sizer = new wxFlexGridSizer(2, 10, 3);
    sizer->Add(grid_sizer, 0, wxEXPAND | wxRIGHT | wxLEFT, 50);

    grid_sizer->Add(new wxStaticText(this, wxID_ANY, "Name", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
    grid_sizer->Add(new wxStaticText(this, wxID_ANY, "Score", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
    grid_sizer->Add(new wxStaticText(this, wxID_ANY, "Fastjack", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
    grid_sizer->Add(new wxStaticText(this, wxID_ANY, "1000", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
    grid_sizer->Add(new wxStaticText(this, wxID_ANY, "Richie", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);
    grid_sizer->Add(new wxStaticText(this, wxID_ANY, "999", wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT), 0, wxEXPAND | wxRIGHT | wxLEFT, 0);

    // wxImagePanel *picture_org = new wxImagePanel( this, wxT("image2.jpg"), wxBITMAP_TYPE_JPEG);
    // sizer->Add(picture_org, 1, wxEXPAND);

    sizer->AddSpacer(20);
    sizer->Add(new wxButton(this, ID_new_game, "New Game"), 0, wxEXPAND | wxRIGHT | wxLEFT, 250);
    sizer->AddSpacer(20);
    
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
    wxMessageBox("Foosball ELO Rating program by Jaap",
                 "About ", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainFrame::on_new_game(wxCommandEvent& event) {
        wxMessageBox("Player:", "Enter game details", wxOK | wxICON_INFORMATION);
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
