/// autor: Michal Szydlo
/// zadanie: Kolorowy Waz

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 2e3+7;

int m,p,n,kolory[maxN][maxN],t[maxN][maxN],czas;
pair<int,int>curr = {1,1};
vector<int>kolor_weza;

void add(){
    if(kolory[curr.first][curr.second] != -1){
        kolor_weza.push_back(kolory[curr.first][curr.second]);
        kolory[curr.first][curr.second] = -1;
    }
    t[curr.first][curr.second] = ++czas;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>m>>p>>n;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++){
            t[i][j] = -1;
            kolory[i][j] = -1;
        }
    t[1][1] = 0;
    kolor_weza.push_back(0);
    for(int i=1;i<=p;i++){
        int x,y,c;
        cin>>x>>y>>c;
        kolory[x][y] = c;
    }
    for(int i=1;i<=n;i++){
        char znak;
        int x,y;
        cin>>znak;
        if(znak == 'G'){
            curr.first--;
            add();
        }
        else if(znak == 'D'){
            curr.first++;
            add();
        }
        else if(znak == 'P'){
            curr.second++;
            add();
        }
        else if(znak == 'L'){
            curr.second--;
            add();
        }
        else{
            cin>>x>>y;
            if(t[x][y] == -1){
                cout<<-1<<"\n";
                continue;
            }
            int kiedy = czas - t[x][y];
            if(kiedy >= (int)kolor_weza.size())
                cout<<-1<<"\n";
            else
                cout<<kolor_weza[(int)kolor_weza.size()-1-kiedy]<<"\n";
        }
    }
}
/*

6 5 14
1 3 1
5 1 5
2 3 2
3 4 1
3 5 3
Z 1 1
Z 1 2
P
P
D
D
P
Z 3 5
P
Z 3 5
D
Z 3 5
L
Z 3 5

*/
