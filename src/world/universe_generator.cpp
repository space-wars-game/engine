#include "universe_generator.hpp"
#include <iostream>
#include <queue>

namespace space_wars {

namespace {

enum SeedTypes {
  SYSTEM, SUN, PLANET, TYPE, RADIUS, SIZE, X, Y, DISTANCE_X, DISTANCE_Y, ORBIT_POSITION, RELAY,
  CONNECTION
};

}

UniverseGenerator::UniverseGenerator(int seed) : seed_(seed) {

}

Universe* UniverseGenerator::Generate() {
  Universe* universe = new Universe;
  universe->system = GenerateSystem(0);

  return universe;
}

System* UniverseGenerator::GenerateSystem(int id) {
  System* system = new System;

  system->sun = GenerateSun(id);
  system->planets = GeneratePlanets(id, system->sun);

  // TODO: Generate home systems
  unsigned int owned_id = in_range(0, (int)system->planets.size());
  system->Conquer(owned_id, 0);

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

  ConnectPlanets(system, planets);

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

void UniverseGenerator::ConnectPlanets(int system, std::vector<Planet*>& planets) {
  // Unconnected planets
  std::vector<Planet*> unconnected(planets);

  // Connected
  std::queue<Planet*> connected;

  // TODO: Add relays
  seed({SYSTEM, system, RELAY});
  int relay_position = in_range(0, unconnected.size());

  connected.push(unconnected[relay_position]);
  unconnected.erase(unconnected.begin() + relay_position);

  seed({SYSTEM, system, CONNECTION});

  while(!unconnected.empty()) {
    // Get the first connected edge
    Planet* edge = connected.front();
    connected.pop();

    // Choose how many planets to connect to this edge
    int num_planets = in_range(Planet::MIN_NUM_CONNECTIONS, std::min(Planet::MAX_NUM_CONNECTIONS, (unsigned int) unconnected.size()));

    // Connect num_planets choosing randomly
    for(int i = 0; i < num_planets; ++i) {
      int p = in_range(0, unconnected.size());

      Planet* connection = unconnected[p];

      edge->connections.push_back(unconnected[p]->id);
      connection->connections.push_back(edge->id);

      connected.push(connection);
      unconnected.erase(unconnected.begin() + p);
    }
  }
}

void UniverseGenerator::seed(const std::vector<int>& elements) {
  std::vector<int> seeds;

  seeds.push_back(seed_);
  seeds.insert(seeds.end(), elements.begin(), elements.end());

  std::seed_seq sseq(seeds.begin(), seeds.end());
  random_.seed(sseq);
}

unsigned int UniverseGenerator::in_range(unsigned int min, unsigned int max) {
  unsigned int diff = max - min;

  if(diff == 0) {
    return min;
  }

  return (unsigned int)(min + random_() % diff);
}

}
