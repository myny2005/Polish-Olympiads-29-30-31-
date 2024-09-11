/// Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 2e3+7, maxN2 = 5e5+7;

int n,Sa,Sb,q,odl[maxN][maxN],sz[maxN2],A[maxN],B[maxN];
long long ans;
pair<int,int>centr;
vector<int>v[maxN];

void dfs_odl(int x, int X, int p){
	for(int a:v[x])
		if(a != p){
			odl[X][a] = odl[X][x]+1;
			dfs_odl(a,X,x);
		}
}

void dfs_sz(int x, int p){
	sz[x] = 1;
	for(int a:v[x])
		if(a != p){
			dfs_sz(a,x);
			sz[x] += sz[a];
		}
}

bool ok(int a, int b){
	if(a == b)
		return false;
	if(odl[a][centr.first] > odl[b][centr.first])
		return false;
	if(odl[a][centr.second] > odl[b][centr.second])
		return false;
	//cout<<a<<' '<<b<<"\n";
	return true;
}






int sz2[maxN2],ODL[maxN2][2],AA[maxN2],BB[maxN2];
int mini[maxN2];
void DFS_sz(int x, int p){
	sz[x] = 1;
	for(int a:v[x])
		if(a != p){
			DFS_sz(a,x);
			sz[x] += sz[a];
		}
}

int DFS(int x, int p){
	for(int a:v[x])
		if(a != p && sz[a] * 2 >= n)
			return DFS(a,x);
	return x;
}

void DFS_odl(int x, bool gdzie){
	for(int a:v[x])
		if(!ODL[a][gdzie]){
			ODL[a][gdzie] = ODL[x][gdzie]+1;
			DFS_odl(a,gdzie);
		}
}

bool comp(int a, int b){
	return make_pair(ODL[a][0], ODL[a][1]) > make_pair(ODL[b][0], ODL[b][1]);
}

bool solve(int a, int b){
	if(a == b)
		return false;
	if(ODL[a][0] > ODL[b][0])
		return false;
	if(ODL[a][1] > ODL[b][1])
		return false;
	return true;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	if(n <= 2000){
		for(int i=1;i<=n;i++)
			dfs_odl(i,i,0);
		for(int i=1;i<=n;i++){
			dfs_sz(i,0);
			bool ok = true;
			for(int a:v[i])
				if(sz[a] * 2 > n)
					ok = false;
			if(ok){
				if(centr.first)
					centr.second = i;
				else
					centr.first = i;
			}
		}
		/*
		cout<<" to sa centroidy\n";
		cout<<centr.first<<' '<<centr.second<<"\n";
		cout<<"to sa odl\n";
		for(int i=1;i<=n;i++){
			cout<<i<<"      ";
			for(int j=1;j<=n;j++)
				cout<<odl[i][j]<<' ';
			cout<<"\n";
		}
		*/
		cin>>Sa>>Sb>>q;
		for(int i=1;i<=Sa;i++)
			cin>>A[i];
		for(int i=1;i<=Sb;i++)
			cin>>B[i];
		for(int i=1;i<=Sa;i++)
			for(int j=1;j<=Sb;j++)
				if(ok(A[i],B[j]))
					ans++;
		cout<<ans<<"\n";
		while(q--){
			char znak1,znak2,x;
			cin>>znak1>>znak2>>x;
			cout<<ans<<"\n";
		}
		return 0;
	}




	/// q=0

	DFS_sz(1,0);
	centr.first = DFS(1,0);
	for(int a:v[centr.first]){
		DFS_sz(a,centr.first);
		if(sz[a]*2 >= n)
			centr.second = a;
	}
	
	ODL[centr.first][0] = 1;
	DFS_odl(centr.first,0);
	if(centr.second){
		ODL[centr.second][1] = 1;
		DFS_odl(centr.second,1);
	}
	else{
		for(int i=1;i<=n;i++)
			ODL[i][1] = -1;
	}


	/*
	for(int i=1;i<=n;i++)
		cout<<sz[i]<<"        ;al;a;a\n";
	cout<<"to sa centroidy\n";
	cout<<centr.first<<' '<<centr.second<<"\n";
	cout<<"to sa odl\n";
	for(int i=1;i<=n;i++){
		cout<<ODL[i][0]<<' ';	
	}
	cout<<"\n";
	*/

	cin>>Sa>>Sb>>q;
	for(int i=1;i<=Sa;i++)
		cin>>AA[i];
	for(int i=1;i<=Sb;i++)
		cin>>BB[i];
	sort(BB+1, BB+1+Sb, comp);
	for(int i=1;i<=n;i++)
		mini[i] = 1000000;
	for(int i=1;i<=Sb;i++){
		mini[BB[i]] = min(mini[BB[i]], i);
	}
	//cout<<solve(AA[4], BB[3])<<" asdfkljsdalkfjasdl;kfj\n";
	//cout<<AA[4]<<' '<<BB[3]<<"\n";
	for(int i=1;i<=Sa;i++){
		int l = 1, r = Sb + 1, mid, ile=0;
		while(l != r){
			mid = (l + r)/2;
			if(solve(AA[i], BB[mid])){
				ile = mid;
				l = mid+1;
			}
			else
				r = mid;
		}
		//cout<<ile<<"\n";
		if(mini[AA[i]] <= ile)
			ile--;
		ans += ile;
	}
	cout<<ans<<"\n";	
}
/*

6
1 2
2 3
3 4
3 5
5 6
1 2 1
1
5 6
A + 2

6
1 2
2 3
3 4
3 5
5 6
2 2 1
1 2
5 6
A + 2

5
1 2
1 3
2 4
2 5
5 5 0
1 2 3 4 5
1 2 3 4 5

*/