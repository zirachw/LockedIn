# Two Sum (Integer)

> [Array], [Hash Table]

Run:

```
javac two_integer_sum.java
java two_integer_sum
```

# 1. My Approach (Hash Map)

Optimal solution

Algorithm:
1. Iterate each element and compute the diff of the current element, `diff = target - nums[i]`
2. Check if the diff exists in the map
3. If exists, return the diff index and the current index.
4. Store the current value (as key) and its index (as value)
5. Out of loop, then return empty array

Time complexity: $O(n)$

Space complexity: $O(n)$

```java
class Solution {
    public int[] twoSum(int[] nums, int target) {
        
        HashMap<Integer, Integer> lookup = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {

            int diff = target - nums[i];
            
            if (lookup.containsKey(diff)) {
                return new int[]{lookup.get(diff), i};
            }
            
            lookup.put(nums[i], i);
        }

        return new int[0];
    }
}
```

## 2. Brute Force

Naive, Two Loops of $i$ and $j$

Algorithm:
1. Iterate $i$ and $j$ pairs that resulting the target.
2. If there is pair, return both index
3. Out of loop, return empty array

Time complexity: $O(n^2)$

Space complexity: $O(1)$

```java
public class Solution {
    public int[] twoSum(int[] nums, int target) {

        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {

                if (nums[i] + nums[j] == target) {
                    return new int[]{i, j};
                }
            }
        }
        return new int[0];
    }
}
```

## 3. Sorting (Two Pointers)

More efficient than the Brute Force

Algorithm:
1. Sort an index array by its `nums` value, in Asc
2. Two pointers, $i$ at start and $j$ at end
3. Iterate
    - If equal, return both index
    - If sum is less than target, move $i$ to the right
    - If sum is more than target, move $j$ to the left
4. Ends if $i$ >= $j$

Time complexity: $O(n \log n)$

Space complexity: $O(n)$

```java
public class Solution {
    public int[] twoSum(int[] nums, int target) {

        Integer[] idx = new Integer[nums.length];

        for (int i = 0; i < idx.length; i++) {
            idx[i] = i;
        }

        Arrays.sort(idx, (a, b) -> nums[a] - nums[b]);

        int i = 0, j = nums.length - 1;

        while (i < j) {
            int sum = nums[idx[i]] + nums[idx[j]];

            if (sum == target) return new int[]{Math.min(idx[i], idx[j]), Math.max(idx[i], idx[j])};

            if (sum < target) i++; 
            else j--;
        }
        return new int[0];
    }
}
```