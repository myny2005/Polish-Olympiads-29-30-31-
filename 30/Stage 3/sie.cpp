/// Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 2e2+7;

int n,m,k,kolor[maxN],kolorek[maxN],jedynki,dwojki,ans;
bool ok=true;
vector<int>v[maxN],spojna;

void dfs(int x){
	spojna.push_back(x);
	if(kolor[x] == 1)
		jedynki++;
	else
		dwojki++;

	for(int a:v[x]){
		if(!kolor[a]){
			if(kolor[x] == 1)
				kolor[a] = 2;
			else
				kolor[a] = 1;
			dfs(a);
		}
		else{
			if(kolor[a] == kolor[x]){
				ok = false;
				return;
			}
		}
	}
}

bool dwudzielny(){
	for(int i=1;i<=n;i++){
		if(!kolor[i]){
			jedynki = 0, dwojki = 0;
			spojna.clear();
			kolor[i] = 1;
			dfs(i);
			ans += max(jedynki, dwojki);
			if(jedynki < dwojki){
				for(int x:spojna){
					if(kolor[x] == 1)
						kolor[x] = 2;
					else
						kolor[x] = 1;
				}
			}
		}
	}
	return ok;
}

int solve(int x){
	for(int i=1;i<=n;i++)
		kolorek[i] = 0;
	queue<int>q;
	for(int i=0;i<n;i++){
		if((1 << i) & x){
			q.push(i+1);
			kolorek[i+1] = 1;
		}
	}
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(int a:v[x]){
			if(kolorek[a]){
				if((kolorek[a]&1) == (kolorek[x]&1))
					return -1;
				continue;
			}
			if(kolorek[x] != k)
				kolorek[a] = kolorek[x]+1;
			else
				kolorek[a] = kolorek[x]-1;
			q.push(a);
		}
	}
	int res = 0;
	for(int i=1;i<=n;i++)
		if(kolorek[i] == 1 || kolorek[i] == k)
			res++;
	return res;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	if(!dwudzielny()){
		cout<<"NIE\n";
		return 0;
	}

	if(n <= 20 && k != 3){
		for(int i=1;i<(1 << n);i++){
			int x = solve(i);
			if(ans < x){
				ans = x;
				for(int j=1;j<=n;j++)
					kolor[j] = kolorek[j];
			}
		}
		cout<<ans<<"\n";
		for(int i=1;i<=n;i++)
			cout<<kolor[i]<<' ';
		cout<<"\n";
		return 0;
	}

	/// to jest chyba solv dla (k nieparzystego zawsze)
	//if(k & 1){
		cout<<ans<<"\n";
		for(int i=1;i<=n;i++)
			cout<<kolor[i]<<' ';
		cout<<"\n";
		return 0;
	//}
}
/*

8 8 4
1 2
2 3
3 4
4 1
1 5
1 6
2 7
2 8

3 3 3
1 2
2 3
3 1



*/