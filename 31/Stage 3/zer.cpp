// Bledne rozwiazanie do zadania "Zera i jedynki"

#include <iostream>
#include <vector>
using namespace std;
#include "zerlib.h"

int n;
vector<int> a;

int main() {
    n = daj_n();
    a.resize(n,2);
   	int essa = suma(0,1);
   	if(essa == 0 || essa == 2){
   		a[0] = essa/2;
   		a[1] = essa/2;
   	}
   	essa = suma(0,2);
   	if(essa == 0 || essa == 2){
   		a[0] = essa/2;
   		a[2] = essa/2;
   	}
   	essa = suma(1,2);
   	if(essa == 0 || essa == 2){
   		a[1] = essa/2;
   		a[2] = essa/2;
   	}

   	if(a[0] == 2){
   		if(a[1] == 1)
   			a[0] = 0;
   		else
   			a[0] = 1;
   	}
   	if(a[1] == 2){
   		if(a[0] == 1)
   			a[1] = 0;
   		else
   			a[1] = 1;
   	}
   	if(a[2] == 2){
   		if(a[1] == 1)
   			a[2] = 0;
   		else
   			a[2] = 1;
   	}
   	for(int i=3;i<n;i++){
   		essa = suma(i-1,i);
   		a[i] = essa - a[i-1];
   	}
    odpowiedz(a);
}
