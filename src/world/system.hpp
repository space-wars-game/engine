#pragma once

#include "system/sun.hpp"
#include "relay.hpp"
#include "planet.hpp"
#include <vector>
#include <set>

namespace space_wars {

class System {
 public:
  static unsigned int MIN_SIZE;
  static unsigned int MAX_SIZE;
  static unsigned int HOME_NUM_CONNECTIONS;

  System();
  ~System();

  void Conquer(unsigned int planet_id, unsigned int player_id);

  Sun* sun;
  Relay* relay;
  std::vector<Planet*> planets;
};

}
