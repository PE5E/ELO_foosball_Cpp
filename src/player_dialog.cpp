#include "player_dialog.hpp"

#include "scrollable_player_info_edit.hpp"

// https://zetcode.com/gui/wxwidgets/dialogs/

using std::cout;
using std::cerr;
using std::endl;

PlayerDialog::PlayerDialog(const wxString& title, const std::shared_ptr<std::vector<Player>> players) : 
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(700, 400)) 
{
    wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);

    // header
    wxBoxSizer *header_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *header_name = new wxStaticText(this, -1, "Name" , wxDefaultPosition, wxSize(300, 30), wxST_NO_AUTORESIZE);
    wxStaticText *header_score = new wxStaticText(this, -1, "Rating", wxDefaultPosition, wxSize(50, 30), wxST_NO_AUTORESIZE);
    header_sizer->Add(header_name);
    header_sizer->AddSpacer(20);
    header_sizer->Add(header_score);
    main_sizer->Add(header_sizer, 0, wxALL | wxEXPAND, 2);

    wxPanel *edit_player_panel = new wxPanel(this, -1, wxPoint(0, 0), wxSize(500, 250));
    wxBoxSizer *edit_player_sizer = new wxBoxSizer(wxHORIZONTAL);
    ScrollablePlayerInfoEdit* edit_player_list = new ScrollablePlayerInfoEdit(edit_player_panel, wxID_ANY, players);
    edit_player_sizer->Add(edit_player_list, 1, wxEXPAND);
    edit_player_panel->SetSizer(edit_player_sizer);
    main_sizer->Add(edit_player_panel, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxGROW, 5, NULL);

    SetSizer(main_sizer);
    Centre();
    ShowModal();
    Destroy(); 
}

PlayerDialog::~PlayerDialog() 
{
}
