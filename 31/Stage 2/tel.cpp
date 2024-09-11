#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxN = 5e5+7, Mod = 998244353;

int n,sz[maxN],Link[maxN],num[maxN],curr;
pair<int,int>zamiana[maxN],hasz[maxN];
vector<int>v[maxN];
set<pair<int,int>>edges;

mt19937 e = (mt19937)310705;
int rand(int a, int b){
	return uniform_int_distribution<int>{a,b}(e);
}

void pre(){
	for(int i=1;i<=n;i++){
		sz[i] = 1;
		Link[i] = i;
		zamiana[i].first = rand(1, (int)1e18);
		zamiana[i].second = rand(1, (int)1e18);
		//cout<<zamiana[i].first<<' '<<zamiana[i].second<<"\n";
	}
}

bool pelny(){
	for(int i=1;i<=n;i++)
		if((int)v[i].size() != n-1)
			return false;
	return true;
}

int Find(int x){
	if(x == Link[x])
		return x;
	Link[x] = Find(Link[x]);
	return Link[x];
}

void Unite(int a, int b){
	a = Find(a), b = Find(b);
	if(a == b)
		return;
	if(sz[a] < sz[b])
		swap(a,b);
	Link[b] = a;
	sz[a] += sz[b];
}

pair<int,int>zamianka(pair<int,int>haszyk, int idx){
	haszyk.first ^= zamiana[idx].first;
	haszyk.second ^= zamiana[idx].second;
	return haszyk;
}

void add_edge(int x, int y){
	x = num[x], y = num[y];
	if(x > y)
		swap(x,y);
	edges.insert({x,y});
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	pre();
	for(int i=1,k;i<=n;i++){
		cin>>k;
		while(k--){
			int a;
			cin>>a;
			v[i].push_back(a);
			hasz[i] = zamianka(hasz[i], a);
		}
	}
	if(n == 1){
		cout<<1<<"\n";
		cout<<1<<"\n";
		return 0;
	}
	if(pelny()){
		cout<<2<<"\n";
		cout<<1<<' ';
		for(int i=2;i<=n;i++)
			cout<<2<<' ';
		cout<<"\n";
		cout<<1<<' '<<2<<"\n";
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int a:v[i]){
			if(a > i && v[i].size() == v[a].size()){
				pair<int,int>x = zamianka(hasz[i], a);
				pair<int,int>y = zamianka(hasz[a], i);
				if(x == y)
					Unite(i,a);
			}
		}
	}
	for(int i=1;i<=n;i++){ // przenumerowanie
		int x = Find(i);
		if(!num[x])
			num[x] = ++curr;
	}
	for(int i=1;i<=n;i++){
		int x = Find(i), y;
		for(int a:v[i]){
			y = Find(a);
			if(x != y)
				add_edge(x,y);
		}
	}
	cout<<curr<<"\n";
	for(int i=1;i<=n;i++)	
		cout<<num[Find(i)]<<' ';
	cout<<"\n";
	for(auto x : edges)
		cout<<x.first<<' '<<x.second<<"\n";
}
/*

8
3 2 4 6
4 1 4 6 7
2 5 7
3 1 2 6
2 3 7
4 1 2 4 7
5 2 3 5 6 8
1 7

4
3 2 3 4
3 1 3 4
3 1 2 4
3 1 2 3

*/