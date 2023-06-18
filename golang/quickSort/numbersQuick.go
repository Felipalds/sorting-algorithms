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
  out, outError := os.Create("./numbersOut.csv")

  if inerror != nil {
      fmt.Println("Erro ao abrir o arquivo!")
      panic(1);
  }

  if outError != nil {
      fmt.Println("Erro ao criar o arquivo!")
      panic(1)
  }

  defer out.Close()

  var numberArray []int

  numberReader := bufio.NewReader(in)
  numberWriter := bufio.NewWriter(out)

  defer numberWriter.Flush()
  fmt.Fprintf(numberWriter, "amount,time,compairs,swaps\n")


  i := 0
  for i < 100000 { //Here starts the count till 100k
    j := 0
    var num int
    for j <= 999 {// Firts we will get 1000, then 0-2000...
      fmt.Fscanf(numberReader, "%d\n", &num)
      numberArray = append(numberArray, num)
      j++
    }
    
    start := time.Now()
    quickSort(&numberArray, 0, len(numberArray))

    // Writing in file
    end := time.Now()
    elapsed := end.Sub(start)
    fmt.Fprintf(numberWriter, "%d,%d,%d,%d\n", len(numberArray), elapsed, comparsionTotal, swapsTotal)
    comparsionTotal = 0
    swapsTotal = 0
    numberReader.Reset(in)
    i+=1000
  }
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


