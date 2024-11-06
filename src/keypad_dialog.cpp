#include "keypad_dialog.hpp"

#include "mainframe.hpp" // for the IDs

using std::cout;
using std::endl;

KeypadDialog::KeypadDialog(const wxString& title) : 
    wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(600, 50)) 
{
    wxBoxSizer *main_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton *button_0 = new wxButton(this, -1, wxT("0"), wxDefaultPosition, wxSize(30, 30));

}

KeypadDialog::~KeypadDialog() 
{
}
