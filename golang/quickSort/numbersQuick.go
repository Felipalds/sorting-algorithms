package main

import (
	"bufio"
	"fmt"
	"os"
	"time"
)

var comparsionTotal int
var swapsTotal int

func main() {
   

  //Números
  in, inerror := os.Open("../../data/numeros 1.txt")
  if inerror != nil {
      fmt.Println("Erro ao abrir o arquivo!")
      panic(0);
  }


  numberReader := bufio.NewReader(in)

  i := 0
  var numberArray []int

  start := time.Now()

  for i < 100000 {
    j := 0
    var num int
    for j <= 999 {
      fmt.Fscanf(numberReader, "%d\n", &num)
      numberArray= append(numberArray, num)
      j++
    }
    fmt.Println(len(numberArray))
    quickSort(&numberArray, 0, len(numberArray))
    numberReader.Reset(in)
    i+=1000
  }
  elapsed := time.Since(start)
  fmt.Printf("\n\n\n")
  fmt.Printf("FUNCTION TOOK %s\n", elapsed)
  fmt.Println("Total comparsions: ", comparsionTotal)
  fmt.Println("Total swaps: ", swapsTotal)
}

func quickSort(numberArray *[] int, low int, high int){
    var i, j, pivo, aux int
    i = low
    j = high - 1
    pivo = (*numberArray)[(i+j)/2]

    for i <= j {
        comparsionTotal++
        for (*numberArray)[i] < pivo && i < high {
            comparsionTotal += 2
            i++
        }

        for (*numberArray)[j] > pivo && j > low {
            comparsionTotal += 2
            j--
        }

        if (i <= j) {
            comparsionTotal++
            aux = (*numberArray)[i]
            (*numberArray)[i] = (*numberArray)[j]
            (*numberArray)[j] = aux
            swapsTotal++
            i++
            j--
        }
    }


    if(j > low){
        quickSort(numberArray, low, j+1)
    }
    if(i < high){
        quickSort(numberArray, i, high)
    }
}

