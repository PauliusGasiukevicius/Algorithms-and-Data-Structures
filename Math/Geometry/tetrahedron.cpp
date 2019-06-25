#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

//If U, V, W, u, v, w are lengths of edges of the tetrahedron
//(first three form a triangle; u opposite to U and so on), then
ld tetrahedronVolume(ld U, ld V, ld W, ld u, ld v, ld w)
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

ld heron(ld a, ld b, ld c)
{
    ld s = (a+b+c)/2.0;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

ld radiusOfSphereInTetrahedron(ld WX, ld WY, ld WZ, ld XY, ld XZ, ld YZ)
{
    ld volume = tetrahedronVolume(XY,YZ,XZ,WZ,WX,WY);
    ld surfaceArea = heron(WX,WY,XY) + heron(WY,WZ,YZ) + heron(WX,WZ,XZ) + heron(XY,XZ,YZ);
    ld R = 3*volume/surfaceArea;
    return R;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    ld WX, WY, WZ, XY, XZ, YZ;
    cin>>t;

    while(t--)
    {
        cin>>WX>>WY>>WZ>>XY>>XZ>>YZ;
        cout<<setprecision(4)<<fixed<<radiusOfSphereInTetrahedron(WX,WY,WZ,XY,XZ,YZ)<<"\n";
    }
}
