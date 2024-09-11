#include <bits/stdc++.h>
#include "zerlib.h"
using namespace std;
constexpr int maxN = 2e5+7;

int n,war,ile[maxN];
int wiadomo = -1;
vector<int>ans;

/*
vector<int>v;
int suma(int a, int b)
{
	return v[a] + v[b];
}

void odpowiedz(vector<int>essa)
{
	for(int a:essa)
		cout<<a<<' ';
	cout<<"\n";
}
*/

int main()
{
	n = daj_n();
	/*
	cin>>n;
	for(int i=0;i<n;i++){
		int a;
		cin>>a;
		v.push_back(a);
	}
	odpowiedz(v);
	cout<<" to byl wejsciowy\n";
	*/

	ans.resize(n);
	for(int i=1;i<n;i++){
		war = suma(0,i);
		if(war == 2)
			wiadomo = 1;
		else if(!war)
			wiadomo = 0;
		ile[i] = war;
	}
	if(wiadomo == -1){
		war = suma(1,2);
		int pierwsza = 1, inne = 0;
		if(war == 2)
			swap(pierwsza, inne);
		ans[0] = pierwsza;
		for(int i=1;i<n;i++)
			ans[i] = inne;
	}
	else{
		ans[0] = wiadomo;
		for(int i=1;i<n;i++){
			ans[i] = ile[i] - wiadomo;
		}
	}
	odpowiedz(ans);
}