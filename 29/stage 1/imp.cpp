/// zadanie: Impreza krasnali 
/// autor: Michal Szydlo

#include <bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e5+7, Mod = 1e9+7;

int n,t[maxN], ile_wystapien[maxN], niewidoczne, pewniaki[maxN]; /// pewniaki -> na pewno tam stoja
bool usuniete[maxN]; /// te ktore juz gdzies sa
long long ans=1;

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

cin>>n;
for(int i=1;i<=n;i++)
    cin>>t[i];
for(int i=1;i<=n;i++) /// sprawdzanie czy dane nie sa sprzeczne
{
    ile_wystapien[t[i]]++;
    if(t[i] == t[i-1] || ile_wystapien[t[i]] > 2)
    {
        cout<<0;
        return 0;
    }
    if(ile_wystapien[t[i]] == 2)
    {
        if(t[i] != t[i-2])
        {
            cout<<0;
            return 0;
        }
        usuniete[i] = true;
        usuniete[i-2] = true;
        pewniaki[i-1] = t[i];
    }
}
for(int i=1;i<=n;i++) /// ile jest niewidocznych
    if(!ile_wystapien[i])
        niewidoczne++;
for(int i=2;i<=niewidoczne;i++) /// silnia z niewidocznych
    ans = (ans * i) % Mod;
pewniaki[0] = 1e9, pewniaki[n+1] = 1e9+2;
for(int i=1;i<n;i+=2) /// uzupelnianie pewniakami od poczatku
    if(pewniaki[i-1])
    {
        usuniete[i] = true;
        if(pewniaki[i-1] != t[i])
            pewniaki[i+1] = t[i];
    }
for(int i=n;i>1;i-=2) /// uzupelnianie pewniakami od tylu
    if(pewniaki[i+1])
    {
        usuniete[i] = true;
        if(pewniaki[i+1] != t[i])
        {
            if(pewniaki[i-1])
            {
                if(t[i] != t[i-2])
                {
                    cout<<0;
                    return 0;
                }
                usuniete[i] = true;
            }
            pewniaki[i-1] = t[i];
        }
    }

int c = 0; /// aktualne
for(int i=1;i<=n;i+=2)
{
    if(pewniaki[i] == 0)
        c++;
    else
    {
        if(c > 1)
            ans = (ans * c) % Mod;
        c = 0;
    }
}
if(c > 1)
    ans = (ans * c) % Mod;
c = 0;
for(int i=2;i<=n;i+=2)
{
    if(pewniaki[i] == 0)
        c++;
    else
    {
        if(c > 1)
            ans = (ans * c) % Mod;
        c = 0;
    }
}
if(c > 1)
    ans = (ans * c) % Mod;
cout<<ans % Mod;
}
