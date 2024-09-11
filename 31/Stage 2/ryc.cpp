#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e4+7, maxK = 15, INF = 1e9, Mod = 998244353, prime = 2137, Mod2 = 1e9+7;

int n,m,d,k,dist_bfs[maxN][2];
int per[] = {0,1,2,3,4,5};
long long pot[maxK];
vector<int>best[maxN],n_best[maxN],ans_1;

struct Edge{
	int b;
	vector<int>val;
	void read(){
		for(int i=0,V;i<k;i++){
			cin>>V;
			val.push_back(V);
		}
	}
}e[maxN];
vector<Edge>v[maxN];
vector<pair<pair<int,int>,Edge>>All;

void bfs(int start, int bit){
	for(int i=1;i<=n;i++)
		dist_bfs[i][bit] = INF;
	dist_bfs[start][bit] = 0;
	queue<int>q;
	q.push(start);
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(auto a:v[x]){
			if(dist_bfs[a.b][bit] == INF){
				dist_bfs[a.b][bit] = dist_bfs[x][bit] + 1;
				q.push(a.b);
			}
		}
	}
}

vector<int>merge(vector<int>x, vector<int>y){
	for(int i=0;i<k;i++)
		x[i] = max(x[i], y[i]);
	return x;
}

vector<int>maksi(vector<int>x, vector<int>y){
	for(int i=0;i<k;i++){
		if(x[per[i]] < y[per[i]])
			return y;
		else if(x[per[i]] > y[per[i]])
			return x;
	}
	return x;
}

bool lepsze_leksykograficznie(vector<int>x, vector<int>y){
	for(int i=0;i<k;i++){
		if(x[i] > y[i])
			return true;
		else if(x[i] < y[i])
			return false;
	}
	return true;
}

long long haszuj(vector<int>essa){
	long long res = 0, sum = 0;
	for(int i=0;i<k;i++){
		res += pot[i] * essa[i];
		sum += essa[i] * 5;
		sum %= Mod2;
		res %= Mod;
	}
	res = res * sum % Mod;
	return res;
}

map<pair<int,int>, bool>mapka;
void solve(int x, int D, vector<int>curr){
	//if(x ==5)
	//cout<<x<<' '<<D<<' '<<haszuj(curr)<<"    ";
	for(int xx : curr)
		cout<<xx<<' ';
	cout<<"\n";
	if(x == n && lepsze_leksykograficznie(curr, ans_1))
		ans_1 = curr;
	if(D == d)
		return;
	for(Edge a : v[x]){
		vector<int>essa = merge(curr, a.val);
		long long haszyk = haszuj(essa);
		bool odwiedzone = mapka[{a.b,haszyk}];
		if(!odwiedzone){
			 mapka[{a.b,haszyk}] = true;
			 solve(a.b,D+1,essa);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m>>d>>k;
	for(int i=1,a,b;i<=m;i++){
		cin>>a>>b;
		Edge E;
		E.read();
		All.push_back({{a,b}, E});
		E.b = b;
		v[a].push_back(E);
		E.b = a;
		v[b].push_back(E);
	}
	if(k == 1){
		bfs(1,0);
		bfs(n,1);
		/*
		for(int i=1;i<=n;i++)
			cout<<dist_bfs[i][0]<<' ';
		cout<<"\n";
		for(int i=1;i<=n;i++)
			cout<<dist_bfs[i][1]<<' ';
		cout<<"\n";
		*/
		int res = 0;
		for(int i=1;i<=n;i++)
			for(auto a : v[i])
				if(dist_bfs[i][0] + dist_bfs[a.b][1] + 1 <= d)
					res = max(res, a.val[0]);
		cout<<res<<"\n";
		return 0;
	}

	if(k <= 5){
		/// dla malego k dziala
		bfs(1,0);
		vector<int>ans_3;
		ans_3.assign(k,0);
		do{
			for(int i=1;i<=n;i++)
				best[i].assign(k,0);
			for(int licznik=1;licznik<=d;licznik++){
				for(int i=1;i<=n;i++)
					n_best[i] = best[i];
				for(pair<pair<int,int>,Edge>x : All){
					//cout<<n_best[x.first.first].size()<<' '<<best[x.first.second].size()<<' '<<x.second.val.size()<<"\n";
					if(dist_bfs[x.first.second][0] < licznik)
						n_best[x.first.first] = maksi(n_best[x.first.first], merge(best[x.first.second], x.second.val));
					if(dist_bfs[x.first.first][0] < licznik)
						n_best[x.first.second] = maksi(n_best[x.first.second], merge(best[x.first.first], x.second.val));
				}
				for(int i=1;i<=n;i++)
					best[i] = n_best[i];
				/*
				for(int i=1;i<=n;i++){
					cout<<i<<"    ";
					for(int j=0;j<k;j++)
						cout<<best[i][j]<<' ';
					cout<<"\n";
				}
				*/
			}
			if(lepsze_leksykograficznie(best[n], ans_3))
				ans_3 = best[n];
		}while(next_permutation(per, per+k));
		//cout<<"to jest ans\n";
		for(int x : ans_3)
			cout<<x<<' ';
		cout<<"\n";
		return 0;
	}

	pot[0] = 1;
	for(int i=1;i<k;i++)
		pot[i] = pot[i-1] * prime % Mod;
	ans_1.assign(k,0);
	queue<tuple<int,int,vector<int>>>Q;
	Q.push({1,0,ans_1});
	//solve(1,0,ans_1);
	while(!Q.empty()){
		auto [x,D,curr] = Q.front();
		Q.pop();

		/*
		cout<<x<<' '<<D<<' '<<haszuj(curr)<<"    ";
		for(int xx : curr)
			cout<<xx<<' ';
		cout<<"\n";
		*/

		if(x == n && lepsze_leksykograficznie(curr, ans_1))
			ans_1 = curr;
		if(D == d)
			break;
		for(Edge a : v[x]){
			vector<int>essa = merge(curr, a.val);
			long long haszyk = haszuj(essa);
			bool odwiedzone = mapka[{a.b,haszyk}];
			if(!odwiedzone){
				 mapka[{a.b,haszyk}] = true;
				 Q.push({a.b,D+1,essa});
			}
		}
	}
	for(int x : ans_1)
		cout<<x<<' ';
	cout<<"\n";
}
/*

4 4 2 3
1 2 1 2 2
1 3 5 3 3
2 3 10 4  3
2 4 5 5 1

7 7 6 2
1 2 7 9
2 7 1 0
1 3 5 6
3 4 10 1
4 7 0 0
5 6 2 17
5 7 3 15

*/