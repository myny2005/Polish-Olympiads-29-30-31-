#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e6+7, INF = 1e9;

int n,q;
pair<int,int>a[maxN];

int check(vector<int>&srodek, int k){
	if(k < 0)
		return -INF;
	k /= 2;
	int res = 0;
	for(int i=0;i<min(k, (int)srodek.size());i++)
		res += srodek[i];
	return res;
}

int solve(int l, int r, int k){
	vector<int>srodek;
	int c = 0, poczatek = 0, koniec = 0;
	bool frst = true;
	for(int i=1;i<=n;i++){
		if(c + a[i].first < l){ // jeszcze to mnie nie interesuje
			c += a[i].first;
			continue;
		}
		if(c + a[i].first >= r){ // koniec
			if(a[i].second == 1){
				if(c >= l)
					koniec = r - c;
				else
					koniec = r - l + 1;
			}
			break;
		}
		if(frst){ // poczatek
			if(a[i].second == 1)
				poczatek = c + a[i].first - l + 1;
			frst = false;
			c += a[i].first;
			continue;
		}
		if(a[i].second == 1)
			srodek.push_back(a[i].first);
		c += a[i].first;
	}
	if(max(poczatek, koniec) == r - l + 1)
		return max(poczatek, koniec);
	if(k == 0)
		return 0;
	sort(srodek.begin(), srodek.end(), greater<int>());
	/*
	cout<<l<<' '<<r<<' '<<k<<"\n";
	cout<<poczatek<<' '<<koniec<<" to jest poczatek i koniec\n";
	for(int x:srodek)
		cout<<x<<' ';
	cout<<"   to jest srodek\n";
	*/
	int res = max({check(srodek,k), check(srodek,k-1) + max(poczatek, koniec), check(srodek, k-2) + koniec + poczatek});
	res = max(res, 0);
	return res;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>q;
	int liczba = 1;
	for(int i=1;i<=n;i++){
		cin>>a[i].first;
		a[i].second = liczba;
		if(liczba == 1)
			liczba = 0;
		else
			liczba = 1;
	}
	while(q--){
		int l,r,k;
		cin>>l>>r>>k;
		//cout<<solve(l,r,k)<<"     to jest ans\n";
		cout<<solve(l,r,k)<<"\n";
	}
}
/*

5 5
1 1 2 1 2
1 4 2
1 4 3
2 6 0
1 7 2
3 7 1


*/