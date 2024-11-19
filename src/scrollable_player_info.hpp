#ifndef SCROLLABLE_PLAYER_INFO
#define SCROLLABLE_PLAYER_INFO

#include <wx/wx.h>

#include "data.hpp"

#include <algorithm> 
#include <sstream>
#include <vector>

class ScrollablePlayerInfo : public wxScrolledWindow
{
public:
    ScrollablePlayerInfo(wxWindow* parent, wxWindowID id, const std::shared_ptr<std::vector<Player>> players) : wxScrolledWindow(parent, id)
    {
        wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
        main_sizer->AddSpacer(2);

        std::vector<Player> _players((*players));
        std::sort(_players.begin(), _players.end(), _players[0]); // sort local data based on ELO rating
        
        for (int index = 0; index != _players.size(); index++)
        {
            const Player &player = _players[index];

            // check if player can be displayed
            if(player.enabled == false)
            {
                continue;
            }

            wxBoxSizer *player_sizer = new wxBoxSizer(wxHORIZONTAL);
            wxStaticText *player_nr = new wxStaticText(this, -1, wxString::Format(wxT("%d"), index + 1) , wxPoint(0, 0) , wxSize(80, 30), wxST_NO_AUTORESIZE);
            wxStaticText *player_name = new wxStaticText(this, -1, player.name , wxPoint(0, 0) , wxSize(300, 30), wxST_NO_AUTORESIZE);
            wxStaticText *player_score = new wxStaticText(this, -1, wxString::Format(wxT("%.0f"), player.rating), wxPoint(0, 0), wxSize(80, 30), wxST_NO_AUTORESIZE);
            player_sizer->AddSpacer(25);
            player_sizer->Add(player_nr);
            player_sizer->AddSpacer(10);
            player_sizer->Add(player_name);
            player_sizer->AddSpacer(10);
            player_sizer->Add(player_score);

            main_sizer->Add(player_sizer, 1, wxALL, 1);
        }

        this->SetSizer(main_sizer);
        this->FitInside();
        this->SetScrollRate(5, 5);
        this->SetSize(5000, 5000);
    }
};

#endif // SCROLLABLE_PLAYER_INFO