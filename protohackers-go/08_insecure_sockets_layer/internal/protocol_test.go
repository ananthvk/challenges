package internal

import "testing"

func TestGetMaxToy(t *testing.T) {
	tests := []struct {
		name     string
		toys     string
		expected string
	}{
		{
			name:     "single toy",
			toys:     "5x toy car",
			expected: "5x toy car",
		},
		{
			name:     "multiple toys with clear max",
			toys:     "3x doll, 7x blocks, 2x puzzle",
			expected: "7x blocks",
		},
		{
			name:     "toys with same quantity - returns first max found",
			toys:     "5x car, 3x ball, 5x book",
			expected: "5x car",
		},
		{
			name:     "large quantities",
			toys:     "100x marbles, 250x stickers, 75x cards",
			expected: "250x stickers",
		},
		{
			name:     "toys with complex names",
			toys:     "12x remote control helicopter, 8x building blocks set, 15x puzzle game",
			expected: "15x puzzle game",
		},
		{
			name:     "single digit quantities",
			toys:     "1x bear, 9x crayons, 3x books",
			expected: "9x crayons",
		},
		{
			name:     "zero quantity",
			toys:     "0x broken toy, 5x working toy",
			expected: "5x working toy",
		},
		{
			name:     "empty string",
			toys:     "",
			expected: "",
		},
		{
			name:     "no valid toys",
			toys:     "just some text without pattern",
			expected: "",
		},
		{
			name:     "toys with special characters in names",
			toys:     "3x toy-car, 8x doll's house, 2x puzzle&game",
			expected: "8x doll's house",
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			result := GetMaxToy(tt.toys)
			if result != tt.expected {
				t.Errorf("GetMaxToy(%q) = %q, want %q", tt.toys, result, tt.expected)
			}
		})
	}
}
