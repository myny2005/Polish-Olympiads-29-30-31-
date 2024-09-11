/// Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 2e5+7;

int n,we[maxN],h[maxN],ans;
bool jest[maxN];
vector<int>v[maxN],v2[maxN];

void clean(){
	ans=min(n,2);
	for(int i=1;i<=n;i++){
		v[i].clear();
		v2[i].clear();
		we[i] = 0;
		h[i] = 0;
		jest[i] = false;
	}
}

void dfs(int x){
	for(int a:v2[x]){
		if(h[a]){
			if(h[a] == h[x])
				ans = max(ans, 3);
			continue;
		}
		if(h[x] == 1)
			h[a] = 2;
		else
			h[a] = 1;
		dfs(a);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>n;
		clean();
		for(int i=1;i<n;i++){
			int a,b,d;
			cin>>a>>b>>d;
			if(!d){
				v2[a].push_back(b);
				v2[b].push_back(a);
			}
			else{
				v[a].push_back(b);
				jest[a] = true;
				we[b]++;
			}
		}
		queue<int>q;
		for(int i=1;i<=n;i++){
			if(!we[i] && jest[i]){
				h[i] = 1;
				q.push(i);
			}
		}
		while(!q.empty()){
			int x = q.front();
			q.pop();
			for(int a:v[x]){
				h[a] = max(h[a], h[x]+1);
				we[a]--;
				if(!we[a] && jest[a])
					q.push(a);
			}
		}
		for(int i=1;i<=n;i++) /// to jest ans dla toposorta 
			ans = max(ans, h[i]);
		for(int i=1;i<=n;i++)
			if(h[i])
				dfs(i);
		cout<<ans<<"\n";
	}
}
/*

1
4
1 2 1
1 3 0
4 1 1

1
4
1 2 1
3 4 1
2 3 0

1
5
1 2 1
3 4 1
2 5 0
5 3 0

1
2
1 2 0





*/