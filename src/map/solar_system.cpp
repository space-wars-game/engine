
#include <random>
#include "solar_system.hpp"
#include "elements.hpp"

namespace space_wars {

SolarSystem::SolarSystem(int seed) {
  // TODO: Improve generation. Move logic to a generator class??
  std::seed_seq sseq({seed, (int)Elements::SOLAR_SYSTEM, (int)Elements::SUN, 0});
  std::mt19937 generator(sseq);

  sun = new Sun(Sun::TYPE::G, 20 + generator() % 10);
}

}
