#include "layers.hpp"

#include <algorithm>
#include <limits>
#include <iostream>

static bool comparator(const MemoryUser& l, const MemoryUser& r) {
  return l.memSize > r.memSize;
}

void solveLayers(std::vector<MemoryUser> users,
                 std::vector<uint64_t>& memPoses) {
  memPoses.resize(users.size(), 0);
  for (int i = 0; i < users.size(); ++i) {
    users[i].id = i;
  }

  std::sort(users.begin(), users.end(), comparator);

  uint64_t memPos = 0;
  std::vector<MemoryUser> layer;
  layer.reserve(users.size());
  do {
    for (int i = 0; i < users.size(); ++i) {
      bool addToLayer = true;
      for (int j = 0; addToLayer && j < layer.size(); ++j) {
        addToLayer = !is_intersection(users[i].startIter, users[i].endIter,
                                      layer[j].startIter, layer[j].endIter);
      }
      if (addToLayer) {
        memPoses[users[i].id] = memPos;
        layer.push_back(users[i]);
        users.erase(users.begin() + i);
        --i;
      }
    }
    memPos += layer[0].memSize;
    layer.clear();
  } while (!users.empty());
}
