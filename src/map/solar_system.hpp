#pragma once

#include "sun.hpp"

namespace space_wars {

class SolarSystem {
 public:
  SolarSystem(int seed);

  Sun* sun;
};

}
