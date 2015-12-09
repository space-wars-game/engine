#include "planet.hpp"


namespace space_wars {

unsigned int Planet::MIN_RADIUS = 7;
unsigned int Planet::MAX_RADIUS = 18;

unsigned int Planet::MIN_DISTANCE_X = 8;
unsigned int Planet::MAX_DISTANCE_X = 12;

unsigned int Planet::MIN_DISTANCE_Y = 4;
unsigned int Planet::MAX_DISTANCE_Y = 7;

Planet::Planet(unsigned int radius, unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position)
    : super(radius, orbit_major, orbit_minor, orbit_position) {

}

}
