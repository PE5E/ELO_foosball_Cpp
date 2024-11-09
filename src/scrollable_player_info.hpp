#ifndef SCROLLABLE_PLAYER_INFO
#define SCROLLABLE_PLAYER_INFO

#include <wx/wx.h>

#include "data.hpp"

#include <sstream>

class ScrollablePlayerInfo : public wxScrolledWindow
{
public:
    ScrollablePlayerInfo(wxWindow* parent, wxWindowID id, const std::vector<Player> players) : wxScrolledWindow(parent, id)
    {
        // the sizer will take care of determining the needed scroll size
        // (if you don't use sizers you will need to manually set the viewport size)
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        
        // add a series of widgets
        std::ostringstream out;
        out.precision(1);
        for (Player player : players)
        {
            out << std::fixed << player.rating;
            wxBoxSizer *player_sizer = new wxBoxSizer(wxHORIZONTAL);
            wxStaticText *player_name = new wxStaticText(parent, -1, player.name , wxDefaultPosition, wxSize(250, 30), wxST_NO_AUTORESIZE);
            wxStaticText *player_score = new wxStaticText(parent, -1, out.str(), wxDefaultPosition, wxSize(50, 30), wxST_NO_AUTORESIZE);
            player_sizer->Add(player_name);
            player_sizer->Add(player_score);

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

#endif // SCROLLABLE_PLAYER_INFO