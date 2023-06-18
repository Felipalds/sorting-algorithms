package main

// pega máximo
// flipa começo até máximo
// flipa tudo até current
// diminui current
// :D

func array_max(array []int) int {
	max := array[0]
	for i := 1; i < len(array); i++ {
		if array[i] > max {
			max = array[i]
		}
	}
	return max
}

func flip_array(array []int, index int) {
	temp := 0
	start := 0
	for start < index {
		temp = array[start]
		array[start] = array[index]
		array[index] = temp
		start += 1
		index -= 1
	}
}

func pancake_sort(array []int) {

	for current_size := len(array) - 1; current_size > 1; current_size -= 1 {
		max := array_max(array[:current_size])
		if max != current_size-1 {
			flip_array(array, max)
			flip_array(array, current_size-1)
		}
	}
}

func main() {

}
