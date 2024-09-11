#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e3+7;

long long n,dp[maxN][maxN],maks_1[maxN],maks_2[maxN],ans = 1e18;
bool odw[maxN][maxN];
int a,b;
vector<long long>v1,v2;

struct stan
{
    long long ile;
    int a,b;
    bool operator <(stan S) const{
        return tie(ile,a,b) < tie(S.ile,S.a,S.b);
    }
}pomoc;

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>n>>a>>b;
if(n <= 1000)
{
    priority_queue<stan>pq;
    pq.push({-a-b,2,1});
    while(!pq.empty()){
        pomoc = pq.top();
        pq.pop();
        if(pomoc.a > n){
            ans = min(ans, -pomoc.ile);
            continue;
        }
        if(odw[pomoc.a][pomoc.b])
            continue;
        //cout<<-pomoc.ile<<' '<<pomoc.a<<' '<<pomoc.b<<"\n";
        odw[pomoc.a][pomoc.b] = true;
        pq.push({pomoc.ile-b, pomoc.a+pomoc.b,pomoc.b});
        pq.push({pomoc.ile-a, pomoc.a,pomoc.a});
    }
    cout<<ans<<"\n";
    return 0;
}

v1.push_back(1);
v1.push_back(2);
v1.push_back(3);
v1.push_back(4);
v2.push_back(2);
v2.push_back(3);
v2.push_back(4);
v2.push_back(5);

while(v1.back() <= ans){
    v1.push_back(v1[v1.size() - 3] * 3);
    v2.push_back(v2.back() + 1);
}
/*
for(int i=0;i<=10;i++)
    cout<<v1[i]<<' '<<v2[i]<<"\n";
*/
for(int i=0;i<v1.size();i++){
    if(n <= v1[i]){
        if(n == v1[i])
            cout<<v2[i]<<"\n";
        else
            cout<<v2[i-1]<<"\n";
        return 0;
    }
}
}
/*

8 2 1

*/