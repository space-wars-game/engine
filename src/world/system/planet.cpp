#include "planet.hpp"
#include <cmath>

namespace space_wars {

namespace {

static unsigned int NEXT_ID = 0;

}

unsigned int Planet::MIN_RADIUS = 7;
unsigned int Planet::MAX_RADIUS = 18;

unsigned int Planet::MIN_DISTANCE_X = 8;
unsigned int Planet::MAX_DISTANCE_X = 12;

unsigned int Planet::MIN_DISTANCE_Y = 4;
unsigned int Planet::MAX_DISTANCE_Y = 7;

unsigned int Planet::MIN_NUM_CONNECTIONS = 1;
unsigned int Planet::MAX_NUM_CONNECTIONS = 5;

Planet::Planet() {

}

Planet::Planet(unsigned int radius, unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position)
    : super(radius, orbit_major, orbit_minor, orbit_position), id(NEXT_ID), owner(-1), ships(0), ships_accum(0.f),
      relay(-1)
{
  NEXT_ID++;
}

bool Planet::is_owned() const {
  return owner != -1;
}

unsigned int Planet::ship_rate() const {
  return radius / 4;
}

bool Planet::HasConnection(int planet_id) const {
  for(int connection : connections) {
    if(planet_id == connection) {
      return true;
    }
  }

  return false;
}

bool Planet::has_relay() const {
  return relay != -1;
}

void Planet::GenerateShips(float delta) {
  if(!is_owned())
    return;

  ships_accum += ship_rate() * delta;

  if(ships_accum >= 1) {
    unsigned int generated_ships = (unsigned int)floor(ships_accum);
    ships += generated_ships;
    ships_accum -= generated_ships;
  }
}

void Planet::FleetArrives(int fleet_owner, int fleet_ships) {
  if(owner == -1) {
    owner = fleet_owner;
  }

  if(fleet_owner == owner) {
    ships += fleet_ships;
  } else {
    if(ships >= fleet_ships) {
      ships -= fleet_ships;
    } else {
      owner = fleet_owner;
      ships = fleet_ships - ships;
    }
  }
}

}
