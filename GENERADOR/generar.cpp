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

using namespace std;

int main(){

	//parametros del numero de puntos
	int NUM_ELEMENTOS=5;
	//int valores[]={4,5};
	int valores[]={100,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000,30000,40000,50000};
	int nro_puntos=sizeof(valores)/sizeof(valores[0]);

	srand(time(NULL));
	ofstream f("Puntos.txt");
	string auxiliar;
	int maximo;
	f<<NUM_ELEMENTOS<<endl;
	for(int i=0;i<nro_puntos;i++){
		f<<valores[i]<<endl;
		maximo=valores[i];
		for(int j=0;j<NUM_ELEMENTOS;j++){
			//crear vector
			auxiliar="";
			for(int k=0;k<valores[i];k++){
				auxiliar=auxiliar+ " " + to_string(1 + rand() % (maximo - 1));
			}
			f<<auxiliar<<endl;
		}
	}	
	f.close();

  return 0;

}
