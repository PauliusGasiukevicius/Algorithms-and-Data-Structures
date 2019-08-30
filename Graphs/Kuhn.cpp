#include <bits/stdc++.h>
using namespace std;
#define oo 666666666
#define ll long long
#define ld long double

int try_kuhn (int c, vector<vector<int>>&G, vector<int>&A, vector<int>&B, vector<int>&used)
{
	if (used[c])  return 0;
	used[c] = 1;

	for (auto&u : G[c])
		if (B[u] == -1 || try_kuhn(B[u],G,A,B,used))
		{
            B[u] = c;
            A[c]=u;
			return 1;
		}
	return 0;
}

int MaximumMatching(vector<vector<int>>&G, int n, int k, vector<int>&A, vector<int>&B)
{
    //assumes left part is indexed 1..n, right 1..k
    //A[i] -> element on left is matched with : ..., (-1 - no match)
    //return size of MaximumMatching
    int ats = 0;

	for (int i=1; i<=n; ++i)//greedily match randomly
		for(auto&u : G[i])
			if (B[u] == -1)
            {
                B[u]=i;
                A[i]=u;
				ats++;
				break;
			}

    vector<int>used(n+1);

	for (int i=1; i<=n; ++i)
    if(A[i]==-1)
    {
		fill(used.begin(), used.end(), 0);
		ats += try_kuhn (i, G, A, B, used);
	}

    return ats;
}

pair<vector<int>,vector<int>> MinimumVertexCover(vector<vector<int>>&G, int n, int k, vector<int>&A, vector<int>&B)
{
    int ats = MaximumMatching(G,n,k,A,B);
    queue<int>q;
    vector<int>visA(n+1),visB(k+1);
    for(int i=1; i<=n; i++)
        if(A[i]==-1)q.push(i),visA[i]=1;

    while(!q.empty())
    {
        int c = q.front();
        q.pop();

        for(auto&u : G[c])
        {
            visB[u]=1;
            if(!visA[B[u]])
                visA[B[u]]=1,q.push(B[u]);
        }
    }
    vector<int>pA,pB;
    for(int i=1; i<=n; i++)
        if(!visA[i])pA.push_back(i);
    for(int i=1; i<=k; i++)
        if(visB[i])pB.push_back(i);

    return {pA, pB};
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<vector<int>>G(n+1);
    vector<int>A(n+1,-1),B(m+1,-1);
    for(int i=1; i<=n; i++)
    {
        int k,x;
        cin>>k;
        while(k-- && cin>>x)
            G[i].push_back(x);
    }
    auto ats = MinimumVertexCover(G,n,m,A,B);
    cout<<ats.first.size() + ats.second.size()<<"\n";
    cout<<ats.first.size();
    for(int&x:ats.first)cout<<" "<<x;
    cout<<"\n";
    cout<<ats.second.size();
    for(int&x:ats.second)cout<<" "<<x;
    cout<<"\n";
}
