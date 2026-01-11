package internal

import (
	"regexp"
	"strconv"
)

var re = regexp.MustCompile(`(\d+)x[^,\n]*`)

// No validation since the string is guaranteed to be formatted correctly
func GetMaxToy(toys string) string {
	m := re.FindAllStringSubmatch(toys, -1)
	var maxToys int64
	maxToy := ""
	for _, match := range m {
		if len(match) != 2 {
			return ""
		}
		// Get the quantity
		i, err := strconv.ParseInt(match[1], 10, 32)
		if err != nil {
			return ""
		}
		if i > maxToys {
			maxToy = match[0]
			maxToys = i
		}
	}
	return maxToy
}
