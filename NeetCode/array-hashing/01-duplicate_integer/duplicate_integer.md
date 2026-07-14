# Duplicate Integer

> [Array], [Hash Table], [Sorting]

Run:

```
g++ duplicate_integer.cpp -o duplicate_integer
./duplicate_integer
```

## 1. Brute Force

Naive

Algorithm:
1. Iterate each element to check fully other element
2. If there is a pair, return `true`
3. If no found, return `false`

Time complexity: $O(n^2)$

Space complexity: $O(1)$

```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }
};
```

## 2. Sorting

Still naive, but less workload

Algorithm:
1. Sort
2. Iterate each element and compare with neighbours
3. If there is a pair, return `true`
4. If no found, return `false`

Time complexity: $O(n \log n)$

Space complexity: $O(1)$ or $O(n)$, depends on the sorting algorithm

```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end())
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                    return true;
            }
        }
    }
    return false;
}
```

## 3. Hash set

Optimal solution

Algorithm:
1. Init an empty hash set to store seen values
2. Iterate each element
3. For each number:
    - If it's already in the set, return `true`
    - If no found, add to the set
4. If the loop finishes without any dups, return `false`

```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {

        unordered_set<int> seen;

        for (int num : nums) {

            if (seen.count(num)) {
                return true;
            }

            seen.insert(num);
        }

        return false;
    }
};
```

Time complexity: $O(n)$

Space complexity: $O(n)$

## 4. Hash set length

Optimal solution, with less code

Algorithm:
1. Convert the array into a hash set, which removes duplicates
2. Compare the size with the original array
3. If the set is smaller, return `true` because the dup is removed
4. Otherwise, return `false`

```cpp
class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {
        return unordered_set<int>(nums.begin(), nums.end()).size() < nums.size();
    }
};
```
