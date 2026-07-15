# 238. Product of Array Except Self

> [Array], [Prefix Sum]

Run:

```
javac products_of_array_except_self.java
java products_of_array_except_self
```

## 1. Prefix & Suffix (Optimal)

Optimal solution

Algorithm:
1. `prefix = 1`
2. First pass (left to right)
    - For each index `i`, set `res[i] = prefix` (product of all elements to the left)
    - Update `prefix *= nums[i]`
3. `postfix = 1`
4. Second pass (right to left)
    - For each index `i`, set `res[i] *= postfix` (product of all elements to the right)
    - Update `postfix *= nums[i]`

Time complexity: $O(n)$

Space complexity: $O(1)$

```java
class Solution 
{
    public int[] productExceptSelf(int[] nums) 
    {
        int n = nums.length;
        int[] res = new int[n];

        res[0] =  1;
        for (int i = 1; i < n; i++)
        {
            res[i] = res[i - 1] * nums[i - 1];
        }

        int postfix = 1;
        for (int i = n - 1; i >= 0; i --)
        {
            res[i] *= postfix;
            postfix *= nums[i];
        }

        return res;
    }
}
```

## 2. Prefix & Suffix

Less space optimal

Algorithm:
1. Init
    - `pref` for prefix products
    - `suff` for suffix products
    - `res` for result
2. Set
    - `pref[0] = 1`, nothing to the left
    - `suff[n-1] = 1`, nothing to the right
3. Build the array
    - Prefix, for each `i` from `1` to `n-1` : `pref[i] = nums[i - 1] * pref[i - 1]`
    - Suffix, for each `i` from `n - 2` down to `0` : `suff[i] = nums[i + 1] * suff[i + 1]`
    - Result, `res[i] = pref[i] * suff[i]`

Time complexity: $O(n)$

Space complexity: $O(n)$

```java
public class Solution 
{
    public int[] productExceptSelf(int[] nums) 
    {
        int n = nums.length;
        int[] res = new int[n];
        int[] pref = new int[n];
        int[] suff = new int[n];

        pref[0] = 1;
        suff[n - 1] = 1;

        for (int i = 1; i < n; i++)
        {
            pref[i] = nums[i - 1] * pref[i - 1];
        }

        for (int i = n - 2; i >= 0; i--) 
        {
            suff[i] = nums[i + 1] * suff[i + 1];
        }

        for (int i = 0; i < n; i++)
        {
            res[i] = pref[i] * suff[i];
        }
        return res;
    }
}

## 3. Division

Simple idea

1. Iterate once with multiply all non-zero num and count how many zero
2. If greater than 1, all zero
3. Iterate again
    - If there is one zero, index with zero gets the product and other is zero
    - If there are no zeros, then `prod // nums[i]`

Time complexity: $O(n)$

Space complexity: $O(1)$

```java
public class Solution 
{
    public int[] productExceptSelf(int[] nums) 
    {
        int prod = 1, zeroCount = 0;
        for (int num : nums) 
        {
            if (num != 0) prod *= num;
            else zeroCount++;
        }

        if (zeroCount > 1) return new int[nums.length];

        int[] res = new int[nums.length];
        for (int i = 0; i < nums.length; i++)
        {
            if (zeroCount > 0) res[i] = (nums[i] == 0) ? prod : 0;
            else res[i] = prod / nums[i];
        }
        return res;
    }
}
```

## 4. Brute Force

Naive

1. For each `i` elements, multiply all `j` besides it.
2. Store the product into `res`

Time complexity: $O(n^2)$

Space complexity: $O(1)$

```java
public class Solution 
{
    public int[] productExceptSelf(int[] nums)
    {
        int n = nums.length;
        int[] res = new int[n];

        for (int i = 0; i < n; i++)
        {
            int prod = 1;
            for (int j = 0; j < n; j++) 
            {
                if (i != j) prod *= nums[j];
            }
            res[i] = prod;
        }
        return res;
    }
}
```