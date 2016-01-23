#pragma once

#include "celestial_body.hpp"
#include <vector>

namespace space_wars {

class Relay : public CelestialBody {
 public:
  typedef CelestialBody super;

  static unsigned int RADIUS;

  Relay(unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position);

  unsigned int id;
  std::vector<int> connections;
  std::vector<int> planets;
};

}
