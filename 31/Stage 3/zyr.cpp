#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxN = 1e6+7;

int k,q,cnt[20][20],a[maxN];
vector<int>essa[maxN];

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>k>>q;
	essa[1] = {1};
	for(int i=2;i<=10;i++){
		int last = essa[i-1].back(), sum = 0;
		for(int x : essa[i-1])
			sum += x;
		while(sum--){
			last++;
			if(last > k)
				last = 1;
			essa[i].push_back(last);
		}
	}
	for(int i=1;i<=10;i++){
		/*
		for(int x:essa[i])
			cout<<x<<' ';
		cout<<"\n";
		*/
		for(int x : essa[i])
			cnt[i][x]++;
	}
	while(q--){
		int d,p;
		cin>>d>>p;
		for(int i=1;i<=d;i++)
			cin>>a[i];
		int ans = 0;
		for(int i=1;i<=p;i++)
			ans += cnt[i][a[1]];
		cout<<ans<<"\n";
	}
}
/*

3 4
3 3
3 2 1
3 4
2 3 2
3 4
3 1 2
1 5
1

*/