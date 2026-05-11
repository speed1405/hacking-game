cmake_minimum_required(VERSION 3.20)
project(LegacyLeak LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
include(FetchContent)

# FTXUI
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# nlohmann/json
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# Sources
set(SOURCES
    src/VFS.cpp
    src/Shell.cpp
    src/Network.cpp
    src/Hardware.cpp
    src/Missions.cpp
    src/Exploits.cpp
    src/SaveSystem.cpp
    main.cpp
)

# Project executable
add_executable(legacyleak ${SOURCES})

target_include_directories(legacyleak PRIVATE include)
target_link_libraries(legacyleak PRIVATE ftxui::screen ftxui::dom ftxui::component nlohmann_json::nlohmann_json)
