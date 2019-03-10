#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int notPrime[100005];
int Grundy[100005];
int visited[100005];

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    notPrime[0]=notPrime[1]=1;
    for(int i=2; i<100005; i++)
        if(!notPrime[i])
        for(int j=2*i; j<100005; j+=i)
        notPrime[j]=1;

    for(int i=4; i<=8008; i++)
        if(notPrime[i])
    {
        for(int j=0; j<=i; j++)
            visited[j]=0;

        for(int a=2; a<i; a++)
            if(i-a!=1 && i-a>=a)
            visited[Grundy[a]^Grundy[a+1]^Grundy[i-a]]++;

        while(visited[Grundy[i]])
            Grundy[i]++;
    }

    int t,n,x;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int ats = 0;
        while(n--)
        {
            cin>>x;
            ats^=Grundy[x];
        }
        cout<<(ats ? ":)\n" : ":(\n");
    }
}
