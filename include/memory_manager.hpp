#ifndef INCLUDE_MEMORY_MANAGER_HPP_
#define INCLUDE_MEMORY_MANAGER_HPP_

#include <stdint.h>

#include <vector>

namespace mem {

struct MemoryUser {
  MemoryUser(uint64_t startIter = 0, uint64_t endIter = 0, uint64_t memSize = 0);

  uint64_t id;  // Optional field (is used internally).
  uint64_t startIter;
  uint64_t endIter;
  uint64_t memSize;

  bool isActual(uint64_t iter);
};

enum Strategy {
  DUMMY,
  // Reuse free block closest to new user's memory size or allocate.
  REUSE_OR_CREATE,
  PACKING
};

void solve(const std::vector<MemoryUser>& users, std::vector<uint64_t>& indices,
           int strategy);

bool is_intersection(uint64_t l_from, uint64_t l_to, uint64_t r_from,
                     uint64_t r_to);

}  // namespace mem

#endif  // INCLUDE_MEMORY_MANAGER_HPP_
