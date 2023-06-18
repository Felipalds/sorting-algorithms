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
  in, inerror := os.Open("../../data/nomes 1.txt")
  out, outError := os.Create("./namesOut.csv")

  if inerror != nil {
      fmt.Println("Erro ao abrir o arquivo!")
      panic(1);
  }

  if outError != nil {
      fmt.Println("Erro ao criar o arquivo!")
      panic(1)
  }

  defer out.Close()

  var namesArray []string

  numberReader := bufio.NewReader(in)
  numberWriter := bufio.NewWriter(out)

  defer numberWriter.Flush()
  fmt.Fprintf(numberWriter, "amount,time,compairs,swaps\n")


  i := 0
  for i < 100000 { //Here starts the count till 100k
    j := 0
    var name string
    for j <= 999 {// Firts we will get 1000, then 0-2000...
      fmt.Fscanf(numberReader, "%s", &name)
      namesArray = append(namesArray, name)
      j++
    }
    
    start := time.Now()
    quickSort(&namesArray, 0, len(namesArray))

    // Writing in file
    end := time.Now()
    elapsed := end.Sub(start)
    fmt.Fprintf(numberWriter, "%d,%d,%d,%d\n", len(namesArray), elapsed, comparsionTotal, swapsTotal)
    comparsionTotal = 0
    swapsTotal = 0
    numberReader.Reset(in)
    i+=1000
  }
}

func quickSort(namesArray *[] string, low int, high int){
    var i, j int
    var pivo, aux string
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

