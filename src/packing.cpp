#include "packing.hpp"

#include <algorithm>
#include <iostream>

static bool comparator(const MemoryUser& l, const MemoryUser& r) {
  return l.memSize > r.memSize;
}

static bool compareByMemPos(const std::pair<MemoryUser, uint64_t>& l,
                            const std::pair<MemoryUser, uint64_t>& r) {
  return l.second < r.second;
}

void packing(std::vector<MemoryUser> users, std::vector<uint64_t>& memPoses) {
  memPoses.resize(users.size(), 0);
  for (int i = 0; i < users.size(); ++i) {
    users[i].id = i;
  }

  // Sort by memory size in descending order.
  std::sort(users.begin(), users.end(), comparator);

  for (int i = 0; i < users.size(); ++i) {
    // Collect processed users that are actual at the same time.
    std::vector<std::pair<MemoryUser, uint64_t> > processedUsers;
    for (int j = 0; j < i; ++j) {
      if (is_intersection(users[i].startIter, users[i].endIter,
                          users[j].startIter, users[j].endIter)) {
        std::pair<MemoryUser, uint64_t> term(users[j], memPoses[users[j].id]);
        processedUsers.push_back(term);
      }
    }
    std::sort(processedUsers.begin(), processedUsers.end(), compareByMemPos);

    uint64_t memPos = 0;
    for (int j = 0; j < processedUsers.size(); ++j) {
      if (is_intersection(memPos, memPos + users[i].memSize - 1,
                          processedUsers[j].second,
                          processedUsers[j].second + processedUsers[j].first.memSize - 1)) {
        memPos = processedUsers[j].second + processedUsers[j].first.memSize;
      }
    }
    memPoses[users[i].id] = memPos;
  }
}
