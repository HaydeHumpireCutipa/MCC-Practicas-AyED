#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <chrono>
#include <time.h>
#include <bits/stdc++.h>
#include <fstream>
#include <thread>
#include <string>

using namespace std;

#include "CountingSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "HeapSort.h"

void imprimir(int* arreglo,int& longitud){
	for(int i=0;i<longitud;i++){
		cout<<arreglo[i]<<" ";
	}
	cout<<endl;
}

int main(){

	int veces;
	cin>>veces;
	int puntos;
	string tiempo;
	ofstream f("CountingC.txt");
	//ofstream f("HeapC.txt");	
	//ofstream f("InsertionC.txt");
	//ofstream f("QuickC.txt");
	ofstream f("SelectionC.txt");
	f<<veces<<endl;
	int numpuntos=15;
	for(int ii=0;ii<numpuntos;ii++){
	  cin>>puntos;
		tiempo=to_string( puntos );
		for(int i=0;i<veces;i++){
			int arreglo[puntos];			
			for(int j=0;j<puntos;j++){
				cin>>arreglo[j];
			}
			auto inicioSort = chrono::high_resolution_clock::now();

			//imprimir(arreglo,puntos);
			countSort(arreglo,puntos);
			//heapSort(arreglo,puntos);
			//InsertionSort(arreglo,puntos);
			//QuickSort(arreglo,0,puntos);

			auto finSort = chrono::high_resolution_clock::now();
			long long tiemposort = chrono::duration_cast<chrono::nanoseconds> (finSort-inicioSort).count();
			//cout<<tiemposort<<endl;
			tiempo=tiempo+ " "+to_string( tiemposort );
		}

		f<<tiempo<<endl;
	}

  return 0;

}
