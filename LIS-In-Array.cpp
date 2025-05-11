#include <iostream>
#include <vector>
#include <algorithm>

int lengthOfLIS(const std::vector<int>& nums) {
    std::vector<int> lis;

    for (int num : nums) {
        auto it = std::lower_bound(lis.begin(), lis.end(), num);
        if (it == lis.end()) {
            lis.push_back(num);
        } else {
            *it = num;  // replace to keep the smallest possible tail
        }
    }
     for(int n : lis)
       std::cout << n <<" " ;
       std::cout << "" <<std::endl;
    return lis.size();  // the length of LIS
}

int main() {
    std::vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    std::cout << "Length of LIS: " << lengthOfLIS(arr) << std::endl;
}


/*
| Step | x   | lower\_bound(lis, x)  | Action             | lis state        |
| ---- | --- | --------------------- | ------------------ | ---------------- |
| 1    | 10  | —                     | append             | `[10]`           |
| 2    | 9   | index 0 (replace 10)  | keep smallest tail | `[9]`            |
| 3    | 2   | index 0 (replace 9)   | keep smallest tail | `[2]`            |
| 4    | 5   | index 1               | append             | `[2, 5]`         |
| 5    | 3   | index 1 (replace 5)   | keep smallest tail | `[2, 3]`         |
| 6    | 7   | index 2               | append             | `[2, 3, 7]`      |
| 7    | 101 | index 3               | append             | `[2, 3, 7, 101]` |
| 8    | 18  | index 3 (replace 101) | keep smallest tail | `[2, 3, 7, 18]`  |
*/