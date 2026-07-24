# 347. Top K Frequent Elements

> [Array], [Hash Table], [Divide and Conquer], [Sorting], [Heap (Priority Queue)], [Bucket Sort], [Counting], [Quickselect]

Run:

```
g++ top_k_frequent_elements.cpp -o top_k_frequent_elements
./top_k_frequent_elements
```

## 1. Sorting

Naive

Algorithm:
1. Freq map
2. Sort a list of `[freq, num]` asc
3. Take from the highest freq until k element

Time complexity: $O(n \ \log \ n)$

Space complexity: $O(n)$

```cpp
class Solution 
{
    public:
        vector<int> topKFrequent(vector<int>& nums, int k)
        {
            unordered_map<int, int> freq;

            for (int num : nums) freq[num]++;

            vector<pair<int, int>> arr;
            for (auto& [key, value] : freq) arr.push_back({value, key});
            sort(arr.rbegin(), arr.rend());

            vector<int> res;
            for (int i = 0; i < k; ++i) res.push_back(arr[i].second)

            return res;
        }
};
```

## 3. Min-Heap

More efficient than sorting

Algorithm:
1. Freq map
2. For each element in freq map
    - Push `(freq, num)` into the heap
    - If heap size bigger than k, pop once to remove the smallest freq
3. Loop from the heap that contains the `k` most freq element

Time complexity: $O(n \ \log \ k)$

Space complexity: $O(n + k)$

```cpp
class Solution
{
    public:
        vector<int> topKFrequent(vector<int>& nums, int k)
        {
            unordered_map<int, int> freq;
            for (int num : nums) freq[num]++;

            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
            for (auto& [key, value] : freq)
            {
                heap.push({value, key});
                if (heap.size() > k) heap.pop();
            }

            vector<int> res;
            for (int i = 0; i < k; i++) {
                res.push_back(heap.top().second);
                heap.pop();
            }
            return res;
        }
};
```

## 2. Used Approach (Freq & Group)

Optimal solution

Algorithm:
1. Freq map
2. Group of same freq ordered 0 to max length
3. Loop from largest freq until k element stored

Time complexity: $O(n)$

Space complexity: $O(n)$

```cpp
class Solution
{
    public:
        vector<int> topKFrequent(vector<int>& nums, int k)
        {
            unordered_map<int, int> freq;

            for (int num : nums) freq[num]++;

            vector<vector<int>> groups(nums.size() + 1);

            for (auto& [key, value] : freq) groups[value].push_back(key);

            vector<int> res;

            for (int i = groups.size() - 1; i > 0; i--)
            {
                for (int num : groups[i])
                {
                    res.push_back(num);

                    if (res.size() == k) return res;
                }
            }

            return res;
        }
};
```