#include "space_wars.hpp"
#include "world/universe_generator.hpp"
#include "deserialize.hpp"
#include "action/send_fleet.hpp"
#include "action/send_fleet_through_relay.hpp"

namespace space_wars {

SpaceWars::SpaceWars() {

}

mmpg::World* SpaceWars::GenerateWorld() {
  UniverseGenerator generator((unsigned int) time(NULL));
  return generator.Generate(100, 3);
}


mmpg::World* SpaceWars::ReadWorld(std::istream& stream) {
  Universe* universe = new Universe;

  // Read universe
  deserialize::Structure(*universe, stream);

  return universe;
}

mmpg::Action* SpaceWars::ReadAction(char type, std::istream& stream) {
  int origin, destination, ships;

  switch(type) {
    case 'F':
      stream >> origin >> destination >> ships;

      return new action::SendFleet(origin, destination, ships);

    case 'R':
      int origin_relay, destination_relay;
      stream >> origin >> origin_relay >> destination_relay >> destination >> ships;

      return new action::SendFleetThroughRelay(origin, origin_relay, destination_relay, destination, ships);

    default:
      return 0;
  }
}

}
