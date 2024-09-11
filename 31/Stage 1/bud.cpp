/// Michal Szydlo
/// zadanie BUD

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1500+7;

int n,m,pref[maxN][maxN],suf[maxN][maxN],dp1[maxN][maxN],dp2[maxN][maxN],pion[maxN][maxN],ans;
bool done[maxN][maxN];
char t[maxN][maxN];

bool solve(int mid){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(pion[i][j] >= mid && max({dp1[i-1][n], dp1[n][j-1], dp2[i+mid][1], dp2[1][j+1]}) >= mid)
				return true;
	return false;
}	


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
   
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>t[i][j];
    
    int maks_poziome=0;
    /// pref poziome i dp1
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(t[i][j] == '.'){
                pref[i][j] = pref[i][j-1]+1;
                maks_poziome = max(maks_poziome, pref[i][j]);
            }
            dp1[i][j] = max({dp1[i-1][j], dp1[i][j-1], pref[i][j]});
        }
    }
    
    /// suf poziome i dp2
    for(int i=n;i>=1;i--){
        for(int j=n;j>=1;j--){
            if(t[i][j] == '.')
                suf[i][j] = suf[i][j+1]+1;
            dp2[i][j] = max({dp2[i+1][j], dp2[i][j+1], suf[i][j]});
        }
    }
    
    int maks_pion=0;
    /// pion
    for(int i=n;i>=1;i--){
        for(int j=1;j<=n;j++){
            if(t[i][j] == '.'){
                pion[i][j] = pion[i+1][j]+1;
                maks_pion = max(maks_pion, pion[i][j]);
            }
        }
    }
    
    if(m == 1){
		cout<<max(maks_pion, maks_poziome)<<"\n";
		return 0;
	}
	
	/// 2 poziome
	ans = maks_poziome/2;
	pair<int,int>maksi = {0,0};
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(suf[i][j] && !done[i][j]){
				if(suf[i][j] >= maksi.first){
					maksi.second = maksi.first;
					maksi.first = suf[i][j];
				}
				else if(suf[i][j] > maksi.second)
					maksi.second = suf[i][j];
				while(suf[i][j]){
					done[i][j] = true;
					j++;
				}
			}
		}
	}
	ans = max(ans, maksi.second);
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			done[i][j] = false;
	maksi = {0,0};
	
	/// 2 pionowe
	ans = max(ans, maks_pion/2);
	for(int j=1;j<=n;j++){
		for(int i=1;i<=n;i++){
			if(pion[i][j] && !done[i][j]){
				if(pion[i][j] >= maksi.first){
					maksi.second = maksi.first;
					maksi.first = pion[i][j];
				}
				else if(pion[i][j] > maksi.second)
					maksi.second = pion[i][j];
				while(pion[i][j]){
					done[i][j] = true;
					i++;
				}
			}
		}
	}
	ans = max(ans, maksi.second);
	
	/// pionowe i poziome
	int l = 1, r = n+1, mid;
	while(l != r){
		mid = (l + r) / 2;
		if(solve(mid)){
			ans = max(ans, mid);
			l = mid+1;
		}
		else
			r = mid;
	}
	cout<<ans<<"\n";
}
/*

5 2
.X...
.XXXX
XX...
.....
.X.X.

*/
