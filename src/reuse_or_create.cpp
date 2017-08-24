#include "reuse_or_create.hpp"

#include <algorithm>
#include <limits>

// Sort by start iter in ascending order and by memory size in descending for
// users with the same start iteration.
static bool comparator(const MemoryUser& l, const MemoryUser& r) {
  if (l.startIter == r.startIter) {
    return l.memSize > r.memSize;
  }
  return l.startIter < r.startIter;
}

void reuseOrCreate(std::vector<MemoryUser> users,
                   std::vector<uint64_t>& memPoses) {
  memPoses.resize(users.size(), 0);
  for (int i = 0; i < users.size(); ++i) {
    users[i].id = i;
  }

  std::sort(users.begin(), users.end(), comparator);

  std::vector<MemoryUser> processedUsers;
  for (int i = 0; i < users.size(); ++i) {
    uint64_t iter = users[i].startIter;

    // Merge free blocks.
    for (int j = 0; j < processedUsers.size(); ++j) {
      if (!processedUsers[j].isActual(iter)) {
        j += 1;
        while (j < processedUsers.size() && !processedUsers[j].isActual(iter)) {
          processedUsers[j - 1].memSize += processedUsers[j].memSize;
          processedUsers.erase(processedUsers.begin() + j);
        }
        // Here we finished or processedUsers[j] is actual.
      }
    }

    // Minimal difference between free memory size and new user memory size.
    // We try to find closest block.
    uint64_t minCost = std::numeric_limits<uint64_t>::max();
    uint64_t bestMemPos = 0;
    int freeBlockIdx = -1;  // Index in processedUsers.

    // Find free memory blocks.
    uint64_t memPos = 0;
    for (int j = 0; j < processedUsers.size(); ++j) {
      // If user is no longer actual.
      if (!processedUsers[j].isActual(iter)) {
        uint64_t freeBlockSize = processedUsers[j].memSize;

        // If free memory is enough for a new user.
        if (freeBlockSize >= users[i].memSize) {
          uint64_t cost = freeBlockSize - users[i].memSize;
          if (cost < minCost) {
            minCost = cost;
            bestMemPos = memPos;
            freeBlockIdx = j;
            if (minCost == 0) {
              break;
            }
          }
        }
      }
      memPos += processedUsers[j].memSize;
    }

    if (freeBlockIdx != -1) {
      // Replace to actual user.
      processedUsers[freeBlockIdx] = users[i];
      memPoses[users[i].id] = bestMemPos;
      if (minCost != 0) {
        // Add fake user with the rest of memory.
        MemoryUser rest(0, 0, minCost);
        processedUsers.insert(processedUsers.begin() + freeBlockIdx + 1, rest);
      }
    } else {
      // Allocate memory at the end.
      processedUsers.push_back(users[i]);
      memPoses[users[i].id] = memPos;
    }
  }
}
