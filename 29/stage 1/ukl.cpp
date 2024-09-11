/// zadanie: Ukladanie kart 
/// autor: Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e6+7;

long long n,jeden,dwa,suma; /// jeden = (n-1)!, dwa = (n-2)!, suma = 1+2...n-1
long long poc,kon; /// poc = najmniejsze w tabeli, kon = najwieksze w tabeli
long long dokr,zwieksz; /// drugi od konca rzad, zwieksze = o ile sie zwiekszaja rzedy
long long czerwone = 1; /// ile jest 1,2,3...n
long long mnoznik, suma_czerwonych = 1; /// czerwone -> juz posortowane
long long z[maxN];
long long ans;
int m;

long long silnia(long long x)
{
    long long wyn = 1;
    for(int i=2;i<=x;i++)
        wyn = (wyn * i) % m;
    return wyn;
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>n>>m;

dwa = silnia(n-2);
jeden = (dwa * (n-1)) % m;
suma = (n*(n-1)/2) % m;
poc = (suma * dwa) % m;
kon = (jeden * (n-1)) % m;

z[3] = 1;
mnoznik = 3;
for(int i=4;i<=n;i++)
{
    z[i] = (z[i-1] * mnoznik) % m;
    mnoznik++;
}
zwieksz = z[n];

for(int i=0;i<n-2;i++) /// obliczanie sumy dla drugiego od konca rzedu
{
    dokr = (dokr + poc) % m;
    poc = (poc + zwieksz) % m;
}

for(int i=1;i<=n;i++)
{
    ans = (ans + dokr) % m;
    dokr = (dokr + kon) % m;
}

mnoznik = n-1;
if(n == 2)
    suma_czerwonych = 0;
for(int i=2;i<=n-2;i++)
{
    czerwone = (czerwone * mnoznik) % m;
    suma_czerwonych = (suma_czerwonych + czerwone) % m;
    mnoznik--;
}
suma_czerwonych = (suma_czerwonych * n) % m;
suma_czerwonych = (suma_czerwonych * (n-1)) % m;
ans = (ans - suma_czerwonych) % m;
if(ans < 0)
    ans += m;
cout<<ans;
}
