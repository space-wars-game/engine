#pragma once

#include "celestial_body.hpp"

namespace space_wars {

class Sun : public CelestialBody {
 public:
  typedef CelestialBody super;

  enum TYPE {
    G
  };

  static unsigned int MIN_RADIUS;
  static unsigned int MAX_RADIUS;

  Sun();
  Sun(TYPE type, unsigned int radius);

  TYPE type;
};

}
