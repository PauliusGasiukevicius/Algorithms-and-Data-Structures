#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

int dp[2002][2002]; //min cost of getting [i][] groups such that last group ends in element [][j]
int cnt_inv[2002][2002];
int BIT[2002];
int A[2002];
int n,k;

void update(int c, int x)
{
    for(c;c<=n;c+=(c&-c))
        BIT[c]+=x;
}

int query(int c)
{
    int sum = 0;
    for(c; c>0; c-=(c&-c))
        sum+=BIT[c];
    return sum;
}

int queryLR(int L, int R)
{
    return query(R) - query(L-1);
}

void inversions()
{
    vector<int>unq,ID(1);
    for(int i=1; i<=n; i++)unq.push_back(A[i]);

    sort(unq.begin(),unq.end());
    unq.erase(unique(unq.begin(),unq.end()),unq.end());

    for(int i=1; i<=n; i++)
        ID.push_back(lower_bound(unq.begin(),unq.end(),A[i]) - unq.begin() + 1);

    for(int i=1; i<=n; i++)//start of interval
    {
        for(int j=i; j<=n; j++)//add elements one by one
        {
            int id = ID[j];
            cnt_inv[i][j] = cnt_inv[i][j-1] + queryLR(id+1,n);
            update(id,1);
        }

        for(int j=i; j<=n; j++)//clear BIT
        {
            int id = ID[j];
            update(id,-1);
        }
    }
}

long long C(int i, int j) //cost function for D&C optimization
{return cnt_inv[i+1][j];}

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int i, int l, int r, int optl, int optr)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    pair<long long, int> best = {oo, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {dp[i-1][k] + C(k, mid), k});
    }

    dp[i][mid] = best.first;
    int opt = best.second;

    compute(i, l, mid - 1, optl, opt);
    compute(i, mid + 1, r, opt, optr);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
     cin>>n>>k;

    for(int i=1; i<=n; i++)
        cin>>A[i];

    for(int i=0; i<=k; i++)
        for(int j=0; j<=n; j++)
            dp[i][j]=oo;

    dp[0][0]=0;

    inversions(); // brute all n^2 intervals to pre-calculate all inversions with BIT

    for(int i=1; i<=k; i++)//D&C optimization so this is also n^2logn
    compute(i,i-1,n,i-1,n);

    cout<<dp[k][n]<<"\n";
}
