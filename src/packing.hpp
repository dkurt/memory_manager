#ifndef MEMORY_MANAGER_PACKING_HPP_
#define MEMORY_MANAGER_PACKING_HPP_

#include <vector>
#include "memory_manager.hpp"

using namespace mem;

void packing(std::vector<MemoryUser> users, std::vector<uint64_t>& memPoses);

#endif  // MEMORY_MANAGER_PACKING_HPP_
