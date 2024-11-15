#ifndef SCROLLABLE_PLAYER_INFO_EDIT
#define SCROLLABLE_PLAYER_INFO_EDIT

#include <wx/wx.h>

#include "data.hpp"

#include <sstream>

class ScrollablePlayerInfoEdit : public wxScrolledWindow
{
public:
    ScrollablePlayerInfoEdit(wxWindow* parent, wxWindowID id, const std::shared_ptr<std::vector<Player>> players) : wxScrolledWindow(parent, id)
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        
        std::ostringstream out;
        out.precision(1);
        for (int index = 0; index != players->size(); index++)
        {
            const Player &player = (*players)[index];
            out << std::fixed << player.rating;

            // player data
            wxBoxSizer *player_sizer = new wxBoxSizer(wxHORIZONTAL);
            wxStaticText *player_name = new wxStaticText(this, -1, player.name , wxDefaultPosition, wxSize(300, 30), wxST_NO_AUTORESIZE);
            wxStaticText *player_score = new wxStaticText(this, -1, out.str(), wxDefaultPosition, wxSize(50, 30), wxST_NO_AUTORESIZE);
            player_sizer->Add(player_name);
            player_sizer->AddSpacer(20);
            player_sizer->Add(player_score);
            player_sizer->AddSpacer(20);

            // buttons
            wxButton *edit_button = new wxButton(this, -1, wxT("Edit"), wxDefaultPosition, wxSize(70, 20));
            wxButton *delete_button = new wxButton(this, -1, wxT("Delete"), wxDefaultPosition, wxSize(70, 20));
            player_sizer->Add(edit_button);
            player_sizer->AddSpacer(20);
            player_sizer->Add(delete_button);

            sizer->Add(player_sizer, 0, wxALL | wxEXPAND, 2);

            out.str("");
            out.clear();
        }
        
        this->SetSizer(sizer);
        this->FitInside();
        this->SetScrollRate(5, 5);
    }
};

#endif // SCROLLABLE_PLAYER_INFO_EDIT