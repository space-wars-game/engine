#include "universe_generator.hpp"

namespace space_wars {

namespace {

enum Elements { SOLAR_SYSTEM, SUN };

}

UniverseGenerator::UniverseGenerator(int seed) : seed_(seed) {

}

void UniverseGenerator::Generate(Universe& universe) {
  std::seed_seq sseq({seed_, (int)Elements::SOLAR_SYSTEM, (int)Elements::SUN, 0});
  random_.seed(sseq);

  universe.planetary_system = new PlanetarySystem;
  universe.planetary_system->sun = new Sun(Sun::G, Sun::MIN_RADIUS + random() % (Sun::MAX_RADIUS - Sun::MIN_RADIUS));
}

}