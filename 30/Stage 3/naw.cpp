/// Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 100+7;

mt19937 e = (mt19937)686968691;
int rand(int a, int b){
    return uniform_int_distribution<int>{a,b}(e);
}

vector<int>v[maxN];
int par[maxN],losowane[maxN];
void dfs(int x){
    for(int a:v[x]){
        if(a != par[x]){
            par[a] = x;
            dfs(a);
        }
    }
}

string zamiana(int x){
    string ans;
    int c;
    while(x){
        c = losowane[x];
        for(int i=0;i<5;i++){
            if(c & 1)
                ans.push_back('1');
            else
                ans.push_back('0');
            c /= 2;
        }
        x = par[x];
    }
    while(ans.size() < 512)
        ans.push_back('0');
    return ans;
}

void enkoder(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    for(int i=1;i<=n;i++) /// tutaj losuje kolejnosc
        losowane[i] = i;
    shuffle(losowane+1, losowane+1+n, e);

    dfs(1);
    for(int i=1;i<=n;i++)
        cout<<zamiana(i)<<"\n";
}

bool takie_same(int l, string a, int r, string b){
    int c1 = 0, c2 = 0, pot = 1;
    for(int i=l*5;i<(l+1)*5;i++){
        if(a[i] == '1')
            c1 += pot;
        pot *= 2;
    }
    pot = 1;
    for(int i=r*5;i<(r+1)*5;i++){
        if(b[i] == '1')
            c2 += pot;
        pot *= 2;
    }
    return (c1 == c2);
}

void dekoder(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m;
    cin>>m;
    while(m--){
        string a,b;
        cin>>a>>b;
        int lewo = 0, prawo, c1, c2, pot, pot2;
        for(int i=0;i<100;i++){
            c1 = 0, pot = 1, prawo = 0;
            bool jest = false;
            for(int j=i*5;j<(i+1)*5;j++){ /// jaka jest teraz liczba po lewej
                if(a[j] == '1')
                    c1 += pot;
                pot *= 2;
            }
            //cout<<c1<<" to jest c1\n";
            for(int j=0;j<100;j++){
                c2 = 0, pot2 = 1;
                for(int k=j*5;k<(j+1)*5;k++){
                    if(b[k] == '1')
                        c2 += pot2;
                    pot2 *= 2;
                }
                //cout<<c2<<" to jest c2\n";
                if(c1 == c2){
                    jest = true;
                    break;
                }
                prawo++;
            }
            if(jest){
                if(takie_same(lewo+1,a,prawo+1,b)){ /// jezeli nawet te nastepne sa takie same
                    break;
                }
                jest = false;
            }
            lewo++;
        }
        cout<<lewo + prawo<<"\n";
    }
}