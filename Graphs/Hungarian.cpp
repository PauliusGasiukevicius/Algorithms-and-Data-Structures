#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define oo 1000000000

//a - matrix [1...n][1...m], [1...n] - people to match, [1...m] - jobs, a[i][j] - costs
// for max matching just multiply all costs by -1
vector<int> Hungarian(vector<vector<int>>&a)
{
    int n = a.size()-1;
    int m = a[0].size()-1;
    vector<int> u (n+1), v (m+1), p (m+1), way (m+1);

    for (int i=1; i<=n; ++i)
    {
        p[0] = i;
        int j0 = 0;
        vector<int> minv (m+1, oo);
        vector<char> used (m+1, false);
        do
        {
            used[j0] = true;
            int i0 = p[j0],  delta = oo,  j1;
            for (int j=1; j<=m; ++j)
                if (!used[j])
                {
                    int cur = a[i0][j]-u[i0]-v[j];
                    if (cur < minv[j])
                        minv[j] = cur,  way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],  j1 = j;
                }
            for (int j=0; j<=m; ++j)
                if (used[j])
                    u[p[j]] += delta,  v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        }
        while (p[j0] != 0);
        do
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        }
        while (j0);
    }

    vector<int> ans (n+1);
    for (int j=1; j<=m; ++j)
	ans[p[j]] = j;

    return ans;
}

signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n;
    vector<vector<int>>M(n+1, vector<int>(n+1));

    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
    cin>>M[i][j];

    auto match = Hungarian(M);
    int cost = 0;
    for(int i=1; i<=n; i++)
        cost+=M[i][match[i]];

    cout<<cost<<"\n";
    for(int i=1; i<=n; i++)
        cout<<i<<" "<<match[i]<<"\n";
}
