package main

import (
	"fmt"
)

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


func main() {
	var n int
	fmt.Scan(&n)

	strs := make([]string, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&strs[i])
	}

	fmt.Println(groupAnagrams(strs))
}