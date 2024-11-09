#include "player_dialog.hpp"

#include "scrollable_player_info.hpp"

// https://zetcode.com/gui/wxwidgets/dialogs/

using std::cout;
using std::cerr;
using std::endl;

PlayerDialog::PlayerDialog(const wxString& title, const std::vector<Player> &players) : 
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(700, 400)) 
{
    _players = players;

    wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);


    ScrollablePlayerInfo* player_list = new ScrollablePlayerInfo(this, wxID_ANY, _players);
    main_sizer->Add(player_list, 1, wxEXPAND);

    /*
    
    
    wxPanel *panel1 = new wxPanel(this, -1);
    main_sizer->Add(panel1, 0, wxEXPAND | wxRIGHT | wxLEFT, 250);

    wxPanel *panel2 = new wxPanel(this, -1);
    wxStaticBox *st2 = new wxStaticBox(panel2, -1, wxT("Team A"), wxPoint(0, 0), wxSize(310, 200));
    wxStaticText *player1_txt = new wxStaticText(panel2, -1, players.at(0), wxPoint(25, 30), wxSize(260, 30), wxST_NO_AUTORESIZE, "player1");
    wxPanel *panel4 = new wxPanel(panel2, -1, wxPoint(115, 150), wxSize(82, 42), wxSIMPLE_BORDER);
    wxStaticText *teamA_txt = new wxStaticText(panel4, -1, score_team_a, wxPoint(0, 8), wxSize(80, 40), wxST_NO_AUTORESIZE | wxALIGN_CENTRE, "Score Team A");
    teamA_txt->SetFont( wxFont(14, wxDEFAULT, wxNORMAL, wxNORMAL, FALSE, "", wxFONTENCODING_SYSTEM));

    wxPanel *panel3 = new wxPanel(this, -1);
    wxStaticBox *st3 = new wxStaticBox(panel3, -1, wxT("Team B"), wxPoint(0, 0), wxSize(310, 200));
    wxStaticText *player2_txt = new wxStaticText(panel3, -1, players.at(1), wxPoint(25, 30), wxSize(260, 30), wxST_NO_AUTORESIZE, "player2");
    wxPanel *panel5 = new wxPanel(panel3, -1, wxPoint(115, 150), wxSize(82, 42), wxSIMPLE_BORDER);
    wxStaticText *teamB_txt = new wxStaticText(panel5, -1, score_team_b, wxPoint(0, 8), wxSize(80, 40), wxST_NO_AUTORESIZE | wxALIGN_CENTRE, "Score Team B");
    teamB_txt->SetFont( wxFont(14, wxDEFAULT, wxNORMAL, wxNORMAL, FALSE, "", wxFONTENCODING_SYSTEM));

    if(teams_2v2)
    {
        wxStaticText *player3_txt = new wxStaticText(panel2, -1, players.at(2), wxPoint(25, 80), wxSize(260, 30), wxST_NO_AUTORESIZE, "player3");
        wxStaticText *player4_txt = new wxStaticText(panel3, -1, players.at(3), wxPoint(25, 80), wxSize(260, 30), wxST_NO_AUTORESIZE, "player4");
    }

    if(a_is_winner)
    {
        teamA_txt->SetFont( wxFont(16, wxDEFAULT, wxNORMAL, wxBOLD, FALSE, "", wxFONTENCODING_SYSTEM));
    }
    else
    {
        teamB_txt->SetFont( wxFont(16, wxDEFAULT, wxNORMAL, wxBOLD, FALSE, "", wxFONTENCODING_SYSTEM));
    }

    wxBoxSizer *team_sizer = new wxBoxSizer(wxHORIZONTAL);
    team_sizer->Add(panel2, 0, wxALL, 3);
    team_sizer->Add(panel3, 0, wxALL, 3);

    main_sizer->Add(team_sizer, 0, wxEXPAND | wxRIGHT | wxLEFT, 0);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    hbox2->Add(main_sizer); // add some space to the sides

    wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"), wxDefaultPosition, wxSize(100, 30));

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(closeButton, 1, wxLEFT, 10);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(hbox2, 1);
    vbox->Add(hbox, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    */
    
    SetSizer(main_sizer);
    Centre();
    ShowModal();
    Destroy(); 
}

PlayerDialog::~PlayerDialog() 
{
}
