package algorithms

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func CyclicShift() {
	reader := bufio.NewReader(os.Stdin)

	testCasesInput, _ := reader.ReadString('\r')
	testCases, _ := strconv.Atoi(strings.TrimSpace(testCasesInput))

	for i := 0; i < testCases; i++ {
		nInput, _ := reader.ReadString(' ')
		n, _ := strconv.Atoi(strings.TrimSpace(nInput))

		kInput, _ := reader.ReadString('\n')
		k, _ := strconv.Atoi(strings.TrimSpace(kInput))

		a, _ := reader.ReadString('\n')

		rotations := computeRotations(n, k, a)
		fmt.Println(rotations)
	}
}

func computeRotations(n int, k int, a string) int {
	timesEqual := 0
	rotations := -1
	maximum := getMaximum(a, n)
	for timesEqual < k {
		current, _ := strconv.ParseUint(strings.TrimSpace(a), 2, 64)
		if current == maximum {
			timesEqual++
		}
		a = rotation(a)
		rotations++
	}
	return rotations
}

func getMaximum(a string, num int) uint64 {
	maximum := uint64(0)
	for i := 0; i < num; i++ {
		current, _ := strconv.ParseUint(a, 2, 64)
		if current > maximum {
			maximum = current
		}
		a = rotation(a)
	}
	return maximum
}

func rotation(a string) string {
	b := []byte(a)
	result := append(b[1:], b[0])
	return string(result)
}
