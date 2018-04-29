#include <bits/stdc++.h>
using namespace std;
#define ld long double
#define ll long long
#define oo 666666666

ll DP[51][51];

ll C(int n, int k)
{
    if(k==0 || k==n)return 1;
    if(DP[n][k]>0)return DP[n][k];
    return DP[n][k] = C(n-1,k-1) + C(n-1,k);
}

int main()
{
    ios::sync_with_stdio(0);
    int t,cs=1;
    cin>>t;

    while(t--)
    {
        string s;
        cin>>s;
        string a,b,c;
        int k=0;
        int i=1;
        while(s[i]!='+')i++;
        a=string(s.begin()+1,s.begin()+i);
        int j=i;
        while(s[j]!=')')j++;
        b=string(s.begin()+i+1,s.begin()+j);
        c=string(s.begin()+j+2,s.end());
        stringstream ss(c);
        ss>>k;

        cout<<"Case "<<cs++<<": ";
        cout<<a;
        if(k!=1)cout<<"^"<<k;
        for(int i=1; i<k; i++)
        {
            cout<<"+"<<C(k,i)<<"*"<<a;
            if(k-i!=1)cout<<"^"<<k-i;
            cout<<"*"<<b;
            if(i!=1)cout<<"^"<<i;
        }

        cout<<"+"<<b;
        if(k!=1)cout<<"^"<<k;
        cout<<"\n";
    }
}
