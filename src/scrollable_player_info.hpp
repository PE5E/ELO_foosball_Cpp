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
        wxBoxSizer* scroll_sizer = new wxBoxSizer(wxVERTICAL);

        // header
        wxBoxSizer *header_sizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText *header_name = new wxStaticText(this, -1, "Name" , wxPoint(0, 0), wxSize(300, 30), wxST_NO_AUTORESIZE);
        wxStaticText *header_score = new wxStaticText(this, -1, "Rating", wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
        header_sizer->Add(header_name);
        header_sizer->AddSpacer(20);
        header_sizer->Add(header_score);
        scroll_sizer->Add(header_sizer, 1, wxALL, 2);
        
        // add a series of widgets
        std::ostringstream out;
        out.precision(1);
        for (Player player : players)
        {
            out << std::fixed << player.rating;
            wxBoxSizer *player_sizer = new wxBoxSizer(wxHORIZONTAL);
            wxStaticText *player_name = new wxStaticText(this, -1, player.name , wxPoint(0, 0) , wxSize(300, 30), wxST_NO_AUTORESIZE); // wxDefaultPosition
            wxStaticText *player_score = new wxStaticText(this, -1, out.str(), wxPoint(0, 0), wxSize(50, 30), wxST_NO_AUTORESIZE);
            player_sizer->Add(player_name);
            player_sizer->AddSpacer(20);
            player_sizer->Add(player_score);

            scroll_sizer->Add(player_sizer, 1, wxALL, 2);

            out.str("");
            out.clear();
        }

        this->SetSizer(scroll_sizer);
        this->FitInside();
        this->SetScrollRate(5, 5);
    }
};

#endif // SCROLLABLE_PLAYER_INFO