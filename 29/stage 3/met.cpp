#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 2e5+7;

int n;
long double ans,srodek;
pair<int,long double>meteor[maxN];

bool check(long double x)
{
	stack<pair<long double,long double>>s;
	stack<pair<long double,long double>>stos;
	pair<long double, long double>pomoc;
	long double m;
	s.push({0,0});
	int last = 0, dodaj;
	for(int i=1;i<=n;i++){
		m = meteor[i].second;
		dodaj = meteor[i].first - last;
		while(!s.empty()){
			pomoc = s.top();
			s.pop();
			pomoc.first -= dodaj;
			pomoc.second += dodaj;
			if(m <= pomoc.first){ /// po lewej
				pomoc.first = max(pomoc.first, m + x);
				if(pomoc.first <= pomoc.second)
					stos.push(pomoc);
			}
			else if(m >= pomoc.second){ /// po prawej 
				pomoc.second = min(pomoc.second, m - x);
				if(pomoc.first <= pomoc.second)
					stos.push(pomoc);
			}
			else if(m >= pomoc.first && m <= pomoc.second){ /// w srodku
				pair<long double, long double>essa = {pomoc.first, m-x};
				if(essa.first <= essa.second)
					stos.push(essa);
				essa = {m+x, pomoc.second};
				if(essa.first <= essa.second)
					stos.push(essa);
			}
		}
		while(!stos.empty()){
			s.push(stos.top());
			stos.pop();
		}
		last = meteor[i].first;
	}
	return (s.size() > 0);
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);


/// 2 podzadanie
cin>>n;
bool takie_same = true;
for(int i=1;i<=n;i++){
	cin>>meteor[i].first>>meteor[i].second;
	if(i >= 2 && meteor[i].first != meteor[i-1].first)
		takie_same = false;
}
sort(meteor+1,meteor+1+n);
if(takie_same){
	int j = 0; /// pierwszy ujemny
	while(meteor[j+1].second < 0)
		j++;
	meteor[n+1].second = 1e9+7;
	if(j > 0){
		if(j != n){ /// stoje w punkcie 0
			ans = min(ans, min(fabs(meteor[j].second), meteor[j+1].second));
			
			srodek = (meteor[j].second + meteor[j+1].second)/2;
			if(srodek < 0)
				srodek = max(srodek, (long double)-meteor[j].first);
			else
				srodek = min(srodek, (long double)meteor[j].first);
			//cout<<srodek<<" to jest srodek\n";
			ans = max(ans, min(fabs(meteor[j].second - srodek), fabs(meteor[j+1].second - srodek)));
			
		}
		else
			ans = max(ans, meteor[n].first - meteor[n].second);
	}
	else
		ans = max(ans, meteor[1].second + meteor[1].first);
	if(meteor[n].second < meteor[n].first)
		ans = max(ans, meteor[n].first - meteor[n].second);
	if(fabs(meteor[1].second) < meteor[1].first)
		ans = max(ans, meteor[1].first - fabs(meteor[1].second));

	for(int i=j;i>=2;i--){
		if(-meteor[i].second >= meteor[i].first)
			break;
		srodek = (meteor[i-1].second + meteor[i].second)/2;
		srodek = max(srodek, (long double)-meteor[i].first);
		ans = max(ans, min(fabs(meteor[i-1].second - srodek), fabs(meteor[i].second - srodek)));
	}

	if(j != n){
		srodek = meteor[j+1].second/2;
		srodek = min(srodek, (long double)meteor[j+1].first);
		ans = max(ans, srodek);
	}

	for(int i=j+1;i<n;i++){
		if(meteor[i].second >= meteor[i].first)
			break;
		srodek = (meteor[i+1].second + meteor[i].second)/2;
		srodek = min(srodek, (long double)meteor[i].first);
		ans = max(ans, min(fabs(meteor[i+1].second - srodek), fabs(meteor[i].second - srodek)));
	}
	if((int)ans == ans)
		cout<<(int)ans<<"\n";
	else
		cout<<fixed<<setprecision(1)<<ans<<"\n";
	return 0;
}
long long l = 0, r = 2e9+2000, mid;
long double zmienna;
while(l != r){
	mid = (l + r)/2;
	zmienna = (long double)mid + 0.5;
	if(check(zmienna - 0.5)){
		l = mid+1;
		ans = mid;
		if(check(zmienna))
			ans = zmienna;
	}
	else
		r = mid;
}
if((int)ans == ans)
	cout<<(int)ans<<"\n";
else
	cout<<fixed<<setprecision(1)<<ans<<"\n";
}
/*

3
5 1
5 3
5 -5

2
1 -1
1 1



6
0 42
0 68
0 -42
0 -76
0 2
0 14

3
5 -3
7 6
4 -4

*/