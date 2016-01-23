cmake_minimum_required(VERSION 2.6)
project(space_wars)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(SOURCE_FILES
        src/space_wars.cpp

        src/action.cpp
        src/action/move.cpp
        src/action/send_fleet.cpp

        src/world/universe_generator.cpp

        src/world/universe.cpp
        src/world/universe.hpp
        src/world/celestial_body.cpp

        src/world/system.cpp
        src/world/system/sun.cpp
        src/world/system/planet.cpp
        src/world/system/relay.cpp

        src/world/entity/fleet.cpp

        src/serialize/raw.cpp
        src/serialize/json.cpp

        src/deserialize.cpp
)

add_subdirectory(lib/engine)

include_directories(
        include/space_wars
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
        src/cmd/player/ai.cpp
        match/build/ai.cpp
        ${SOURCE_FILES}
)

target_link_libraries(player
        MMPGPlayer
        ${MMPG_LIBRARIES}
)
