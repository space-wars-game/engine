#include <iostream>
#include "space_wars.hpp"
#include "action/move.hpp"
#include "world/universe_generator.hpp"
#include "world/unserialize.hpp"

namespace space_wars {

SpaceWars::SpaceWars() {

}

mmpg::World* SpaceWars::GenerateWorld() {
  UniverseGenerator generator((unsigned int) time(NULL));
  return generator.Generate();
}


mmpg::World* SpaceWars::ReadWorld(std::istream& stream) {
  Universe* universe = new Universe;

  // Read universe
  Unserialize(*universe, stream);

  return universe;
}

mmpg::Action* SpaceWars::ReadAction(std::istream& stream) {
  char t;

  stream >> t;

  switch(t) {
    case 'U':
    case 'D':
    case 'L':
    case 'R':
      return new Move(t);

    default:
      return 0;
  }
}

}
