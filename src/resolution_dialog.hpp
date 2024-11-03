#ifndef RESOLUTION_DIALOG_HPP
#define RESOLUTION_DIALOG_HPP

#include <wx/wx.h>

class ResolutionDialog : public wxDialog
{
public:
    ResolutionDialog(const wxString& title);
    ~ResolutionDialog();
    wxString getResolutionH();
    wxString getResolutionV();
    int getChannels();
    int getBitDepth();
    void setBytes(int nr_bytes);

private:
    void calculate_bpp(wxCommandEvent & event);

private:
    wxTextCtrl *inputH;
    wxTextCtrl *inputV;
    wxStaticText *input_bytes_nr;
    wxStaticText *bits_per_pixel;
    wxRadioBox *channel_box;
    wxRadioBox *bits_box;
    int _nr_bytes;

    const int ID_TEXT1 = 1;
    const int ID_TEXT2 = 2;

};

#endif // RESOLUTION_DIALOG_HPP