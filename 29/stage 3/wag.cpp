#include <bits/stdc++.h>
#include "waglib.h"
using namespace std;

int ile[10],essa,t[10][10]; /// 1 - wygrana, 0 - nie bylo, -1 przegrana
vector<int>niezrobione;

/*
int lewo,prawo;
void poloz_lewo(vector<int>v, int x)
{
	lewo += v[x];
}
void poloz_prawo(vector<int>v, int x)
{
	prawo += v[x];
}
void odloz(vector<int>v, int x)
{
	if(lewo == v[x])
		lewo = 0;
	else
		prawo = 0;
}

int operacje;
int wazenie()
{
	cout<<lewo<<' '<<prawo<<"   essa\n";
	operacje++;
	if(lewo < prawo)
		return 1;
	else
		return -1;
}
void odpowiedz(vector<int>essa)
{
	for(int i=0;i<7;i++)
		cout<<essa[i]<<' ';
	cout<<"\n";
	cout<<"operacje   "<<operacje<<"\n";
}
*/

void porownaj(int x, int a)
{
	poloz_lewo(x);
	poloz_prawo(a);
	essa = wazenie();
	if(essa == -1){
		t[x][a] = 1;
		t[a][x] = -1;
	}
	else{
		t[x][a] = -1;
		t[a][x] = 1;
	}
	odloz(x);
	odloz(a);
	for(int i=1;i<=7;i++)
		if(t[x][i] && t[x][i] == t[a][x]){
			if(t[x][i] == -1){
				t[a][i] = -1;
				t[i][a] = 1;
			}
			else{
				t[a][i] = 1;
				t[i][a] = -1;
			}
		}
	for(int i=1;i<=7;i++)
		if(t[a][i] && t[a][i] == t[x][a]){
			if(t[a][i] == -1){
				t[x][i] = -1;
				t[i][x] = 1;
			}
			else{
				t[x][i] = 1;
				t[i][x] = -1;
			}
		}
}
void dodaj()
{
	for(int i=1;i<=7;i++){
		bool ok = false;
		for(int j=1;j<=7;j++){
			if(i != j && !t[i][j]){
				ok = true;
				break;
			}
		}
		if(ok)
			niezrobione.push_back(i);
	}
}

void clean()
{
	for(int i=1;i<=7;i++)
		for(int j=1;j<=7;j++)
			t[i][j] = 0;
}

int main()
{
srand(time(NULL));
int T = liczba_testow();
//vector<int>v(10);
//int T;
//cin>>T;
//int T = 1;
while(T--){
	clean();
	vector<int>ans(7);
	dodaj();
	/*
	for(int i=1;i<=7;i++)
		cin>>v[i];
	for(int i=1;i<=7;i++)
		cout<<v[i]<<' ';
	cout<<"\n";
	*/
	while(!niezrobione.empty()){
		random_shuffle(niezrobione.begin(), niezrobione.end());
		int x = niezrobione.back();
		niezrobione.pop_back();
		int a = rand()%7+1;
		while(true){
			a = rand()%7+1;
			if(a != x && !t[a][x])
				break;
		}
		porownaj(x,a);
		niezrobione.clear();
		dodaj();
	}
	for(int i=1;i<=7;i++){
		ile[i] = 0;
		for(int j=1;j<=7;j++)
			if(t[i][j] == 1)
				ile[i]++;
		ans[i-1] = ile[i]+1;
	}
	for(int i=1;i<=7;i++)
		ans[i-1] = ile[i]+1;
	odpowiedz(ans);
}
}
/*

2
1 4 3 2 7 5 6
1 2 3 4 5 6 7

*/