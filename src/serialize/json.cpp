#include "json.hpp"
#include "../world/universe.hpp"

namespace space_wars {
namespace serialize {
namespace json {

#define QUOTE "\""
#define ATTR(__name__) QUOTE #__name__ QUOTE

void Structure(const Universe& universe, std::ostream& stream) {
  stream << "{";

  Structure(universe.systems, stream);

  stream << "}";
}

void Structure(const std::vector<System*>& systems, std::ostream& stream) {
  stream << ATTR(systems) << ":[";

  for(unsigned int i = 0; i < systems.size(); ++i) {
    if(i != 0) {
      stream << ',';
    }

    Structure(*systems[i], stream);
  }

  stream << "]";
}

void Structure(const System& system, std::ostream& stream) {
  stream << '{';

  Structure(*system.sun, stream);

  stream << ',';

  Structure(system.planets, stream);

  stream << '}';
}

void Structure(const Sun& sun, std::ostream& stream) {
  stream << ATTR(sun) << ":{";
  stream << ATTR(type) << ":" << QUOTE << "G" << QUOTE << "," << ATTR(radius) << ":" << sun.radius;
  stream << "}";
}

void Structure(const std::vector<Planet*>& planets, std::ostream& stream) {
  stream << ATTR(planets) << ":[";

  for(unsigned int i = 0; i < planets.size(); ++i) {
    const Planet& planet = *planets[i];

    if(i != 0) {
      stream << ",";
    }

    stream << "{";
    stream << ATTR(id) << ":" << planet.id << ",";
    stream << ATTR(x) << ":" << planet.x << "," << ATTR(y) << ":" << planet.y << ",";
    stream << ATTR(radius) << ":" << planet.radius << ",";
    stream << ATTR(connections) << ":[";

    for(unsigned int j = 0; j < planet.connections.size(); ++j) {
      if(j != 0) {
        stream << ",";
      }

      stream << planet.connections[j];
    }

    stream << "]";

    stream << "}";
  }

  stream << "]";
}

void Data(const Universe& universe, std::ostream& stream) {
  stream << "{";

  stream << ATTR(planets) << ":[";

  stream << universe.planets[0]->owner << ',' << universe.planets[0]->ships;

  for(unsigned int i = 1; i < universe.planets.size(); ++i) {
    stream << ',' << universe.planets[i]->owner << ',' << universe.planets[i]->ships;
  }

  stream << "]}";
}

#undef QUOTE
#undef ATTR

}
}
}
