#include <bits/stdc++.h>
#include "glolib.h"
using namespace std;
constexpr int maxN = 2e5+7;

int n,rozmiar[maxN],p[maxN];
pair<int,int>ile[maxN]; /// pomarancza, grejfrut
vector<int>v[maxN];

/*
bool comp(pair<int,int>a, pair<int,int>b)
{
	return a.second < b.second;
}

void dfs(int x, int par)
{
	p[x] = par;
	if(v[x].empty()){
		rozmiar[x] = 1;
		return;
	}
	for(int i=0;i<v[x].size();i++){
		dfs(v[x][i].first, x);
		v[x][i].second = rozmiar[v[x][i].first];
	}
	sort(v[x].begin(), v[x].end(), comp);
	for(int i=0;i<v[x].size();i++){
		rozmiar[x] += rozmiar[]
	}
}
*/

void DFS(int x, int par)
{
	p[x] = par;
	if(v[x].empty()){
		rozmiar[x] = 1;
		return;
	}
	for(int a:v[x]){
		DFS(a,x);
		rozmiar[x] += rozmiar[a];
	}
}

int dfs(int x)
{
	for(int a:v[x])
		if(ile[a].first == ile[a].second)
			return dfs(a);
	for(int a:v[x])
		if(ile[a].first + ile[a].second < rozmiar[a])
			return dfs(a);
	return x;
}

void add(int x, bool pierwszy)
{
	while(x){
		if(!pierwszy)
			ile[x].first++;
		else
			ile[x].second++;
		x = p[x];
	}
}

int main()
{
n = daj_n();
//cin>>n;
for(int i=2;i<=n;i++){
	v[daj_przelozonego(i)].push_back(i);
	/*
	int a;
	cin>>a;
	v[a].push_back(i);
	*/
}
DFS(1,0);
int kopia = n;
while(kopia > 0){
	int pom = dfs(1);
	add(pom,0);
	kopia--;
	pom = ruch(pom);
	if(!kopia)
		break;
	add(pom,1);
	kopia--;
}

}