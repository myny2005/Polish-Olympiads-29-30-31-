/// Michal Szydlo
/// zadanie ZAP

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e5+7;

int n;
bool taken[maxN];
pair<int,int>skal[maxN*2];

struct seg{
	int l,r,idx;
}s[maxN];

bool comp(seg a, seg b){
	return make_pair(a.r, -a.l) < make_pair(b.r, -b.l);
}

void wypisz(vector<pair<int,int>>lelelele){
	cout<<lelelele.size()<<"\n";
	for(auto x:lelelele)
		cout<<x.first<<' '<<x.second<<"\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
   
    cin>>n;
    for(int i=1,l,r;i<=n;i++){
		cin>>l>>r;
		skal[i].first = l;
		skal[i].second = i;
		skal[i+n].first = r;
		skal[i+n].second = i;
		s[i].idx = i;
	}
	
	/// skalowanie danych
	sort(skal+1, skal+1+2*n);
	int K = 0;
	for(int i=1;i<=2*n;i++){
		if(skal[i].first != skal[i-1].first)
			K++;
		if(s[skal[i].second].l)
			s[skal[i].second].r = K;
		else
			s[skal[i].second].l = K;
	}
	sort(s+1, s+1+n, comp);
	
	/// wszyskie rozlaczne i ostatni to zamiennik kazdego
	vector<pair<int,int>>ans1;
	int last = 0;
	for(int i=1;i<=n;i++){
		if(last <= s[i].l){
			ans1.push_back({s[i].idx, -123});
			last = s[i].r;
		}
	}
	
	last = ans1.back().first;
	ans1.pop_back();
	for(auto &x : ans1)
		x.second = last;
	vector<pair<int,int>>ans2;
	int last_max = 0, last_min = 0, j = 1;
	for(int i=1;i<=n;i++){
		if(s[i].l >= last_max && !taken[i]){
			taken[i] = true;
			while(taken[j] || s[j].l < last_min){
				j++;
				if(j == n+1)
					break;
			}
			if(j == n+1)
				break;
			taken[j] = true;
			ans2.push_back({s[i].idx, s[j].idx});
			last_min = s[i].r;
			last_max = max(s[j].r, s[i].r);
		}
	}
	if((int)ans1.size() >= (int)ans2.size())
		wypisz(ans1);
	else
		wypisz(ans2);
}
/*

8
1 5
3 10
4 8
9 12
11 16
14 15
20 22
15 21

5
1 2
2 3
3 4
4 5
5 6

5
2 7
4 7
6 8
1 5
2 3

*/	
