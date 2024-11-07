#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

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

    struct player
    {
        uint id; // starting from 1
        std::string name;
        double ranking;
        uint games_played;
    };

    public:
        MainFrame();
        ~MainFrame();
        void add_score_to_list(const std::string &name, const std::string score);

    private:
        void OnAbout(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);

        void on_new_game(wxCommandEvent& event);

        wxFlexGridSizer *score_grid;

        int _main_width = 800;
        int _main_height = 400;
        uint _max_score = 10;
        bool _only_max_score_game = true; // if set to true, only a score from one team that is equal to max score is accepted

        // last game settings
        bool _last_game_2v2 = false;
        uint _last_players[4] = {0};


        std::vector<player> _players; // info from all players
};

#endif // MAINFRAME_HPP
