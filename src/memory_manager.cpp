#include "memory_manager.hpp"
#include "reuse_or_create.hpp"

namespace mem {

MemoryUser::MemoryUser(uint64_t startIter, uint64_t endIter, uint64_t memSize)
  : startIter(startIter), endIter(endIter), memSize(memSize) {}

bool MemoryUser::isActual(uint64_t iter) {
  return startIter <= iter && iter <= endIter;
}

static void dummy(const std::vector<MemoryUser>& users,
                  std::vector<uint64_t>& indices) {
  indices.resize(users.size(), 0);
  for (int i = 1; i < users.size(); ++i) {
    indices[i] = indices[i - 1] + users[i - 1].memSize;
  }
}

void solve(const std::vector<MemoryUser>& users,
           std::vector<uint64_t>& indices, int strategy) {
  if (strategy == REUSE_OR_CREATE) {
    reuseOrCreate(users, indices);
  } else {
    dummy(users, indices);
  }
}

}  // namespace mem
