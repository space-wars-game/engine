cmake_minimum_required(VERSION 2.6)
project(space_wars)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(SOURCE_FILES)

add_subdirectory(lib/engine)

include_directories(
        ${MMPG_INCLUDE_DIRS}
)

# Master process
add_executable(master
        src/cmd/master/main.cpp
        ${SOURCE_FILES}
)

target_link_libraries(master
        MMPGMaster
        ${MMPG_LIBRARIES}
)

# Player process
add_executable(player
        src/cmd/player/main.cpp
        match/build/ai.cpp
        ${SOURCE_FILES}
)

target_link_libraries(player
        MMPGPlayer
        ${MMPG_LIBRARIES}
)
