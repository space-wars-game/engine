#pragma once

#include "celestial_body.hpp"
#include <vector>

namespace space_wars {

class Relay : public CelestialBody {
 public:
  typedef CelestialBody super;

  static unsigned int RADIUS;
  static unsigned int MIN_NUM_CONNECTIONS;
  static unsigned int MAX_NUM_CONNECTIONS;

  Relay();
  Relay(unsigned int id, unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position);

  bool HasConnection(int relay_id) const;

  unsigned int id;
  std::vector<int> connections;
  std::vector<int> planets;
};

}
