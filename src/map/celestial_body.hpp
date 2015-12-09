#pragma once

namespace space_wars {

class CelestialBody {
 public:
  CelestialBody(unsigned int radius, unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position);

  void MoveInOrbit(unsigned int position);

  float x, y;
  unsigned int radius;
  unsigned int orbit_major;
  unsigned int orbit_minor;
  unsigned int orbit_position;
  float orbit_focus;
};

}
