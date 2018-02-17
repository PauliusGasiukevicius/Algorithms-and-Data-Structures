// solving CodeForces 939E - Maximize! 
#include <bits/stdc++.h>
using namespace std;

long long A[500005];
long long P[500005];

int main()
{
    ios::sync_with_stdio(0);
    int q,c=1,t,x;
    cin>>q;

    while(q--)
    {
        cin>>t;
        if(t==1)
        cin>>x,A[c]=x,P[c]+=x,c++,P[c]+=P[c-1];
        else
        {

        int l = 0, r=c-2; //prefix to calc mean

        while( r-l > 5)
        {

            int ML = l + (r-l)/3;
            int MR = r - (r-l)/3;

            double c1 = A[c-1] - ((double)P[ML]+A[c-1])/(ML+1);
            double c2 = A[c-1] - ((double)P[MR]+A[c-1])/(MR+1);

            if( c1 < c2)
            l = ML;
            else
            r = MR;
        }

        double ats = 0.0;

        for(int R = l; R<=r; R++)
        {
        ats=max(ats,A[c-1] - ((double)P[R]+A[c-1])/(R+1));
        //cout<<P[R]<<" "<<R<<"\n";
        }

        cout<<fixed<<setprecision(13)<<ats<<"\n";

        }
    }
}
