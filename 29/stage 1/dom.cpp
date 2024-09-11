/// zadanie: Domino 
/// autor: Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 100;

long long m,dp[maxN],ans=2e18;
map<long long, int>obliczone;

void solve(long long x, long long wyn)
{
    long long o = obliczone[x];
    if(o && o <= wyn)
        return;
    obliczone[x] = wyn;
    for(int i=2;i<=86;i++)
    {
        if(x == dp[i])
            ans = min(ans,wyn + i);
        else if(x % dp[i] == 0)
            solve(x / dp[i], wyn + i + 1);
    }
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>m;
if(m == 1)
{
    cout<<1;
    return 0;
}

dp[1] = 1;
dp[2] = 2;
for(int i=3;i<=86;i++) /// Fibonacci
    dp[i] = dp[i-1] + dp[i-2];
solve(m,0);
if(ans != 2e18)
    cout<<ans;
else
    cout<<"NIE";
}
