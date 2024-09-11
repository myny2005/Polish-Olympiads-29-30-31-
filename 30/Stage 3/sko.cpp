#include "skolib.h"
#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e3+7;
const int t2[] = {1,2,2,1,-1,-2,-2,-1}, t1[] = {2,1,-1,-2,-2,-1,1,2};

int n,dist[maxN][maxN];
vector<pair<int,int>>oddalone;

bool bylo[maxN][maxN],ok[maxN][maxN],dodac[maxN][maxN];
mt19937 e = (mt19937)420;
int rand(int a, int b){
	return uniform_int_distribution<int>{a,b}(e);
}

void clean(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dist[i][j] = 0;
}

bool inside(int x, int y){
	return (x >= 1 && x <= n && y >= 1 && y <= n);
}

/*
void bfs(int x, int y){
	int start_x = x, start_y = y;
	v[start_x][start_y][0].push_back({start_x,start_y});
	clean();
	queue<pair<int,int>>q;
	q.push({x,y});
	dist[x][y] = 1;
	int X,Y;
	while(!q.empty()){
		x = q.front().first, y = q.front().second;
		//cout<<x<<' '<<y<<' '<<dist[x][y]-1<<"\n";
		q.pop();
		for(int i=0;i<8;i++){
			X = x + t1[i], Y = y + t2[i];
			if(!inside(X,Y) || dist[X][Y])
				continue;
			q.push({X,Y});
			dist[X][Y] = dist[x][y]+1;
			v[start_x][start_y][dist[X][Y]-1].push_back({X,Y});
		}
	}
}
*/

void BFS(int x, int y, int odl){
	oddalone.clear();
	clean();
	queue<pair<int,int>>q;
	q.push({x,y});
	dist[x][y] = 1;
	int X,Y;
	while(!q.empty()){
		x = q.front().first, y = q.front().second;

		if(dist[x][y] == odl)
			oddalone.push_back({x,y});

		q.pop();
		for(int i=0;i<8;i++){
			X = x + t1[i], Y = y + t2[i];
			if(!inside(X,Y) || dist[X][Y])
				continue;
			q.push({X,Y});
			dist[X][Y] = dist[x][y]+1;
		}
	}
}



/*
int szachownica[8][8] = {
{ 4, 3, 4, 3, 2, 1, 2, 3 },
{ 5, 4, 3, 2, 3, 2, 3, 0 },
{ 4, 3, 4, 3, 2, 1, 2, 3 },
{ 5, 4, 3, 2, 3, 4, 1, 2 },
{ 4, 3, 4, 3, 2, 3, 2, 3 },
{ 5, 4, 3, 4, 3, 2, 3, 2 },
{ 4, 5, 4, 3, 4, 3, 4, 3 },
{ 5, 4, 5, 4, 3, 4, 3, 4 }};


int szachownica[10][10] = {
{ 4, 3, 4, 3, 4, 3, 4, 5, 4, 5 },
{ 3, 4, 3, 4, 3, 4, 3, 4, 5, 4 },
{ 2, 3, 2, 3, 2, 3, 4, 3, 4, 5 },
{ 3, 2, 3, 2, 3, 2, 3, 4, 3, 4 },
{ 4, 1, 2, 1, 4, 3, 2, 3, 4, 5 },
{ 1, 2, 3, 2, 1, 2, 3, 4, 3, 4 },
{ 2, 3, 0, 3, 2, 3, 2, 3, 4, 5 },
{ 1, 2, 3, 2, 1, 2, 3, 4, 3, 4 },
{ 4, 1, 2, 1, 4, 3, 2, 3, 4, 5 },
{ 3, 2, 3, 2, 3, 2, 3, 4, 3, 4 }};


void odpowiedz(int a, int b){
	cout<<a<<' '<<b<<"\n";
}

int pytanie(int a, int b){
	return szachownica[b-1][a-1];
}
*/



int main(){
	n = daj_n();
	//n = 8;
	
	vector<pair<int,int>>wynik; /// potencjalny wynik
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			wynik.push_back({i,j});

	while(wynik.size() > 1){
		//cout<<"alslalala\n";
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				ok[i][j] = false;
				dodac[i][j] = false;
			}

		int a = rand(1, n);
		int b = rand(1, n);
		while(bylo[a][b]){
			a = rand(1, n);
			b = rand(1, n);
		}
		bylo[a][b] = true;
		int odl = pytanie(a,b);
		//cout<<a<<' '<<b<<' '<<odl<<"\n";

		for(pair<int,int>x : wynik)
			ok[x.first][x.second] = true;
		BFS(a,b,odl+1);
		for(pair<int,int>x : oddalone)
			dodac[x.first][x.second] = true;

		wynik.clear();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(dodac[i][j] && ok[i][j])
					wynik.push_back({i,j});
		//cout<<wynik.size()<<"    to ejst wynik.size()\n";
	}
	odpowiedz(wynik[0].first, wynik[0].second);
	
}
/*

g++ -O3 -static -std=c++17 skolib.cpp wzor.cpp


8
4 3 4 3 2 1 2 3
5 4 3 2 3 2 3 0
4 3 4 3 2 1 2 3
5 4 3 2 3 4 1 2
4 3 4 3 2 3 2 3
5 4 3 4 3 2 3 2
4 5 4 3 4 3 4 3
5 4 5 4 3 4 3 4

{ 4, 3, 4, 3, 2, 1, 2, 3 },
{ 5, 4, 3, 2, 3, 2, 3, 0 },
{ 4, 3, 4, 3, 2, 1, 2, 3 },
{ 5, 4, 3, 2, 3, 4, 1, 2 },
{ 4, 3, 4, 3, 2, 3, 2, 3 },
{ 5, 4, 3, 4, 3, 2, 3, 2 },
{ 4, 5, 4, 3, 4, 3, 4, 3 },
{ 5, 4, 5, 4, 3, 4, 3, 4 }

{
{ 4, 3, 4, 3, 4, 3, 4, 5, 4, 5 },
{ 3, 4, 3, 4, 3, 4, 3, 4, 5, 4 },
{ 2, 3, 2, 3, 2, 3, 4, 3, 4, 5 },
{ 3, 2, 3, 2, 3, 2, 3, 4, 3, 4 },
{ 4, 1, 2, 1, 4, 3, 2, 3, 4, 5 },
{ 1, 2, 3, 2, 1, 2, 3, 4, 3, 4 },
{ 2, 3, 0, 3, 2, 3, 2, 3, 4, 5 },
{ 1, 2, 3, 2, 1, 2, 3, 4, 3, 4 },
{ 4, 1, 2, 1, 4, 3, 2, 3, 4, 5 },
{ 3, 2, 3, 2, 3, 2, 3, 4, 3, 4 }}

*/