
#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e6+7;

int n,ans;
long long ludzie[maxN];
bool done[maxN];
pair<int,long long>par[maxN];
vector<pair<int,long long>>v[maxN];

void dfs(int x, int p){
	for(pair<int, long long>a : v[x]){
		if(a.first != p){
			par[a.first] = {x,a.second};
			dfs(a.first, x);
		}
	}
	pair<long long,int>maksi = {-1,0};
	for(pair<int,long long>a : v[x]){
		if(done[a.first] || a.first == p) // ten syn wyslal dla x lub jest ojcem
			continue;
		maksi = max(maksi, {par[a.first].second, a.first});
	}
	if(maksi.first >= ludzie[x]){ // wysylam cos dla syna jak moge
		par[x].second = min(par[x].second, par[maksi.second].second - ludzie[x]);
		ludzie[x] = 0; // tego nie musze chyba
	}
	else{
		if(par[x].second >= ludzie[x]){ // wysylam dla ojca
			done[x] = true;
			ludzie[par[x].first] += ludzie[x];
		}
		else{ // stawiam wyjscie w x
			ans++;
		}
	}
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>ludzie[i];
	for(int i=1,a,b;i<n;i++){
		long long c;
		cin>>a>>b>>c;
		v[a].push_back({b,c});
		v[b].push_back({a,c});
	}
	dfs(1,0);
	cout<<ans<<"\n";
}
/*

10
20 30 64 10 4 80 20 5 10 4
1 2 80
2 3 90
3 4 60
4 5 4
5 6 4
2 7 80
3 8 10
4 9 20
5 10 4

*/