package main
import "fmt"
import "os"
import "log"
import "bufio"
import "strconv"
import "time"

func quickSort(arr []int, low, high int) []int {
	if low < high {
		var p int
		arr, p = partition(arr, low, high)
		arr = quickSort(arr, low, p-1)
		arr = quickSort(arr, p+1, high)
	}
	return arr
}

func partition(arr []int, low, high int) ([]int, int) {
	pivot := arr[high]
	i := low
	for j := low; j < high; j++ {
		if arr[j] < pivot {
			arr[i], arr[j] = arr[j], arr[i]
			i++
		}
	}
	arr[i], arr[high] = arr[high], arr[i]
	return arr, i
}

func main() {
  
   file, err := os.Open("PuntosReal.txt")
   if err != nil {
        log.Fatalf("Error when opening file: %s", err)
    }
   fileScanner := bufio.NewScanner(file)
   fileScanner.Split(bufio.ScanWords)
   //var cases int = 15
   var iterations int = 5 
   var sizeArray int
   var data int
   var tiempo string
   for fileScanner.Scan() {
        sizeArray, err = strconv.Atoi(fileScanner.Text())
        if err != nil {}
        fmt.Print(sizeArray)
        for i := 0; i < iterations; i++ {
          var array []int
          for j := 0; j < sizeArray; j++ {
            fileScanner.Scan()
            data, err = strconv.Atoi(fileScanner.Text())
            if err != nil {}
            array = append(array, data)
          }
          start := time.Now()
          array=quickSort(array,0,len(array)-1)
          elapsed := time.Since(start)
          tiempo = strconv.Itoa(int(elapsed));
          fmt.Print(" " + tiempo)          
        }
        
        fmt.Println()   
    }
    file.Close()
}