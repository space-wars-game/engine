#include "json_serializer.hpp"
#include "universe.hpp"

namespace space_wars {

#define QUOTE "\""
#define ATTR(__name__) QUOTE #__name__ QUOTE

JSONSerializer::JSONSerializer() {

}

void JSONSerializer::Serialize(const Universe& universe, std::ostream& stream) {
  stream << "{" << ATTR(players) << ":[";

  // TODO: Serialize player data

  stream << "],";

  Serialize(*universe.system, stream);

  stream << "}";
}

void JSONSerializer::Serialize(const System& system, std::ostream& stream) {
  stream << ATTR(system) << ":{";

  Serialize(*system.sun, stream);

  stream << ",";

  Serialize(system.planets, stream);

  stream << "}";
}

void JSONSerializer::Serialize(const Sun& sun, std::ostream& stream) {
  stream << ATTR(sun) << ":{";
  stream << ATTR(type) << ":" << QUOTE << "G" << QUOTE << "," << ATTR(radius) << ":" << sun.radius;
  stream << "}";
}

void JSONSerializer::Serialize(const std::vector<Planet*>& planets, std::ostream& stream) {
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

      stream << planet.connections[j]->id;
    }

    stream << "]";

    stream << "}";
  }

  stream << "]";
}

#undef QUOTE
#undef ATTR

}
