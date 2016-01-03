#include "celestial_body.hpp"
#include <cmath>
#include "../vec2.hpp"

namespace space_wars {

CelestialBody::CelestialBody() {

}

CelestialBody::CelestialBody(unsigned int radius, unsigned int orbit_major, unsigned int orbit_minor,
                             unsigned int orbit_position)
    : x(0), y(0), radius(radius), orbit_major(orbit_major), orbit_minor(orbit_minor), orbit_position(orbit_position)
{
  orbit_focus = (float) sqrt(orbit_major * orbit_major - orbit_minor * orbit_minor);
  MoveInOrbit(orbit_position);
}

void CelestialBody::MoveInOrbit(unsigned int position) {
  float radians = (float) (position * M_PI / 180.0);
  x = (float) (orbit_major * cos(radians));
  y = (float) (orbit_minor * sin(radians));
  orbit_position = position;
}

float CelestialBody::distance(const CelestialBody& body) const {
  float xd = body.x - x;
  float yd = body.y - y;

  return sqrtf(xd*xd + yd*yd);
}

bool CelestialBody::ConnectionIntersects(const CelestialBody* a, const CelestialBody* b) const {
  vec2f av = vec2f(a->x, a->y);
  vec2f bv = vec2f(b->x, b->y);
  vec2f cv = vec2f(x, y);

  vec2f d = bv - av;
  vec2f f = av - cv;

  float ax = vec2f::dot(d, d);
  float bx = 2 * vec2f::dot(f, d);
  float cx = vec2f::dot(f, f) - radius*radius;

  float discriminant = bx*bx - 4*ax*cx;

  if(discriminant < 0) {
    return false;
  }

  discriminant = sqrtf(discriminant);

  float t1 = (-bx - discriminant) / (2*ax);
  float t2 = (-bx + discriminant) / (2*ax);

  return (t1 >= 0 and t1 <= 1) or (t2 >= 0 and t2 <= 1);
}

}
