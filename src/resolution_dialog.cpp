#include "resolution_dialog.hpp"

#include "myframe.hpp" // for the IDs

// https://zetcode.com/gui/wxwidgets/dialogs/

ResolutionDialog::ResolutionDialog(const wxString& title) : 
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(500, 350)) 
{
    _nr_bytes = 0;

    wxFlexGridSizer *grid = new wxFlexGridSizer(2, 2, 10, 10);
    
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

    wxPanel *panel3 = new wxPanel(this, -1);
    wxStaticBox *st3 = new wxStaticBox(panel3, -1, wxT("Channel Format"), wxPoint(5, 5), wxSize(230, 120));
    wxString channels[] = {"1 Channel: Grayscale", "3 Channels: RGB", "4 Channels: RGBA"};
    int channel_count = 3;
    channel_box = new wxRadioBox(panel3, wxID_ANY, _T(""), wxPoint(30, 15), wxDefaultSize, channel_count,
                            channels, 1, wxRA_SPECIFY_COLS | wxNO_BORDER, wxDefaultValidator, _T("Channel format"));

    wxPanel *panel4 = new wxPanel(this, -1);
    wxStaticBox *st4 = new wxStaticBox(panel4, -1, wxT("Bit Depth Per Channel"), wxPoint(5, 5), wxSize(230, 100));
    wxString bit_depth[] = {"8 Bit", "12 Bit", "16 Bit"};
    int bit_count = 3;
    bits_box = new wxRadioBox(panel4, wxID_ANY, _T(""), wxPoint(30, 15), wxDefaultSize, bit_count,
                            bit_depth, 1, wxRA_SPECIFY_COLS | wxNO_BORDER, wxDefaultValidator, _T("Bit Depth"));

    grid->Add(panel1);
    grid->Add(panel3);
    grid->Add(panel4);
    grid->Add(panel2);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

    hbox2->Add(grid); // add some space to the sides

    wxButton *okButton = new wxButton(this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
    wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxSize(70, 30));

    // bindings
    // Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ResolutionDialog::button));
    Connect(ID_TEXT1, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(ResolutionDialog::calculate_bpp));
    Connect(ID_TEXT2, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(ResolutionDialog::calculate_bpp));
    
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(okButton, 1);
    hbox->Add(closeButton, 1, wxLEFT, 5);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(hbox2, 1);
    vbox->Add(hbox, 1, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    
    SetSizer(vbox);
    Centre();
}

ResolutionDialog::~ResolutionDialog() {

}

wxString ResolutionDialog::getResolutionH()
{
   return inputH->GetValue();
}

wxString ResolutionDialog::getResolutionV()
{
   return inputV->GetValue();
}

int ResolutionDialog::getChannels() {
    return channel_box->GetSelection();
}

int ResolutionDialog::getBitDepth() {
    return bits_box->GetSelection();
}

void ResolutionDialog::setBytes(int nr_bytes) {
    _nr_bytes = nr_bytes;
    input_bytes_nr->SetLabelText(wxString::Format(wxT("%i"), nr_bytes));
}

void ResolutionDialog::calculate_bpp(wxCommandEvent & event) {
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