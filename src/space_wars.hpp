#pragma once

#include <mmpg/game.hpp>

namespace space_wars {

class SpaceWars : public mmpg::Game {
 public:
  SpaceWars();

  mmpg::World* GenerateWorld();
  mmpg::World* ReadWorld(std::istream& stream);

  mmpg::Action* ReadAction(char type, std::istream& stream);
};

}
