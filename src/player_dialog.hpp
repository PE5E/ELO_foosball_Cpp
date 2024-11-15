#ifndef PLAYER_DIALOG_HPP
#define PLAYER_DIALOG_HPP

#include <wx/wx.h>

#include "data.hpp"

#include <memory>
#include <vector>


class PlayerDialog : public wxDialog
{
public:
    PlayerDialog(const wxString& title, const std::shared_ptr<std::vector<Player>> players);
    ~PlayerDialog();


private:
};

#endif // PLAYER_DIALOG_HPP