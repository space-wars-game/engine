#include "relay.hpp"

namespace space_wars {

namespace {

static unsigned int NEXT_ID = 0;

}

unsigned int Relay::RADIUS = 20;

Relay::Relay(unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position) :
  super(RADIUS, orbit_major, orbit_minor, orbit_position), id(NEXT_ID)
{
  NEXT_ID++;
}

}
