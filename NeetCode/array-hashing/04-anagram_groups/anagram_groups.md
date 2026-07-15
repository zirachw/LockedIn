# Anagram Groups

> [Array], [Hash Table], [String], [Sorting]

Run:

```
go run anagram_groups.go
```

# 1. My Approach (Hash Table)

Optimal solution

Algorithm:
1. Hash Map, 26 char freq as key, list of strings with that freq as value
2. For each string
    - Init freq array of size `26`
    - Increment char count as go on
    - Use it as key
    - Append each string with same key
3. Reformat into the answer

Time complexity: $O(m * n)$

Space complexity: $O(m)$, if excluding the output else $O(m * n)$

```go
func groupAnagrams(strs []string) [][]string {

    table := make(map[[26]int][]string)

    for _, str := range strs {

        var freq [26]int

        for _, char := range str {

            freq[char - 'a']++
        }

		table[freq] = append(table[freq], str)
    }

	var res [][]string

    for _, group := range table {
		res = append(res, group)
	}
        
	return res
}
```

## 2. Sorting

Naive, If sorted same then same

Algorithm:
1. Hash map, sorted version of a string as key, list of strings as value
2. For each string
    - Sort to form the key
    - Append to the same key
3. Reformat into the answer

Time complexity: $O(m * n \ \log \ n)$

Space complexity: $O(m * n)$

```go
import "slices"

func groupAnagrams(strs []string) [][]string {
	res := make(map[string][]string)

	for _, str := range strs {
		runeStr := []rune(str)
		slices.Sort(runeStr)
		res[string(runeStr)] = append(res[string(runeStr)], s)
	}

	var result [][]string
	for _, group := range res {
		result = append(result, group)
	}
	return result
}
```