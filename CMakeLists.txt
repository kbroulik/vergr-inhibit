cmake_minimum_required(VERSION 3.16)

project(vergr-inhibit)

include(GNUInstallDirs)
include(FeatureSummary)

set(ZOOM_DIR "/opt/zoom" CACHE PATH "Zoom installation directory")
add_feature_info(ZOOM_DIR On "Zoom installation directory is '${ZOOM_DIR}'")
set(ZOOM_EXECUTABLE "${ZOOM_DIR}/zoom" CACHE FILEPATH "Zoom executable binary")
add_feature_info(ZOOM_EXECUTABLE On "Zoom executable binary is '${ZOOM_EXECUTABLE}'")
set(ZOOM_QT_LIBDIR "${ZOOM_DIR}" CACHE PATH "Location of Zoom's Qt libraries")
add_feature_info(ZOOM_QT_LIBDIR On "Location of Zoom's Qt libraries is '${ZOOM_QT_LIBDIR}'")

find_package(Qt5 5.12 CONFIG REQUIRED COMPONENTS DBus Gui)

add_subdirectory(src)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
