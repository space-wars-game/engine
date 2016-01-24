#pragma once

#include <mmpg/player/ai.hpp>
#include "planet.hpp"
#include "relay.hpp"

namespace space_wars {

class Universe;

class AI : public mmpg::AI {
 public:
  void ScanUniverse();

  void SendFleet(int origin_id, int connection_id, int num_ships);
  void SendFleet(int origin_id, int relay_a, int relay_b, int destination_id, int num_ships);

  const std::vector<int>& owned_planets(int player_id) const;
  const Planet& planet(int planet_id) const;
  const Relay& relay(int relay_id) const;

 protected:
  void world(mmpg::World* world);

 private:
  Universe* universe_ = 0;
};

}
