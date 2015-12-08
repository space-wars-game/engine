#pragma once

#include "system.hpp"

namespace space_wars {

class Universe;

class JSONSerializer {
 public:
  JSONSerializer();

  void Serialize(const Universe& universe, std::ostream& stream);
  void Serialize(const System& system, std::ostream& stream);
};

}
