#include <numeric>

#include <gtest/gtest.h>

#include "memory_manager.hpp"

using namespace mem;

static void genUsers(int numUsers, int maxNumIters, int maxMemSize,
                     std::vector<MemoryUser>& users) {
  users.resize(numUsers);
  for (int i = 0; i < numUsers; ++i) {
    users[i].startIter = rand() % maxNumIters;
    users[i].endIter = users[i].startIter + rand() % (maxNumIters - users[i].startIter);
    users[i].memSize = 1 + rand() % maxMemSize;
  }
}

static void testMaxMemUsage(const std::vector<MemoryUser>& users,
                            const std::vector<uint64_t>& memPoses, float* ratio)
{
  uint64_t memUsage = 0;
  uint64_t maxMemUsage = 0;
  uint64_t minMemUsage = 0;
  uint64_t numIters = 0;
  ASSERT_EQ(users.size(), memPoses.size());
  for (int i = 0; i < users.size(); ++i) {
    memUsage = std::max(memUsage, memPoses[i] + users[i].memSize);
    maxMemUsage += users[i].memSize;
    numIters = std::max(numIters, users[i].endIter);
  }
  numIters += 1;
  ASSERT_LE(memUsage, maxMemUsage);

  for (uint64_t i = 0; i < numIters; ++i) {
    uint64_t iterMemUsage = 0;
    for (int j = 0; j < users.size(); ++j) {
      if (users[j].startIter <= i && i <= users[j].endIter) {
        iterMemUsage += users[j].memSize;
      }
    }
    minMemUsage = std::max(minMemUsage, iterMemUsage);
  }
  ASSERT_GE(memUsage, minMemUsage);

  if (maxMemUsage != minMemUsage) {
    *ratio = (float)(memUsage - minMemUsage) / (maxMemUsage - minMemUsage);
  } else {
    *ratio = 0;
  }
}

static void testCorrectness(const std::vector<MemoryUser>& users,
                            const std::vector<uint64_t>& memPoses) {
  for (int i = 0; i < users.size(); ++i) {
    for (int j = 0; j < users.size(); ++j) {
      if (i == j)
        continue;
      if (is_intersection(users[i].startIter, users[i].endIter,
                          users[j].startIter, users[j].endIter)) {
        ASSERT_FALSE(is_intersection(memPoses[i],
                                     memPoses[i] + users[i].memSize - 1,
                                     memPoses[j],
                                     memPoses[j] + users[j].memSize - 1));
      }
    }
  }
}

static void test(int strategy) {
  static const int kNumRuns = 10000;

  std::vector<MemoryUser> users;
  std::vector<uint64_t> memPoses;

  std::vector<float> ratios(kNumRuns);
  for (int i = 0; i < kNumRuns; ++i) {
    genUsers(25, 20, 1000, users);
    solve(users, memPoses, strategy);

    testMaxMemUsage(users, memPoses, &ratios[i]);
    testCorrectness(users, memPoses);
  }

  std::sort(ratios.begin(), ratios.end());

  int mid = ratios.size() / 2;
  if (ratios.size() & 1) {
    std::cout << "median: " << ratios[mid] << std::endl;
  } else {
    std::cout << "median: " << (ratios[mid - 1] + ratios[mid]) * 0.5 << std::endl;
  }
  std::cout << "mean: " << std::accumulate(ratios.begin(), ratios.end(), 0.0f) /
                           ratios.size() << std::endl;
}

TEST(TestMemoryManager, dummy) {
  test(DUMMY);
}

TEST(TestMemoryManager, reuse_or_create) {
  test(REUSE_OR_CREATE);
}

TEST(TestMemoryManager, packing) {
  test(PACKING);
}
