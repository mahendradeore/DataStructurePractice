#include "gtest/gtest.h"
#include <algorithm>
#include <vector>

typedef std::pair<int, int> range;

std::vector< range > mergeIntervals(std::vector< range > ranges) {
    std::vector<range> result;
    sort(ranges.begin(),ranges.end(),[](const range &a, const range &b) {
        return a.first < b.first; 
    });
  
   for (const auto &current : ranges) {
        // If the result is empty or the current interval does not overlap with the last one, add it
        if (result.empty() || result.back().second < current.first) {
            result.push_back(current);
        } else {
            // Otherwise, there is overlap, so merge the current interval with the last one
            result.back().second = std::max(result.back().second, current.second);
        }
    }

    return result;
}

// print your findings using this function!
#define LOG
void log() {
    auto a = mergeIntervals({ });
    for (auto i : a) std::cout << i.first << ' ' << i.second << std::endl;
}

// tests

TEST(OnlyOneOverlap, MergeIntervals) {
    EXPECT_EQ(
        mergeIntervals({{1, 4}, {2, 5}, {7, 10}, {12, 16}}),
        std::vector< range >({{1, 5}, {7, 10}, {12, 16}})
    );
}

TEST(AllIntervalsOverlapping, MergeIntervals) {
    EXPECT_EQ(
        mergeIntervals({{1, 3}, {2, 9}, {3, 10}, {1, 16}}),
        std::vector< range >({{1, 16}})
    );
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
