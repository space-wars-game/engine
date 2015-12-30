#pragma once

#include "system.hpp"
#include <vector>
#include <ostream>

namespace space_wars {

class Universe;

class JSONSerializer {
 public:
  JSONSerializer();

  void Serialize(const Universe& universe, std::ostream& stream);
  void Serialize(const System& system, std::ostream& stream);
  void Serialize(const Sun& sun, std::ostream& stream);
  void Serialize(const std::vector<Planet*>& planets, std::ostream& stream);
};

}
