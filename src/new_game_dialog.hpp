#ifndef NEW_GAME_DIALOG_HPP
#define NEW_GAME_DIALOG_HPP

#include <wx/wx.h>

#include "data.hpp"

#include <memory>
#include <utility>
#include <vector>

class NewGameDialog : public wxDialog
{
public:
    NewGameDialog(const wxString& title, bool teams_2v2, const std::shared_ptr<std::vector<Player>> players, const uint last_player_ids[4]);
    ~NewGameDialog();
    bool get_teams_2v2();
    uint get_player1(); // returns player ID
    uint get_player2();
    uint get_player3();
    uint get_player4();
    uint get_score_a();
    uint get_score_b();

private:
    void set_players(wxCommandEvent &event);
    void score_input_a(wxCommandEvent &event);
    void score_input_b(wxCommandEvent &event);
    void player_input_1(wxCommandEvent &event);
    void player_input_2(wxCommandEvent &event);
    void player_input_3(wxCommandEvent &event);
    void player_input_4(wxCommandEvent &event);
    void keypad_score_a(wxCommandEvent &event);

private:
    wxComboBox *_teamA;
    wxComboBox *_teamB;
    wxRadioBox *_team_box;
    wxComboBox *_player1_box;
    wxComboBox *_player2_box;
    wxComboBox *_player3_box;
    wxComboBox *_player4_box;

    // wxWindowIDs
    const int ID_TEAMS_BOX = 1;
    const int ID_TEAM_A    = 2;
    const int ID_TEAM_B    = 3;
    const int ID_PLAYER_1  = 4;
    const int ID_PLAYER_2  = 5;
    const int ID_PLAYER_3  = 6;
    const int ID_PLAYER_4  = 7;

    bool _teams_2v2 = false;
    bool _first_score = true;
    uint _score_a = 0;
    uint _score_b = 0;

    std::vector<uint> _player_ids;

    uint _player1_id = 0;
    uint _player2_id = 0;
    uint _player3_id = 0;
    uint _player4_id = 0;

    std::vector<Player> _players;
};

#endif // NEW_GAME_DIALOG_HPP