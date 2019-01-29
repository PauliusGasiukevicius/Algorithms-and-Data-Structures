#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int Find(vector<int>&P, int u)
{
    return P[u] < 0 ? u : P[u] = Find(P,P[u]);
}

void Union(vector<int>&P, int u, int v)
{
    u = Find(P,u);
    v = Find(P,v);
    if(u==v)return;
    P[u]=v;
}

ll cross(ll x1, ll y1, ll x2, ll y2)
{
    return x1*y2 - y1*x2;
}

ll direction(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3)
{
	return (x3-x1)*(y2-y1)-(x2-x1)*(y3-y1);
}

bool inside(ll L, ll x, ll R)
{
    return x>=L && x<=R;
}

bool onsegment(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3)
{
	return (inside(min(x1,x2),x3,max(x1,x2)) && inside(min(y1,y2),y3,max(y1,y2)));
}

//checks if 2 line segments {(x1,y1),(x2,y2)} and {(x3,y3),(x4,y4)} intersect
bool intersect(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4)
{
    int d1, d2, d3, d4;
	d1 = direction(x3, y3, x4, y4, x1, y1);
	d2 = direction(x3, y3, x4, y4, x2, y2);
	d3 = direction(x1, y1, x2, y2, x3, y3);
	d4 = direction(x1,y1, x2, y2, x4, y4);

	if(((d1>0 && d2<0)||(d1<0 && d2>0)) && ((d3>0 && d4<0)||(d3<0 && d4>0))) return true;
	if(!d1 && onsegment(x3, y3, x4, y4, x1, y1)) return true;
	if(!d2 && onsegment(x3, y3, x4, y4, x2, y2)) return true;
	if(!d3 && onsegment(x1, y1, x2, y2, x3, y3)) return true;
	if(!d4 && onsegment(x1, y1, x2, y2, x4, y4)) return true;
	return false;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t,n,m;
    cin>>t;

    while(t--)
    {
        cin>>n>>m;
        vector<array<ll,4>>A(n);
        vector<int>P(n,-1);
        for(auto&v:A)
            for(auto&x:v)cin>>x;

        for(int i=0; i<n; i++)
            for(int j=i+1; j<n; j++)
                if(intersect(A[i][0],A[i][1],A[i][2],A[i][3],A[j][0],A[j][1],A[j][2],A[j][3]))
                    Union(P,i,j);

        while(m--)
        {
            int u,v;
            cin>>u>>v;
            u--,v--;
            cout<<(Find(P,u)==Find(P,v) ? "YES\n" : "NO\n");
        }
    }
}

