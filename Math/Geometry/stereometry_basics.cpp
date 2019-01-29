#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ld dot(array<ld,3>A, array<ld,3>B)
{
    return A[0]*B[0] + A[1]*B[1] + A[2]*B[2];
}

array<ld,3> cross(array<ld,3>A, array<ld,3>B)
{
    return {A[1]*B[2] - B[1]*A[2], A[2]*B[0] - B[2]*A[0], A[0]*B[1] - B[0]*A[1]};
}

ld volume(array<ld,3>A, array<ld,3>B, array<ld,3>C)
{
    return dot(A,cross(B,C));
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        int x[4],y[4],z[4];
        for(int i=0; i<4; i++)
            cin>>x[i]>>y[i]>>z[i];

        array<ld,3>A[4];
        for(int i=1; i<4; i++)
        A[i]={x[i]-x[0],y[i]-y[0],z[i]-z[0]};

        ld ats = fabs(volume(A[1],A[2],A[3]))/6.0;
        cout<<setprecision(13)<<fixed<<ats<<"\n";
    }
}
