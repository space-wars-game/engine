#include "deserialize.hpp"
#include "world/universe.hpp"

namespace space_wars {
namespace deserialize {

void Structure(Universe& universe, std::istream& stream) {
  Structure(universe.systems, stream, universe);
}

void Structure(std::vector<System*>& systems, std::istream& stream, Universe& universe) {
  int num_systems;

  stream >> num_systems;

  for(int i = 0; i < num_systems; ++i) {
    System* system = new System;

    Structure(*system, stream, universe);

    systems.push_back(system);
  }
}

void Structure(System& system, std::istream& stream, Universe& universe) {
  system.sun = new Sun;
  Structure(*system.sun, stream);

  system.relay = new Relay;
  Structure(*system.relay, stream);
  universe.relays.push_back(system.relay);

  Structure(system.planets, stream, universe);
}

void Structure(Sun& sun, std::istream& stream) {
  stream >> sun.radius;

  // TODO: Sun type (un)serialization
  sun.type = Sun::G;
}

void Structure(Relay& relay, std::istream& stream) {
  int num_connections;

  stream >> relay.id >> relay.x >> relay.y >> num_connections;

  for(int i = 0; i < num_connections; ++i) {
    int connection;
    stream >> connection;

    relay.connections.push_back(connection);
  }

  int num_planets;

  stream >> num_planets;

  for(int i = 0; i < num_planets; ++i) {
    int planet;
    stream >> planet;

    relay.planets.push_back(planet);
  }
}

void Structure(std::vector<Planet*>& planets, std::istream& stream, Universe& universe) {
  int num_planets;

  stream >> num_planets;

  for(int i = 0; i < num_planets; ++i) {
    Planet* planet = new Planet;

    Structure(*planet, stream);

    planets.push_back(planet);

    universe.planets.push_back(planet);
  }
}

void Structure(Planet& planet, std::istream& stream) {
  int num_connections;

  stream >> planet.id >> planet.radius >> planet.x >> planet.y >> planet.relay >> num_connections;

  for(int i = 0; i < num_connections; ++i) {
    int connection_id;
    stream >> connection_id;

    planet.connections.push_back(connection_id);
  }
}

void Data(Universe& universe, std::istream& stream) {
  universe.player_planets.clear();

  for(unsigned int i = 0; i < universe.planets.size(); ++i) {
    Planet* planet = universe.planets[i];

    stream >> planet->owner >> planet->ships;

    if(planet->is_owned()) {
      universe.player_planets[planet->owner].push_back(i);
    }
  }
}

}
}
