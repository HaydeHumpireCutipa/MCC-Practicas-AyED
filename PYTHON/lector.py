from time import time
import Algoritmos

#w = open("BubblePy.txt","w")
#w = open("CountingPy.txt","w")
#w = open("HeapPy.txt","w")
#w = open("InsertionPy.txt","w")
#w = open("MergePy.txt","w")
#w = open("QuickPy.txt","w")
w = open("SelectionPy.txt","w")

NUM_PRUEBAS=int(input())
w.write(str(NUM_PRUEBAS)+"\n")

numpuntos=15

for ii in range(numpuntos):
	DIM_ARREGLO=int(input())
	tiempo=str(DIM_ARREGLO)
	for i in range(NUM_PRUEBAS):
		aux=input()
		aux=aux.split()
		arreglo=[]
		for j in arreglo:
			arreglo·append(int(j))

		start_time = time()
		#Algoritmos.BubbleSort(arreglo)
		#Algoritmos.countSort(arreglo)
		#Algoritmos.HeapSort(arreglo)
		#Algoritmos.InsertionSort(arreglo)
		#Algoritmos.MergeSort(arreglo)
		#Algoritmos.QuickSort(arreglo)
		Algoritmos.SelectionSort(arreglo)

		elapsed_time = time()-start_time
		tiempo=tiempo+" "+str( elapsed_time*1000000000 );
	w.write(tiempo+"\n")

w.close()
