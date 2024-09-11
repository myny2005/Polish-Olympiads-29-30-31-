/// autor: Michal Szydlo
/// zadanie: Zboze      

/// lca wzorowane na implementacji ze strony:https://cp-algorithms.com/#navigation
/// rozbicie na centroidy wzorowane na implementacji ze strony:https://usaco.guide/plat/centroid?lang=cpp

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e5+7, Log = 17;
constexpr long long INF = 1e18;

int n,k,sz[maxN],root,anc[maxN],lo[2*maxN],essa[maxN],PRE[maxN],POST[maxN],pre,post;
long long dist[maxN],ans[maxN];
bool r[maxN];
pair<long long,int>dp[maxN],sub[maxN]; /// disty, cnt
pair<int,long long>sparse[2*maxN][Log+1];
vector<pair<int,int>>v[maxN],path;

int dfs(int x, int p=0){
	sz[x] = 1;
	for(pair<int,int>a : v[x])
		if(a.first != p && !r[a.first])
			sz[x] += dfs(a.first, x);
	return sz[x];
}

int get_centroid(int x, int ms, int p=0){
	for(pair<int,int>a : v[x])
		if(a.first != p && !r[a.first])
			if(sz[a.first]*2 > ms)
				return get_centroid(a.first, ms, x);
	return x;
}

void centroid(int x, int last){
	int C = get_centroid(x, dfs(x));
	if(!last)
		root = C;
	anc[C] = last;
	r[C] = true;
	for(pair<int,int>a : v[C])
		if(!r[a.first])
			centroid(a.first, C);
}

void dfs2(int x, int p, int depth){
	PRE[x] = pre++;
    path.push_back({x, depth});
    essa[x] = (int)path.size();
    for(pair<int,int>a : v[x]) {
        if(a.first != p) {
            dist[a.first] = dist[x] + a.second;
            dfs2(a.first, x, depth + 1);
            path.push_back({x, depth});
        }
    }
    POST[x] = post++;
}
int LCA(int l, int r) {
    l = essa[l], r = essa[r];
    if(l > r)
        swap(l,r);
    if(sparse[l][lo[r-l+1]].second <= sparse[r-(1<<lo[r-l+1])+1][lo[r-l+1]].second)
        return sparse[l][lo[r-l+1]].first;
    return sparse[r-(1<<lo[r-l+1])+1][lo[r-l+1]].first;
}
long long DIST(int a, int b) {
    return dist[a] + dist[b] - (2 * dist[LCA(a, b)]);
}

void add(int x){
	int start = x;
	dp[x].second++;
	sub[x].first += DIST(x, anc[x]);
	sub[x].second++;
	while(anc[x]){
		x = anc[x];
		dp[x].first += DIST(start, x);
		dp[x].second++;
		sub[x].first += DIST(start, anc[x]);
		sub[x].second++;
	}
}

long long solve(int x){
	long long res = 0;
	int start = x, previous = x;
	pair<long long,int>added;
	res += dp[x].first;
	while(anc[x]){
		x = anc[x];
		added = {dp[x].first - sub[previous].first, dp[x].second - dp[previous].second};
		res += added.first + DIST(start, x) * added.second;
		previous = x;
	}
	return res*2;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin>>n>>k;
	for(int i=1;i<n;i++){
		int a,b,c;
		cin>>a>>b>>c;
		v[a].push_back({b,c});
		v[b].push_back({a,c});
	}
	centroid(1, 0);
	dfs2(root, 0, 0);
	for(int i=2;i<=200010;i++)
        lo[i] = lo[i/2]+1;
    for(int j=0; j<=Log; j++) 
        for(int i=1; i<=(int)path.size(); i++) 
            sparse[i][j].second = INF;
    for(int i=1; i<=(int)path.size(); i++)
        sparse[i][0] = path[i - 1];
    for(int j=1; j<=Log; j++) {
        for(int i=1; i+(1<<j)<=(int)path.size(); i++){
            if(sparse[i][j-1].second <= sparse[i+(1<<(j-1))][j-1].second)
                sparse[i][j] = sparse[i][j-1];
            else 
                sparse[i][j] = sparse[i + (1<<(j-1))][j-1];
        }
    }
	add(1);
	for(int i=1;i<=k;i++){
		int x;
		cin>>x;
		ans[i] = ans[i-1] + solve(x);
		add(x);
	}
	for(int i=1;i<=k;i++)
		cout<<ans[i]<<"\n";
}
/*


5 3
1 4 3
3 1 6
1 2 5
4 5 1
5
3
2

5 2
1 2 1
2 3 1
3 4 1
4 5 1
5
4


*/