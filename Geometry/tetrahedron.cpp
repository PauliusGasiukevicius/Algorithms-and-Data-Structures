#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

//If U, V, W, u, v, w are lengths of edges of the tetrahedron
//(first three form a triangle; u opposite to U and so on), then
ld tetrahedronArea(ld U, ld V, ld W, ld u, ld v, ld w)
{
    ld z = (W-u+v)*(u-v+W);
    ld Z = (v-W+u)*(W+u+v);
    ld y = (V-w+u)*(w-u+V);
    ld Y = (u-V+w)*(V+w+u);
    ld x = (U-v+w)*(v-w+U);
    ld X = (w-U+v)*(U+w+v);
    ld a = sqrt(x*Y*Z);
    ld b = sqrt(y*Z*X);
    ld c = sqrt(z*X*Y);
    ld d = sqrt(x*y*z);

    return sqrt((-a+b+c+d)*(a-b+c+d)*(a+b-c+d)*(a+b+c-d)) / 192 / u / v / w;
}

int main()
{
    ios::sync_with_stdio(0);
    int t;
    ld u,v,w,U,V,W;
    cin>>t;

    while(t--)
    {
        cin>>u>>w>>v>>V>>W>>U;
        cout<<setprecision(4)<<fixed<<tetrahedronArea(U,V,W,u,v,w) <<"\n";
    }
}
