/// Michal Szydlo     	O(d)

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 2e5+7;

int n;
long long d;
bool t[maxN];
deque<bool>dq;

void wypisz(){
	for(int i=0;i<dq.size();i++)
		cout<<dq[i];
	cout<<"\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>d;
	for(int i=1;i<=n;i++){
		char a;
		cin>>a;
		t[i] = (a == '1');
	}
	for(long long i=1;i<=d/n;i++){
		t[n+1] = (t[1] ^ t[2]);
		for(int j=1;j<=n;j++)
			t[j] ^= t[j+1];
 	}
	d = d % n;
	for(int i=1;i<=n;i++)
		dq.push_back(t[i]);
	for(int i=1;i<=d;i++){
		dq.push_back((dq[0] ^ dq[1]));
		dq.pop_front();
	}
	wypisz();
}
/*

5 4
01010


*/