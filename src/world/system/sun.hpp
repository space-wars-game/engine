#pragma once

#include <ostream>
#include "../celestial_body.hpp"

namespace space_wars {

class Sun {
 public:

  enum TYPE {
    G
  };

  static unsigned int MIN_RADIUS;
  static unsigned int MAX_RADIUS;

  Sun();
  Sun(TYPE type, unsigned int radius);

  TYPE type;
  unsigned int radius;
};

}
