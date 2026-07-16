# String Cantik OSN-P

> [String], [Prefix Sum]

Run:

```
g++ A.cpp -o A
./A
```

# 1. My Approach (One-Pass Counter)

Optimal solution

Algorithm:
1. Iterate each character
2. If it's `O`, `S`, or `N`, increment its running count
3. If it's `P` and all of `O`, `S`, `N` have been seen at least once
    - Extend the previous best chain by 1 (add this `P`), or
    - Start fresh using the full `O+S+N` count so far
    - Take whichever is bigger
4. Return the best result found, or `-1` if never valid

Time complexity: $O(n)$

Space complexity: $O(1)$, 4 letters

```cpp
class Solution {
public:
    int stringCantik(string s)
    {
        unordered_map<char, int> umap;

        int idx = 0;
        int res = -1;
        
        while (idx < s.length())
        {
            char c = s[idx];

            if (c == 'O' || c == 'S' || c == 'N')
            {
                umap[c]++;
            }
            if (umap['O'] && umap['S'] && umap['N'] && c == 'P')
            {
                res = max(res + 1, umap['O'] + umap['S'] + umap['N'] + 1);
            }
            idx++;
        }

    return res;
    }
};
```

## 2. Brute Force

Naive, try every split point

Algorithm:
1. For each split index $i$, count `O`, `S`, `N` in `s[0..i-1]` and `P` in `s[i..n-1]`
2. If prefix has all three and suffix has at least one `P`, track the max total
3. Return the max found, or `-1` if none valid

Time complexity: $O(n^2)$

Space complexity: $O(1)$

```cpp
class Solution {
public:
    int stringCantik(string s) 
    {
        int n = s.length();
        int res = -1;

        for (int i = 0; i <= n; i++) 
        {
            int o = 0, s = 0, n = 0, p = 0;

            for (int j = 0; j < i; j++) 
            {
                if (s[j] == 'O') o++;
                if (s[j] == 'S') s++;
                if (s[j] == 'N') n++;
            }

            for (int j = i; j < n; j++) 
            {
                if (s[j] == 'P') p++;
            }

            if (o > 0 && s > 0 && n > 0 && p > 0) 
            {
                res = max(res, o + s + n + p);
            }
        }

        return res;
    }
};
```

## 3. Prefix/Suffix Arrays

More efficient than Brute Force, precompute the counts once instead of rescanning per split

Algorithm:
1. Precompute prefix counts of `O`, `S`, `N` up to each index
2. Precompute suffix counts of `P` from each index to the end
3. For each split index, combine the precomputed prefix and suffix in $O(1)$
4. Track and return the max valid total, or `-1` if none valid

Time complexity: $O(n)$

Space complexity: $O(n)$

```cpp
class Solution {
public:
    int stringCantik(string s) 
    {
        int n = s.length();

        vector<int> prefO(n + 1), prefS(n + 1), prefN(n + 1), sufP(n + 2);

        for (int i = 0; i < n; i++) 
        {
            prefO[i + 1] = prefO[i] + (s[i] == 'O');
            prefS[i + 1] = prefS[i] + (s[i] == 'S');
            prefN[i + 1] = prefN[i] + (s[i] == 'N');
        }

        for (int i = n - 1; i >= 0; i--) 
        {
            sufP[i] = sufP[i + 1] + (s[i] == 'P');
        }

        int res = -1;

        for (int i = 0; i <= n; i++) 
        {
            if (prefO[i] > 0 && prefS[i] > 0 && prefN[i] > 0 && sufP[i] > 0) 
            {
                res = max(res, prefO[i] + prefS[i] + prefN[i] + sufP[i]);
            }
        }

        return res;
    }
}
```
