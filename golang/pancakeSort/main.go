package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

// pega máximo
// flipa começo até máximo
// flipa tudo até current
// diminui current
// :D

var COLUMNS = [...]string{"times", "amount", "compairs", "swaps"}

func flip_array(array *[]int, index int) int {
	temp := 0
	start := 0
	swaps := 0
	for start < index {
		temp = (*array)[start]
		(*array)[start] = (*array)[index]
		(*array)[index] = temp
		start += 1
		index -= 1
		swaps++
	}
	return swaps
}

func sflip_array(array *[]string, index int) int {
	temp := "0"
	start := 0
	swaps := 0
	for start < index {
		temp = (*array)[start]
		(*array)[start] = (*array)[index]
		(*array)[index] = temp
		start += 1
		index -= 1
		swaps++
	}
	return swaps
}

func pancake_sort_par(array *[]int, arrayX *[]string, details *[]int) {
	(*details) = []int{0, 0}
	n := len((*array))
	for i := n - 1; i != -1; i-- {
		max_ := i
		for j := i; j != -1; j-- {
			if (*array)[j] > (*array)[max_] || ((*array)[j] == (*array)[max_] && (*arrayX)[j] > (*arrayX)[max_]) {
				(*details)[0] += 5
				max_ = j
			}
		}
		if max_ != i {
			(*details)[0]++
			(*details)[1] += flip_array(array, max_)
			(*details)[1] += flip_array(array, i)
			(*details)[1] += sflip_array(arrayX, max_)
			(*details)[1] += sflip_array(arrayX, i)
		}
	}
}

func pancake_sort_str(array *[]string, details *[]int) {
	(*details) = []int{0, 0}
	n := len((*array))
	for i := n - 1; i != -1; i-- {
		max_ := i
		for j := i; j != -1; j-- {
			if (*array)[j] > (*array)[max_] {
				(*details)[0]++
				max_ = j
			}
		}
		if max_ != i {
			(*details)[0]++
			(*details)[1] += sflip_array(array, max_)
			(*details)[1] += sflip_array(array, i)
		}
	}
}

func pancake_sort(array *[]int, details *[]int) {
	(*details) = []int{0, 0}
	n := len((*array))
	for i := n - 1; i != -1; i-- {
		max_ := i
		for j := i; j != -1; j-- {
			if (*array)[j] > (*array)[max_] {
				(*details)[0]++
				max_ = j
			}
		}
		if max_ != i {
			(*details)[0]++
			(*details)[1] += flip_array(array, max_)
			(*details)[1] += flip_array(array, i)
		}
	}
}

func to_csv(file_path string, data [][]string) {
	csv_file, _ := os.Create(file_path)
	fmt.Fprintf(csv_file, "%s,%s,%s,%s\n", COLUMNS[0], COLUMNS[1], COLUMNS[2], COLUMNS[3])
	for i := 0; i < len(data); i++ {
		for j := 0; j < len(data[0])-1; j++ {
			fmt.Fprintf(csv_file, "%s,", data[i][j])
		}
		fmt.Fprintf(csv_file, "%s\n", data[i][len(data[0])-1])
	}
	csv_file.Close()
}

func main() {
	// Numbers
	data := [][]string{}
	for t := 1000; t <= 100000; t += 1000 {
		numbers_file, _ := os.Open("../../data/numeros 1.txt")
		numbers_array := []int{}
		for i := 0; i < t; i++ {
			var number int
			fmt.Fscanf(numbers_file, "%d\n", &number)
			numbers_array = append(numbers_array, number)

		}
		details := []int{0, 0}
		start := time.Now()
		pancake_sort(&numbers_array, &details)
		end := time.Since(start).Milliseconds()
		fmt.Println(numbers_array)
		os.Exit(1)
		line := []string{fmt.Sprint(end), fmt.Sprint(t), fmt.Sprint(details[0]), fmt.Sprint(details[1])}
		data = append(data, line)
		numbers_file.Close()
		fmt.Println(line)
	}
	to_csv("pancakesort-numbers.csv", data)
	// Names
	data = [][]string{}
	for t := 1000; t <= 100000; t += 1000 {
		names_file, _ := os.Open("../../data/nomes 1.txt")
		names_array := []string{}
		for i := 0; i < t; i++ {
			var name string
			fmt.Fscanf(names_file, "%s\n", &name)
			names_array = append(names_array, name)

		}
		details := []int{0, 0}
		start := time.Now()
		pancake_sort_str(&names_array, &details)
		end := time.Since(start).Milliseconds()
		line := []string{fmt.Sprint(end), fmt.Sprint(t), fmt.Sprint(details[0]), fmt.Sprint(details[1])}
		data = append(data, line)
		names_file.Close()
		fmt.Println(line)
	}
	to_csv("pancakesort-names.csv", data)
	// Persons
	data = [][]string{}
	for t := 1000; t <= 100000; t += 1000 {
		persons_file, _ := os.Open("../../data/pessoa 1.txt")
		scanner := bufio.NewScanner(persons_file)
		ids_array := []int{}
		persons_array := []string{}
		for i := 0; i < t; i++ {
			scanner.Scan()
			line := scanner.Text()
			parts := strings.Split(line, "\t")
			id, _ := strconv.Atoi(parts[0])
			name := strings.Join(parts[1:], " ")
			ids_array = append(ids_array, id)
			persons_array = append(persons_array, name)
		}
		details := []int{0, 0}
		start := time.Now()
		pancake_sort_par(&ids_array, &persons_array, &details)
		end := time.Since(start).Milliseconds()
		line := []string{fmt.Sprint(end), fmt.Sprint(t), fmt.Sprint(details[0]), fmt.Sprint(details[1])}
		data = append(data, line)
		persons_file.Close()
		fmt.Println(line)
	}
	to_csv("pancakesort-persons.csv", data)
}
