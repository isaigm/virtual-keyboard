cmake_minimum_required(VERSION 3.16)

project(virtual-keyboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QX11Info (X11Extras) only exists in Qt 5, so this project is Qt 5 only.
find_package(Qt5 REQUIRED COMPONENTS Widgets X11Extras)
find_package(X11 REQUIRED)
if(NOT X11_Xtst_FOUND)
    message(FATAL_ERROR "libXtst not found (install libxtst-dev / libxtst)")
endif()

add_executable(virtual-keyboard
    main.cpp
    widget.cpp widget.h widget.ui
    keyboard.cpp keyboard.h
    ckey.cpp ckey.h
    virtualkeyboard.cpp virtualkeyboard.h
    uinputvkeyboard.cpp uinputvkeyboard.h
    x11vkeyboard.cpp x11vkeyboard.h
)

# Libraries go here, not in CMAKE_CXX_FLAGS: flags end up before the object
# files on the link line, and with --as-needed (default on Debian/Ubuntu)
# the linker drops them.
target_link_libraries(virtual-keyboard PRIVATE
    Qt5::Widgets
    Qt5::X11Extras
    X11::X11
    X11::Xtst
)

include(GNUInstallDirs)
install(TARGETS virtual-keyboard
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
