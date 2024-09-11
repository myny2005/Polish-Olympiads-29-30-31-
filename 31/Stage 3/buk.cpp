#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 20+7, maxZ = 1e6+7, INF = 1e9+7;
constexpr long long INFL = 1e18;

int n,a[maxN],b[maxN],k[maxZ],z,q,pytanko[maxZ];
pair<long long,int> maksi[1025];
pair<long long, int>ans_2[1025];
string zaklad[maxZ],pytanie;

long long solve(int idx){
	long long res = -k[idx];
	for(int i=0;i<n;i++){
		if(pytanie[i] == '0' && zaklad[idx][i] == '0')
			res += a[i];
		else if(pytanie[i] == '1' && zaklad[idx][i] == '1')
			res += b[i];
	}
	return res;
}

int zamiana(string &s){
	int res = 0;
	for(int i=0;i<n;i++)
		if(s[i] == '1')
			res += (1 << i);
	return res;
}

pair<long long,int> solve_2(int x){
	pair<long long,int>res = {-INFL,0};
	for(int mask=0;mask<(1<<n);mask++){
		long long wyniczek = maksi[mask].first;
		for(int i=0;i<n;i++){
			if((mask & (1 << i)) == 0 && (x & (1 << i)) == 0)
				wyniczek += a[i];
			else if((mask & (1 << i)) > 0 && (x & (1 << i)) > 0)
				wyniczek += b[i];
		}
		if(wyniczek > res.first)
			res = {wyniczek, maksi[mask].second};
		else if(wyniczek == res.first)
			res.second += maksi[mask].second;
	}
	return res;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<n;i++)
		cin>>b[i];
	cin>>z;
	for(int i=0;i<z;i++)
		cin>>zaklad[i]>>k[i];
	if(n <= 10){
		for(int i=0;i<(1<<n);i++)
			maksi[i].first = -INFL;
		for(int i=0;i<z;i++){
			int num = zamiana(zaklad[i]);
			if(maksi[num].first < -k[i])
				maksi[num] = {-k[i],1};
			else if(maksi[num].first == -k[i])
				maksi[num].second++;
		}
		cin>>q;
		for(int i=1;i<=q;i++){
			cin>>pytanie;
			pytanko[i] = zamiana(pytanie);
		}
		for(int i=0;i<(1<<n);i++)
			ans_2[i] = solve_2(i);
		for(int i=1;i<=q;i++)
			cout<<ans_2[pytanko[i]].first<<' '<<ans_2[pytanko[i]].second<<"\n";
		return 0;
	}
	cin>>q;
	while(q--){
		cin>>pytanie;
		pair<long long,int>ans = {-INF,0};
		for(int i=0;i<z;i++){
			long long res = solve(i);
			if(res > ans.first)
				ans = {res, 1};
			else if(res == ans.first)
				ans.second++;
		}
		cout<<ans.first<<' '<<ans.second<<"\n";
	}
}
/*

3
1 3 5
4 2 5
5
000 5
010 2
101 1
000 8
011 3
3
000
011
100

*/
