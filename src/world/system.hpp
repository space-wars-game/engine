#pragma once

#include "system/sun.hpp"
#include "system/planet.hpp"
#include <vector>
#include <set>

namespace space_wars {

class System {
 public:
  static unsigned int MIN_SIZE;
  static unsigned int MAX_SIZE;

  System();

  void Conquer(unsigned int planet_id, unsigned int player_id);

  Sun* sun;
  std::vector<Planet*> planets;
};

}
