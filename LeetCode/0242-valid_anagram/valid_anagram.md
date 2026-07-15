# 242. Valid Anagram

> [Hash Table], [String], [Sorting]

Run:

```
go run valid_anagram.go
```

# 1. My Approach (Hash Map)

Optimal solution

Algorithm:
1. Check if len aren't the same, then `false`
2. Simply, record the freq
3. If same, then `true`

Time complexity: $O(n + m)$

Space complexity: $O(1)$, 26 char

```go
func isAnagram(s string, t string) bool {
	
	if len(s) != len(t) {
		return false
	}
	
	smap := make(map[rune]int)
	tmap := make(map[rune]int)

	for _, char := range s {
		smap[char]++
	} 

	for _, char := range t {
		tmap[char]++
	}

	for keyS, valS := range smap {
		if tmap[keyS] != valS {
            return false
        }
	}

	return true
}
```

## 2. Sorting

Naive, If sorted same then same.

Algorithm:
1. As usual, if len aren't the same then `false`
2. Sort both strings
3. If same, return `true`. Otherwise return `false`

Time complexity: $O(n \log n + m \log m)$

Space complexity: $O(1)$ or $O(n + m)$, depends on the sorting algorithm

```go
import "slices"

func isAnagram(s string, t string) bool {
	
	if len(s) != len(t) {
		return false
	}

    runeS, runeT := []rune(s), []rune(t)

    slices.Sort(runeS)
    slices.Sort(runeT)

    stringS := string(runeS)
    stringT := string(runeT)

    return stringS == stringT
}
```

## 3. Hash Table

Clever way, increment for $s$ and decrement for $t$.
If all not 0, then not same.

Algorithm:
1. As usual, if len aren't the same then `false`
2. Freq array `count`, size `26`, all `0`
3. Iterate both strings
    - Increment char index value for each findings in `s`
    - Decrement char index value for each findings in `t`
4. Final loop to check all `0` then `true`, else `false`

Time complexity: $O(n + m)$

Space complexity: $O(1)$, 26 char

```go
func isAnagram(s string, t string) bool {
	
	if len(s) != len(t) {
		return false
	}

    count := [26]int{}

    for i := 0; i < len(s); i++ {
        count[s[i] - 'a']++
        count[t[i] - 'a']--
    }

    for _, val := range count {
        if val != 0 {
            return false
        }
    }

    return true
}
```