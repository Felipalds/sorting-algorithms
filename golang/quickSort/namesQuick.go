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
   

  //Nomes
  in, inerror := os.Open("../../data/nomes 1.txt")
  if inerror != nil {
      fmt.Println("Erro ao abrir o arquivo!")
      panic(0);
  }


  numberReader := bufio.NewReader(in)

  i := 0
  var namesArray []string

  start := time.Now()

  for i < 100000 {
    j := 0
    var name string
    for j <= 999 {
      fmt.Fscanf(numberReader, "%s\n", name)
      namesArray= append(namesArray, name)
      j++
    }
    fmt.Println(len(namesArray))
    quickSort(&namesArray, 0, len(namesArray))
    numberReader.Reset(in)
    i+=1000
  }
  elapsed := time.Since(start)
  fmt.Printf("\n\n\n")
  fmt.Printf("FUNCTION TOOK %s\n", elapsed)
  fmt.Println("Total comparsions: ", comparsionTotal)
  fmt.Println("Total swaps: ", swapsTotal)
}

func quickSort(namesArray *[] string, low int, high int){
    var i, j, pivo, aux int
    i = low
    j = high - 1
    pivo = (*namesArray)[(i+j)/2]

    for i <= j {
        comparsionTotal++
        for (*namesArray)[i] < pivo && i < high {
            comparsionTotal += 2
            i++
        }

        for (*namesArray)[j] > pivo && j > low {
            comparsionTotal += 2
            j--
        }

        if (i <= j) {
            comparsionTotal++
            aux = (*namesArray)[i]
            (*namesArray)[i] = (*namesArray)[j]
            (*namesArray)[j] = aux
            swapsTotal++
            i++
            j--
        }
    }


    if(j > low){
        quickSort(namesArray, low, j+1)
    }
    if(i < high){
        quickSort(namesArray, i, high)
    }
}

