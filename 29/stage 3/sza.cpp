#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e3+7, Mod = 1e9+7, prime1=29, prime2=31;

int n,maks[maxN];
string s;
pair<long long,long long>pot[maxN], h[maxN], wzor1, wzor2;
vector<int>ans;

void ustaw(int x)
{
	for(int i=1;i<=n;i++)
		maks[i] = 0;
	wzor1 = {0,0};
	wzor2 = {0,0};
	for(int i=1;i<=x;i++){
		wzor1.first = (wzor1.first * prime1 + s[i]) % Mod;
		wzor1.second = (wzor1.second * prime2 + s[i]) % Mod;
	}	
	for(int i=x;i>=1;i--){
		wzor2.first = (wzor2.first * prime1 + s[i]) % Mod;
		wzor2.second = (wzor2.second * prime2 + s[i]) % Mod;
	}
}

pair<int,int> hasz(int i, int j)
{
	pair<int, int>wyn;
	wyn.first = (h[j].first - h[i-1].first * pot[j-i+1].first) % Mod;
	if(wyn.first < 0)
		wyn.first += Mod;
	wyn.second = (h[j].second - h[i-1].second * pot[j-i+1].second) % Mod;
	if(wyn.second < 0)
		wyn.second += Mod;
	return wyn;
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);

cin>>s;
n = s.size();
s = '!' + s;
pot[0] = {1,1};
for(int i=1;i<=n;i++){
	s[i] = s[i] - 'a' + 1;

	pot[i].first = (pot[i-1].first * prime1) % Mod;
	pot[i].second = (pot[i-1].second * prime2) % Mod;

	h[i].first = (h[i-1].first * prime1 + s[i]) % Mod;
	h[i].second = (h[i-1].second * prime2 + s[i]) % Mod;
}
bool ok;
pair<int,int>pomoc;
/*
for(int i=1;i<=n;i++)
	cout<<h[i].first<<' ';
cout<<"\n";
pomoc = hasz(12,16);
*/
for(int i=1;i<=n;i++){
	ustaw(i);
	//cout<<i<<"      "<<wzor1.first<<' '<<wzor1.second<<"      "<<wzor2.first<<' '<<wzor2.second<<"  to sa wzory\n";
	ok = true;
	for(int j=1;j<=n-i+1;j++){
		if(maks[j-1] > 1)
			maks[j] = maks[j-1]-1;
		pomoc = hasz(j, j+i-1);
		if(pomoc.first == wzor1.first && pomoc.second == wzor1.second)
			maks[j] = i;
		else if(pomoc.first == wzor2.first && pomoc.second == wzor2.second)
			maks[j] = i;
		if(!maks[j]){
			ok = false;
			break;
		}
	}
	for(int j=n-i+2;j<=n;j++){
		if(maks[j-1] > 1)
			maks[j] = maks[j-1]-1;
		if(!maks[j]){
			ok = false;
			break;
		}
	}
	if(ok)
		ans.push_back(i);
	/*
	if(i == 5){
		cout<<"to jest dla 5\n";
		for(int j=1;j<=n;j++)
			cout<<maks[j]<<' ';
		cout<<"\n";
	}
	*/
}
for(int a:ans)
	cout<<a<<' ';
cout<<"\n";
}
/*

abcabcabacbabcab

*/