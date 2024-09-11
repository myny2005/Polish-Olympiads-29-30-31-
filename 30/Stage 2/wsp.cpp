#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e5+7;

int n,m,k,f[maxN];
long long dp[maxN],odjac[maxN];
bool odw[maxN],path[maxN][2];
vector<int>v[maxN];

void dfs(int x){
	odw[x] = true;
	for(int a:v[x])
		if(!odw[a])
			dfs(a);
}

long long solve_brut(int start){
	long long res = 0;
	for(int i=1;i<=n;i++)
		odw[i] = false;
	dfs(start);
	for(int i=1;i<=n;i++)
		if(odw[i])
			res += f[i];
	return res;
}

int grupa[maxN];
vector<int>maski[10];
vector<int>w_masce[maxN],poza[maxN];

/// moge nawet na 4 chyba
long long ans[maxN/2][(1 << 8)];
bool vis[10];
int res;

void dfs_seg(int x){
	//cout<<x<<"\n";
	vis[x % k] = true;
	res += (1 << (x%k));
	for(int a : w_masce[x])
		if(!vis[a])
			dfs_seg(a + k*grupa[x]);
}

int nowa_maska(int idx, int mask){
	for(int i=0;i<k;i++)
		vis[i] = false;
	res = 0;
	for(int i=0;i<k;i++)
		if(((1 << i) & mask) && !vis[i])
			dfs_seg(idx*k+i);
	return res;
}


long long w_segmencie(int idx, int mask){
	long long result = 0;
	for(int i=0;i<k;i++)
		if(((1 << i) & mask))
			result += f[idx * k + i];
	return result;
}

long long poza_segmentem(int idx, int mask){
	int maseczka = 0;
	for(int i=0;i<k;i++)
		if(((1 << i) & mask))
			for(int a:poza[idx*k+i]){
				//cout<<idx*k+i<<" ssiuuuuuuuuuuuuuu\n";
				//cout<<a<<"\n";
				maseczka |= (1 << a);
			}
	//cout<<maseczka<<" dsajflajdflajdflk\n";
	//return ans[idx+1][nowa_maska(idx+1, maseczka)];
	return ans[idx+1][maseczka];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		cin>>f[i];
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		v[a].push_back(b);
	}

	if(n <= 1000){ /// 2 subtask
		for(int i=1;i<=n;i++)
			cout<<solve_brut(i)<<"\n";
		return 0;
	}

	/// 1 subtask
	bool ok = true;
	for(int i=1;i<=n-1;i++)
		if(v[i].size() != 1)
			ok = false;
	if(ok){
		dp[n] = f[n];
		for(int i=n-1;i>=1;i--)
			dp[i] = dp[v[i].back()] + f[i];
		for(int i=1;i<=n;i++)
			cout<<dp[i]<<"\n";
		return 0;
	}

	/// 4 subtask
	if(k <= 2){ 
		for(int i=1;i<=n;i++){
			for(int a:v[i]){
				if(a == i+1)
					path[i][0] = true;
				else
					path[i][1] = true;
			}
		}
		dp[n] = f[n];
		for(int i=n-1;i>=1;i--){
			dp[i] = f[i];
			if(v[i].empty())
				continue;
			if(v[i].size() == 1){
				dp[i] += dp[v[i].back()];
				if(path[i][0])
					odjac[i] = dp[i+1];
				else
					odjac[i] = odjac[i+1];
			}
			else{
				dp[i] += dp[i+1] + dp[i+2];
				dp[i] -= odjac[i+1];
				odjac[i] = dp[i+1];
			}
		}
		for(int i=1;i<=n;i++)
			cout<<dp[i]<<"\n";
		return 0;
	}

	for(int i=1;i<=n;i++)
		grupa[i] = i/k;

	for(int i=1;i<=n;i++){
		for(int a:v[i])
			if(grupa[a] == grupa[i])
				w_masce[i].push_back(a%k);
			else
				poza[i].push_back(a%k);
	}

	for(int i=(1 << k);i>=1;i--){
		for(int j=0;j<k;j++){ /// pierwszy na lewo zapalony bit
			if(i & (1 << j)){
				maski[j].push_back(i);
				break;
			}
		}
	}


	/*
	cout<<"to sa maski\n";
	for(int i=0;i<k;i++){
		for(int a:maski[i])
			cout<<a<<' ';
		cout<<"\n";
	}
	*/

	for(int i=n;i>=1;i--){
		int L = i % k;
		for(int mask:maski[L]){
			int nowa = nowa_maska(grupa[i], mask);
			//if(i == 2)
			//	cout<<mask<<"   "<<nowa<<"      to ejst maksa i nowa\n";
			/*
			if(nowa != mask)
				ans[grupa[i]][mask] = ans[grupa[i]][nowa];
			else
			*/
			//if(i == 1)
			//	cout<<nowa<<"lalkasdfjkl;asdjflkasdfj\n";
			ans[grupa[i]][nowa] = w_segmencie(grupa[i], nowa) + poza_segmentem(grupa[i], nowa);
			ans[grupa[i]][mask] = ans[grupa[i]][nowa];
		}
	}

	//cout<<nowa_maska(grupa[3],3)<<"       blablablablbalbalbla\n";
	
	/*
	cout<<" to jest grupa\n";
	for(int i=1;i<=n;i++)
		cout<<grupa[i]<<' ';
	cout<<"\n";

	cout<<"to sa ans dla grup\n";
	for(int i=0;i<=2;i++){
		for(int j=0;j<(1 << k);j++)
			cout<<ans[i][j]<<' ';
		cout<<"\n";
	}

	cout<<";aklsdfjlkasdjfkl;sadjflk;sdjafl\n";
	cout<<w_segmencie(0, 2)<<"\n";
	cout<<poza_segmentem(0, 2)<<"\n";
	for(int a:w_masce[1])
		cout<<a<<"    tututututu      ";
	cout<<"\n";
	for(int a:poza[1])
		cout<<a<<"    essaessa      ";
	cout<<"\n";
	*/


	//cout<<"to jest ans\n";
	for(int i=1;i<=n;i++){
		int maseczka = (1 << (i % k));
		for(int a:w_masce[i])
			maseczka |= (1 << a);
		//if(i == 1){
			//cout<<maseczka<<" to jest jesjt ejjestj \n";
			//cout<<nowa_maska(grupa[i],maseczka)<<"\n";
		//}
		cout<<ans[grupa[i]][nowa_maska(grupa[i],maseczka)]<<"\n";
	}

}
/*

4 4 2
3 4 5 1
1 2
2 4
1 3
3 4

*/