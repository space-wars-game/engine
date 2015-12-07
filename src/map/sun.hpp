#pragma once

#include <ostream>

namespace space_wars {

class Sun {
 public:
  enum TYPE {
    G
  };

  Sun(TYPE type, unsigned int radius);

  void PrintJSON(std::ostream& stream) const;

  TYPE type;
  unsigned int radius;
};

}
