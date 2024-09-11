/// autor: Michal Szydlo
/// zadanie: Plytkie nawiasowanie

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e6+7;

int n,H,otwierajace,ans;
string s;

bool moge_dodac(){
    return (otwierajace+1 <= H);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>H;
    cin>>s;
    s = '!' + s;
    for(int i=1;i<=n;i++){
        if(s[i] == '('){
            if(moge_dodac())
                otwierajace++;
            else{
                otwierajace--;
                ans++;
            }
        }
        else{
            if(otwierajace != 0)
                otwierajace--;
            else{
                otwierajace++;
                ans++;
            }
        }
    }
    cout<<ans<<"\n";
}   
/*

8 2
(()(()))

*/