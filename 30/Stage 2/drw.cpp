/// Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e6+7;

int n,t[maxN],ans,suma;
bool knapsack[maxN];

int solve(){
	int A=0,B=0;
	for(int i=1;i<=n;i++){
		if(A <= B)
			A += t[i];
		else
			B += t[i];
	}
	return max(A,B);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>t[i];
	sort(t+1, t+1+n);

	/// 1 subtask
	if(n <= 10){
		do{
			ans = max(ans, solve());
		}while(next_permutation(t+1, t+1+n));
		cout<<ans<<"\n";
		return 0;
	}

	/// 2,3 subtask
	for(int i=1;i<n;i++)
		suma += t[i];
	knapsack[0] = true;
	suma /= 2;
	for(int i=1;i<n;i++)
		for(int j=suma;j>=t[i];j--)
			knapsack[j] |= knapsack[j-t[i]];
	int maks = 0;
	for(int i=suma;i>=0;i--){
		if(knapsack[i]){
			maks = i;
			break;
		}
	}
	cout<<maks + t[n]<<"\n";
}
/*

3
2 3 1

6
1 2 3 4 5 6

*/