#pragma once

#include <mmpg/world.hpp>
#include "system.hpp"
#include "json_serializer.hpp"

namespace space_wars {

class Universe : public mmpg::World {
 public:
  Universe();

  void Print(std::ostream& stream);
  void PrintJSON(std::ostream& stream);

 private:
  JSONSerializer json_serializer_;

 public:
  System* system;
};

}
