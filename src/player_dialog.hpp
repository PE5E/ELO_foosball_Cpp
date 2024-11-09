#ifndef PLAYER_DIALOG_HPP
#define PLAYER_DIALOG_HPP

#include <wx/wx.h>

#include "data.hpp"

#include <vector>


class PlayerDialog : public wxDialog
{
public:
    PlayerDialog(const wxString& title, const std::vector<Player> &players);
    ~PlayerDialog();


private:
    std::vector<Player> _players;
};

#endif // PLAYER_DIALOG_HPP