    #include <bits/stdc++.h>
    using namespace std;
    #define oo 666666666
    #define ll long long
    #define ld long double
     
    int A[25][25];
    ll DP[1<<21];
    ll mod = 1e9+7;
    int n;
     
    ll solve(ll mask)
    {
        if(mask == (1<<n)-1)return 1;
        bitset<32>M(mask);
        int man = M.count();
        if(man >= n)return 0;
        if(DP[mask]!=-1)return DP[mask];
     
        DP[mask]=0;
     
        for(int i=0; i<n; i++)
            if(!M[i] && A[man][i])
                {
                    DP[mask]+=solve(mask|(1<<i));
                    DP[mask]%=mod;
                }
     
        return DP[mask];
    }
     
    int main()
    {
        ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
        memset(DP, -1, sizeof DP);
        cin>>n;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            cin>>A[i][j];
     
        cout<<solve(0);
    }
