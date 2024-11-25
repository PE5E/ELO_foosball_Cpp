#include "new_player_dialog.hpp"

// https://zetcode.com/gui/wxwidgets/dialogs/

using std::cout;
using std::cerr;
using std::endl;

NewPlayerDialog::NewPlayerDialog(const wxString& title) : 
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(700, 400)) 
{
    wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);

    main_sizer->AddSpacer(50);
    wxStaticText *name_lbl = new wxStaticText(this, -1, "Enter The Name For The New Player" , wxPoint(0, 0), wxSize(300, 40), wxST_NO_AUTORESIZE);
    main_sizer->AddSpacer(20);
    name_input = new wxTextCtrl(this, -1, "", wxPoint(0, 0), wxSize(300, 40));
    name_input->Bind(wxEVT_TEXT, &NewPlayerDialog::set_name, this);  

    main_sizer->Add(name_lbl, 0, wxEXPAND | wxRIGHT | wxLEFT, 200);
    main_sizer->Add(name_input, 0, wxEXPAND | wxRIGHT | wxLEFT, 200);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    hbox2->Add(main_sizer); // add some space to the sides

    wxButton *okButton = new wxButton(this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxSize(100, 30));
    wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxSize(100, 30));
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(okButton, 1, wxRIGHT, 10);
    hbox->Add(closeButton, 1, wxLEFT, 10);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(hbox2, 1);
    vbox->Add(hbox, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    

    SetSizer(vbox);
    Centre();
}

NewPlayerDialog::~NewPlayerDialog() 
{
}

wxString NewPlayerDialog::get_player_name()
{
   return _player_name;
}

void NewPlayerDialog::set_name(wxCommandEvent &event)
{
    _player_name = name_input->GetValue();
}