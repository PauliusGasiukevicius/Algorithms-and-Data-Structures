#include <bits/stdc++.h>
using namespace std;
#define ll long long

//Finds such C and D, that A*C + B*D = GCD(A,B) in O(log(max(A,B)))
//Can be used to find modulo inverses:
//Inverse of A modulo M is solution to A*C + M*D = GCD(A,M). (GCD must be 1!!!)
vector<ll> ExtendedEuclid(ll A, ll B)
{
    vector<vector<ll>>M = {{1,0,A},{0,1,B}};
    if(M[0][2] < M[1][2])swap(M[0],M[1]);

    while(M[1][2]!=0)
    {
        ll mul = M[0][2]/M[1][2];
        for(int j=0; j<3; j++)
            M[0][j]-=M[1][j]*mul;

        swap(M[0],M[1]);
    }
    return M[0];
}

int main()
{
    ios::sync_with_stdio(0);
    ll A,B;
    while(cin>>A>>B)
    {
        vector<ll>ats = ExtendedEuclid(A,B);
        cout<<ats[0]<<" "<<ats[1]<<" "<<ats[2]<<"\n";
    }
}
