/// zadanie: Montazysta
/// autor: Michal Szydlo
/// rozwiazanie wzorowane na: https://cp-algorithms.com/schedules/schedule-with-completion-duration.html

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e5+7;

int n;
vector<int>ans;
set<pair<int,int>>s;

struct Film
{
    int czas, termin, id;
    void wczytaj()
    {
        cin>>czas>>termin;
    }
} dodaj, Filmiki[maxN];
vector<Film>v;

bool comp(Film a, Film b)
{
    if(a.termin != b.termin)
        return (a.termin < b.termin);
    return (a.czas < b.czas);
}

bool comp2(int a, int b)
{
    return (Filmiki[a].termin < Filmiki[b].termin);
}

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>n;
for(int i=1;i<=n;i++)
{
    dodaj.wczytaj();
    dodaj.id = i;
    Filmiki[i] = dodaj;
    v.push_back(dodaj);
}
sort(v.begin(), v.end(), comp);

for (int i = v.size()-1; i>=0; i--)
{
    int roznica_terminow = v[i].termin - (i ? v[i-1].termin : 0);
    s.insert(make_pair(v[i].czas, v[i].id));
    while (!s.empty() && roznica_terminow != 0)
    {
        auto it = s.begin();
        if (it->first <= roznica_terminow)
        {
            roznica_terminow -= it->first;
            ans.push_back(it->second);
        }
        else
        {
            s.insert(make_pair(it->first - roznica_terminow, it->second));
            roznica_terminow = 0;
        }
        s.erase(it);
    }
}
sort(ans.begin(), ans.end(), comp2);
cout<<ans.size()<<endl;
int zaczecie_montowania = 1;
for(int x:ans)
{
    cout<<x<<' '<<zaczecie_montowania<<endl;
    zaczecie_montowania += Filmiki[x].czas;
}
}
