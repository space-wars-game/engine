#include "json_serializer.hpp"
#include "universe.hpp"

namespace space_wars {

JSONSerializer::JSONSerializer() {

}

void JSONSerializer::Serialize(const Universe& universe, std::ostream& stream) {
  stream << "{\"players\":[";

  for(const Universe::Ship* ship : universe.ships) {
    stream << "{\"x\":" << ship->x << ",\"y\":" << ship->y << "}";
  }

  stream << "],";

  Serialize(*universe.system, stream);

  stream << "}";
}

void JSONSerializer::Serialize(const System& system, std::ostream& stream) {
  stream << "\"sun\":{";
  stream << "\"type\":\"G\",\"radius\":" << system.sun->radius;
  stream << "}";
}

}
