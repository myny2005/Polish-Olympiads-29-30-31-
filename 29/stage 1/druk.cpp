/// zadanie: Druk 
/// autor: Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e3+7;

int n,m,odw[maxN][maxN],num,litery[30],pomoc[30],ile_roznych; /// num - do odw[]
char t[maxN][maxN];
string poziomo="",pionowo="";
vector<int>ans;

void uzupelnij_do_dolu(string szablon, int x, int y)
{
	if(y + szablon.size() - 2 <= n)
	{
		bool mozna = true;
		int c = 1;
		for(int i=y;i<=y+szablon.size()-2;i++)
		{
			if(odw[i][x] == num || t[i][x] != szablon[c++])
			{
				mozna = false;
				break;
			}
        }
		if(mozna)
			for(int i=y;i<=y+szablon.size()-2;i++)
				odw[i][x] = num;
	}
}

void uzupelnij_do_gory(string szablon, int x, int y)
{
	if(y - szablon.size() + 2 >= 1)
	{
		bool mozna = true;
		int c = szablon.size()-1;
		for(int i=y;i>=y-szablon.size()+2;i--)
			if(odw[i][x] == num || t[i][x] != szablon[c--])
			{
				mozna = false;
				break;
			}
		if(mozna)
			for(int i=y;i>=y-szablon.size()+2;i--)
				odw[i][x] = num;
	}
}

void uzupelnij_do_prawej(string szablon, int x, int y)
{
	if(x + szablon.size() - 2 <= m)
	{
		bool mozna = true;
		int c = 1;
		for(int i=x;i<=x+szablon.size()-2;i++)
			if(odw[y][i] == num || t[y][i] != szablon[c++])
			{
				mozna = false;
				break;
			}
		if(mozna)
			for(int i=x;i<=x+szablon.size()-2;i++)
				odw[y][i] = num;
	}
}

void uzupelnij_do_lewej(string szablon, int x, int y)
{
	if(x - szablon.size() + 2 >= 1)
	{
		bool mozna = true;
		int c = szablon.size()-1;
		for(int i=x;i>=x-szablon.size()+2;i--)
			if(odw[y][i] == num || t[y][i] != szablon[c--])
			{
				mozna = false;
				break;
			}
		if(mozna)
			for(int i=x;i>=x-szablon.size()+2;i--)
				odw[y][i] = num;
	}
}

bool solve(string szablon)
{
	szablon = '!' + szablon;
	int xx1 = 1, yy1 = 1, xx2 = m, yy2 = n;
	while(xx1 <= xx2 && yy1 <= yy2)
	{
		for(int i=xx1;i<=xx2;i++) /// poziomo
		{
			if(odw[yy1][i] != num) /// patrze gore
				uzupelnij_do_prawej(szablon, i, yy1);
			if(odw[yy2][i] != num) /// patrze dol
				uzupelnij_do_prawej(szablon, i, yy2);

            if(odw[yy1][i] != num) /// patrze gore
				uzupelnij_do_dolu(szablon, i, yy1);
			if(odw[yy2][i] != num) /// patrze dol
				uzupelnij_do_gory(szablon, i, yy2);

			if(odw[yy1][i] != num) /// patrze gore
				return false;
			if(odw[yy2][i] != num) /// patrze dol
				return false;

		}
		for(int i=yy1;i<=yy2;i++) /// pionowo
		{
			if(odw[i][xx1] != num) /// lewo
				uzupelnij_do_dolu(szablon, xx1, i);
			if(odw[i][xx2] != num) /// prawo
				uzupelnij_do_dolu(szablon, xx2, i);

            if(odw[i][xx1] != num) /// lewo
				uzupelnij_do_prawej(szablon, xx1, i);
			if(odw[i][xx2] != num) /// prawo
				uzupelnij_do_lewej(szablon, xx2, i);

			if(odw[i][xx1] != num) /// lewo
				return false;
			if(odw[i][xx2] != num) /// prawo
				return false;

		}
		xx1++,yy1++,xx2--,yy2--;
	}
	return true;
}

bool czy_ma_sens(string szablon, int dl)
{
	if(szablon.size() != dl)
		return false;
	int ile_szablonow = (n*m)/dl;
	for(int i=0;i<26;i++)
		pomoc[i] = 0;
	for(int i=0;i<dl;i++)
		pomoc[szablon[i] - 'a']++;
	for(int i=0;i<26;i++)
	{
		if(litery[i])
		{
			if(!pomoc[i])
				return false;
			if(litery[i] % pomoc[i] != 0)
				return false;
			if(litery[i] / pomoc[i] != ile_szablonow)
				return false;
		}
	}
	return true;

}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>n>>m;
for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		cin>>t[i][j];
		litery[t[i][j] - 'a']++;
		if(litery[t[i][j] - 'a'] == 1)
			ile_roznych++;
	}
if(ile_roznych == 1) /// tylko 1 rodzaj liter
{
	for(int i=1;i<=max(n,m);i++)
		if((n * m) % i == 0)
            if(n % i == 0 || m % i == 0)
                ans.push_back(i);
	cout<<ans.size()<<endl;
	for(int x:ans)
		cout<<x<<' ';
	return 0;
}
for(int i=1;i<=max(n,m);i++)
{
	if(i <= m)
		poziomo += t[1][i];
	if(i <= n)
		pionowo += t[i][1];
	if((n * m) % i == 0) /// jest kandydatem
	{
		num++;
		if(czy_ma_sens(poziomo, i))
		{
			for(int j=1;j<=i;j++)
				odw[1][j] = num;
			if(solve(poziomo))
			{
				ans.push_back(i);
				continue;
			}
		}
		num++;
		if(czy_ma_sens(pionowo,i))
		{
			for(int j=1;j<=i;j++)
				odw[j][1] = num;
			if(solve(pionowo))
				ans.push_back(i);
		}
	}
}
cout<<ans.size()<<endl;
for(int x:ans)
	cout<<x<<' ';
}
