#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 20+7;

int n,q;
long long d,l,w,ans[maxN];
pair<int,long long>gdzie[maxN];
vector<pair<int,long long>>lawki[maxN];

bool comp(pair<int,long long>a, pair<int,long long>b){
	return a.second < b.second;
}

long long solve(int x){
	long long res = 0;
	for(int i=1;i<=l;i++){
		long long last = 0;
		for(pair<int,long long>a : lawki[i]){
			if((1 << a.first) & x){ /// przesuwam
				last = last + d;
			}
			else{ /// zostawiam
				res += (a.second - last) / d;
				last = a.second+d;
			} 
		}
		res += (w - last) / d;
	}
	return res;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>q>>d>>l>>w; /// d - dl laptopa, l - ile lawek, w - dl lawki
	for(int i=0;i<n;i++){
		cin>>gdzie[i].first>>gdzie[i].second;
		lawki[gdzie[i].first].push_back({i, gdzie[i].second});
	}
	for(int i=1;i<=l;i++)
		sort(lawki[i].begin(), lawki[i].end(), comp);

	for(int i=0;i<(1 << n);i++){
		int bity = __builtin_popcount(i);
		ans[bity] = max(ans[bity], solve(i));
	}

	while(q--){
		long long a;
		cin>>a;
		if(a > ans[n]){
			cout<<-1<<"\n";
			continue;
		}
		for(int i=0;i<=n;i++){
			if(ans[i] >= a){
				cout<<i<<"\n";
				break;
			}
		}
	}
}
/*

4 3 3 2 10
2 1
1 2
1 6
2 5
2 1 3


*/