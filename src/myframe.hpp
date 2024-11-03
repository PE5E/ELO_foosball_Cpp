#ifndef MYFRAME_HPP
#define MYFRAME_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <memory>

class MyFrame : public wxFrame {
    public:
        MyFrame();
        ~MyFrame();
    private:
        void OnAbout(wxCommandEvent& event);
        void OnFileLoad(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        bool load_icon(const std::string &file);

        void on_new_game(wxCommandEvent& event);

        // std::unique_ptr<Image> _image;
        std::string _icon_file = "icon_foosball.jpeg";
        int _input_type_int;
        std::string _input_type_string;

        enum {
            ID_Hello = 1,
            ID_file,
            ID_new_game,
            ID_players
        };
};

#endif // MYFRAME_HPP
