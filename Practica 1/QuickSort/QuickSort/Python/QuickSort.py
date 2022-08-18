from time import time
def partition(arr, low, high):
    i = (low-1)         
    pivot = arr[high]     
    for j in range(low, high):
        if arr[j] <= pivot:
            i = i+1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return (i+1)


def QuickSort(arr):
    def quickSort(arr, low, high):
        if len(arr) == 1:
            return arr
        if low < high:
            # at right place
            pi = partition(arr, low, high)
            quickSort(arr, low, pi-1)
            quickSort(arr, pi+1, high)
    quickSort(arr, 0, len(arr)-1)
    return arr

#Read data
numbers =[]
with open('D:/Cursos/Maestría CS/Algoritmos y Estructuras de Datos/Primera Práctica/QuickSort/Python/PuntosReal.txt','r') as file:
    for line in file:           
        for num in line.split():         
            numbers.append(int(num))

outputFile = open('D:/Cursos/Maestría CS/Algoritmos y Estructuras de Datos/Primera Práctica/QuickSort/Python/timesQuickSortPython.txt','w')

cases = 15
cont=0
iterations = numbers[cont]
cont=cont+1
for i in range (cases):    
    sizeArray=numbers[cont]
    cont=cont+1
    print(sizeArray, end=" ")
    outputFile.write(str(sizeArray)+" ")
    array = []
    for j in range (iterations):
        for k in range (sizeArray):
            array.append(numbers[cont])
            cont=cont+1            
        start = time()
        QuickSort(array)
        end = time()
        print(int((end-start)*1000000000), end=" ")
        outputFile.write(str(int((end-start)*1000000000))+" ")
    print("\n")
    outputFile.write("\n")

outputFile.close()