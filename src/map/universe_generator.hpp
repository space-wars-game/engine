#pragma once

#include <random>
#include "universe.hpp"


namespace space_wars {

class UniverseGenerator {
 public:
  UniverseGenerator(int seed);

  void Generate(Universe& universe);

 private:
  int seed_;
  std::mt19937 random_;
};

}
