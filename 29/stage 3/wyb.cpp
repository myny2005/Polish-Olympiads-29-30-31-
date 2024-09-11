#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e6+7, Base = 1024*1024;

int n,m,dodaj[2*maxN],koniec;
string s;
int suma[2*Base+7], tree[2*Base+7], lazy[2*Base+7];
pair<int,int>seg[2*Base+7];

void insert(int v, int a, int b, int p, int k, int val)
{
	if(a > k || b < p)
		return;
	if(a >= p && b <= k){
		tree[v] = val;
		lazy[v] = val;
		suma[v] = (b-a+1) * dodaj[val];
		//cout<<v<<' '<<val<<"	to jest val\n";
	}
	else{
		int l = 2*v, r = 2*v+1, mid = (a+b)/2;
		//tree[l] = max(tree[l], lazy[v]);
		//tree[r] = max(tree[r], lazy[v]);
		//lazy[l] = max(lazy[l], lazy[v]);
		//lazy[r] = max(lazy[r], lazy[v]); /// to nie musi byc chyba max tylko poprosut =
		//lazy[v] = 0;
		insert(l,a,mid,p,k,val);
		insert(r,mid+1,b,p,k,val);
		//tree[v] = max(tree[l], tree[r]);
		suma[v] = suma[l] + suma[r];
	}
}

int Find(int v, int p, char znak)
{
	if(v >= Base)
		return v-Base;
	int l = 2*v, r = 2*v+1;
	
	if(tree[v]){
		tree[l] = tree[v];
		tree[r] = tree[v];
		suma[l] = suma[v]/2;
		suma[r] = suma[v]/2;
	}
	tree[v] = 0;
	int ile = suma[l];
	//cout<<v<<' '<<p<<' '<<suma[l]<<' '<<suma[r]<<' '<<(seg[l].second - max(seg[l].first, 1) + 1) - ile<<' '<<znak<<' '<<ile<<"  essa\n";

	if(znak == 'a')
		ile = (seg[l].second - max(seg[l].first, 1) + 1) - ile;
	//cout<<ile<<"\n";
	if(p <= ile)
		return Find(l,p,znak);
	return Find(r,p-ile,znak);
}

void zepchij(int v)
{
	if(v >= Base)
		return;
	int l = 2*v, r = 2*v+1;
	tree[l] = max(tree[l], tree[v]);
	tree[r] = max(tree[r], tree[v]);
	zepchij(l);
	zepchij(r);
}

void wypisz()
{
	cout<<"to jest suma    ";
	for(int i=1;i<2*Base;i++)
		cout<<suma[i]<<' ';
	cout<<"\n";
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);

cin>>n>>m;
cin>>s;
s = '!' + s;


if((long long)n * m <= (int)1e7){
	int p,ile;
	char a,b;
	while(m--){
		cin>>p>>a>>b;
		if(!p)
			continue;
		ile = 0;
		for(int i=1;i<=n;i++){
			if(s[i] == a){
				ile++;
				s[i] = b;
				if(ile == p)
					break;
			}
		}
	}
	for(int i=1;i<=n;i++)
		cout<<s[i];
	cout<<"\n";
	return 0;
}


for(int i=1;i<=n;i++){
	if(s[i] == 'b')
		dodaj[i] = 1;
	tree[i+Base] = i;
	suma[i+Base] = dodaj[i];
	seg[i+Base] = {i,i};
}
for(int i=n+1;i<Base;i++)
	seg[i+Base] = {i,i};
for(int i=Base-1;i>=1;i--){
	//tree[i] = max(tree[2*i], tree[2*i+1]);
	suma[i] = suma[2*i] + suma[2*i+1];
	seg[i].first = seg[i*2].first;
	seg[i].second = seg[i*2+1].second;
}
/*
cout<<" to sa seg\n";
for(int i=1;i<2*Base;i++)
	cout<<i<<"       "<<seg[i].first<<' '<<seg[i].second<<"\n";
*/

//wypisz();

int p;
char a,b;
int j = n+1;
while(m--){
	cin>>p>>a>>b;
	if(!p)
		continue;
	koniec = Find(1,p,a);
	//cout<<koniec<<" to jest koniec\n";
	dodaj[j] = (b == 'b');
	insert(1,0,Base-1,1,koniec,j);
	//wypisz();
	j++;
}
zepchij(1);
/*
cout<<"to jest drzewo na koncu\n";
for(int i=1;i<2*Base;i++)
	cout<<tree[i]<<' ';
	cout<<"\n";
*/
for(int i=1;i<=n;i++){
	int id = tree[i+Base];
	cout<<((!dodaj[id]) ? 'a' : 'b');
}
cout<<"\n";
}
/*

10 3
acabbabbac
3 b c
4 a b
3 c a

7 2
abbaaab
1 a b
2 b a

*/