#include <iostream>
#include <vector>
#include "perlib.h"
using namespace std;
constexpr int maxN = 5e2+7;

int N,lnk[maxN],sz[maxN];
bool done[maxN];
vector<int>ans,podstawowa;

/*
vector<int>per = {0,1,2,4,5,3};

int daj_n(){
	return per.size();
}
bool zapytaj(vector<int>essa, int a, int b){
	vector<int>nowa(N,0);
	for(int i=0;i<N;i++)
		nowa[i] = per[essa[i]];
	for(int i=0;i<=N;i++){
		if(a == b)
			return true;
		a = nowa[a];
	}
	return false;
}
void odpowiedz(vector<int>v){
	for(int x : v)
		cout<<x<<' ';
	cout<<"\n";
}
*/


int Find(int x){
	if(x == lnk[x])
		return x;
	lnk[x] = Find(lnk[x]);
	return lnk[x];
}

bool same(int a, int b){
	return Find(a) == Find(b);
}

void unite(int a, int b){
	a = Find(a), b = Find(b);
	if(a == b)
		return;
	if(sz[a] < sz[b])
		swap(a,b);
	sz[a] += sz[b];
	lnk[b] = a;
}

void solve(vector<int>v){
	/*
	cout<<"to jest rozwiazywane\n";
	for(int x:v)
		cout<<x<<' ';
	cout<<"\n";
	*/
	if(v.size() == 1){
		ans[v[0]] = v[0];
		return;
	}
	if(v.size() == 2){
		ans[v[0]] = v[1];
		ans[v[1]] = v[0];
		return;
	}
	for(int i=0;i<v.size();i++){ // sprawdzam czy i jest na miejscu j
		for(int j=0;j<v.size();j++){
			if(i != j){
				swap(podstawowa[v[j]], podstawowa[v[i]]);
				bool ok = true;
				for(int k=0;k<v.size();k++){
					if(k != i && k != j){
						if(zapytaj(podstawowa, v[i], v[k])){
							ok = false;
							break;
						}
					}
				}
				swap(podstawowa[v[j]], podstawowa[v[i]]);
				if(ok){
					ans[v[i]] = v[j];
					break;
				}
			}
		}
	}
}


int main(){
	N = daj_n();
	int Z = daj_z();
	int P = daj_podzadanie();
	/*
	cin>>N;
	per.assign(N,0);
	for(int i=0;i<N;i++)
		cin>>per[i];
	*/
	ans.assign(N,0);
	for(int i=0;i<N;i++){
		lnk[i] = i;
		sz[i] = 1;
		podstawowa.push_back(i);
	}
	for(int i=0;i<N;i++){
		for(int j=i+1;j<N;j++){
			if(!same(i,j)){
				if(zapytaj(podstawowa, i, j)){
					unite(i,j);
				}
			}
		}
	}
	for(int i=0;i<N;i++){
		if(done[Find(i)])
			continue;
		done[Find(i)] = true;
		vector<int>przypisz;
		for(int j=0;j<N;j++)
			if(same(i,j))
				przypisz.push_back(j);
		solve(przypisz);
	}
	odpowiedz(ans);
}
/*



*/