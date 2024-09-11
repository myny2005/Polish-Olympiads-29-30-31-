#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e6+7;

int q;
int licznosc[maxN],grupa[maxN];
vector<int>v[maxN];

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>q;
v[1].push_back(2);
v[2].push_back(1);
char znak;
int x,licznik=2;
if(q <= 5000)
{
    for(int i=1;i<=q;i++){
        cin>>znak>>x;
        if(znak == '?')
            cout<<v[x].size()<<"\n";
        else if(znak == 'Z'){ /// zazdrosny
            licznik++;
            for(int a:v[x]){
                v[licznik].push_back(a);
                v[a].push_back(licznik);
            }
        }
        else{ /// wybredny
            licznik++;
            v[licznik].push_back(x);
            v[x].push_back(licznik);
        }
    }
    return 0;
}
licznosc[1] = 1;
licznosc[2] = 1;
grupa[1] = 1;
grupa[2] = 2;

for(int i=1;i<=q;i++){
    cin>>znak>>x;
    if(znak == '?'){
        if(grupa[x] == 1)
            cout<<licznosc[2]<<"\n";
        else
            cout<<licznosc[1]<<"\n";
    }
    else if(znak == 'Z'){ /// zazdrosny
        licznik++;
        if(grupa[x] == 1){
            licznosc[2]++;
            grupa[licznik] = 1;
        }
        else{
            licznosc[1]++;
            grupa[licznik] = 2;
        }
    }
    else
        continue;
}
}
/*

7
? 1
Z 2
? 1
Z 1
W 2
? 2
? 3

*/
