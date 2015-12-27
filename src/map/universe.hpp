#pragma once

#include <mmpg/world.hpp>
#include "system.hpp"
#include "json_serializer.hpp"

namespace space_wars {

class Universe : public mmpg::World {
 public:
  Universe();

  void Generate(int seed);
  void Read(std::istream& stream);
  void Update(int player, const mmpg::Action& action);
  void Print(std::ostream& stream);
  void PrintJSON(std::ostream& stream);

 private:
  JSONSerializer json_serializer_;

 public:
  struct Ship {
    float x, y;
  };

  std::vector<Ship*> ships;
  System* system;
};

}
