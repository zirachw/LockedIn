package main

import (
	"fmt"
	"slices"
)

func groupAnagrams(strs []string) [][]string {
	res := make(map[string][]string)

	for _, s := range strs {
		b := []byte(s)
		slices.Sort(b)
		res[string(b)] = append(res[string(b)], s)
	}

	var result [][]string
	for _, group := range res {
		result = append(result, group)
	}
	return result
}


func main() {
	var n int
	fmt.Scan(&n)

	strs := make([]string, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&strs[i])
	}

	fmt.Println(groupAnagrams(strs))
}