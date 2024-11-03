#include "myapp.hpp"

#include "myframe.hpp"

bool MyApp::OnInit() {
    wxInitAllImageHandlers();

    // if(FILE *file = fopen(icon_file.c_str(), "r")) {
    //     fclose(file);
    //     load_icon(icon_file);
    // }
    // else {
    //     std::cout << "Could not open icon file: " << icon_file << std::endl;
    // }

    MyFrame *frame = new MyFrame();
    frame->Show(true);
    
    return true;
}
