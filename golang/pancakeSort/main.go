package main

import "fmt"

// pega máximo
// flipa começo até máximo
// flipa tudo até current
// diminui current
// :D

func array_max(array []int) int {
	max := array[0]
	i := 1
	for i = 1; i < len(array); i++ {
		if array[i] > max {
			max = array[i]
		}
	}
	fmt.Println(max)
	return i
}

func flip_array(array *[]int, index int) {
	temp := 0
	start := 0
	for start < index {
		temp = (*array)[start]
		(*array)[start] = (*array)[index]
		(*array)[index] = temp
		start += 1
		index -= 1
	}
	fmt.Println(array)
}

func pancake_sort(array *[]int) {

	n := len((*array))
	for i := n - 1; i != -1; i-- {
		max_ := i
		for j := i; j != -1; j-- {
			if (*array)[j] > (*array)[max_] {
				max_ = j
			}
		}
		if max_ != i {
			flip_array(array, max_)
			flip_array(array, i)
		}
	}
}

func main() {
	myArray := []int{4, 2, 3, 5, 10, 2, 1, 10, 2, 2}
	pancake_sort(&myArray)
	fmt.Println(myArray)
}
