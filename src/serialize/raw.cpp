#include "raw.hpp"
#include "../world/universe.hpp"

namespace space_wars {
namespace serialize {
namespace raw {

void Structure(const Universe& universe, std::ostream& stream) {
  Structure(universe.systems, stream);
}

void Structure(const std::vector<System*>& systems, std::ostream& stream) {
  stream << systems.size() << std::endl;

  for(System* system : systems) {
    Structure(*system, stream);
  }
}

void Structure(const System& system, std::ostream& stream) {
  Structure(*system.sun, stream);
  Structure(*system.relay, stream);
  Structure(system.planets, stream);
}

void Structure(const Sun& sun, std::ostream& stream) {
  stream << sun.radius << std::endl;
}

void Structure(const Relay& relay, std::ostream& stream) {
  stream << relay.id << ' ' << relay.x << ' ' << relay.y << ' ' << relay.connections.size();

  for(int connection : relay.connections) {
    stream << ' ' << connection;
  }

  stream << ' ' << relay.planets.size();

  for(int planet : relay.planets) {
    stream << ' ' << planet;
  }

  stream << std::endl;
}

void Structure(const std::vector<Planet*>& planets, std::ostream& stream) {
  stream << planets.size() << std::endl;

  for(Planet* planet : planets) {
    Structure(*planet, stream);
  }
}

void Structure(const Planet& planet, std::ostream& stream) {
  stream << planet.id << ' ' << planet.radius << ' ' << planet.x << ' ' << planet.y << ' '  << planet.relay << ' '
    << planet.type << ' ' << planet.rotation_direction << ' ' << planet.rotation_speed << ' '
    << planet.connections.size();

  for(int connection : planet.connections) {
    stream << ' ' << connection;
  }

  stream << std::endl;
}

void Data(const Universe& universe, std::ostream& stream) {
  for(Planet* planet : universe.planets) {
    stream << planet->owner << ' ' << planet->ships << std::endl;
  }
}

}
}
}
