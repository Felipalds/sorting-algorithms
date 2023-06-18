package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

var comparsionTotal int
var swapsTotal int

type Person struct {
	name string
	id   int
}

func main() {

	in, inerror := os.Open("../../data/pessoa 1.txt")
	out, outError := os.Create("./personsOut.csv")

	if inerror != nil {
		fmt.Println("Erro ao abrir o arquivo!")
		panic(1)
	}

	if outError != nil {
		fmt.Println("Erro ao criar o arquivo!")
		panic(1)
	}

	defer out.Close()

	personReader := bufio.NewReader(in)
	personWriter := bufio.NewWriter(out)

	defer personWriter.Flush()
	fmt.Fprintf(personWriter, "amount,time,compairs,swaps\n")

	for i := 1000; i <= 100000; i += 1000 { //Here starts the count till 100k
		persons_file, _ := os.Open("../../data/pessoa 1.txt")
		scanner := bufio.NewScanner(persons_file)
		ids_array := []int{}
		personsArray := []Person{}
		for j := 0; j < i; j++ {
			scanner.Scan()
			line := scanner.Text()
			parts := strings.Split(line, "\t")
			id, _ := strconv.Atoi(parts[0])
			name := strings.Join(parts[1:], " ")
			ids_array = append(ids_array, id)
			personsArray = append(personsArray, Person{name, id})
		}

		start := time.Now()
		quickSort(&personsArray, 0, len(personsArray))
		end := time.Now()
		elapsed := end.Sub(start).Milliseconds()
		// Writing in file
		fmt.Println(elapsed, " -Tempo")
		fmt.Fprintf(personWriter, "%d,%d,%d,%d\n", i, elapsed, comparsionTotal, swapsTotal)
		comparsionTotal = 0
		swapsTotal = 0
		personReader.Reset(in)
	}
}

func quickSort(personArray *[]Person, low int, high int) {
	var i, j int
	i = low
	j = high - 1
	pivot := (*personArray)[(i+j)/2].id
	pivotX := (*personArray)[(i+j)/2].name
	for i <= j {
		for (*personArray)[i].id < pivot || ((*personArray)[i].id == pivot && (*personArray)[i].name < pivotX) && i < high {
			comparsionTotal += 7
			i++
		}

		for (*personArray)[j].id > pivot || ((*personArray)[j].id == pivot && (*personArray)[j].name > pivotX) && j > low {
			comparsionTotal += 7
			j--
		}

		if i <= j {
			aux := (*personArray)[i]
			(*personArray)[i] = (*personArray)[j]
			(*personArray)[j] = aux
			i++
			j--
			swapsTotal += 2
		}
	}
	if j > low {
		comparsionTotal++
		quickSort(personArray, low, j+1)
	}
	if i < high {
		comparsionTotal++
		quickSort(personArray, i, high)
	}
}
