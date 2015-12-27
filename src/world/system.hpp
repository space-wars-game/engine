#pragma once

#include "system/sun.hpp"
#include "system/planet.hpp"
#include <vector>

namespace space_wars {

class System {
 public:
  static unsigned int MIN_SIZE;
  static unsigned int MAX_SIZE;

  System();

  Sun* sun;
  std::vector<Planet*> planets;
};

}
