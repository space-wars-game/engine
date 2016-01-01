#pragma once

#include <map>
#include <vector>
#include <mmpg/world.hpp>
#include "system.hpp"
#include "json_serializer.hpp"
#include "entity/fleet.hpp"

namespace space_wars {

class Universe : public mmpg::World {
 public:
  Universe();
  virtual ~Universe();

  const Planet& planet(int planet_id) const;
  const std::vector<int>& owned_planets(int player_id) const;

  void Update(float delta);
  void MoveFleet(int player_id, int origin_id, int destination_id, int num_ships);

  void Print(std::ostream& stream);
  void PrintJSON(std::ostream& stream);

 private:
  JSONSerializer json_serializer_;

 public:
  std::vector<System*> systems;
  std::map<int, Planet*> planets;
  std::map<int, std::vector<int>> player_planets;
  std::vector<Fleet*> fleets;
};

}
