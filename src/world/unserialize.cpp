#include "unserialize.hpp"
#include "universe.hpp"

namespace space_wars {

void Unserialize(Universe& universe, std::istream& stream) {
  universe.system = new System;

  Unserialize(*universe.system, stream, universe);

  for(Planet* planet : universe.system->planets) {
    universe.planets[planet->id] = planet;

    if(planet->is_owned()) {

    }
  }
}

void Unserialize(System& system, std::istream& stream, Universe& universe) {
  system.sun = new Sun;

  Unserialize(*system.sun, stream);
  Unserialize(system.planets, stream, universe);
}

void Unserialize(Sun& sun, std::istream& stream) {
  stream >> sun.radius;

  // TODO: Sun type (un)serialization
  sun.type = Sun::G;
}

void Unserialize(std::vector<Planet*>& planets, std::istream& stream, Universe& universe) {
  int num_planets;

  stream >> num_planets;

  for(int i = 0; i < num_planets; ++i) {
    Planet* planet = new Planet;

    Unserialize(*planet, stream);

    planets.push_back(planet);

    // Update universe useful data structures
    // TODO: Think about moving this data somewhere else, as it is not used in the master process
    universe.planets[planet->id] = planet;

    if(planet->is_owned()) {
      universe.player_planets[planet->owner].push_back(planet->id);
    }
  }
}

void Unserialize(Planet& planet, std::istream& stream) {
  int num_connections;

  stream >> planet.id >> planet.radius >> planet.x >> planet.y >> planet.owner >> planet.ships >> num_connections;

  for(int i = 0; i < num_connections; ++i) {
    int connection_id;
    stream >> connection_id;

    planet.connections.push_back(connection_id);
  }
}

}
