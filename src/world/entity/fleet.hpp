#pragma once

namespace space_wars {

class Fleet {
 public:
  Fleet(int owner, int ships, int destination_id, float distance);

  void Update(float delta);

  bool has_arrived() const;

  int owner;
  int ships;
  int destination_id;

 private:
  float time_left_;
};

}