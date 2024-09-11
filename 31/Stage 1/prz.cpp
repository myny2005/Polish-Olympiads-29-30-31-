/// Michal Szydlo
/// zadanie PRZ

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e5+7;

int n,m,sz_tree;
bool done[2*maxN],taken[5*maxN];
pair<int,int>last[2*maxN];
vector<int>roots,cycle;
vector<pair<int,int>>v[2*maxN];

void dfs(int x){
	sz_tree++;
	done[x] = true;
	for(pair<int,int>a:v[x]){
		if(!cycle.empty()) /// juz znalazlem cykl
			return;
		if(!done[a.first]){
			last[a.first] = {x, a.second};
			dfs(a.first);
		}
		else if(last[x].first != a.first){ /// cykl
			cycle.push_back(a.second);
			int c = x;
			while(c != a.first){
				cycle.push_back(last[c].second);
				c = last[c].first;
			}
			return;
		}
	}
}

int sz[maxN];
void dfs_tree(int x, int par){
	sz[x] = 1;
	for(pair<int,int>a:v[x]){
		if(a.first == par)
			continue;
		dfs_tree(a.first, x);
		if(sz[a.first] % 2 == 0) /// odcinam parzyste podrzewo
			taken[a.second] = false;
		else
			sz[x] += sz[a.first];
	}
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
   
    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		v[x].push_back({y+n,i});
		v[y+n].push_back({x,i});
	}
	/// sprawdzic czy jest cykl
	bool parzyste = false, nieparzyste = false;
	for(int i=1;i<=2*n;i++)
		if(v[i].empty())
			parzyste = true;
	for(int i=1;i<=n;i++){
		if(!done[i] && !v[i].empty()){
			sz_tree = 0;
			dfs(i);
			roots.push_back(i);
			if(!cycle.empty()){
				cout<<"TAK\n";
				cout<<cycle.size()<<"\n";
				for(int x:cycle)
					cout<<x<<' ';
				cout<<"\n";
				return 0;
			}
			if(sz_tree & 1)
				nieparzyste = true;
		}
	}
	if(nieparzyste){
		cout<<"NIE\n";
		return 0;
	}
	if(parzyste){
		cout<<"NIE\n";
		return 0;
	}
	/// reszta chyba zawsze tak
	/// zostal mi juz tylko las z kazdym parzystym drzewem
	for(int i=1;i<=m;i++)
		taken[i] = true;
	for(int x:roots)
		dfs_tree(x,0);
	int ans = 0;
	for(int i=1;i<=m;i++)
		if(taken[i])
			ans++;
	cout<<"TAK\n";
	cout<<ans<<"\n";
	for(int i=1;i<=m;i++) /// tutaj m a nie n
		if(taken[i])
			cout<<i<<' ';
	cout<<"\n";
}
/*

3 6
1 1
1 2
2 2
3 1
3 2
3 3

*/	
