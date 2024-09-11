/// Michal Szydlo
/// zadanie: CHA

#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxN = 1e6+7, Mod = 1e9+7;
constexpr pair<int,int>prime = {3823, 2137};

int n,k,a,b,leader[200];
string s;
pair<int,int>pot[4*maxN],hasz[4*maxN];
map<pair<int,int>,char>lit;
map<pair<int,int>,int>Last;

void pre(){
	s = '!' + s;
	pot[0] = {1,1};
	for(int i=1;i<=4000010;i++){
		pot[i].first = pot[i-1].first * prime.first % Mod;
		pot[i].second = pot[i-1].second * prime.second % Mod;
	}
	for(int i=1;i<=n;i++){
		hasz[i].first = (hasz[i-1].first * prime.first + s[i]) % Mod;
		hasz[i].second = (hasz[i-1].second * prime.second + s[i]) % Mod;
	}
}

pair<int,int>hash_val(int i, int j){
	pair<int,int>res = {0,0}; 
	res.first = (hasz[j].first - hasz[i-1].first * pot[j-i+1].first) % Mod;
	res.second = (hasz[j].second - hasz[i-1].second * pot[j-i+1].second) % Mod;
	if(res.first < 0)
		res.first += Mod;
	if(res.second < 0)
		res.second += Mod;
	return res;
}

bool comp(int x, int y){
	return hash_val(x,x+k-1) < hash_val(y,y+k-1);
}

bool litera(char LIT){
	return (LIT >= 'a' && LIT <= 'z');
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>k>>a>>b;
	cin>>s;
	pre();
	vector<int>all;
	for(int i=1;i<=n-k;i++)
		all.push_back(i);
	sort(all.begin(), all.end(), comp);
	stack<int>S;
	for(int i=0;i<(int)all.size();i++){
		S.push(all[i]);
		/// tutaj i == all.size()-1
		if(i == (int)all.size()-1 || hash_val(all[i], all[i]+k-1) != hash_val(all[i+1], all[i+1]+k-1)){ /// tutaj zmiana byla
			for(int j='a';j<='z';j++)
				leader[j] = 0;
			while(!S.empty()){
				int x = S.top();
				S.pop();
				leader[s[x+k]]++;
			}
			char lead = 'a';
			for(int j='b';j<='z';j++)
				if(leader[j] > leader[lead])
					lead = j;
			lit[hash_val(all[i], all[i]+k-1)] = lead;
			//cout<<hash_val(all[i], all[i]+k-1).first<<' '<<lead<<"     to jest nastepnik\n";
		}
	}
		
	/*
	cout<<"to jest haszyk\n";
	for(int i=1;i<=n-k;i++)
		cout<<hash_val(i, i+k-1).first<<' ';
	cout<<"\n";
	*/
	
	int N = n;
	while(N < b){
		int x = Last[hash_val(N-k+1,N)];
		//cout<<x<<' '<<hash_val(N-k+1,N).first<<" to jest x\n";
		if(x){
			int cycle_sz = N - x;
			string cycle = "", cycle_copy="";
			for(int i=x+1;i<=N;i++)
				cycle.push_back(s[i]);
			cycle_copy = cycle;
			if(a <= N){
				for(int i=a;i<=N;i++)
					cout<<s[i];
				a = N+1;
			}
			int dl = b - a + 1;
			int dl_cycle = cycle.size();
			int essa = (a - N - 1) % dl_cycle; /// ktore zaczynam w cycle
			//cout<<essa<<"\n";
			//cout<<dl<<"\n";
			//cout<<cycle.size()<<"\n";
			while((int)cycle.size() - essa <= dl + cycle_copy.size())
				cycle += cycle_copy;
			//cout<<cycle.size()<<"\n";
			//cout<<cycle_copy<<"\n";
			
			while(dl--)
				cout<<cycle[essa++];
			cout<<"\n";
			return 0;
		}
		char add_letter = 'a';
		if(litera(lit[hash_val(N-k+1,N)]))
			add_letter = lit[hash_val(N-k+1,N)];
		hasz[N+1].first = (hasz[N].first * prime.first + add_letter) % Mod;
		hasz[N+1].second = (hasz[N].second * prime.second + add_letter) % Mod;
		s.push_back(add_letter);
		Last[hash_val(N-k+1,N)] = N;
		N++;
	}
	//cout<<s<<"       to jest s\n";
	for(int i=a;i<=b;i++)
		cout<<s[i];
	cout<<"\n";
}
/*
 
11 3 12 13
abaaabababa

20 3 30 40
abcdabcdabcdabcdabcd

5 3 6 10
aaaaa

*/
