#pragma once

#include "planetary_system.hpp"

namespace space_wars {

class Universe;

class JSONSerializer {
 public:
  JSONSerializer();

  void Serialize(const Universe& universe, std::ostream& stream);
  void Serialize(const PlanetarySystem& system, std::ostream& stream);
};

}
