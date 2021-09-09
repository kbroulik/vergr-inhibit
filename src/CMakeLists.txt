set(vergrinhibit_SRCS
    main.cpp
    notificationinhibition.cpp
    windowwatcher.cpp
)

# Zoom ships its own Qt, we want to be able to run against it no matter what
add_definitions(-DQT_NO_VERSION_TAGGING)

add_library(vergrinhibit SHARED ${vergrinhibit_SRCS})

set_target_properties(vergrinhibit PROPERTIES AUTOMOC ON)

target_link_libraries(vergrinhibit PUBLIC Qt5::DBus Qt5::Gui)

install(TARGETS vergrinhibit DESTINATION ${CMAKE_INSTALL_LIBDIR})

configure_file(vergrzoom.sh.in vergrzoom.sh @ONLY)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/vergrzoom.sh TYPE BIN)
