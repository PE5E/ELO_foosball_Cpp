#include "new_game_dialog.hpp"

#include "mainframe.hpp" // for the IDs

// https://zetcode.com/gui/wxwidgets/dialogs/

NewGameDialog::NewGameDialog(const wxString& title) : 
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(700, 400)) 
{
    _nr_bytes = 0;

    wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);
    
    /*
    wxPanel *panel1 = new wxPanel(this, -1);
    wxStaticBox *st1 = new wxStaticBox(panel1, -1, wxT("Resolution"), wxPoint(5, 5), wxSize(230, 120));
    wxStaticText *textH = new wxStaticText(panel1, wxID_ANY, "Horizontal:", wxPoint(15, 35));
    inputH = new wxTextCtrl(panel1, ID_TEXT1, wxT("0"), wxPoint(110, 35));
    wxStaticText *textV = new wxStaticText(panel1, wxID_ANY, "Vertical:", wxPoint(15, 75));
    inputV = new wxTextCtrl(panel1, ID_TEXT2, wxT("0"), wxPoint(110, 75));

    wxPanel *panel2 = new wxPanel(this, -1);
    wxStaticBox *st2 = new wxStaticBox(panel2, -1, wxT("Bitsize"), wxPoint(5, 5), wxSize(230, 100));
    wxStaticText *input_bytes = new wxStaticText(panel2, wxID_ANY, "Total bytes:", wxPoint(15, 30));
    input_bytes_nr = new wxStaticText(panel2, wxID_ANY, "0", wxPoint(110, 30));
    wxStaticText *bytespp = new wxStaticText(panel2, wxID_ANY, "Bits per pixel:", wxPoint(15, 65));
    bits_per_pixel = new wxStaticText(panel2, wxID_ANY, "0", wxPoint(110, 65));
    */

    wxPanel *panel1 = new wxPanel(this, -1);
    wxString teams[] = {"1 vs 1", "2 vs 2"};
    int team_count = 2;
    team_box = new wxRadioBox(panel1, wxID_ANY, _T(""), wxPoint(0, 0), wxDefaultSize, team_count,
                            teams, 1, wxRA_SPECIFY_ROWS | wxNO_BORDER, wxDefaultValidator, _T("Teams"));

    main_sizer->Add(panel1, 0, wxEXPAND | wxRIGHT | wxLEFT, 250);


    wxPanel *panel2 = new wxPanel(this, -1);
    wxStaticBox *st2 = new wxStaticBox(panel2, -1, wxT("Team A"), wxPoint(0, 0), wxSize(318, 200));

    wxPanel *panel3 = new wxPanel(this, -1);
    wxStaticBox *st3 = new wxStaticBox(panel3, -1, wxT("Team B"), wxPoint(0, 0), wxSize(318, 200));

    wxBoxSizer *team_sizer = new wxBoxSizer(wxHORIZONTAL);
    team_sizer->Add(panel2, 0, wxALL, 3);
    team_sizer->Add(panel3, 0, wxALL, 3);

    main_sizer->Add(team_sizer, 0, wxEXPAND | wxRIGHT | wxLEFT, 0);


    // wxString bit_depth[] = {"8 Bit", "12 Bit", "16 Bit"};
    // int bit_count = 3;
    // bits_box = new wxRadioBox(panel4, wxID_ANY, _T(""), wxPoint(30, 15), wxDefaultSize, bit_count,
    //                         bit_depth, 1, wxRA_SPECIFY_COLS | wxNO_BORDER, wxDefaultValidator, _T("Bit Depth"));

    // grid->Add(panel4);
    // grid->Add(panel2);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

    hbox2->Add(main_sizer); // add some space to the sides

    wxButton *okButton = new wxButton(this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
    wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxSize(70, 30));

    // bindings
    // Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewGameDialog::button));
    // Connect(ID_TEXT1, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(NewGameDialog::calculate_bpp));
    // Connect(ID_TEXT2, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(NewGameDialog::calculate_bpp));
    
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(okButton, 1);
    hbox->Add(closeButton, 1, wxLEFT, 5);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(hbox2, 1);
    vbox->Add(hbox, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    
    SetSizer(vbox);
    Centre();
}

NewGameDialog::~NewGameDialog() {

}

wxString NewGameDialog::getResolutionH()
{
   // return inputH->GetValue();
}

wxString NewGameDialog::getResolutionV()
{
   // return inputV->GetValue();
}

int NewGameDialog::getChannels() {
    // return channel_box->GetSelection();
}

int NewGameDialog::getBitDepth() {
    // return bits_box->GetSelection();
}

void NewGameDialog::setBytes(int nr_bytes) {
    _nr_bytes = nr_bytes;
    // input_bytes_nr->SetLabelText(wxString::Format(wxT("%i"), nr_bytes));
}

void NewGameDialog::calculate_bpp(wxCommandEvent & event) {
    try {
        int v = wxAtoi(inputV->GetValue());
        int h = wxAtoi(inputH->GetValue());

        if(v != 0 && h != 0) {
            float bpp = 8.0 * (float)_nr_bytes / ((float)v * (float)h);
            bits_per_pixel->SetLabel(wxString::Format(wxT("%f"), bpp));
        }
        else {
            bits_per_pixel->SetLabel("0");
        }
    }
    catch(std::exception ex) {
        std::cerr << "Error calculating bytes per pixel, probably input is not a number" << ex.what() << std::endl;
    }
}