#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e3+7;
const int ty[] = {1,-1,0,0}, tx[] = {0,0,1,-1};

int n,ile[maxN][maxN];
char t[maxN][maxN];
bool wybuch[maxN][maxN],jest_mur;
pair<int,int>start,koniec,miejsce_bomby;
pair<int,string>ans;

void bomba(int y, int x){
    wybuch[y][x] = true;
    for(int i=x+1;i<=n;i++){
        if(t[y][i] == 'X')
            break;
        wybuch[y][i] = true;
    }
    for(int i=x-1;i>=1;i--){
        if(t[y][i] == 'X')
            break;
        wybuch[y][i] = true;
    }
    for(int i=y+1;i<=n;i++){
        if(t[i][x] == 'X')
            break;
        wybuch[i][x] = true;
    }
    for(int i=y-1;i>=1;i--){
        if(t[i][x] == 'X')
            break;
        wybuch[i][x] = true;
    }
}   
void anuluj_bomba(int y, int x)
{
    wybuch[y][x] = false;
    for(int i=x+1;i<=n;i++){
        if(t[y][i] == 'X')
            break;
        wybuch[y][i] = false;
    }
    for(int i=x-1;i>=1;i--){
        if(t[y][i] == 'X')
            break;
        wybuch[y][i] = false;
    }
    for(int i=y+1;i<=n;i++){
        if(t[i][x] == 'X')
            break;
        wybuch[i][x] = false;
    }
    for(int i=y-1;i>=1;i--){
        if(t[i][x] == 'X')
            break;
        wybuch[i][x] = false;
    }
}

pair<int,int>pomoc;
int dodaj_y,dodaj_x;
string essa;
void odzyskaj(int y, int x){
    if(t[y][x] == 'P'){
        reverse(essa.begin(), essa.end());
        return;
    }
    for(int i=0;i<4;i++){
        dodaj_y = ty[i];
        dodaj_x = tx[i];
        if(ile[y][x]-1 == ile[y + dodaj_y][x + dodaj_x]){
            if(dodaj_y == 1)
                essa.push_back('G');
            else if(dodaj_y == -1)
                essa.push_back('D');
            else if(dodaj_x == 1)
                essa.push_back('L');
            else
                essa.push_back('P');
            odzyskaj(y+dodaj_y, x+dodaj_x);
            return;
        }
    }
}

queue<pair<int,int>>q;
void bfs(int Y, int X)
{
    q.push(start);
    ile[start.first][start.second] = 1;
    while(!q.empty()){
        pomoc = q.front();
        //cout<<pomoc.first<<' '<<pomoc.second<<"    "<<ile[pomoc.first][pomoc.second]<<"\n";
        q.pop();
        for(int i=0;i<4;i++){
            dodaj_y = ty[i];
            dodaj_x = tx[i];
            if(!ile[pomoc.first + dodaj_y][pomoc.second + dodaj_x]
                && pomoc.first + dodaj_y <= n && pomoc.first + dodaj_y >= 1 
                && pomoc.second + dodaj_x <= n && pomoc.second + dodaj_x >= 1){
                if(t[pomoc.first + dodaj_y][pomoc.second + dodaj_x] == '.' || 
                    wybuch[pomoc.first + dodaj_y][pomoc.second + dodaj_x]){
                    ile[pomoc.first + dodaj_y][pomoc.second + dodaj_x] = ile[pomoc.first][pomoc.second]+1;
                    q.push({pomoc.first + dodaj_y, pomoc.second + dodaj_x});
                }
            }
        }
    }
    if(ile[koniec.first][koniec.second] && ile[koniec.first][koniec.second] < ans.first){
        ans.first = ile[koniec.first][koniec.second]-1;
        essa = "";
        odzyskaj(koniec.first, koniec.second);
        ans.second = essa;
        miejsce_bomby = {Y,X};
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ile[i][j] = 0;
        }
    }
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>n;
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        cin>>t[i][j];
        if(t[i][j] == 'P')
            start = {i,j};
        else if(t[i][j] == 'K')
        {
            t[i][j] = '.';
            koniec = {i,j};
        }
        if(t[i][j] == '#')
            jest_mur = true;
    }
}

ans.first = 1e9;
if(jest_mur)
{
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(t[i][j] != 'X'){
                bomba(i,j);
                bfs(i,j);
                anuluj_bomba(i,j);
            }
        }
    }
}
else
    bfs(start.first, start.second);

if(ans.first == 1e9){
    cout<<"NIE\n";
    return 0;
}

cout<<ans.first<<"\n";
cout<<miejsce_bomby.first<<' '<<miejsce_bomby.second<<"\n";
cout<<ans.second<<"\n";
}
/*

6
......
.X.##.
..#.X.
..X.#K
.P#.X#
.X....

*/