/// autor: Michal Szydlo
/// zadanie: Pociag Towarowy

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 3e5+7, INF = 1e9;

int n,m,k,pociag[maxN],bitek[maxN],lewo[maxN],suf[maxN],ostatnie[maxN];
bool ans[maxN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        cin>>pociag[i];
    for(int i=1;i<=m;i++)
        cin>>bitek[i];
    int c = 0;
    for(int i=1;i<=n;i++){
        if(bitek[c+1] == pociag[i]){
            lewo[i] = c+1;
            ostatnie[pociag[i]] = c+1;
            c++;
            continue;
        }
        lewo[i] = ostatnie[pociag[i]];
    }
    for(int i=1;i<=k;i++)
        ostatnie[i] = INF;
    c = m+1;
    suf[n+1] = INF;
    for(int i=n;i>=1;i--){
        if(bitek[c-1] == pociag[i]){
            suf[i] = c-1;
            ostatnie[pociag[i]] = c-1;
            c--;
            continue;
        }
        suf[i] = ostatnie[pociag[i]];
        suf[i] = min(suf[i], suf[i+1]);
    }
    for(int i=1;i<=n;i++){
        if(lewo[i] == m)
            ans[i] = true;
        if(lewo[i] && suf[i+1] <= lewo[i]+1)
            ans[i] = true;
    }
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<' ';
    cout<<"\n";
}
/*

9 4 3
1 3 2 1 2 3 1 3 2
1 3 1 2

*/
