#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e3+7;

long long n,k;
int c;
vector<long long>dzielniki,ans;
set<long long>secik;

void faktoryzacja(long long x)
{
    for (long long i=2;i*i<=x;i++)
    {
        while (x%i== 0)
        {
            if(secik.count(i) == 0)
                dzielniki.push_back(i);
            secik.insert(i);
            x /= i;
        }
    }
    if(x > 1 && secik.count(x) == 0)
        dzielniki.push_back(x);
}

long long ile(long long x)
{
    long long wyn = 0, dzielniczek;
    int y;
    for(int i=1;i<(1 << dzielniki.size());i++){
        y = i;
        dzielniczek = 1;
        for(int j=0;j<dzielniki.size();j++){
            if(y & 1)
                dzielniczek *= dzielniki[j];
            y /= 2;
        }
        if(__builtin_popcount(i) % 2 == 0)
            dzielniczek *= -1;
        wyn += (x/dzielniczek);
    }
    return wyn;
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>n>>k>>c;
faktoryzacja(n);

long long l=1,r=1e18,mid,start=r,wartosc;
while(l != r){
    mid = (l + r)/2;
    wartosc = ile(mid);
    if(mid - wartosc >= k){
        start = min(start, mid);
        r = mid;
    }
    else if(mid - wartosc < k)
        l = mid+1;
}

while(c){
    if(__gcd(start, n) == 1){
        ans.push_back(start);
        c--;
    }
    start++;
}
for(long long A:ans)
    cout<<A<<' ';
cout<<"\n";

}
/*

10 3 4

*/