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
    ScrollablePlayerInfo(wxWindow* parent, wxWindowID id, const std::shared_ptr<std::vector<Player>> players) : wxScrolledWindow(parent, id),
        _players((*players))
    {
        if((*players).size() == 0)
        {
            return;
        }

        remove_empty_and_sort_players();

        wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
        main_sizer->AddSpacer(5);
        
        for (int index = 0; index != _players.size(); index++)
        {
            const Player &player = _players[index];

            wxBoxSizer *player_sizer = new wxBoxSizer(wxHORIZONTAL);
            uint row_height = 26;
            std::string name;
            if(player.games_played < 5) // newbie
            {
                name = "* ";
            }
            name += player.name;

            wxFont font(11, wxDEFAULT, wxNORMAL, wxNORMAL);
            switch(index)
            {
                case 0: row_height = 34;
                    font.SetPointSize(15);
                    font.SetWeight(wxBOLD);
                    break;
                case 1: row_height = 32;
                    font.SetPointSize(13);
                    break;
                case 2: row_height = 28;
                    font.SetPointSize(12);
                    break;
                default:
                    ;
            }
            wxStaticText *player_nr = new wxStaticText(this, -1, wxString::Format(wxT("%d"), index + 1) , wxPoint(0, 0) , wxSize(80, row_height), wxST_NO_AUTORESIZE);
            player_nr->SetFont(font);
            player_nr->SetForegroundColour(wxColour(255, 255, 255));
            wxStaticText *player_name = new wxStaticText(this, -1, name , wxPoint(0, 0) , wxSize(300, row_height), wxST_NO_AUTORESIZE);
            player_name->SetFont(font);
            player_name->SetForegroundColour(wxColour(255, 255, 255));
            wxStaticText *player_score = new wxStaticText(this, -1, wxString::Format(wxT("%.0f"), player.rating), wxPoint(0, 0), wxSize(80, row_height), wxST_NO_AUTORESIZE);
            player_score->SetFont(font);
            player_score->SetForegroundColour(wxColour(255, 255, 255));
            player_sizer->AddSpacer(25);
            player_sizer->Add(player_nr);
            player_sizer->AddSpacer(10);
            player_sizer->Add(player_name);
            player_sizer->AddSpacer(10);
            player_sizer->Add(player_score);

            main_sizer->Add(player_sizer, 0, wxLEFT | wxRIGHT, 0);
        }

        this->SetSizer(main_sizer);
        this->FitInside();
        this->SetScrollRate(5, 5);
        this->SetSize(5000, 5000);
    }

    // function that will delete all players that are not enabled or have not played any games
    // and then sort based on ELO rating
    void remove_empty_and_sort_players()
    {
        _players.erase(std::remove_if(_players.begin(), 
                                        _players.end(),
                                        [](Player player){return (player.enabled == false || player.games_played == 0);}),
                                    _players.end());

        std::sort(_players.begin(), _players.end(), _players[0]); // sort local data based on ELO rating
    }

private:
    std::vector<Player> _players;

};



#endif // SCROLLABLE_PLAYER_INFO
