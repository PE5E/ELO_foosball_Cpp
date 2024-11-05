#ifndef NEW_GAME_DIALOG_HPP
#define NEW_GAME_DIALOG_HPP

#include <wx/wx.h>

class NewGameDialog : public wxDialog
{
public:
    NewGameDialog(const wxString& title, bool teams_2v2 = false);
    ~NewGameDialog();
    bool getTeams2v2();

private:
    void set_players(wxCommandEvent & event);
    void score_inputs(wxCommandEvent & event);

private:
    wxTextCtrl *_teamA;
    wxTextCtrl *_teamB;
    wxRadioBox *_team_box;
    wxComboBox *_player1_box;
    wxComboBox *_player2_box;
    wxComboBox *_player3_box;
    wxComboBox *_player4_box;


    const int ID_TEAMS_BOX = 1;
    const int ID_TEAM_A = 2;
    const int ID_TEAM_B = 3;
    bool _teams_2v2;

};

#endif // NEW_GAME_DIALOG_HPP