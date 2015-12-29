#include "space_wars.hpp"
#include "world/universe_generator.hpp"
#include "world/unserialize.hpp"
#include "action/send_fleet.hpp"

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

mmpg::Action* SpaceWars::ReadAction(char type, std::istream& stream) {
  switch(type) {
    case 'F':
      int origin, destination, ships;
      stream >> origin >> destination >> ships;

      return new SendFleet(origin, destination, ships);

    default:
      return 0;
  }
}

}
