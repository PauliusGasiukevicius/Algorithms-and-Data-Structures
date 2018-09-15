#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t,n,k;
    cin>>t;

    while(t--)
    {
        cin>>n>>k;
        unordered_map<int,int>DP[101];
        int A[101];

        for(int i=0; i<n; i++)
            cin>>A[i];

        DP[n][k]=1;

        for(int i=n-1; i>=0; i--)
            for(int j=-10000; j<=10000; j++)
        {
            if(DP[i+1].count(j+A[i]))DP[i][j]=1;
            if(DP[i+1].count(j-A[i]))DP[i][j]=1;
        }

        string s = "+-";
        int x = A[0]-A[1];
        for(int i=2; i<n; i++)
            if(DP[i+1].count(x+A[i]))s+="+",x+=A[i];
            else s+="-",x-=A[i];

        for(int i=n-1; i>=1; i--)
            if(s[i]=='+')
        {
            int j=i;
            while(j>=0 && s[j]=='+')j--;
            j++;
            int sz = i-j+1;
            //cout<<s<<" "<<i<<" "<<j<<endl;
            s.erase(s.begin()+j,s.begin()+j+sz);
            i=s.size();
            while(sz--)
                cout<<j<<"\n";
        }

        for(int i=1; i<s.size(); i++)
            cout<<1<<"\n";

        cout<<"\n";
    }
}
