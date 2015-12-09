#include <iostream>
#include "universe_generator.hpp"

namespace space_wars {

namespace {

enum SeedTypes { SYSTEM, SUN, PLANET, TYPE, RADIUS, SIZE, X, Y, DISTANCE_X, DISTANCE_Y, ORBIT_POSITION };

}

UniverseGenerator::UniverseGenerator(int seed) : seed_(seed) {

}

void UniverseGenerator::Generate(Universe& universe) {
  universe.system = GenerateSystem(0);
}

System* UniverseGenerator::GenerateSystem(int id) {
  System* system = new System;

  system->sun = GenerateSun(id);
  system->planets = GeneratePlanets(id, system->sun);

  return system;
}

Sun* UniverseGenerator::GenerateSun(int system) {
  seed({SYSTEM, system, SUN, RADIUS});

  return new Sun(Sun::G, in_range(Sun::MIN_RADIUS, Sun::MAX_RADIUS));
}

std::vector<Planet*> UniverseGenerator::GeneratePlanets(int system, Sun* sun) {
  seed({SYSTEM, system, SIZE});

  unsigned int size = in_range(System::MIN_SIZE, System::MAX_SIZE);

  std::vector<Planet*> planets;

  for(unsigned int i = 0; i < size; ++i) {
    planets.push_back(GeneratePlanet(system, (int)i, i == 0 ? (CelestialBody*)sun : (CelestialBody*)planets[i-1]));
  }

  return planets;
}

Planet* UniverseGenerator::GeneratePlanet(int system, int id, CelestialBody* previous) {
  seed({SYSTEM, system, PLANET, id, RADIUS});
  unsigned int radius = in_range(Planet::MIN_RADIUS, Planet::MAX_RADIUS);

  seed({SYSTEM, system, PLANET, id, DISTANCE_X});
  unsigned int distance_x = in_range(Planet::MIN_DISTANCE_X, Planet::MAX_DISTANCE_X) + previous->radius + radius;

  seed({SYSTEM, system, PLANET, id, DISTANCE_Y});
  unsigned int distance_y = in_range(Planet::MIN_DISTANCE_Y, Planet::MAX_DISTANCE_Y) + previous->radius + radius;

  seed({SYSTEM, system, PLANET, id, ORBIT_POSITION});
  unsigned int orbit_position = in_range(0, 360);

  return new Planet(radius, previous->orbit_major + distance_x, previous->orbit_minor + distance_y, orbit_position);
}

void UniverseGenerator::seed(const std::vector<int>& elements) {
  std::vector<int> seeds;

  seeds.push_back(seed_);
  seeds.insert(seeds.end(), elements.begin(), elements.end());

  std::seed_seq sseq(seeds.begin(), seeds.end());
  random_.seed(sseq);
}

unsigned int UniverseGenerator::in_range(unsigned int min, unsigned int max) {
  return (unsigned int)(min + random_() % (max - min));
}

}
