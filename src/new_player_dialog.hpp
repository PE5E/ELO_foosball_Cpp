#ifndef NEW_PLAYER_DIALOG_HPP
#define NEW_PLAYER_DIALOG_HPP

#include <wx/wx.h>

#include <utility>
#include <vector>

class NewPlayerDialog : public wxDialog
{
public:
    NewPlayerDialog(const wxString& title);
    ~NewPlayerDialog();
    wxString get_player_name();

private:
    void set_name(wxCommandEvent &event);

    wxString _player_name = "";
    wxTextCtrl *name_input;
};

#endif // NEW_PLAYER_DIALOG_HPP