#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
    Convex Hull Trick LiChao
    !important maxn should be set to maximum possible x value
    its a kind of segment tree that supports 2 operations:
    1) add line y=a*x+b to the tree by calling add_line({a,b});
    2) get minimum value for some y given x
    (untested)*3) if we want maximum value we just add line as {-a,-b}
*/
typedef ll ftype;
typedef complex<ftype> point;

ftype dot(point a, point b) {
    return (conj(a) * b).real();
}

ftype f(point a,  ftype x) {
    return dot(a, {x, 1});
}

const int maxn = 1e6+5;

point line[4 * maxn];

void add_line(point nw, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    bool lef = f(nw, l) < f(line[v], l);
    bool mid = f(nw, m) < f(line[v], m);
    if(mid) {
        swap(line[v], nw);
    }
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * v, l, m);
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }
}

ll Get(ll x, int v = 1, int l = 0, int r = maxn) {
    ll m = (l + r) / 2;
    if(r - l == 1) return f(line[v], x);
    if(x < m)return min(f(line[v], x), Get(x, 2 * v, l, m));
    return min(f(line[v], x), Get(x, 2 * v + 1, m, r));
}

ll H[maxn];
ll DP[maxn];

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll n,C;
    cin>>n>>C;
    for(int i=1; i<=n; i++)
        cin>>H[i];

    //(H[i]-H[j])^2 + C = H[i]^2 -2*H[i]*H[j] + H[j]^2 + C
    //DP[i] = min(H[i]^2 -2*H[i]*H[j] + H[j]^2 + DP[j]) for all j
    // we notice that f(H[j]) = (-2*H[i])*H[j] + (H[j]^2+DP[i])
    // we notice that f(x) = (-2*H[i])*x + (H[j]^2+DP[i])

    add_line({-2*H[1],H[1]*H[1]});

    for(int i=2; i<=n; i++)
    {
        DP[i]=H[i]*H[i] + Get(H[i]) + C;
        add_line({-2*H[i],H[i]*H[i]+DP[i]});
    }
    cout<<DP[n];
}
