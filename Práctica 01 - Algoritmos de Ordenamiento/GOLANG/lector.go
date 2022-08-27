package main
import "fmt"
import "time"
import "strconv"
import "os"
import "./Algoritmos"

func main() {
   var NUM_PRUEBAS int
   fmt.Scan(&NUM_PRUEBAS)
   var numpuntos int
   numpuntos=15
   var DIM_ARREGLO int
   var aux int
   var tiempo string
   f, err := os.Create("CountingGo.txt")
   //f, err := os.Create("HeapGo.txt")
   //f, err := os.Create("InsertionGo.txt")
   //f, err := os.Create("QuickGo.txt")

   if err != nil {
       fmt.Println(err)
       return
   }
   f.WriteString(strconv.Itoa(NUM_PRUEBAS)+"\n")
   for ii := 0; ii < numpuntos; ii++ {
      fmt.Scan(&DIM_ARREGLO)
      tiempo=""+strconv.Itoa(DIM_ARREGLO)
      for i:=0;i<NUM_PRUEBAS;i++{
         var array []int
         for j:=0;j<DIM_ARREGLO;j++{
            fmt.Scan(&aux)
            array=append(array,aux)    
         }
         start := time.Now()
         array=Algoritmos.CountingSort(array)
         //array=Algoritmos.HeapSort(array)
         //array=Algoritmos.InsertionSort(array)
         //array=Algoritmos.QuickSort(array,0,len(array)-1)
         elapsed := time.Since(start)
         tiempo=tiempo+" "+strconv.Itoa(int(elapsed));
      }
      tiempo=tiempo+"\n"
      //fmt.Println(tiempo)
      f.WriteString(tiempo)
   }

}



