#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <memory>

class MainFrame : public wxFrame {
    public:
        MainFrame();
        ~MainFrame();
    private:
        void OnAbout(wxCommandEvent& event);
        void OnFileLoad(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        bool load_icon(const std::string &file);

        void on_new_game(wxCommandEvent& event);

        std::string _icon_file = "icon_foosball.jpeg";

        enum {
            ID_Hello = 1,
            ID_file,
            ID_new_game,
            ID_players
        };
};

#endif // MAINFRAME_HPP
