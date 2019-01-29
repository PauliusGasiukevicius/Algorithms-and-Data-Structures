#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll A[1001][1001];
ll B[1001][1001];
ll C[1001][1001];
ll ABr[1001];
ll Br[1001];
ll Cr[1001];

long long M = 1e9+7;

int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;
    vector<ll>r(n);
    for(int i=0; i<n; i++)
        r[i]=i+1;
    srand(time(nullptr)*666);

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        cin>>A[i][j];

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        cin>>B[i][j];

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        cin>>C[i][j];



       for(int k=0; k<10; k++) // good answer with high probability p = 1 - 1/2^k
       {
            random_shuffle(r.begin(),r.end());

                for(int i=0; i<n; i++)
                ABr[i]=Br[i]=Cr[i]=0,r[i] = (r[i] + rand()%M)%M;

                for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    Br[i]= (Br[i]%M + (B[i][j]*r[j])%M)%M;

                for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    ABr[i]= (ABr[i]%M + (A[i][j]*Br[j])%M)%M;

                for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    Cr[i] = (Cr[i]%M + (C[i][j]*r[j])%M)%M;

            for(int j=0; j<n; j++)
                if(Cr[j]%M != ABr[j]%M)return cout<<"NO\n",0;
       }

    cout<<"YES\n";
}
