#include "universe_generator.hpp"

namespace space_wars {

namespace {

enum Elements { SYSTEM, SUN };

}

UniverseGenerator::UniverseGenerator(int seed) : seed_(seed) {

}

void UniverseGenerator::Generate(Universe& universe) {
  seed({SYSTEM, SUN, 0});

  universe.system = new System;
  universe.system->sun = new Sun(Sun::G, Sun::MIN_RADIUS + random_() % (Sun::MAX_RADIUS - Sun::MIN_RADIUS));
}

void UniverseGenerator::seed(const std::vector<int>& elements) {
  std::vector<int> seeds;

  seeds.push_back(seed_);
  seeds.insert(seeds.end(), elements.begin(), elements.end());

  std::seed_seq sseq(seeds.begin(), seeds.end());
  random_.seed(sseq);
}

}
