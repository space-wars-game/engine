#include "universe_generator.hpp"

namespace space_wars {

namespace {

enum SeedTypes {
  SYSTEM, SUN, PLANET, TYPE, RADIUS, SIZE, X, Y, DISTANCE_X, DISTANCE_Y, ORBIT_POSITION, RELAY,
  CONNECTION
};

class ConnectionGenerator {
 public:
  ConnectionGenerator(const std::vector<CelestialBody*>& bodies, const std::vector<Planet*> planets, int relay)
      : bodies_(bodies), planets_(planets), disconnected_(planets)
  {
    connected_.push_back(planets_[relay]);
    disconnected_.erase(disconnected_.begin() + relay);
  }

  bool is_finished() const {
    return disconnected_.empty();
  }

  void Connect(int c, int d) {
    if(!find_connection_candidates(c, d)) {
      disconnected_.erase(disconnected_.begin() + d);
      return;
    }

    // Connect planets
    Planet* pc = connected_[c];
    Planet* pd = disconnected_[d];

    pc->connections.push_back(pd->id);
    pd->connections.push_back(pc->id);

    connected_.push_back(pd);
    disconnected_.erase(disconnected_.begin() + d);
  }

  int connected_count() const {
    return connected_.size();
  }

  int disconnected_count() const {
    return disconnected_.size();
  }

 private:
  std::vector<CelestialBody*> bodies_;
  std::vector<Planet*> planets_;
  std::vector<Planet*> connected_;
  std::vector<Planet*> disconnected_;

  bool find_connection_candidates(int& c, int& d)
  {
    c = next_connected_candidate(c);

    int original_c = c;
    int original_d = d;

    while(connection_intersects(connected_[c], disconnected_[d])) {
      c = next_connected_candidate(c);

      if(c == original_c) {
        d = (d + 1) % (unsigned int)disconnected_.size();

        if(d == original_d) {
          return false;
        }
      }
    }

    return true;
  }

  int next_connected_candidate(int i) {
    do {
      i = (i + 1) % (unsigned int)connected_.size();
    } while(connected_[i]->connections.size() >= Planet::MAX_NUM_CONNECTIONS);

    return i;
  }

  bool connection_intersects(const CelestialBody* c, const CelestialBody* d) {
    // Check connection does NOT intersect other planets
    for(CelestialBody* b : bodies_) {
      if(b == c or b == d) {
        continue;
      }

      if(b->ConnectionIntersects(c, d)) {
        return true;
      }
    }

    return false;
  }
};

}

UniverseGenerator::UniverseGenerator(int seed) : seed_(seed) {

}

Universe* UniverseGenerator::Generate(int num_players, int neutral_systems_ratio) {
  Universe* universe = new Universe;

  for(int i = 0; i < num_players * neutral_systems_ratio; ++i) {
    System* system = (i % 3 == 0) ? GenerateHomeSystem(i, i / neutral_systems_ratio) : GenerateSystem(i);

    for(Planet* planet : system->planets) {
      universe->planets.push_back(planet);
    }

    universe->systems.push_back(system);
  }

  return universe;
}

System* UniverseGenerator::GenerateSystem(int id) {
  System* system = new System;

  system->sun = GenerateSun(id);
  system->planets = GeneratePlanets(id, system->sun);

  return system;
}

System* UniverseGenerator::GenerateHomeSystem(int id, int player_id) {
  System* system = new System;

  system->sun = GenerateSun(id);

  Planet* home = new Planet(Planet::MAX_RADIUS, 100, 80, 0);
  home->owner = player_id;

  system->planets.push_back(home);

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

  ConnectPlanets(system, sun, planets);

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

void UniverseGenerator::ConnectPlanets(int system, Sun* sun, std::vector<Planet*>& planets) {
  // List system bodies
  std::vector<CelestialBody*> bodies;

  bodies.push_back(sun);

  for(Planet* planet : planets) {
    bodies.push_back(planet);
  }

  // TODO: Add relays
  seed({SYSTEM, system, RELAY});
  int relay_position = in_range(0, planets.size());

  ConnectionGenerator connection_generator(bodies, planets, relay_position);

  seed({SYSTEM, system, CONNECTION});

  while(!connection_generator.is_finished()) {
    // Get a connected planet randomly
    int c = in_range(0, connection_generator.connected_count());

    // Get a disconnected planet randomly
    int d = in_range(0, connection_generator.disconnected_count());

    connection_generator.Connect(c, d);
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
