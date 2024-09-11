/// Michal Szydlo
/// zadanie SAT

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e3+7, Mod = 1e9+7;
constexpr pair<long long,long long>prime = {1031, 2137};

int n,p,m,grupa[2*maxN];
bool naprawa[2*maxN],przerobione[2*maxN],vis[2*maxN]; /// to jest potrzebne do dfsa;
bool added[3*maxN][3*maxN];
vector<int>v[2*maxN],v_grupy[2*maxN],grupy[2*maxN],A,B;
vector<char>ans[2*maxN],ans_a[2*maxN],ans_b[2*maxN];
//map<vector<int>,vector<int>>mp1,mp2;
map<pair<int,int>, vector<int>>mp1,mp2;

/*
void clean(){
	A.clear(), B.clear();
	mp1.clear(), mp2.clear();
	for(int i=1;i<=2*n;i++){
		v[i].clear(); /// vector int
		v_grupy[i].clear();
		grupy[i].clear();
		grupa[i] = 0; /// int
		naprawa[i] = 0; /// boole
		przerobione[i] = 0;
		vis[i] = 0;
		ans[i].clear(); /// vector chary
		ans_a[i].clear();
		ans_b[i].clear();
	}
}
* */

void insert_col(){
	for(int i=1;i<=n;i++){
		ans[i].push_back('A');
		ans[i+n].push_back('B');
	}
}

void insert_col_a(){
	for(int i=1;i<=n;i++){
		ans_a[i].push_back('A');
		ans_a[i+n].push_back('B');
	}
}
void insert_col_b(){
	for(int i=1;i<=n;i++){
		ans_b[i].push_back('A');
		ans_b[i+n].push_back('B');
	}
}

void wyrownaj(){
	int maks_dl = 0;
	for(int i=1;i<=2*n;i++)
		maks_dl = max(maks_dl, (int)ans[i].size());
	for(int i=1;i<=n;i++)
		while((int)ans[i].size() < maks_dl)
			ans[i].push_back('A');
	for(int i=n+1;i<=2*n;i++)
		while((int)ans[i].size() < maks_dl)
			ans[i].push_back('B');
}

void dfs(int x){
	vis[x] = true;
	if(!przerobione[grupa[x]]){
		if(x <= n)
			A.push_back(grupa[x]);
		else
			B.push_back(grupa[x]);
	}
	przerobione[grupa[x]] = true;
	for(int a : v[x])
		if(!vis[a])
			dfs(a);
}

void solve(){
	/*
	cout<<" to jes teraz spojna\n";
	for(int a:A)
		cout<<a<<' ';
	cout<<"\n";
	for(int b:B)
		cout<<b<<' ';
	cout<<"\n";
	*/
	for(int i=1;i<=2*n;i++){
		ans_a[i].clear();
		ans_b[i].clear();
	}
	//int licznik = 0;
	for(int i : A){
		insert_col_a();
		//cout<<i<<" to jest i\n";
		for(int x:v_grupy[i]){
			
			for(int satelita : grupy[i]){
				//licznik++;
				ans_a[satelita].pop_back();
				ans_a[satelita].push_back('C');
			}
			for(int satelita : grupy[x]){
				//licznik++;
				ans_a[satelita].pop_back();
				ans_a[satelita].push_back('C');
			}
		}
	}
	//cout<<licznik<<"                    to jest licnzik\n";
	for(int i : B){
		//cout<<i<<" to jest i   w B\n";
		insert_col_b();
		for(int x:v_grupy[i]){
			for(int satelita : grupy[i]){
				ans_b[satelita].pop_back();
				ans_b[satelita].push_back('C');
			}
			for(int satelita : grupy[x]){
				ans_b[satelita].pop_back();
				ans_b[satelita].push_back('C');
			}
		}
	}
	if((int)ans_a[1].size() <= (int)ans_b[1].size()){
		for(int i=1;i<=2*n;i++)
			for(int j=0;j<(int)ans_a[i].size();j++)
				ans[i].push_back(ans_a[i][j]);
	}
	else{
		for(int i=1;i<=2*n;i++)
			for(int j=0;j<(int)ans_b[i].size();j++)
				ans[i].push_back(ans_b[i][j]);
	}
}

pair<int,int>haszuj_vector(vector<int>wektorek){
	pair<long long,long long>res = {0,0};
	for(int x:wektorek){
		res.first = (res.first * prime.first + x) % Mod;
		res.second = (res.second * prime.second + x) % Mod;
	}
	return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
   
		cin>>n>>p>>m;
		for(int i=1,a,b;i<=p;i++){
			cin>>a>>b;
			//a += n, b -= n;
			v[a].push_back(b);
			v[b].push_back(a);
		}
		
		/// mam dwie mapy bo moze byc tak ze zbior wierzcholkow wchodzi do pustego zbioru
		for(int i=1;i<=n;i++){
			sort(v[i].begin(), v[i].end());
			mp1[haszuj_vector(v[i])].push_back(i);
		}
		for(int i=n+1;i<=2*n;i++){
			sort(v[i].begin(), v[i].end());
			mp2[haszuj_vector(v[i])].push_back(i);
		}
		int idx = 0, koniec_a;
		for(auto grupencja : mp1){
			vector<int>te_same = grupencja.second;
			idx++;
			for(int satelity : te_same){
				grupa[satelity] = idx;
				grupy[idx].push_back(satelity);
			}
			A.clear();
			for(int i=1;i<(int)te_same.size();i++)
				A.push_back(te_same[i]);
			if(!A.empty()){
				int bit = 0;
				while((2 << bit) - 1 < A.size())
					bit++;
				int c = 1;
				for(int x:A){
					for(int i=0;i<=bit;i++){
						if((1 << i) & c)
							ans[x].push_back('C');
						else
							ans[x].push_back('A');
					}
					c++;
				}
			}
		}
		/// zapomnialem wyrownac
		wyrownaj();
		
		koniec_a = idx;
		for(auto grupencja : mp2){
			vector<int>te_same = grupencja.second;
			idx++;
			for(int satelity : te_same){
				grupa[satelity] = idx;
				grupy[idx].push_back(satelity); /// zmiana z satelity
			}
			B.clear();
			for(int i=1;i<(int)te_same.size();i++)
				B.push_back(te_same[i]);
			if(!B.empty()){
				int bit = 0;
				while((2 << bit) - 1 < B.size())
					bit++;
				int c = 1;
				for(int x:B){
					for(int i=0;i<=bit;i++){
						if((1 << i) & c)
							ans[x].push_back('C');
						else
							ans[x].push_back('B');
					}
					c++;
				}
			}
		}
		wyrownaj();
		

		for(int i=1;i<=2*n;i++){
			for(int x:v[i]){
				if(!added[grupa[i]][grupa[x]]){
					added[grupa[i]][grupa[x]] = true;
					v_grupy[grupa[i]].push_back(grupa[x]);
				}
			}
		}
		for(int i=1;i<=idx;i++)
			sort(v_grupy[i].begin(), v_grupy[i].end());
		
		/*
		/// debug
		for(int i=1;i<=2*n;i++)
			cout<<grupa[i]<<' ';
		cout<<"\n";
		for(int i=1;i<=idx;i++){
			cout<<i<<"   nr grupki:   ";
			for(int essa : v_grupy[i])
				cout<<essa<<' ';
			cout<<"\n";	
		}
		*/
		
		/// tutaj teraz tylko musze zrobic;
		for(int i=1;i<=n;i++){
			if(!vis[i] && v[i].size()){
				//cout<<i<<' '<<"tutaj zaczynam dfsa\n";
				A.clear();
				B.clear();
				dfs(i);
				solve();
			}
		}
		
		/// dla pewnosci
		if((int)ans[1].size() <= n)
			insert_col();
		cout<<ans[1].size()<<"\n";
		for(int i=1;i<=2*n;i++){
			for(char x:ans[i])
				cout<<x;
			cout<<"\n";
		}
}

/*

3 4 4
1 4
2 6
3 4
3 6

2 4 3
1 3
1 4
2 3
2 4

6 27 7
1 7
1 8
1 9
2 7
2 8
2 9
3 7
3 8
3 9
4 7
4 8
4 9
5 7
5 8
5 9
6 7
6 8
6 9
1 10
2 11
3 12
4 10
4 11
5 10
5 12
6 11
6 12

3 7 4
1 4
2 4
3 4
1 5
2 5
3 5
3 6

3 3 4
2 6
1 6
3 5


*/	

