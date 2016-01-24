#include "relay.hpp"

namespace space_wars {

unsigned int Relay::RADIUS = 20;
unsigned int Relay::MIN_NUM_CONNECTIONS = 1;
unsigned int Relay::MAX_NUM_CONNECTIONS = 4;

Relay::Relay() {

}

Relay::Relay(unsigned int id, unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position) :
  super(RADIUS, orbit_major, orbit_minor, orbit_position), id(id)
{

}

bool Relay::HasConnection(int relay_id) const {
  for(int connection : connections) {
    if(connection == relay_id) {
      return true;
    }
  }

  return false;
}

}
