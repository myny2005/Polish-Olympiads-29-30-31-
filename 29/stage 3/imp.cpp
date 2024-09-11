#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e3+7;

int n,t[maxN],tab[maxN],ans;
bool ok;

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);

cin>>n;
for(int i=1;i<=n;i++){
	cin>>t[i];
	tab[i] = i;
}
do{
	ok = true;
	for(int i=1;i<=n;i++){
		if(t[i] != tab[i-1] && t[i] != tab[i] && t[i] != tab[i+1]){
			ok = false;
			break;
		}
	}
	ans += ok;
}while(next_permutation(tab+1, tab+1+n));
cout<<ans<<"\n";
}
/*

4
2 4 2 1

*/