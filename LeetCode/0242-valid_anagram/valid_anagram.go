package main

import "fmt"

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

	for key, valS := range smap {
		valT, exists := tmap[key]
		if !exists || valS != valT {
			return false
		}
	}

	return true
}

func main() {
	var s, t string
	fmt.Scan(&s)
	fmt.Scan(&t)
	
	fmt.Println(isAnagram(s,t))
}