package main

import "fmt"

func modifyArray(arr *[3]int) {
    (*arr)[0] = 100
    fmt.Println("Inside modifyArray:", *arr)
}

func main() {
    originalArray := [3]int{1, 2, 3}
    fmt.Println("Before modifyArray:", originalArray)
    modifyArray(&originalArray)
    fmt.Println("After modifyArray:", originalArray)
}
