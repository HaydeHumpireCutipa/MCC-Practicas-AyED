package Algoritmos
//INSERTION SORT
func InsertionSort(arr []int) []int {
    len := len(arr)
    for i := 1; i < len; i++ {
        for j := 0; j < i; j++ {
            if arr[j] > arr[i] {
                arr[j], arr[i] = arr[i], arr[j]
            }
        }
    }
		return arr;
}