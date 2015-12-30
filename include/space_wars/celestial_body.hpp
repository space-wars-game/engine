#pragma once

namespace space_wars {

class CelestialBody {
 public:
  CelestialBody();
  CelestialBody(unsigned int radius, unsigned int orbit_major, unsigned int orbit_minor, unsigned int orbit_position);

  void MoveInOrbit(unsigned int position);

  float distance(const CelestialBody& body) const;

  bool ConnectionIntersects(const CelestialBody* a, const CelestialBody* b) const;

  float x, y;
  unsigned int id;
  unsigned int radius;
  unsigned int orbit_major;
  unsigned int orbit_minor;
  unsigned int orbit_position;
  float orbit_focus;

 private:
  static unsigned int NEXT_ID;
};

}
