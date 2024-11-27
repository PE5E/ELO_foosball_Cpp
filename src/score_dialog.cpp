#include "score_dialog.hpp"

// https://zetcode.com/gui/wxwidgets/dialogs/

using std::cout;
using std::cerr;
using std::endl;

ScoreDialog::ScoreDialog(const wxString& title, bool teams_2v2, const std::vector<EloPlayer> players, const std::string &score_team_a, const std::string &score_team_b, bool a_is_winner) : 
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(700, 400)) 
{
    wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);
    
    // Team A
    wxPanel *panel_a = new wxPanel(this, -1);
    panel_a->SetBackgroundColour(wxColour(160, 40, 40));
    wxStaticBox *st_a = new wxStaticBox(panel_a, -1, wxT("Team A"), wxPoint(0, 0), wxSize(310, 230));

    wxBoxSizer *team_a_sizer = new wxBoxSizer(wxVERTICAL);
    team_a_sizer->AddSpacer(30);
    
    // header
    wxBoxSizer *header_a_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *header_a1_txt = new wxStaticText(panel_a, -1, "name", wxPoint(0, 0), wxSize(100, 30), wxST_NO_AUTORESIZE);
    header_a_sizer->AddSpacer(10);
    header_a_sizer->Add(header_a1_txt, 0);
    header_a_sizer->AddSpacer(10);
    wxStaticText *header_a2_txt = new wxStaticText(panel_a, -1, "old", wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    header_a_sizer->Add(header_a2_txt, 0);
    header_a_sizer->AddSpacer(10);
    wxStaticText *header_a3_txt = new wxStaticText(panel_a, -1, "diff", wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    header_a_sizer->Add(header_a3_txt, 0);
    header_a_sizer->AddSpacer(10);
    wxStaticText *header_a4_txt = new wxStaticText(panel_a, -1, "new", wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    header_a_sizer->Add(header_a4_txt, 0);
    team_a_sizer->Add(header_a_sizer, 0);

    // add a * before name of newbie
    std::string name1;
    if(players.at(0).games_played < 5) // newbie
    {
        name1 = "* ";
    }
    name1 += players.at(0).name;

    std::string name2;
    if(players.at(1).games_played < 5) // newbie
    {
        name2 = "* ";
    }
    name2 += players.at(1).name;

    std::string name3;
    std::string name4;
    
    if(teams_2v2)
    {    
        if(players.at(2).games_played < 5) // newbie
        {
            name3 = "* ";
        }
        name3 += players.at(2).name;

        if(players.at(3).games_played < 5) // newbie
        {
            name4 = "* ";
        }
        name4 += players.at(3).name;
    }

    // player 1
    wxBoxSizer *player_1_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *player_1_name = new wxStaticText(panel_a, -1, name1, wxPoint(0, 0), wxSize(100, 30), wxST_NO_AUTORESIZE);
    player_1_sizer->AddSpacer(10);
    player_1_sizer->Add(player_1_name, 0);
    player_1_sizer->AddSpacer(10);
    wxStaticText *player_1_o_elo = new wxStaticText(panel_a, -1, wxString::Format(wxT("%.0f"), players.at(0).old_elo), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    player_1_sizer->Add(player_1_o_elo, 0);
    player_1_sizer->AddSpacer(10);
    wxStaticText *player_1_elo_diff = new wxStaticText(panel_a, -1, wxString::Format(wxT("%.0f"), players.at(0).elo_diff), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    player_1_sizer->Add(player_1_elo_diff, 0);
    player_1_sizer->AddSpacer(10);
    wxStaticText *player_1_n_elo = new wxStaticText(panel_a, -1, wxString::Format(wxT("%.0f"), players.at(0).new_elo), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    player_1_sizer->Add(player_1_n_elo, 0);
    team_a_sizer->Add(player_1_sizer, 0);
    team_a_sizer->AddSpacer(10);

    // player 3
    if(teams_2v2)
    {
        wxBoxSizer *player_3_sizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText *player_3_name = new wxStaticText(panel_a, -1, name3, wxPoint(0, 0), wxSize(100, 30), wxST_NO_AUTORESIZE);
        player_3_sizer->AddSpacer(10);
        player_3_sizer->Add(player_3_name, 0);
        player_3_sizer->AddSpacer(10);
        wxStaticText *player_3_o_elo = new wxStaticText(panel_a, -1, wxString::Format(wxT("%.0f"), players.at(2).old_elo), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
        player_3_sizer->Add(player_3_o_elo, 0);
        player_3_sizer->AddSpacer(10);
        wxStaticText *player_3_elo_diff = new wxStaticText(panel_a, -1, wxString::Format(wxT("%.0f"), players.at(2).elo_diff), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
        player_3_sizer->Add(player_3_elo_diff, 0);
        player_3_sizer->AddSpacer(10);
        wxStaticText *player_3_n_elo = new wxStaticText(panel_a, -1, wxString::Format(wxT("%.0f"), players.at(2).new_elo), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
        player_3_sizer->Add(player_3_n_elo, 0);
        team_a_sizer->Add(player_3_sizer, 0);
        team_a_sizer->AddSpacer(10);
    }

    st_a->SetSizer(team_a_sizer);

    // score team A
    wxPanel *panel4 = new wxPanel(panel_a, -1, wxPoint(115, 170), wxSize(82, 42), wxSIMPLE_BORDER);
    wxStaticText *teamA_txt = new wxStaticText(panel4, -1, score_team_a, wxPoint(0, 8), wxSize(80, 40), wxST_NO_AUTORESIZE | wxALIGN_CENTRE, "Score Team A");
    teamA_txt->SetFont( wxFont(14, wxDEFAULT, wxNORMAL, wxNORMAL, FALSE, "", wxFONTENCODING_SYSTEM));



    // Team B
    wxPanel *panel_b = new wxPanel(this, -1);
    panel_b->SetBackgroundColour(wxColour(20, 20, 160));
    wxStaticBox *st_b = new wxStaticBox(panel_b, -1, wxT("Team B"), wxPoint(0, 0), wxSize(310, 230));

    wxBoxSizer *team_b_sizer = new wxBoxSizer(wxVERTICAL);
    team_b_sizer->AddSpacer(30);
    
    // header
    wxBoxSizer *header_b_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *header_b1_txt = new wxStaticText(panel_b, -1, "name", wxPoint(0, 0), wxSize(100, 30), wxST_NO_AUTORESIZE);
    header_b_sizer->AddSpacer(10);
    header_b_sizer->Add(header_b1_txt, 0);
    header_b_sizer->AddSpacer(10);
    wxStaticText *header_b2_txt = new wxStaticText(panel_b, -1, "old", wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    header_b_sizer->Add(header_b2_txt, 0);
    header_b_sizer->AddSpacer(10);
    wxStaticText *header_b3_txt = new wxStaticText(panel_b, -1, "diff", wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    header_b_sizer->Add(header_b3_txt, 0);
    header_b_sizer->AddSpacer(10);
    wxStaticText *header_b4_txt = new wxStaticText(panel_b, -1, "new", wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    header_b_sizer->Add(header_b4_txt, 0);
    team_b_sizer->Add(header_b_sizer, 0);

    // player 2
    wxBoxSizer *player_2_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *player_2_name = new wxStaticText(panel_b, -1, name2, wxPoint(0, 0), wxSize(100, 30), wxST_NO_AUTORESIZE);
    player_2_sizer->AddSpacer(10);
    player_2_sizer->Add(player_2_name, 0);
    player_2_sizer->AddSpacer(10);
    wxStaticText *player_2_o_elo = new wxStaticText(panel_b, -1, wxString::Format(wxT("%.0f"), players.at(1).old_elo), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    player_2_sizer->Add(player_2_o_elo, 0);
    player_2_sizer->AddSpacer(10);
    wxStaticText *player_2_elo_diff = new wxStaticText(panel_b, -1, wxString::Format(wxT("%.0f"), players.at(1).elo_diff), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    player_2_sizer->Add(player_2_elo_diff, 0);
    player_2_sizer->AddSpacer(10);
    wxStaticText *player_2_n_elo = new wxStaticText(panel_b, -1, wxString::Format(wxT("%.0f"), players.at(1).new_elo), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
    player_2_sizer->Add(player_2_n_elo, 0);
    team_b_sizer->Add(player_2_sizer, 0);
    team_b_sizer->AddSpacer(10);

    // player 4
    if(teams_2v2)
    {
        wxBoxSizer *player_4_sizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText *player_4_name = new wxStaticText(panel_b, -1, name4, wxPoint(0, 0), wxSize(100, 30), wxST_NO_AUTORESIZE);
        player_4_sizer->AddSpacer(10);
        player_4_sizer->Add(player_4_name, 0);
        player_4_sizer->AddSpacer(10);
        wxStaticText *player_4_o_elo = new wxStaticText(panel_b, -1, wxString::Format(wxT("%.0f"), players.at(3).old_elo), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
        player_4_sizer->Add(player_4_o_elo, 0);
        player_4_sizer->AddSpacer(10);
        wxStaticText *player_4_elo_diff = new wxStaticText(panel_b, -1, wxString::Format(wxT("%.0f"), players.at(3).elo_diff), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
        player_4_sizer->Add(player_4_elo_diff, 0);
        player_4_sizer->AddSpacer(10);
        wxStaticText *player_4_n_elo = new wxStaticText(panel_b, -1, wxString::Format(wxT("%.0f"), players.at(3).new_elo), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
        player_4_sizer->Add(player_4_n_elo, 0);
        team_b_sizer->Add(player_4_sizer, 0);
        team_b_sizer->AddSpacer(10);
    }

    st_b->SetSizer(team_b_sizer);

    
    // score team B
    wxPanel *panel5 = new wxPanel(panel_b, -1, wxPoint(115, 170), wxSize(82, 42), wxSIMPLE_BORDER);
    wxStaticText *teamB_txt = new wxStaticText(panel5, -1, score_team_b, wxPoint(0, 8), wxSize(80, 40), wxST_NO_AUTORESIZE | wxALIGN_CENTRE, "Score Team B");
    teamB_txt->SetFont( wxFont(14, wxDEFAULT, wxNORMAL, wxNORMAL, FALSE, "", wxFONTENCODING_SYSTEM));

    if(a_is_winner)
    {
        teamA_txt->SetFont( wxFont(16, wxDEFAULT, wxNORMAL, wxBOLD, FALSE, "", wxFONTENCODING_SYSTEM));
    }
    else
    {
        teamB_txt->SetFont( wxFont(16, wxDEFAULT, wxNORMAL, wxBOLD, FALSE, "", wxFONTENCODING_SYSTEM));
    }

    wxBoxSizer *team_sizer = new wxBoxSizer(wxHORIZONTAL);
    team_sizer->Add(panel_a, 0, wxALL, 3);
    team_sizer->Add(panel_b, 0, wxALL, 3);

    main_sizer->Add(team_sizer, 0, wxEXPAND | wxRIGHT | wxLEFT, 0);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    hbox2->Add(main_sizer); // add some space to the sides

    wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"), wxDefaultPosition, wxSize(100, 30));

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(closeButton, 1, wxLEFT, 10);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(hbox2, 1);
    vbox->Add(hbox, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    
    SetSizer(vbox);
    Centre();
    ShowModal();
    Destroy(); 
}

ScoreDialog::~ScoreDialog() 
{
}
