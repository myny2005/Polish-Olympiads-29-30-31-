/// Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e5+7, Mod = 1001;
constexpr long long INF = 1e18;

long long n,dp[maxN];
int d,a,b,cena[Mod][Mod];
map<long long,long long>mapa;

void oblicz_cene(){
	for(int i=0;i<=1000;i++)
		for(int j=0;j<=1000;j++)
			cena[i][j] = min(cena[i][j], cena[j][i]);
}

long long kopia;
long long solve(long long x){
	if(x <= 1)
		return 0;
	kopia = mapa[x];
	if(kopia)
		return kopia;
	mapa[x] = INF;
	long long p1,p2,res=INF;
	if(x % 2 == 0){
		for(int j=0;j<=d;j+=2){
			p1 = x/2 + j/2;
			p2 = x/2 - j/2;
			if(p1 - p2 > d)
				break;
			if(p1 >= x || p2 <= 0)
				break;
			res = min(res, solve(p1) + solve(p2) + cena[p1%Mod][p2%Mod]);
		}
	}
	else{
		for(int j=0;j<=d;j+=2){
			p1 = x/2 + j/2 + 1;
			p2 = x/2 - j/2;
			if(p1 - p2 > d)
				break;
			if(p1 >= x || p2 <= 0)
				break;
			res = min(res, solve(p1) + solve(p2) + cena[p1%Mod][p2%Mod]);
		}
	}
	if(res < mapa[x])
		mapa[x] = res;
	return mapa[x];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>d>>a>>b;
	for(int i=0;i<=1000;i++)
		for(int j=0;j<=1000;j++)
			cena[i][j] = (a*i + b*j) % Mod;
	if(n <= 100000){
		int polowa,p1,p2;
		for(int i=2;i<=n;i++){
			dp[i] = INF;
			polowa = i/2;
			if(i % 2 == 0){
				for(int j=0;j<=d;j+=2){
					p1 = polowa + j/2;
					p2 = polowa - j/2;
					if(p1 - p2 > d)
						break;
					if(p1 >= i || p2 <= 0)
						break;
					dp[i] = min(dp[i], dp[p1] + dp[p2] + cena[p1%Mod][p2%Mod]);
					dp[i] = min(dp[i], dp[p1] + dp[p2] + cena[p2%Mod][p1%Mod]);
				}
			}
			else{
				for(int j=0;j<=d;j+=2){
					p1 = polowa + j/2+1;
					p2 = polowa - j/2;
					if(p1 - p2 > d)
						break;
					if(p1 >= i || p2 <= 0)
						break;
					dp[i] = min(dp[i], dp[p1] + dp[p2] + cena[p1%Mod][p2%Mod]);
					dp[i] = min(dp[i], dp[p1] + dp[p2] + cena[p2%Mod][p1%Mod]);
				}
			}
		}
		cout<<dp[n]<<"\n";
		return 0;
	}
	oblicz_cene();
	cout<<solve(n)<<"\n";
}
/*

5 1 1 1

100000 1000 3 5

*/
