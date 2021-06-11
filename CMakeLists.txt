cmake_minimum_required(VERSION 3.12)
project(myproject)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wfatal-errors")

add_subdirectory(lib/piksel)

set(SOURCES
    src/main.cpp
    src/app.cpp
    src/them.cpp
)
add_executable(index ${SOURCES})
target_include_directories(index
    PUBLIC src
    PUBLIC lib/piksel/src
)
target_link_libraries(index
    piksel
)