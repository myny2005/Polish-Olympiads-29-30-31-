/// autor: Michal Szydlo
/// zadanie: Wyprzedzanie


#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e5+7, Log = 17;
using ll = __int128;
constexpr ll INF = 1e18;

int n,lewo[maxN],lo[maxN],ans=1;
ll D,W,M,pref_d[maxN];

struct ulamek{
    ll x,y;
}roznica,stykanie[maxN],sparse[maxN][Log+1];

bool czy_staszic_oszukuje_na_oiu(){
    return true;
}

ll GCD(ll x, ll y){
    if(!y) return x;
    return GCD(y, x%y);
}

int porownaj(ulamek a, ulamek b){
    if((__int128)a.x * b.y - (__int128)a.y * b.x > 0)
        return 1;
    if((__int128)a.x * (__int128)b.y - a.y * b.x == 0)
        return 0;
    return -1;
}

ulamek odejmij(ulamek a, ulamek b){
    ll nww = (__int128)a.y * b.y / GCD(a.y, b.y);
    return {a.x * (nww / a.y) - b.x * (nww / b.y), nww};
}

ulamek maksi(ulamek a, ulamek b){
    if(porownaj(a,b) == 1)
        return a;
    return b;
}

ulamek przedzial_maksi(int l, int r){
    int j = lo[r-l+1];
    ulamek res = sparse[l][j];
    if(porownaj(res, sparse[r - (1 << j) + 1][j]) == -1)
        res = sparse[r - (1 << j) + 1][j];
    return res;
}

struct cie{
    ll x,d;
    ulamek v;
    void read(){
        long long xx,dd,xxx,yyy;
        cin>>xx>>dd>>xxx>>yyy;
        x = xx, d = dd, v.x = xxx, v.y = yyy;
    }
}c[maxN];

struct wyd{
    ulamek t;
    int c1,c2;
    bool operator <(wyd W) const{
        return make_pair((__int128)t.x * W.t.y, -c1) < make_pair((__int128)t.y * W.t.x, -W.c1);
    }
}w[maxN], pomoc;
set<wyd>s;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long DD,WW,MM;
    cin>>n>>DD>>WW>>MM;
    D = DD, W = WW, M = MM;
    for(int i=1;i<=n;i++){
        c[i].read();
        pref_d[i] = pref_d[i-1] + c[i].d;
        lewo[i] = i-1;
    }
    for(int i=1;i<n;i++){
        pomoc.c1 = i, pomoc.c2 = i+1;
        ll odl = c[i+1].x - c[i+1].d - c[i].x;
        roznica = odejmij(c[i].v, c[i+1].v);
        if(roznica.x < 0)
            pomoc.t = {INF, 1};
        else if(roznica.x == 0 && odl > 0)
            pomoc.t = {INF, 1};
        else
            pomoc.t = {roznica.y * odl, roznica.x};
        w[i] = pomoc;
        s.insert(pomoc);
    }

    while(!s.empty()){
        wyd teraz = *s.begin();
        stykanie[teraz.c1] = teraz.t;
        s.erase(s.begin());
        lewo[teraz.c2] = lewo[teraz.c1];
        c[teraz.c2].d += c[teraz.c1].d;

        if(lewo[teraz.c1]){
            s.erase(w[lewo[teraz.c1]]);
            pomoc.c1 = lewo[teraz.c1], pomoc.c2 = teraz.c2;
            ll odl = c[pomoc.c2].x - c[pomoc.c2].d - c[pomoc.c1].x;
            roznica = odejmij(c[pomoc.c1].v, c[pomoc.c2].v);

            if(roznica.x < 0)
                pomoc.t = {INF, 1};
            else if(roznica.x == 0 && odl > 0)
                pomoc.t = {INF, 1};
            else
                pomoc.t = {roznica.y * odl, roznica.x};

            w[pomoc.c1] = pomoc;
            s.insert(pomoc);
        }
    }
    for(int i=1;i<=n;i++)
        sparse[i][0] = stykanie[i];
    for(int i=1;i<=n;i++){
        if(sparse[i][0].x == 0)
            sparse[i][0] = {1, INF};
    }
    for(int i=1;i<=Log;i++)
        for(int j=1;j+(1 << i)-1 <= n; j++)
            sparse[j][i] = maksi(sparse[j][i-1], sparse[j + (1 << (i-1))][i-1]);
    for(int i=2;i<=n;i++)
        lo[i] = lo[i/2]+1;

    int l,r,mid,ostatnie; /// do binsearcha
    for(int i=1;i<n;i++){
        ll odl = c[i].x + D;
        ulamek roznica = odejmij({W,M}, c[i].v);
        ulamek czas = {roznica.y * odl, roznica.x}; /// czas po ktorym wiade przed ciezarowe

        if(porownaj(czas, sparse[i][0]) >= 0)
            continue;
        l = i, r = n, ostatnie = i;
        while(l != r){
            mid = (l + r)/2;
            if(porownaj(czas, przedzial_maksi(i+1, mid)) >= 0){
                ostatnie = mid;
                l = mid+1;
            }
            else
                r = mid;
        }
        if(sparse[i+1][0].x == INF)
            ostatnie = i;
        odl =  c[ostatnie+1].x - (pref_d[ostatnie+1] - pref_d[i]) - c[i].x;
        roznica = odejmij({c[i].v.x * czas.x, c[i].v.y * czas.y},
            {c[ostatnie+1].v.x * czas.x, c[ostatnie+1].v.y * czas.y});
        roznica = odejmij({roznica.y * odl, roznica.y}, roznica);
        if(roznica.x / roznica.y >= D){
            ans++;
        }
    }
    if(czy_staszic_oszukuje_na_oiu())
        cout<<ans<<"\n";
}
/*

3 1 1 1
3 2 1 4
6 3 1 2
10 2 1 4

*/