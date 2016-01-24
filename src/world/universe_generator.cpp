#include "universe_generator.hpp"
#include <queue>

namespace space_wars {

namespace {

enum SeedTypes {
  SYSTEM, SUN, PLANET, TYPE, RADIUS, SIZE, X, Y, DISTANCE_X, DISTANCE_Y, ORBIT_POSITION, RELAY,
  CONNECTION
};

bool connection_intersects(const CelestialBody* c, const CelestialBody* d, const std::vector<CelestialBody*> bodies) {
  // Check connection does NOT intersect other planets
  for(CelestialBody* b : bodies) {
    if(b == c or b == d) {
      continue;
    }

    if(b->ConnectionIntersects(c, d)) {
      return true;
    }
  }

  return false;
}

class ConnectionGenerator {
 public:
  ConnectionGenerator(const std::vector<CelestialBody*>& bodies, const std::vector<Planet*> planets, int start)
      : bodies_(bodies), planets_(planets), disconnected_(planets)
  {
    connected_.push_back(planets_[start]);
    disconnected_.erase(disconnected_.begin() + start);
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

    while(connection_intersects(connected_[c], disconnected_[d], bodies_)) {
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
};

}

UniverseGenerator::UniverseGenerator(int seed) : seed_(seed) {

}

Universe* UniverseGenerator::Generate(int num_players, int neutral_systems_ratio) {
  Universe* universe = new Universe;

  for(int i = 0; i < num_players * neutral_systems_ratio; ++i) {
    System* system = (i % neutral_systems_ratio == 0) ? GenerateHomeSystem(i, i / neutral_systems_ratio) : GenerateSystem(i);

    for(Planet* planet : system->planets) {
      universe->planets.push_back(planet);
    }

    universe->systems.push_back(system);
    universe->relays.push_back(system->relay);
  }

  ConnectSystems(*universe);

  return universe;
}

System* UniverseGenerator::GenerateSystem(int id) {
  System* system = new System;

  system->sun = GenerateSun(id);
  system->relay = GenerateRelay(id, system->sun);
  system->planets = GeneratePlanets(id, system->relay);

  ConnectRelayToPlanets(id, *system);
  ConnectPlanets(id, *system);

  return system;
}

System* UniverseGenerator::GenerateHomeSystem(int id, int player_id) {
  System* system = new System;

  system->sun = GenerateSun(id);
  system->relay = new Relay(id, 100, 80, 90);

  Planet* home = new Planet(Planet::MAX_RADIUS, 100, 80, 0);
  home->owner = player_id;

  system->planets.push_back(home);

  ConnectRelayToPlanets(id, *system);

  return system;
}

Sun* UniverseGenerator::GenerateSun(int system) {
  seed({SYSTEM, system, SUN, RADIUS});

  return new Sun(Sun::G, in_range(Sun::MIN_RADIUS, Sun::MAX_RADIUS));
}

Relay* UniverseGenerator::GenerateRelay(int system, Sun* sun) {
  seed({SYSTEM, system, RELAY, DISTANCE_X});
  unsigned int distance_x = in_range(Planet::MIN_DISTANCE_X, Planet::MAX_DISTANCE_X) + sun->radius + Relay::RADIUS;

  seed({SYSTEM, system, RELAY, DISTANCE_Y});
  unsigned int distance_y = in_range(Planet::MIN_DISTANCE_Y, Planet::MAX_DISTANCE_Y) + sun->radius + Relay::RADIUS;

  seed({SYSTEM, system, RELAY, ORBIT_POSITION});
  unsigned int orbit_position = in_range(0, 360);

  return new Relay(system, distance_x, distance_y, orbit_position);
}

std::vector<Planet*> UniverseGenerator::GeneratePlanets(int system, CelestialBody* previous) {
  seed({SYSTEM, system, SIZE});

  unsigned int size = in_range(System::MIN_SIZE, System::MAX_SIZE);

  std::vector<Planet*> planets;

  for(unsigned int i = 0; i < size; ++i) {
    planets.push_back(GeneratePlanet(system, (int)i, i == 0 ? previous : (CelestialBody*)planets[i-1]));
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

void UniverseGenerator::ConnectSystems(Universe& universe) {
  std::vector<System*> home_systems;
  std::vector<System*> neutral_systems;

  for(System* system : universe.systems) {
    if(system->planets.size() > 1) {
      neutral_systems.push_back(system);
    } else {
      home_systems.push_back(system);
    }
  }

  std::queue<System*> connected;
  std::queue<System*> edges;
  std::vector<System*> disconnected(neutral_systems);

  seed({SYSTEM, CONNECTION});
  int start = in_range(0, disconnected.size());

  edges.push(disconnected[start]);
  disconnected.erase(disconnected.begin() + start);

  // Connect neutral systems
  while(!disconnected.empty()) {
    System* origin = edges.front();
    edges.pop();

    int num_connections = in_range(Relay::MIN_NUM_CONNECTIONS, std::min(Relay::MAX_NUM_CONNECTIONS, (unsigned int)disconnected.size()));

    for(int i = 0; i < num_connections; ++i) {
      int d = in_range(0, disconnected.size());

      System* destination = disconnected[d];

      origin->relay->connections.push_back(destination->relay->id);

      edges.push(destination);
      disconnected.erase(disconnected.begin() + d);
    }

    connected.push(origin);
  }

  // Connect remaining edges
  while(!edges.empty()) {
    System* edge = edges.front();
    edges.pop();

    int num_connections = in_range(Relay::MIN_NUM_CONNECTIONS, std::min(Relay::MAX_NUM_CONNECTIONS, (unsigned int)connected.size()));

    for(int i = 0; i < num_connections; ++i) {
      System* connection = connected.front();
      connected.pop();

      edge->relay->connections.push_back(connection->relay->id);
    }

    connected.push(edge);
  }

  // Connect home systems to neutral systems
  for(System* home : home_systems) {
    for(unsigned int i = 0; i < System::HOME_NUM_CONNECTIONS; ++i) {
      int d = in_range(0, neutral_systems.size());
      System* destination = neutral_systems[d];

      home->relay->connections.push_back(destination->relay->id);

      neutral_systems.erase(neutral_systems.begin() + d);
    }
  }
}

void UniverseGenerator::ConnectRelayToPlanets(int id, System& system) {
  // List system bodies
  std::vector<CelestialBody*> bodies;

  bodies.push_back(system.sun);

  for(Planet* planet : system.planets) {
    bodies.push_back(planet);
  }

  seed({SYSTEM, id, RELAY, CONNECTION});
  std::vector<Planet*> planets(system.planets);
  int num_planets = in_range(Planet::MIN_NUM_CONNECTIONS, std::min(Planet::MAX_NUM_CONNECTIONS, (unsigned int)planets.size()));
  int i = 0;

  while(!planets.empty() and i < num_planets) {
    int s = in_range(0, (unsigned int)planets.size());
    int p = s;
    bool found = true;

    while(connection_intersects(system.relay, planets[p], bodies)) {
      p = (p + 1) % (unsigned int)planets.size();

      if(p == s) {
        found = false;
        break;
      }
    }

    if(found) {
      Planet* planet = planets[p];
      system.relay->planets.push_back(planet->id);
      planet->relay = system.relay->id;
      planets.erase(planets.begin() + p);
    }

    ++i;
  }
}

void UniverseGenerator::ConnectPlanets(int id, System& system) {
  // List system bodies
  std::vector<CelestialBody*> bodies;

  bodies.push_back(system.sun);
  bodies.push_back(system.relay);

  for(Planet* planet : system.planets) {
    bodies.push_back(planet);
  }

  // Connect planets between them
  seed({SYSTEM, id, CONNECTION});
  int start = in_range(0, system.planets.size());

  ConnectionGenerator connection_generator(bodies, system.planets, start);

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
