#pragma once

#include <map>
#include <vector>
#include <mmpg/world.hpp>
#include "system.hpp"
#include "entity/fleet.hpp"

namespace space_wars {

class Universe : public mmpg::World {
 public:
  Universe();
  virtual ~Universe();

  const Planet& planet(int planet_id) const;
  const Relay& relay(int relay_id) const;
  const std::vector<int>& owned_planets(int player_id) const;

  void Update(float delta);
  void MoveFleet(int player_id, int origin_id, int destination_id, int num_ships);
  void SendFleetThroughRelay(int player_id, int origin_id, int origin_relay, int destination_relay, int destination_id,
                             int num_ships);

  void PrintStructure(std::ostream& stream) const;
  void PrintViewerStructure(std::ostream& stream) const;

  void ReadData(std::istream& stream);
  void PrintData(std::ostream& stream) const;
  void PrintViewerData(std::ostream& stream) const;

 public:
  std::vector<System*> systems;
  std::vector<Planet*> planets;
  std::vector<Relay*> relays;
  std::map<int, std::vector<int>> player_planets;
  std::vector<Fleet*> fleets;
};

}
