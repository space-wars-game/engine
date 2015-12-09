#pragma once

#include "../celestial_body.hpp"

namespace space_wars {

class Planet : public CelestialBody {
 public:
  typedef CelestialBody super;

  static unsigned int MIN_RADIUS;
  static unsigned int MAX_RADIUS;

  static unsigned int MIN_DISTANCE_X;
  static unsigned int MAX_DISTANCE_X;

  static unsigned int MIN_DISTANCE_Y;
  static unsigned int MAX_DISTANCE_Y;

  Planet(unsigned int radius, unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position);


};

}
