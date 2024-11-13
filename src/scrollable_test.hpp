#ifndef SCROLLABLE_TEST
#define SCROLLABLE_TEST

#include <wx/wx.h>

#include "data.hpp"

#include <sstream>

class ScrollableTest : public wxScrolledWindow
{
public:
    ScrollableTest(wxWindow* parent, wxWindowID id, const std::vector<Player> players) : wxScrolledWindow(parent, id)
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        
        // add a series of widgets
        for (int w=1; w<=120; w++)
        {
            wxButton* b = new wxButton(this, wxID_ANY, wxString::Format(wxT("Button %i"), w));
            sizer->Add(b, 0, wxALL, 3);
        }
        
        this->SetSizer(sizer);

        // this part makes the scrollbars show up
        this->FitInside(); // ask the sizer about the needed size
        this->SetScrollRate(5, 5);
    }
};

#endif // SCROLLABLE_TEST