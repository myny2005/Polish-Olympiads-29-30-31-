#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e4+7, nax = 1e5;

int n,m,k,a[maxN],ans,dp[nax][101];
map<vector<int>,int>mapa;

bool git(int x, int digit){
	for(int i=1;i<k;i++){
		if(digit == x % 10)
			return false;
		x /= 10;
	}
	return true;
}

int zmiana(int x, int digit){
	int piersza = x / 10000;
	x -= ((x / 10000) * 10000);
	x *= 10;
	x += digit;
	return x;
}

bool ok(vector<int>essa, int c){
	for(int x : essa)
		if(x == c)
			return false;
	return true;
}

vector<int>nowy_wektor(vector<int>essa, int c){
	vector<int>res;
	for(int i=1;i<essa.size();i++)
		res.push_back(essa[i]);
	res.push_back(c);
	return res;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	if(k == 2){
		deque<int>dq;
		for(int j=1;j<=n;j++){
			int c = a[j];
			bool ok = true;
			if(dq.size() == k){
				for(int i=1;i<k;i++)
					if(dq[i] == c)
						ok = false;
				if(ok){
					ans++;
					dq.push_back(c);
					dq.pop_front();
				}
			}
			else{
				for(int i=0;i<dq.size();i++)
					if(dq[i] == c)
						ok = false;
				if(ok){
					ans++;
					dq.push_back(c);
				}
			}
		}
		cout<<ans<<"\n";
		return 0;
	}
	if(n <= 100 && m <= 10 && k == 5){
		for(int i=1;i<=n;i++){
			int c = a[i] - 1;
			for(int j=0;j<nax;j++){
				dp[j][i] = max(dp[j][i-1], dp[j][i]);
				if(git(j,c)){
					int nowe = zmiana(j,c);
					dp[nowe][i] = max(dp[nowe][i], dp[j][i-1] + 1);
				}
			}
		}
		for(int i=1;i<nax;i++)
			ans = max(ans, dp[i][n]);
		cout<<ans<<"\n";
		return 0;
	}
	vector<int>poczatek(k-1,0);
	mapa[poczatek] = 0;
	for(int i=1;i<=n;i++){
		int c = a[i];
		vector<pair<vector<int>, int>>nowiuskie;
		vector<vector<int>>usuwasne;
		for(auto essa : mapa){
			if(ok(essa.first, c)){
				int wyniczek = mapa[essa.first] + 1;
				nowiuskie.push_back({nowy_wektor(essa.first,c), wyniczek});


				/*
				cout<<" to jest nowy wektor\n";
				for(int x : nowy_wektor(essa.first,c))
					cout<<x<<' ';
				cout<<"\n";
				*/


				ans = max(ans, wyniczek);
			}
		}
		for(auto essa : mapa)
			if(essa.second <= ans-k)
				usuwasne.push_back(essa.first);
		for(vector<int>usun : usuwasne)
				mapa.erase(usun);
		for(pair<vector<int>,int>dodaj : nowiuskie){

			/*
			cout<<dodaj.second<<"	to jest to\n";	
			for(int x : dodaj.first)
				cout<<x<<"  ";
			cout<<"\n";
			*/

			mapa[dodaj.first] = dodaj.second;
		}
	}
	cout<<ans<<"\n";
}
/*

8 4 3
1 1 2 1 3 4 4 2

4 2 2
1 2 2 1

10 2 3
1 0 1 0 1 0 1 0 1 0

10 10 5
1 2 3 4 5 6 7 8 9 9

5 3 3
1 2 1 3 2

3 3 3
1 2 3

*/