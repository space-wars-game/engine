#pragma once

#include <map>
#include <vector>
#include <mmpg/world.hpp>
#include "system.hpp"
#include "json_serializer.hpp"

namespace space_wars {

class Universe : public mmpg::World {
 public:
  Universe();
  ~Universe();

  const Planet& planet(int planet_id) const;
  const std::vector<int>& owned_planets(int player_id) const;

  void Update(float delta);

  void Print(std::ostream& stream);
  void PrintJSON(std::ostream& stream);

 private:
  JSONSerializer json_serializer_;

 public:
  System* system;
  std::map<int, Planet*> planets;
  std::map<int, std::vector<int>> player_planets;
};

}
