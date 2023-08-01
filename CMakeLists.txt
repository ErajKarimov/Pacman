cmake_minimum_required(VERSION 3.25)
project(Pacman)

set(CMAKE_CXX_STANDARD 20)

include_directories(SFML/include)

file(GLOB SOURCES
        Headers/*.hpp
        Source/*.cpp
        )

set(SFML_DIR "SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Pacman ${SOURCES})

target_link_libraries(Pacman sfml-graphics sfml-window sfml-system)

# file(GLOB BINARY_DEP_DLLS SFML/include/SFML/)
file(GLOB BINARY_DEP_DLLS SFML/bin/*.dll)
file (COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
file (COPY Resources DESTINATION ${CMAKE_BINARY_DIR})




