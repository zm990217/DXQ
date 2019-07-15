cmake_minimum_required(VERSION 3.10)

project(OhKami)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)


# Find the QtWidgets library (add more Qt componets here)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
# import targets
# find_package(Qt5 COMPONENTS Core REQUIRED)
# get_target_property(QtCore_location Qt5::Core LOCATION)

file(GLOB SOURCE_FILE
    "*.cpp"
    "*.h"
    "*.ui"
)

if (APPLE) 
    add_executable(${PROJECT_NAME} ${SOURCE_FILE})
elseif(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILE})
else()
    add_executable(${PROJECT_NAME} ${SOURCE_FILE})
endif()

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)