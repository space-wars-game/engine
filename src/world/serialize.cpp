#include "serialize.hpp"
#include "universe.hpp"

namespace space_wars {

void Serialize(const space_wars::Universe& universe, std::ostream& stream) {
  Serialize(*universe.system, stream);
}

void Serialize(const System& system, std::ostream& stream) {
  Serialize(*system.sun, stream);
  Serialize(system.planets, stream);
}

void Serialize(const Sun& sun, std::ostream& stream) {
  stream << sun.radius << std::endl;
}

void Serialize(const std::vector<Planet*>& planets, std::ostream& stream) {
  stream << planets.size() << std::endl;

  for(Planet* planet : planets) {
    Serialize(*planet, stream);
  }
}

void Serialize(const Planet& planet, std::ostream& stream) {
  stream << planet.id << ' ' << planet.radius << ' ' << planet.x << ' ' << planet.y << ' ' << planet.owner << ' ' <<
    planet.ships << ' ' << planet.connections.size();

  for(int connection : planet.connections) {
    stream << ' ' << connection;
  }

  stream << std::endl;
}

}
