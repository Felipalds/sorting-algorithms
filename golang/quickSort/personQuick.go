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

	var personArray []Person

	personReader := bufio.NewReader(in)
	personWriter := bufio.NewWriter(out)

	defer personWriter.Flush()
	fmt.Fprintf(personWriter, "amount,time,compairs,swaps\n")

	i := 0
	for i < 1000 { //Here starts the count till 100k
		persons_file, _ := os.Open("../../data/pessoa 1.txt")
		scanner := bufio.NewScanner(persons_file)
		ids_array := []int{}
		personsArray := []string{}
		for i := 0; i < i; i++ {
			scanner.Scan()
			line := scanner.Text()
			parts := strings.Split(line, "\t")
			id, _ := strconv.Atoi(parts[0])
			name := strings.Join(parts[1:], " ")
			ids_array = append(ids_array, id)
			personsArray = append(personsArray, name)
		}

		start := time.Now()
		quickSort(&personArray, 0, len(personArray))

		// Writing in file
		end := time.Now()
		elapsed := end.Sub(start)
		fmt.Fprintf(personWriter, "%d,%d,%d,%d\n", len(personArray), elapsed, comparsionTotal, swapsTotal)
		comparsionTotal = 0
		swapsTotal = 0
		personReader.Reset(in)
		i += 1000
	}
}

func quickSort(personArray *[]Person, low int, high int) {
	var i, j int
	var pivo, aux Person
	i = low
	j = high - 1
	pivo = (*personArray)[(i+j)/2]

	for i <= j {
		comparsionTotal++
		for (*personArray)[i].id < pivo.id && i < high {
			comparsionTotal += 2
			i++
		}

		for (*personArray)[j].id > pivo.id && j > low {
			comparsionTotal += 2
			j--
		}

		if i <= j {
			comparsionTotal++
			aux = (*personArray)[i]
			(*personArray)[i] = (*personArray)[j]
			(*personArray)[j] = aux
			swapsTotal++
			i++
			j--
		}
	}

	if j > low {
		quickSort(personArray, low, j+1)
	}
	if i < high {
		quickSort(personArray, i, high)
	}
}
