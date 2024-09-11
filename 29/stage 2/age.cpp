#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e5+7;

int n,k,oryginalne[maxN],agenci[15],ans=maxN,t[15];
int odl[15][15];
bool odw[maxN];
pair<int,int>pomoc;
vector<int>v[maxN];

int vis[15];
void dfs(int x, int parent)
{
    vis[x] = parent;
    for(int a:v[x])
        if(vis[a] != parent){
            odl[parent][a] = odl[parent][x]+1;
            dfs(a,parent);
        }
}
int solve()
{
    int wyn = 0;
    for(int i=1;i<=n;i++)
        odw[i] = false;
    for(int i=1;i<=k;i++){
        agenci[i] = oryginalne[i];
        odw[agenci[i]] = true;
    }
    for(int i=1;i<=n;i++){
        if(odw[t[i]])
            continue;
        pomoc = {1e9,420};
        for(int j=1;j<=k;j++)
            pomoc = min(pomoc, {odl[t[i]][agenci[j]], j});
        wyn += pomoc.first;
        agenci[pomoc.second] = t[i];
        odw[t[i]] = true;
    }
    return wyn;
}

pair<int,int>dp[maxN];
void dfs2(int x, int oj){
    pair<int,int> teraz = {-1, 420};
    for(int a:v[x])
        if(a != oj){
            dfs2(a,x);
            if(dp[a].second - dp[a].first > teraz.first)
                teraz = {dp[a].second - dp[a].first, a};
        }
    if(teraz.first != -1){ /// nie jest lisciem
        dp[x].first = dp[teraz.second].first+1;
        dp[x].second = dp[teraz.second].second+2;
        for(int a:v[x]){
            if(a != oj && a != teraz.second){
                dp[x].first += dp[a].second+2;
                dp[x].second += dp[a].second+2;
            }
        }
    }
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>n>>k;
for(int i=1;i<=k;i++)
    cin>>oryginalne[i];
for(int i=1;i<n;i++){
    int a,b;
    cin>>a>>b;
    v[a].push_back(b);
    v[b].push_back(a);
}

if(n <= 10){
    for(int i=1;i<=n;i++){
        dfs(i,i);
        t[i] = i;
    }
    do{
        ans = min(ans, solve());
    }while(next_permutation(t+1,t+1+n));
    cout<<ans<<"\n";
    return 0;
}
dfs2(oryginalne[1], 0);
//for(int i=1;i<=n;i++)
  //  cout<<dp[i].first<<' '<<dp[i].second<<"\n";
cout<<dp[oryginalne[1]].first<<"\n";
}
/*

6 2
2 6
1 2
2 3
2 4
5 4
5 6

6 1
2
1 2
2 3
2 4
5 4
5 6

7 1
7
1 2
2 3
3 4
1 5
1 6
3 7

*/