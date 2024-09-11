#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e2+7;
const int t1[] = {1,0,-1,0}, t2[] = {0,1,0,-1};

int n,m,z,odw[maxN][maxN];
bool pion[maxN],poziom[maxN];

void clean()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			odw[i][j] = 0;
}

int bfs(long long c)
{
	clean();
	int wyn = 0;
	queue<pair<int,int>>q;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(pion[i] || poziom[j]){
				q.push({i,j});
				odw[i][j] = 1;
			}
		}
	}
	pair<int,int>pomoc;
	while(!q.empty()){
		pomoc = q.front();
		q.pop();
		c -= (odw[pomoc.first][pomoc.second] - 1);
		if(c >= 0)
			wyn++;
		else
			break;
		for(int i=0;i<4;i++){
			if(pomoc.first + t1[i] <= n && pomoc.first + t1[i] >= 1 
				&& pomoc.second + t2[i] <= m && pomoc.second + t2[i] >= 1
				&& !odw[pomoc.first + t1[i]][pomoc.second + t2[i]]){
				odw[pomoc.first+t1[i]][pomoc.second + t2[i]] = odw[pomoc.first][pomoc.second]+1;
				q.push({pomoc.first+t1[i], pomoc.second+t2[i]});
			}
		}
	}
	return wyn;
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);

cin>>n>>m>>z;
char stan;
for(int i=1;i<=n;i++){
	cin>>stan;
	if(stan == '+')
		pion[i] = true;
}
for(int i=1;i<=m;i++){
	cin>>stan;
	if(stan == '+')
		poziom[i] = true;
}
char typ;
int a;
long long c;
for(int L=1;L<=z;L++){
	cin>>typ;
	if(typ == 'Z'){
		cin>>c;
		cout<<bfs(c)<<"\n";
	}
	else if(typ == 'N'){
		cin>>a;
		pion[a] = !pion[a];
	}
	else{
		cin>>a;
		poziom[a] = !poziom[a];
	}
	
}
}
/*


3 4 11
--+
+++-
Z 1
M 1
M 2
M 3
Z 7
N 3
Z 1000000000000000000
M 2
N 2
Z 4
Z 1000000000000000000


*/