#ifndef MEMORY_MANAGER_LAYERS_HPP_
#define MEMORY_MANAGER_LAYERS_HPP_

#include <vector>
#include "memory_manager.hpp"

using namespace mem;

void solveLayers(std::vector<MemoryUser> users, std::vector<uint64_t>& memPoses);

#endif  // MEMORY_MANAGER_LAYERS_HPP_
