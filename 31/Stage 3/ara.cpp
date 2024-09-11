#include <bits/stdc++.h>
using namespace std;

int licznik;
long long a,b;
char ans[50];
__int128 wyn;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T;
	cin>>T;
	while(T--){
		cin>>a>>b;
		wyn = a;
		wyn *= b;
		licznik = 0;
		while(wyn > 0){
			ans[licznik++] = wyn - wyn / 10 * 10;
			wyn /= 10;
		}
		for(int i=licznik-1;i>=0;i--){
			ans[i] += '0';
			cout<<ans[i];
		}
		cout<<"\n";
	}
}
/*

2
1 1
3 5

1
1000000000000000000
1000000000000000000

*/
