#pragma once

#include <mmpg/player/ai.hpp>
#include "planet.hpp"

namespace space_wars {

class Universe;

class AI : public mmpg::AI {
 public:
  void ScanUniverse();
  void RefreshWorld();
  void SendShips(int origin_id, int connection_id, int num_ships);

  const std::vector<int>& owned_planets(int player_id) const;
  const Planet& planet(int planet_id) const;

 private:
  Universe* universe_ = 0;
};

}
