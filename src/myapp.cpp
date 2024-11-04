#include "myapp.hpp"

#include "mainframe.hpp"

bool MyApp::OnInit() {
    wxInitAllImageHandlers();

    // if(FILE *file = fopen(icon_file.c_str(), "r")) {
    //     fclose(file);
    //     load_icon(icon_file);
    // }
    // else {
    //     std::cout << "Could not open icon file: " << icon_file << std::endl;
    // }

    MainFrame *frame = new MainFrame();
    frame->Show(true);
    
    return true;
}
