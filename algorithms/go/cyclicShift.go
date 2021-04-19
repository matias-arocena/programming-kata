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

		aInput, _ := reader.ReadString('\n')
		a := strings.TrimSpace(aInput)

		rotations := computeRotations(n, k, a)
		fmt.Println(rotations)
	}
}

func computeRotations(n int, k int, a string) int {
	maximums, numberOfMaximums := getIndexOfMaximums(a, n)
	if k > numberOfMaximums {
		return (k/numberOfMaximums)*n + maximums[(k-1)%numberOfMaximums]
	} else {
		return maximums[k-1]
	}
}

func getIndexOfMaximums(a string, num int) ([]int, int) {
	maximum := uint64(0)
	var maximumIndex []int
	var numberOfMaximums int
	for i := 0; i < num; i++ {
		current, _ := strconv.ParseUint(a, 2, 64)
		if current > maximum {
			maximumIndex = make([]int, 0)
			maximumIndex = append(maximumIndex, i)

			maximum = current

			numberOfMaximums = 1
		} else if current == maximum {
			maximumIndex = append(maximumIndex, i)
			numberOfMaximums++
		}

		a = rotation(a)
	}
	return maximumIndex, numberOfMaximums
}

func rotation(a string) string {
	b := []byte(a)
	result := append(b[1:], b[0])
	return string(result)
}
