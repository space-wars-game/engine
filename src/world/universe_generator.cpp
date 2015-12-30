#include <iostream>
#include "universe_generator.hpp"

namespace space_wars {

namespace {

enum SeedTypes {
  SYSTEM, SUN, PLANET, TYPE, RADIUS, SIZE, X, Y, DISTANCE_X, DISTANCE_Y, ORBIT_POSITION, RELAY,
  CONNECTION
};

int next_connected_candidate(const std::vector<Planet*>& connected, int i) {
  do {
    i = (i + 1) % (unsigned int)connected.size();
  } while(connected[i]->connections.size() >= Planet::MAX_NUM_CONNECTIONS);

  return i;
}

bool connection_intersects(const std::vector<Planet*>& planets, const Planet* c, const Planet* d) {
  // Check connection does NOT intersect other planets
  for(Planet* p : planets) {
    if(p == c or p == d) {
      continue;
    }

    if(p->ConnectionIntersects(c, d)) {
      return true;
    }
  }

  return false;
}

bool find_connection_candidates(const std::vector<Planet*>& planets, const std::vector<Planet*>& connected,
                                const std::vector<Planet*>& disconnected, int& c, int& d)
{
  c = next_connected_candidate(connected, c);

  int original_c = c;
  int original_d = d;

  while(connection_intersects(planets, connected[c], disconnected[d])) {
    c = next_connected_candidate(connected, c);

    if(c == original_c) {
      d = (d + 1) % (unsigned int)disconnected.size();

      if(d == original_d) {
        return false;
      }
    }
  }

  return true;
}

}

UniverseGenerator::UniverseGenerator(int seed) : seed_(seed) {

}

Universe* UniverseGenerator::Generate() {
  Universe* universe = new Universe;
  universe->system = GenerateSystem(0);

  for(Planet* planet : universe->system->planets) {
    universe->planets[planet->id] = planet;
  }

  return universe;
}

System* UniverseGenerator::GenerateSystem(int id) {
  System* system = new System;

  system->sun = GenerateSun(id);
  system->planets = GeneratePlanets(id, system->sun);

  // TODO: Generate home systems
  unsigned int owned_id = in_range(0, (int)system->planets.size());
  system->planets[owned_id]->owner = 0;
  system->planets[(owned_id+1) % system->planets.size()]->owner = 1;

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
  std::vector<Planet*> disconnected(planets);

  // Connected
  std::vector<Planet*> connected;

  // TODO: Add relays
  seed({SYSTEM, system, RELAY});
  int relay_position = in_range(0, disconnected.size());

  connected.push_back(disconnected[relay_position]);
  disconnected.erase(disconnected.begin() + relay_position);

  seed({SYSTEM, system, CONNECTION});

  while(!disconnected.empty()) {
    // Get a connected planet randomly
    int c = in_range(0, connected.size());

    // Get a disconnected planet randomly
    int d = in_range(0, disconnected.size());

    if(!find_connection_candidates(planets, connected, disconnected, c, d)) {
      disconnected.erase(disconnected.begin() + d);
      continue;
    }

    // Connect planets
    Planet* pc = connected[c];
    Planet* pd = disconnected[d];

    pc->connections.push_back(pd->id);
    pd->connections.push_back(pc->id);

    connected.push_back(pd);
    disconnected.erase(disconnected.begin() + d);
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
