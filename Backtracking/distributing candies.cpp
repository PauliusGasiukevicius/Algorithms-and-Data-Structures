#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int c[16],L[16],F[16],cp[16],a,n,lim,b;
int win[1<<9];
ld lose[1<<9];
ld ats,prob,p;

void solve(int cur, int k)
{
    if(cur==n)//all candies already distributed
    {
        for(int i=0; i<n; i++)
            cp[i]=min(100,F[i]+c[i]);

        prob = 0.0;

        for(int x=0; x<lim; x++)
        {
                p = 1.0; //probability that this event will happen

                for(int j=0; j<n; j++)
                    if(x&(1<<j))
                    p*=0.01*cp[j];
                    else
                    p*=(1-0.01*cp[j]);

                if(win[x])//if success
                    prob+=p;
                else
                    prob+=p*lose[x];
        }
        ats = prob > ats ? prob : ats;
        return;
    }
    solve(cur+1,k);//go to next person

    if(k>0 && F[cur] + c[cur] < 100)//give current person candies
    {
        c[cur]+=10;
        solve(cur,k-1);
        c[cur]-=10;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    int k;
    cin>>n>>k>>a;
    lim = 1<<n;

    for(int i=0; i<n; i++)
        cin>>L[i]>>F[i];

    for(int x=0; x<lim; x++)
    {
        int b = 0;
        int bits = 0;
        for(int j=0; j<n; j++)
            if(x&(1<<j))
                bits++;
            else
                b+=L[j];

        lose[x]=1.0*a/(a+b+0.0);
        win[x]=(bits*2 > n);
    }

    solve(0,k);
    cout<<setprecision(13)<<fixed<<ats<<"\n";
}
