#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "data.hpp"

#include <memory>
#include <string>
#include <vector>

class MainFrame : public wxFrame {
    enum
    {
        ID_Hello = 1,
        ID_file,
        ID_new_game,
        ID_players
    };

    public:
        MainFrame();
        ~MainFrame();
        void add_player_to_list(const std::string &name);

    private:
        void OnAbout(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);

        void on_new_game(wxCommandEvent& event);
        void on_player_menu(wxCommandEvent& event);

        wxFlexGridSizer *score_grid;

        int _main_width = 800;
        int _main_height = 400;
        uint _max_score = 10;
        bool _only_max_score_game = true; // if set to true, only a score from one team that is equal to max score is accepted

        // last game settings
        bool _last_game_2v2 = false;
        uint _last_players[4] = {0};

        double _starting_rate = 1000.0;
        uint _highest_player_id = 1;


        std::vector<Player> _players; // info from all players
};

#endif // MAINFRAME_HPP
