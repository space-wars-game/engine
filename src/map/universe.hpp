#pragma once

#include <world.hpp>
#include "solar_system.hpp"

namespace space_wars {

class Universe : public mmpg::World {
 public:
  Universe();

  void Read(std::istream& stream);
  void Update(int player, const mmpg::Action& action);
  void Print(std::ostream& stream);
  void PrintJSON(std::ostream& stream);

  // TODO: Move this logic
  mmpg::Action* ParseAction(std::istream& data);

 private:
  struct Ship {
    float x, y;
  };

  std::vector<Ship*> ships_;
  SolarSystem solar_system_;
};

}
