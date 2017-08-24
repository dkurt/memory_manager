#ifndef MEMORY_MANAGER_REUSE_OR_CREATE_HPP_
#define MEMORY_MANAGER_REUSE_OR_CREATE_HPP_

#include <vector>
#include "memory_manager.hpp"

using namespace mem;

void reuseOrCreate(std::vector<MemoryUser> users, std::vector<uint64_t>& memPoses);

#endif  // MEMORY_MANAGER_REUSE_OR_CREATE_HPP_
