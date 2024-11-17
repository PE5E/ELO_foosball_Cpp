#ifndef SCORE_DIALOG_HPP
#define SCORE_DIALOG_HPP

#include <wx/wx.h>

#include "elo_calculator.hpp"

#include <vector>
#include <string>


class ScoreDialog : public wxDialog
{
public:
    ScoreDialog(const wxString& title, bool teams_2v2, const std::vector<EloPlayer> players, const std::string &score_team_a, const std::string &score_team_b, bool a_is_winner);
    ~ScoreDialog();


private:

};

#endif // SCORE_DIALOG_HPP