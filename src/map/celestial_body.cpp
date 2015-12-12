#include "celestial_body.hpp"
#include <cmath>

namespace space_wars {

unsigned int CelestialBody::NEXT_ID = 0;

CelestialBody::CelestialBody(unsigned int radius, unsigned int orbit_major, unsigned int orbit_minor,
                             unsigned int orbit_position)
    : x(0), y(0), radius(radius), orbit_major(orbit_major), orbit_minor(orbit_minor), orbit_position(orbit_position)
{
  id = NEXT_ID;
  NEXT_ID++;

  orbit_focus = (float) sqrt(orbit_major * orbit_major - orbit_minor * orbit_minor);
  MoveInOrbit(orbit_position);
}

void CelestialBody::MoveInOrbit(unsigned int position) {
  float radians = (float) (position * M_PI / 180.0);
  x = (float) (orbit_major * cos(radians));
  y = (float) (orbit_minor * sin(radians));
  orbit_position = position;
}

}
