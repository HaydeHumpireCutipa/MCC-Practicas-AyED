#include <iostream>
#include <fstream>
#include <chrono>

int partition(int*, int , int );
void Quicksort(int* , int , int );
void print(int* ,int );
void generateTimes();

using namespace std;
int main() {
  generateTimes();
}

void Quicksort(int* arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    Quicksort(arr, low, pi - 1);
    Quicksort(arr, pi + 1, high);
  }
}

int partition(int* arr, int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);  
  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  int temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;
  return i + 1;
}

void generateTimes(){
  ifstream inputFile("PuntosReal.txt");
  ofstream outputFile("timesQuickSortC++.txt");
  int cases=15, iterations, sizeArray;
  inputFile>>iterations;  
  //Number o cases
  for(int i=0; i<cases;i++){
    inputFile>>sizeArray;
    outputFile<<sizeArray;
    int array[sizeArray];
    for(int j=0; j<iterations;j++){    
      for(int k=0;k<sizeArray;k++){
        inputFile>>array[k];
      }
      auto start = chrono::system_clock::now();
      Quicksort(array,0,sizeArray);
      auto end = chrono::system_clock::now();
		  chrono::duration<long,std::nano> duration = end-start;
      long time = duration.count();        
      outputFile<<" "<<time;
    }
    outputFile<<endl;    
  }
  inputFile.close();
  outputFile.close();  
}

void print(int* array,int size){
	for(int i=0;i<size;i++){
		cout<<array[i]<<" ";
	}
	cout<<endl;
}


