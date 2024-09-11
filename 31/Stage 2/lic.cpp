#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxN = 3e5+7;

int n,m;
bool zera = true;
pair<int,int>licznik[maxN];
vector<int>v[maxN];
multiset<int>ms;

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>licznik[i].first;
	for(int i=0;i<n;i++){
		cin>>licznik[i].second;
		if(licznik[i].second > 0)
			zera = false;
	}
	for(int i=1;i<=m;i++){
		for(int j=1,a;j<=n;j++){
			cin>>a;
			v[i].push_back(a);
		}
		sort(v[i].begin(), v[i].end());
	}
	sort(licznik, licznik+n, greater<pair<int,int>>());
	if(zera){ // podzadanie 1
		for(int i=0;i<n;i++)
			v[0].push_back(licznik[i].second);
		for(int i=1;i<=m;i++){
			ms.clear();
			for(int j=0;j<n;j++)
				ms.insert(v[i][j]);
			for(int j=0;j<n;j++){
				auto it = ms.lower_bound(v[i-1][j]);
				if(it == ms.end()){
					cout<<"NIE\n";
					return 0;
				}
				v[i][j] = *it;
				ms.erase(it);
			}
		}
		int res = 0;
		sort(v[m].begin(), v[m].end());
		for(int i=0;i<n;i++)
			res += v[m][i] * licznik[i].first;
		cout<<res<<"\n";
		return 0;
	}

	/*
	for(int i=0;i<n;i++){
		cout<<licznik[i].first<<' '<<licznik[i].second<<"\n";
	}
	*/
		for(int i=0;i<n;i++)
			v[0].push_back(licznik[i].second);
		for(int i=1;i<=m;i++){
			ms.clear();
			for(int j=0;j<n;j++)
				ms.insert(v[i][j]);
			for(int j=0;j<n;j++){
				auto it = ms.lower_bound(v[i-1][j]);
				if(it == ms.end()){
					cout<<"NIE\n";
					return 0;
				}
				v[i][j] = *it;
				ms.erase(it);
			}
		}
		int res = 0;
		for(int i=0;i<n;i++)
			res += (v[m][i] - v[0][i]) * licznik[i].first;
		cout<<res<<"\n";
		return 0;
}
/*

4 2
3 1 4 3
3 2 4 7
5 10 3 7
4 6 10 9

4 1
3 1 4 3
3 2 4 7
4 6 10 9

4 1
1 2 3 4
0 0 0 0
1 2 3 4

2 1
2 2
2 2
2 2

*/