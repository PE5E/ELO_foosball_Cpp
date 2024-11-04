cmake_minimum_required(VERSION 3.10.0)

find_package(wxWidgets 3.0 COMPONENTS core base REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

# Define a variable containing a list of source files for the project
set(SRC_FILES
    main.cpp
    myapp.cpp
    mainframe.cpp
    resolution_dialog.cpp
)

if(WIN32)
    # Include a RC file for windows
    list(APPEND SRC_FILES ../sample.rc)
endif()

# Define the build target for the executable
add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

