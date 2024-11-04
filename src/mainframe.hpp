#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <memory>
#include <string>

class MainFrame : public wxFrame {
    enum {
            ID_Hello = 1,
            ID_file,
            ID_new_game,
            ID_players
        };

    public:
        MainFrame();
        ~MainFrame();
        void add_score_to_list(const std::string &name, const std::string score);

    private:
        void OnAbout(wxCommandEvent& event);
        void OnFileLoad(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        bool load_icon(const std::string &file);

        void on_new_game(wxCommandEvent& event);

        std::string _icon_file = "icon_foosball.jpeg";

        wxFlexGridSizer *score_grid;
};

#endif // MAINFRAME_HPP
