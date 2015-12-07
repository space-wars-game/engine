#pragma once

#include <ostream>

namespace space_wars {

class Sun {
 public:
  enum TYPE {
    G
  };

  static unsigned int MIN_RADIUS;
  static unsigned int MAX_RADIUS;

  Sun(TYPE type, unsigned int radius);

  TYPE type;
  unsigned int radius;
};

}
