#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "data.hpp"

#include "data_manager.hpp"
#include "elo_calculator.hpp"

#include "scrollable_player_info.hpp"

#include <memory>
#include <string>
#include <vector>

class MainFrame : public wxFrame {
    enum
    {
        ID_Hello = 1,
        ID_file,
        ID_new_game,
        ID_add_player,
        ID_players,
        ID_scroll_up,
        ID_scroll_down
    };

    public:
        MainFrame();
        ~MainFrame();
        bool add_player_to_list(const std::string &name);
        Player& get_player(uint player_id);

    private:
        void OnAbout(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);

        void on_new_game(wxCommandEvent& event);
        void on_scroll_up(wxCommandEvent& event);
        void on_scroll_down(wxCommandEvent& event);
        void on_add_player_menu(wxCommandEvent& event);
        void on_player_menu(wxCommandEvent& event);
        
        void update_player_list();

        // UI elements
        wxFlexGridSizer *score_grid;
        wxPanel *_player_panel;
        // wxBoxSizer *_player_sizer;
        ScrollablePlayerInfo *_player_list;

        int _main_width = 800;
        int _main_height = 480;

        // game settings
        uint _max_score = 10; // score that one team needs to win
        bool _only_max_score_game = true; // if set to true, only a score from one team that is equal to max score is accepted

        // last game settings
        bool _last_game_2v2 = false;
        uint _last_players[4] = {0};

        double _starting_rate = 1000.0;
        uint _highest_player_id = 0; 
        uint _highest_game_id = 0;

        std::unique_ptr<DataManager> _data_manager;
        std::shared_ptr<std::vector<Player>> _players;
        EloCalculator _elo_calculator;
};

#endif // MAINFRAME_HPP
