#include "new_game_dialog.hpp"

#include "mainframe.hpp" // for the IDs

// https://zetcode.com/gui/wxwidgets/dialogs/

NewGameDialog::NewGameDialog(const wxString& title, bool teams_2v2, const int total_players, const std::vector<wxString> player_names, const std::vector<uint> player_ids) : 
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(700, 400)) 
{
    _teams_2v2 = teams_2v2;
    _player_names = player_names;
    _player_ids = player_ids;

    wxString player_names_wx[total_players];
    for(int index = 0; index != total_players; index++)
    {
        player_names_wx[index] = player_names[index];
    }

    wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);
    
    /*
    wxPanel *panel1 = new wxPanel(this, -1);
    wxStaticBox *st1 = new wxStaticBox(panel1, -1, wxT("Resolution"), wxPoint(5, 5), wxSize(230, 120));
    wxStaticText *textH = new wxStaticText(panel1, wxID_ANY, "Horizontal:", wxPoint(15, 35));
    inputH = new wxTextCtrl(panel1, ID_TEXT1, wxT("0"), wxPoint(110, 35));
    wxStaticText *textV = new wxStaticText(panel1, wxID_ANY, "Vertical:", wxPoint(15, 75));
    inputV = new wxTextCtrl(panel1, ID_TEXT2, wxT("0"), wxPoint(110, 75));

    wxPanel *panel2 = new wxPanel(this, -1);
    wxStaticBox *st2 = new wxStaticBox(panel2, -1, wxT("Bitsize"), wxPoint(5, 5), wxSize(230, 100));
    wxStaticText *input_bytes = new wxStaticText(panel2, wxID_ANY, "Total bytes:", wxPoint(15, 30));
    input_bytes_nr = new wxStaticText(panel2, wxID_ANY, "0", wxPoint(110, 30));
    wxStaticText *bytespp = new wxStaticText(panel2, wxID_ANY, "Bits per pixel:", wxPoint(15, 65));
    bits_per_pixel = new wxStaticText(panel2, wxID_ANY, "0", wxPoint(110, 65));
    */

    wxPanel *panel1 = new wxPanel(this, -1);
    wxString teams[] = {"1 vs 1", "2 vs 2"};
    int team_count = 2;
    _team_box = new wxRadioBox(panel1, ID_TEAMS_BOX, _T(""), wxPoint(0, 0), wxDefaultSize, team_count,
                            teams, 1, wxRA_SPECIFY_ROWS | wxNO_BORDER, wxDefaultValidator, _T("Teams"));
    if(teams_2v2)
    {
        _team_box->SetSelection(1);
    }
    else
    {
        _team_box->SetSelection(0);
    }

    main_sizer->Add(panel1, 0, wxEXPAND | wxRIGHT | wxLEFT, 250);


    wxPanel *panel2 = new wxPanel(this, -1);
    wxStaticBox *st2 = new wxStaticBox(panel2, -1, wxT("Team A"), wxPoint(0, 0), wxSize(310, 200));
    
    _player1_box = new wxComboBox(panel2, ID_PLAYER_1, "Player 1", wxPoint(25, 30), wxSize(260, 30), total_players, player_names_wx, wxCB_READONLY, wxDefaultValidator, "player1");
    _player3_box = new wxComboBox(panel2, ID_PLAYER_3, "Player 3", wxPoint(25, 80), wxSize(260, 30), total_players, player_names_wx, wxCB_READONLY, wxDefaultValidator, "player3");
    _teamA = new wxTextCtrl(panel2, ID_TEAM_A, wxT(""), wxPoint(115, 150), wxSize(80, 40), wxTE_CENTRE, wxTextValidator(wxFILTER_DIGITS));
    _teamA->SetFont( wxFont( 14, wxDEFAULT, wxNORMAL, wxBOLD, FALSE, "", wxFONTENCODING_SYSTEM ) );

    wxPanel *panel3 = new wxPanel(this, -1);
    wxStaticBox *st3 = new wxStaticBox(panel3, -1, wxT("Team B"), wxPoint(0, 0), wxSize(310, 200));
    _player2_box = new wxComboBox(panel3, ID_PLAYER_2, "Player 2", wxPoint(25, 30), wxSize(260, 30), total_players, player_names_wx, wxCB_READONLY, wxDefaultValidator, "player2");
    _player4_box = new wxComboBox(panel3, ID_PLAYER_4, "Player 4", wxPoint(25, 80), wxSize(260, 30), total_players, player_names_wx, wxCB_READONLY, wxDefaultValidator, "player4");
    _teamB = new wxTextCtrl(panel3, ID_TEAM_B, wxT(""), wxPoint(115, 150), wxSize(80, 40), wxTE_CENTRE, wxTextValidator(wxFILTER_DIGITS));
    _teamB->SetFont( wxFont( 14, wxDEFAULT, wxNORMAL, wxBOLD, FALSE, "", wxFONTENCODING_SYSTEM ) );

    _player1_box->SetSelection(0);
    _player2_box->SetSelection(0);
    _player3_box->SetSelection(0);
    _player4_box->SetSelection(0);

    if(!teams_2v2)
    {
        _player3_box->Hide();
        _player4_box->Hide();
    }

    wxBoxSizer *team_sizer = new wxBoxSizer(wxHORIZONTAL);
    team_sizer->Add(panel2, 0, wxALL, 3);
    team_sizer->Add(panel3, 0, wxALL, 3);

    main_sizer->Add(team_sizer, 0, wxEXPAND | wxRIGHT | wxLEFT, 0);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    hbox2->Add(main_sizer); // add some space to the sides

    wxButton *okButton = new wxButton(this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxSize(100, 30));
    wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxSize(100, 30));

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(okButton, 1, wxRIGHT, 10);
    hbox->Add(closeButton, 1, wxLEFT, 10);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(hbox2, 1);
    vbox->Add(hbox, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    
    SetSizer(vbox);
    Centre();

    // bindings
    Connect(ID_TEAMS_BOX, wxEVT_RADIOBOX, wxCommandEventHandler(NewGameDialog::set_players));
    Connect(ID_TEAM_A, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(NewGameDialog::score_input_a));
    Connect(ID_TEAM_B, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(NewGameDialog::score_input_b));
    Connect(ID_PLAYER_1, wxEVT_COMBOBOX, wxCommandEventHandler(NewGameDialog::player_input_1));
    Connect(ID_PLAYER_2, wxEVT_COMBOBOX, wxCommandEventHandler(NewGameDialog::player_input_2));
    Connect(ID_PLAYER_3, wxEVT_COMBOBOX, wxCommandEventHandler(NewGameDialog::player_input_3));
    Connect(ID_PLAYER_4, wxEVT_COMBOBOX, wxCommandEventHandler(NewGameDialog::player_input_4));
}

NewGameDialog::~NewGameDialog() 
{
    delete _team_box;
    delete _player1_box;
    delete _player2_box;
    delete _player3_box;
    delete _player4_box;
    delete _teamA;
    delete _teamB;
}

bool NewGameDialog::get_teams_2v2()
{
   return _teams_2v2;
}
std::pair<uint, const std::string> NewGameDialog::get_player1()
{
    return std::pair<uint, const std::string>{_player1_id, std::string(_player1_name)};
}

std::pair<uint, const std::string> NewGameDialog::get_player2()
{
    return std::pair<uint, const std::string>{_player2_id, std::string(_player2_name)};
}

std::pair<uint, const std::string> NewGameDialog::get_player3()
{
    return std::pair<uint, const std::string>{_player3_id, std::string(_player3_name)};
}

std::pair<uint, const std::string> NewGameDialog::get_player4()
{
    return std::pair<uint, const std::string>{_player4_id, std::string(_player4_name)};
}

uint NewGameDialog::get_score_a()
{
    return _score_a;
}

uint NewGameDialog::get_score_b()
{
    return _score_b;
}

void NewGameDialog::set_players(wxCommandEvent &event) 
{
    _teams_2v2 = _team_box->GetSelection() == 1;
    std::cout << "Teams: " << (_teams_2v2 ? "2v2" : "1v1") << std::endl;

    if(_teams_2v2)
    {
        _player3_box->Show();
        _player4_box->Show();
    }
    else
    {
        _player3_box->Hide();
        _player4_box->Hide();
    }
}

void NewGameDialog::score_input_a(wxCommandEvent &event)
{

    int team_a = std::atoi(_teamA->GetLineText(0));
    
    if(team_a > 10) 
    {
         _teamA->ChangeValue("0"); // do not allow score > 10
         _score_a = 0;
    }
    else 
    {
        _score_a = team_a;
    }

    if(_first_score) 
    {
        _teamB->ChangeValue("10"); // set the score from other team to 10
        _score_b = 10;
    }

    _first_score = false;
    std::cout << "Team A: " << team_a << std::endl; 
}

void NewGameDialog::score_input_b(wxCommandEvent &event)
{
    int team_b = std::atoi(_teamB->GetLineText(0));
    
    if(team_b > 10) 
    {
        _teamB->ChangeValue("0"); // do not allow score > 10
        _score_b = 0;
    }
    else 
    {
        _score_b = team_b;
    }

    if(_first_score) 
    {
        _teamA->ChangeValue("10"); // set the score from other team to 10
        _score_a = 10;
    }

    _first_score = false;
    std::cout << "Team B: " << team_b << std::endl; 
}

void NewGameDialog::player_input_1(wxCommandEvent &event)
{
    std::cerr << "player_input_1: _player1_box->GetSelection(): ";
    std::cerr << _player1_box->GetSelection() << std::endl;
    _player1_id = _player_ids[_player1_box->GetSelection()];
    _player1_name = _player_names[_player1_box->GetSelection()];
}

void NewGameDialog::player_input_2(wxCommandEvent &event)
{
    _player2_id = _player_ids[_player2_box->GetSelection()];
    _player2_name = _player_names[_player2_box->GetSelection()];
}

void NewGameDialog::player_input_3(wxCommandEvent &event)
{
    _player3_id = _player_ids[_player3_box->GetSelection()];
    _player3_name = _player_names[_player3_box->GetSelection()];
}

void NewGameDialog::player_input_4(wxCommandEvent &event)
{
    _player4_id = _player_ids[_player4_box->GetSelection()];
    _player4_name = _player_names[_player4_box->GetSelection()];
}