package Algoritmos
//COUNTING SORT
func FindMax(arr []int) int {
	var temp int

	temp = arr[0]

	for _, e := range arr {
		if temp < e {
			temp = e
		}
	}

	return temp
}

func MakeRange(min, max int) []int {
	a := make([]int, max-min+1)
	for i := range a {
		a[i] = 0
	}
	return a
}

func CountingSort(arr []int) []int {
	counter := MakeRange(0, FindMax(arr))
	// count
	for _, e := range arr {
		counter[e] += 1
	}
	for i := 1; i < len(counter); i++ {
		counter[i] += counter[i-1]
	}
	res := make([]int, len(arr))

	for i := 0 ; i < len(arr) ; i++ {
		e := arr[i] // elem to add
		t := counter[e] - 1 // target pos

		res[t] = e
		counter[e] = counter[e] - 1
	}

	return res
}