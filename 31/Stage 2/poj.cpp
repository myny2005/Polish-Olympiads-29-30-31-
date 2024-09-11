#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxN = 1e6+7, INF = 1e9;

int n,k,wolne[maxN];
vector<pair<int,int>>ans[maxN],mniejsze,wieksze;

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>k;
	int sum = 0;
	for(int i=1,cap;i<=n;i++){
		cin>>cap;
		sum += cap;
		if(cap < k)
			mniejsze.push_back({i,cap});
		else
			wieksze.push_back({i,cap});
		wolne[i] = k;
	}
	if(sum > k * n){
		cout<<"NIE\n";
		return 0;
	}
	priority_queue<pair<int,int>>pq; // ile wolnego, idx
	int last = 1;
	for(pair<int,int>x : mniejsze){
		wolne[last] -= x.second;
		ans[last].push_back(x);
		pq.push({-wolne[last], last++});
	}
	for(pair<int,int>x : wieksze){
		while(!pq.empty() && x.second >= -pq.top().first){
			int idx = pq.top().second;
			pq.pop();
			x.second -= wolne[idx];
			ans[idx].push_back({x.first, wolne[idx]});
			wolne[idx] = 0;
		}
		while(x.second > 0){
			int odejmij = min(k, x.second);
			x.second -= odejmij;
			wolne[last] -= odejmij;
			ans[last].push_back({x.first, odejmij});
			if(wolne[last] > 0)
				pq.push({-wolne[last], last});
			last++;
		}
	}
	cout<<"TAK\n";
	for(int i=1;i<=n;i++){
		cout<<ans[i].size()<<' ';
		for(pair<int,int>essasito : ans[i])
			cout<<essasito.first<<' '<<essasito.second<<' ';
		cout<<"\n";
	}
}
/*

5 6
1
11
3
4
2

2 10
20
1


4 30
29 29 30 31

4 5
4 4 5 6

*/