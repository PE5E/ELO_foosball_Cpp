#ifndef SCROLLABLE_PLAYER_INFO_EDIT
#define SCROLLABLE_PLAYER_INFO_EDIT

#include <wx/wx.h>

#include "data.hpp"

#include <sstream>

class ScrollablePlayerInfoEdit : public wxScrolledWindow
{
public:
    ScrollablePlayerInfoEdit(wxWindow* parent, wxWindowID id, const std::vector<Player> players) : wxScrolledWindow(parent, id)
    {
        // the sizer will take care of determining the needed scroll size
        // (if you don't use sizers you will need to manually set the viewport size)
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        // header
        wxBoxSizer *header_sizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText *header_name = new wxStaticText(parent, -1, "Name" , wxDefaultPosition, wxSize(300, 30), wxST_NO_AUTORESIZE);
        wxStaticText *header_score = new wxStaticText(parent, -1, "Rating", wxDefaultPosition, wxSize(50, 30), wxST_NO_AUTORESIZE);
        header_sizer->Add(header_name);
        header_sizer->AddSpacer(20);
        header_sizer->Add(header_score);
        sizer->Add(header_sizer, 0, wxALL | wxEXPAND, 2);
        
        // add a series of widgets
        std::ostringstream out;
        out.precision(1);
        for (Player player : players)
        {
            out << std::fixed << player.rating;

            // player data
            wxBoxSizer *player_sizer = new wxBoxSizer(wxHORIZONTAL);
            wxStaticText *player_name = new wxStaticText(parent, -1, player.name , wxDefaultPosition, wxSize(300, 30), wxST_NO_AUTORESIZE);
            wxStaticText *player_score = new wxStaticText(parent, -1, out.str(), wxDefaultPosition, wxSize(50, 30), wxST_NO_AUTORESIZE);
            player_sizer->Add(player_name);
            player_sizer->AddSpacer(20);
            player_sizer->Add(player_score);
            player_sizer->AddSpacer(20);

            // buttons
            wxButton *edit_button = new wxButton(parent, -1, wxT("Edit"), wxDefaultPosition, wxSize(70, 20));
            wxButton *delete_button = new wxButton(parent, -1, wxT("Delete"), wxDefaultPosition, wxSize(70, 20));
            player_sizer->Add(edit_button);
            player_sizer->AddSpacer(20);
            player_sizer->Add(delete_button);

            sizer->Add(player_sizer, 0, wxALL | wxEXPAND, 2);

            out.str("");
            out.clear();
        }
        
        this->SetSizer(sizer);

        // this part makes the scrollbars show up
        this->FitInside(); // ask the sizer about the needed size
        this->SetScrollRate(5, 5);
    }

};

#endif // SCROLLABLE_PLAYER_INFO_EDIT